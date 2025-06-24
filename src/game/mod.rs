use std::thread;
use std::time::Duration;
use std::sync::mpsc;
use eframe;
use eframe::egui;
use crate::command::*;
use crate::math;
use crate::engine::*;


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
                let mut engine = Engine::new(input_receiver, output_sender);
                engine.run();
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

