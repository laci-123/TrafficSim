use eframe::egui;

use crate::math;


#[derive(Debug)]
pub enum InputCommand {
    CreateCar {
        position: math::Vektor<2>,
    },
    Quit,
}


pub enum OutputCommand {
    Render {
        shapes: Vec<egui::Shape>,
    }
}
