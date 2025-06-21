use eframe;
use eframe::egui;


pub struct Game {
    
}

impl eframe::App for Game {
    fn update(&mut self, ctx: &egui::Context, _frame: &mut eframe::Frame) {
        ctx.set_pixels_per_point(1.5);

        egui::CentralPanel::default().show(ctx, |ui| {
            ui.heading("Ez a cím");
            
            egui::Frame::canvas(ui.style()).show(ui, |ui| {
                let size = ui.available_size();
                let (_response, painter) = ui.allocate_painter(size, egui::Sense::click_and_drag());

                painter.circle(egui::Pos2::new(100.0, 100.0), 5.0, egui::Color32::WHITE, egui::Stroke::default());
            });
        });
    }
}
