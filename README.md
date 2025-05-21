# Particle-Detector by abelcastar

A modern C++ simulation that models charged and neutral particles passing through a configurable LEGO-style detector stack (Tracker, ECAL, HCAL, Muon Chamber Scintillator).
It showcases templates, smart-pointer ownership, Gaussian-smeared measurements, and dynamic detector replacement, 

---

## Features

| Category                       | Highlights                                                                                                                                                  |
| :----------------------------- | :---------------------------------------------------------------------------------------------------------------------------------------------------------- |
| **Detector Hierarchy**         | Five concrete detectors share a common `Detector` interface; `MeasurementDetector` adds Gaussian smearing and resolution logic.                             |
| **FullDetector “LEGO” System** | Detectors can be plugged in/out at run-time via `add_detector()` (lvalue & rvalue). Identity inference relies solely on detector responses.                 |
| **Particle Hierarchy**         | `Electron`, `Muon`, `Photon`, and `Hadron` derive from an abstract `Particle` with a reusable `FourMomentum` object.                                        |
| **Relativistic Four-Momentum** | Energy-based construction auto-generates isotropic momentum; setters maintain \$E^2 = p^2 + m^2\$.                                                          |
| **Gaussian Noise**             | All measurement detectors smear values with a resolution-scaled normal distribution.                                                                        |
| **Templates & Utility**        | `validate_value<T>()` is a header-only clamp template used throughout for safe parameter initialisation.                                                    |
| **Rule of Zero / Five**        | Move-aware `FullDetector` deletes copy operations, while other classes implement the Rule of 5 when needed.                                                 |
| **Smart Pointers**             | `std::shared_ptr` manages detector ownership; `std::unique_ptr` is used internally for photon containers (future-proofed).                                  |
| **Const-Correct RNG**          | Mutable PRNGs allow stochastic sampling inside logically `const` methods—pure interface, no global state.                                                   |
| **Maps & Enumerators**         | Type-safe `std::map<DetectorType, shared_ptr<Detector>>` paired with `enum class` for fast lookup and no runtime string parsing.                            |
| **Lambda Logic**               | Lightweight lambdas streamline decision logic—used in particle ID deduction and detector response filtering.                                                |
| **Testing Suite**              | Three standalone test files cover detector setup, full-system simulation, and particle-specific features to save time for the  marker checks. |

---


## File Structure

```
PROJECT-PARTICLE-DETECTOR-ABELCASTAR
│
├── logic
│   ├── detector
│   │   ├── full_detector.cpp
│   │   ├── hcal.cpp
│   │   ├── measurement_detector.cpp
│   │   ├── muon_chamber.cpp
│   │   ├── scintillator.cpp
│   │   └── tracker.cpp
│   └── particles
│       ├── four_momentum.cpp
│       ├── hadron.cpp
│       ├── particle.cpp
│       └── photon.cpp
│
├── src
│   ├── detectors
│   │   ├── detector.h
│   │   ├── ecal.h
│   │   ├── full_detector.h
│   │   ├── hcal.h
│   │   ├── measurement_detector.h
│   │   ├── muon_chamber.h
│   │   ├── scintillator.h
│   │   └── tracker.h
│   ├── particles
│   │   ├── electron.h
│   │   ├── four_momentum.h
│   │   ├── hadron.h
│   │   ├── muon.h
│   │   └── photon.h
│   └── validate_value.h
│
├── testing
│   ├── test_main_detectors.cpp
│   ├── test_main_full_detector.cpp
│   └── test_main_particles.cpp
│
├── main.cpp
├── LICENSE
└── README.md
```

---

# How to Build main.cpp

```bash
g++ -o main_program main.cpp  logic/particles/particle.cpp logic/particles/photon.cpp logic/particles/hadron.cpp logic/particles/four_momentum.cpp logic/detector/detector.cpp logic/detector/muon_chamber.cpp logic/detector/scintillator.cpp logic/detector/measurement_detector.cpp logic/detector/tracker.cpp logic/detector/hcal.cpp logic/detector/ecal.cpp logic/detector/full_detector.cpp
```

*subsequent test file compile lines*

### test_main_particles.cpp
```bash
g++ -o main_program testing/test_main_particles.cpp  logic/particles/particle.cpp logic/particles/photon.cpp logic/particles/hadron.cpp logic/particles/four_momentum.cpp logic/detector/detector.cpp logic/detector/muon_chamber.cpp logic/detector/scintillator.cpp logic/detector/measurement_detector.cpp logic/detector/tracker.cpp logic/detector/hcal.cpp logic/detector/ecal.cpp logic/detector/full_detector.cpp
```

### test_main_detectors.cpp
```bash
g++ -o main_program testing/test_main_detectors.cpp  logic/particles/particle.cpp logic/particles/photon.cpp logic/particles/hadron.cpp logic/particles/four_momentum.cpp logic/detector/detector.cpp logic/detector/muon_chamber.cpp logic/detector/scintillator.cpp logic/detector/measurement_detector.cpp logic/detector/tracker.cpp logic/detector/hcal.cpp logic/detector/ecal.cpp logic/detector/full_detector.cpp
```

### test_main_full_detector.cpp
```bash
g++ -o main_program testing/test_main_full_detector.cpp  logic/particles/particle.cpp logic/particles/photon.cpp logic/particles/hadron.cpp logic/particles/four_momentum.cpp logic/detector/detector.cpp logic/detector/muon_chamber.cpp logic/detector/scintillator.cpp logic/detector/measurement_detector.cpp logic/detector/tracker.cpp logic/detector/hcal.cpp logic/detector/ecal.cpp logic/detector/full_detector.cpp
```

---

## Usage

1. **`main.cpp`**
   *Runs a mixed demonstration:* constructs particles, individual detectors, then assembles a `FullDetector`, shows detector replacement, and compares a *perfect* vs *realistic* stack.

2. **Testing drivers**

   - `test_main_particles.cpp` : validates setters, energy clamping, name/charge switching.
   - `test_main_detectors.cpp` :  diagnostics & measurement routines per detector.
   - `test_main_full_detector.cpp` :  integration tests for adding, replacing, and querying detectors.

Each executable writes comprehensive, tagged console output so you can diff results across resolutions or compiler versions.

---

## Author: ###Abel Castaneda Rodriguez
---

## Use of AI

VS Code's GitHub Copilot feature was used to streamline debugging and house style formatting.
