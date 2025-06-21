use std::time::Duration;

use eframe;
use eframe::egui;
use hecs;
use crate::math;


const TARGET_FPS: u32 = 30;
const FRAME_DURATION: f32 = 1.0 / TARGET_FPS as f32;


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
                        let velocity = Velocity(math::Vektor::<2>{ coordinates: [10.0, 8.0] });
                        self.world.spawn((position, velocity));
                    }
                }

                let dt = ctx.input(|i| i.unstable_dt);
                for (_id, (position, velocity)) in self.world.query_mut::<(&mut Position, &Velocity)>() {
                    position.0 += velocity.0.clone() * dt;
                }

                for (_id, position) in self.world.query::<&Position>().iter() {
                    painter.circle(egui::Pos2::from(position.0.clone()), 5.0, egui::Color32::WHITE, egui::Stroke::default());
                }
            });

            ctx.request_repaint_after(Duration::from_secs_f32(FRAME_DURATION));
        });
    }
}


struct Position(math::Vektor<2>);


struct Velocity(math::Vektor<2>);

