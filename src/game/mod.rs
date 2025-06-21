use eframe;
use eframe::egui;
use hecs;
use crate::math;


pub struct Game {
    world: hecs::World,
}

impl Default for Game {
    fn default() -> Self {
        Self {
            world: hecs::World::new(),
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
                        let position = Position(math::Vektor::from(mouse_pos));
                        let velocity = Velocity(math::Vektor::<2>{ coordinates: [1.0, 1.0] });
                        self.world.spawn((position, velocity));
                    }
                }

                for (_id, (position, velocity)) in self.world.query_mut::<(&mut Position, &Velocity)>() {
                    position.0 += velocity.0.clone();
                }

                for (_id, position) in self.world.query::<&Position>().iter() {
                    painter.circle(egui::Pos2::from(position.0.clone()), 5.0, egui::Color32::WHITE, egui::Stroke::default());
                }
            });
        });
    }
}


struct Position(math::Vektor<2>);


struct Velocity(math::Vektor<2>);

