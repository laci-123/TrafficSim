use std::thread;
use std::time::Duration;
use std::sync::mpsc;
use std::time::Instant;
use eframe;
use eframe::egui;
use hecs;
use crate::command::*;
use crate::math;


const TARGET_FPS: u32 = 30;
const FRAME_DURATION: f32 = 1.0 / TARGET_FPS as f32;
const MAX_UI_LAG_DURATION: f32 = 0.1;

pub struct Game {
    engine_thread: Option<thread::JoinHandle<()>>,
    input_sender: mpsc::Sender<InputCommand>,
    output_receicer: mpsc::Receiver<OutputCommand>,
    shapes: Vec<egui::Shape>,
}

impl Default for Game {
    fn default() -> Self {
        let (input_sender, input_receiver) = mpsc::channel();
        let (output_sender, output_receicer) = mpsc::channel();
        
        Self {
            input_sender,
            output_receicer,
            shapes: Vec::new(),
            engine_thread: Some(thread::spawn(move || {
                let mut world = hecs::World::new();                
                let mut keep_running = true;
                let mut last_frame_started;
                let mut dt = Duration::ZERO;

                while keep_running {                    
                    last_frame_started = Instant::now();

                    let sleep_time = Duration::from_secs_f32(FRAME_DURATION).saturating_sub(dt);
                    if sleep_time > Duration::ZERO {
                        std::thread::sleep(sleep_time);         
                    }

                    for (_id, (position, velocity)) in world.query_mut::<(&mut Position, &Velocity)>() {
                        position.0 += velocity.0.clone() * dt.as_secs_f32();
                    }

                    let mut shapes = Vec::new();
                    for (_id, position) in world.query::<&Position>().iter() {
                        let circle = egui::Shape::circle_filled(egui::Pos2::from(position.0.clone()), 5.0, egui::Color32::WHITE);
                        shapes.push(circle);
                    }

                    if output_sender.send(OutputCommand::Render { shapes }).is_err() {
                        eprintln!("engine thread is unable to send commands to main thread therefore engine thread quits, too");
                        keep_running = false;
                    }

                    for command in input_receiver.try_iter() {
                        match command {
                            InputCommand::CreateCar { position } => {
                                let velocity = Velocity(math::Vektor::<2>{ coordinates: [10.0, 8.0] });
                                world.spawn((Position(position), velocity));
                            },
                            InputCommand::Quit => {
                                keep_running = false;
                            }
                        }
                    }

                    dt = Instant::now().duration_since(last_frame_started);
                }
            })),
        }
    }
}

impl Drop for Game {
    fn drop(&mut self) {
        if let Some(thread) = self.engine_thread.take() {
            if self.input_sender.send(InputCommand::Quit).is_err() {
                eprintln!("failed to send Quit signal to engine thread");
            }
            if thread.join().is_err() {
                eprintln!("failed to join engine thread");
            }
        }
    }
}

impl eframe::App for Game {
    fn update(&mut self, ctx: &egui::Context, _frame: &mut eframe::Frame) {
        ctx.set_pixels_per_point(1.5);

        egui::CentralPanel::default().show(ctx, |ui| {
            ui.heading("Ez a cím");
            
            egui::Frame::canvas(ui.style()).show(ui, |ui| {
                let size = ui.available_size();
                let (response, painter) = ui.allocate_painter(size, egui::Sense::click_and_drag());

                if response.clicked() {
                    if let Some(mouse_pos) = response.interact_pointer_pos() {
                        let position = math::Vektor::from(mouse_pos);
                        self.input_sender.send(InputCommand::CreateCar { position }).unwrap();
                    }
                }

                painter.extend(self.shapes.iter().map(|s| s.clone()));
            });

            if let Ok(command) = self.output_receicer.recv_timeout(Duration::from_secs_f32(MAX_UI_LAG_DURATION)) {
                match command {
                    OutputCommand::Render { shapes } => {
                        self.shapes = shapes;
                    },
                }
            }

            ctx.request_repaint();
        });
    }
}


struct Position(math::Vektor<2>);


struct Velocity(math::Vektor<2>);

