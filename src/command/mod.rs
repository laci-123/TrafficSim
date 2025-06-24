use eframe::egui;
use crate::math::*;


pub enum InputCommand {
    CreateCar {
        position: Vektor<2>,
    },
    CreateRoadSegment {
        start: Vektor<2>,
        end: Vektor<2>,
    },
    Quit,
}


pub enum OutputCommand {
    Render {
        shapes: Vec<egui::Shape>,
    }
}
