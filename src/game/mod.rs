use std::thread;
use std::time::Duration;
use std::sync::mpsc;
use eframe::egui;
use crate::command::*;
use crate::engine::*;
use crate::ui::*;


const MAX_UI_LAG_DURATION: f32 = 0.1;

pub struct Game {
    engine_thread: Option<thread::JoinHandle<()>>,
    ui: Ui,
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
            ui: Ui::default(),
            engine_thread: Some(thread::spawn(move || {
                let mut engine = Engine::new(input_receiver, output_sender);
                engine.run();
            })),
        }
    }
}

impl eframe::App for Game {
    fn update(&mut self, ctx: &egui::Context, _frame: &mut eframe::Frame) {
        self.ui.update(ctx, &self.input_sender, &self.shapes);

        if let Ok(command) = self.output_receicer.recv_timeout(Duration::from_secs_f32(MAX_UI_LAG_DURATION)) {
            match command {
                OutputCommand::Render { shapes } => {
                    self.shapes = shapes;
                },
            }
        }

        ctx.request_repaint();
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
