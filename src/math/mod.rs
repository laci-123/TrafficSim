use std::ops::{Add, AddAssign, Mul};


pub type Scalar = f32;


#[derive(Clone, Debug)]
pub struct Vektor<const N: usize> {
    pub coordinates: [Scalar; N],
}

impl<const N: usize> Vektor<N> {
    pub fn zero() -> Self {
        Self {
            coordinates: [0 as Scalar; N],
        }
    }

    pub fn dot(&self, other: &Vektor<N>) -> Scalar {
        self.coordinates
            .iter()
            .zip(other.coordinates.iter())
            .map(|(x, y)| x * y)
            .sum()
    }

    pub fn length(&self) -> Scalar {
        self.coordinates
            .iter()
            .map(|x| x*x)
            .sum::<Scalar>()
            .sqrt()
    }
}

impl<const N: usize> Add for Vektor<N> {
    type Output = Self;

    fn add(self, rhs: Self) -> Self::Output {
        let mut result = Self::default();
        for i in 0..N {
            result.coordinates[i] = self.coordinates[i] + rhs.coordinates[i];
        }
        result
    }
}

impl<const N: usize> AddAssign for Vektor<N> {
    fn add_assign(&mut self, rhs: Self) {
        for i in 0..N {
            self.coordinates[i] += rhs.coordinates[i];
        }
    }
}

impl<const N: usize> Mul<Scalar> for Vektor<N> {
    type Output = Self;

    fn mul(self, rhs: Scalar) -> Self::Output {
        let mut result = Self::default();
        for i in 0..N {
            result.coordinates[i] = self.coordinates[i] * rhs;
        }
        result
    }
}

impl<const N: usize> Default for Vektor<N> {
    fn default() -> Self {
        Self {
            coordinates: [Scalar::default(); N],
        }
    }
}

impl<const N: usize> From<Scalar> for Vektor<N> {
    fn from(value: Scalar) -> Self {
        Self {
            coordinates: [value; N],
        }
    }
}

impl From<eframe::egui::Pos2> for Vektor<2> {
    fn from(value: eframe::egui::Pos2) -> Self {
        Self {
            coordinates: [value.x, value.y],
        }
    }
}

impl From<Vektor<2>> for eframe::egui::Pos2 {
    fn from(value: Vektor<2>) -> Self {
        Self::new(value.coordinates[0], value.coordinates[1])
    }
}
