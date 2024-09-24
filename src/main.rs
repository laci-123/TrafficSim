use bevy::prelude::*;
use bevy_wasm_window_resize::WindowResizePlugin;

fn main() {
    App::new()
        .add_plugins(DefaultPlugins)
        .add_plugins(WindowResizePlugin)
        .add_systems(Startup, setup)
        .add_systems(Update, sprite_movement)
        .run();
}

#[derive(Component)]
enum Direction {
    Up,
    Down,
}

fn setup(mut commands: Commands, asset_server: Res<AssetServer>) {
    commands.spawn(Camera2dBundle::default());
    commands.spawn((
        SpriteBundle {
            texture: asset_server.load("duckling.png"),
            transform: Transform::from_xyz(10.0, 0.0, 0.0),
            ..default()
        },
        Direction::Up,
    ));
}

fn sprite_movement(time: Res<Time>, mut sprite_position: Query<(&mut Direction, &mut Transform)>) {
    for (mut direction, mut transform) in &mut sprite_position {
        match *direction {
            Direction::Up => transform.translation.y += 10. * time.delta_seconds(),
            Direction::Down => transform.translation.y -= 10. * time.delta_seconds(),
        }

        if transform.translation.y > 200.0 {
            *direction = Direction::Down;
        } else if transform.translation.y < -200.0 {
            *direction = Direction::Up;
        }
    }
}
