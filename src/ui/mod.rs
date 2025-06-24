use std::sync::mpsc;
use eframe::egui;
use crate::math::*;
use crate::command::*;


#[derive(Default)]
pub struct Ui {
    selected_tool: Tool,
}

impl Ui {
    pub fn update(&mut self, ctx: &egui::Context, input_sender: &mpsc::Sender<InputCommand>, shapes: &[egui::Shape]) {
        ctx.set_pixels_per_point(1.5);

        egui::CentralPanel::default().show(ctx, |ui| {
            ui.horizontal(|ui| {
                if ui.add(egui::Button::new("car").frame(self.selected_tool == Tool::Car)).clicked() {
                    self.selected_tool = Tool::Car;
                }
                if ui.add(egui::Button::new("road").frame(self.selected_tool == Tool::Road)).clicked() {
                    self.selected_tool = Tool::Road;
                }
            });
            
            egui::Frame::canvas(ui.style()).show(ui, |ui| {
                let size = ui.available_size();
                let (response, painter) = ui.allocate_painter(size, egui::Sense::click_and_drag());

                if response.clicked() {
                    if let Some(mouse_pos) = response.interact_pointer_pos() {
                        match self.selected_tool {
                            Tool::Car => {
                                let position = Vektor::from(mouse_pos);
                                send_command(input_sender, InputCommand::CreateCar { position });
                            },
                            Tool::Road => {
                                let start = Vektor::from(mouse_pos);
                                let end   = start + Vektor { coordinates: [20.0, 30.0] };
                                send_command(input_sender, InputCommand::CreateRoadSegment { start, end });
                            },
                        }
                    }
                }

                painter.extend(shapes.iter().map(|s| s.clone()));
            });
        });
    }
}


fn send_command(input_sender: &mpsc::Sender<InputCommand>, command: InputCommand) {
    input_sender.send(command).expect("engine thread should be running");
}


#[derive(Default, PartialEq, Eq)]
enum Tool {
    #[default]
    Car,
    Road,
}
