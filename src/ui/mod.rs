use std::sync::mpsc;
use eframe::egui;
use crate::math::*;
use crate::command::*;


#[derive(Default)]
pub struct Ui {
    
}

impl Ui {
    pub fn update(&mut self, ctx: &egui::Context, input_sender: &mpsc::Sender<InputCommand>, shapes: &[egui::Shape]) {
        ctx.set_pixels_per_point(1.5);

        egui::CentralPanel::default().show(ctx, |ui| {
            ui.heading("Ez a cím");
            
            egui::Frame::canvas(ui.style()).show(ui, |ui| {
                let size = ui.available_size();
                let (response, painter) = ui.allocate_painter(size, egui::Sense::click_and_drag());

                if response.clicked() {
                    if let Some(mouse_pos) = response.interact_pointer_pos() {
                        let position = Vektor::from(mouse_pos);
                        input_sender.send(InputCommand::CreateCar { position }).expect("engine thread should be running");
                    }
                }

                painter.extend(shapes.iter().map(|s| s.clone()));
            });
        });
    }
}
