use std::time::*;
use std::sync::mpsc;
use eframe::egui;
use crate::command::*;
use crate::components::*;
use crate::math::*;


const TARGET_FPS: u32 = 30;
const FRAME_DURATION: f32 = 1.0 / TARGET_FPS as f32;


pub struct Engine {
    world: hecs::World,
    keep_running: bool,
    input_receiver: mpsc::Receiver<InputCommand>,
    output_sender: mpsc::Sender<OutputCommand>,
}

impl Engine {
    pub fn new(input_receiver: mpsc::Receiver<InputCommand>, output_sender: mpsc::Sender<OutputCommand>) -> Self {
        Self {
            world: hecs::World::new(),
            keep_running: true,
            input_receiver,
            output_sender,
        }
    }

    pub fn run(&mut self) {
        let mut last_frame_started;
        let mut dt = Duration::ZERO;

        while self.keep_running {                    
            last_frame_started = Instant::now();

            let sleep_time = Duration::from_secs_f32(FRAME_DURATION).saturating_sub(dt);
            if sleep_time > Duration::ZERO {
                std::thread::sleep(sleep_time);         
            }

            for (_id, (position, velocity)) in self.world.query_mut::<(&mut Position, &Velocity)>() {
                position.value += velocity.value.clone() * dt.as_secs_f32();
            }

            let mut shapes = Vec::new();
            for (_id, position) in self.world.query::<&Position>().iter() {
                let circle = egui::Shape::circle_filled(egui::Pos2::from(position.value.clone()), 5.0, egui::Color32::GREEN);
                shapes.push(circle);
            }

            self.send_command(OutputCommand::Render { shapes });

            for command in self.input_receiver.try_iter() {
                match command {
                    InputCommand::CreateCar { position } => {
                        let velocity = Velocity{ value: Vektor::<2>{ coordinates: [10.0, 8.0] } };
                        self.world.spawn((Position{ value: position }, velocity));
                    },
                    InputCommand::Quit => {
                        self.keep_running = false;
                    }
                }
            }

            dt = Instant::now().duration_since(last_frame_started);
        }
    }

    fn send_command(&mut self, command: OutputCommand) {
        if self.output_sender.send(command).is_err() {
            eprintln!("engine thread is unable to send commands to main thread therefore engine thread quits, too");
            self.keep_running = false;
        }
    }
}
