#![windows_subsystem = "windows"]
fn main() -> eframe::Result {
    let options = eframe::NativeOptions::default();
    eframe::run_native("próba", options, Box::new(|_context| {
        Ok(Box::new(game::Game::default()))
    }))
}


mod game;
mod math;
