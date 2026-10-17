# N-Pendulum-2D

A C++20 simulation of an **N-link pendulum system in two dimensions**, with real-time visualisation, numerical integration, data collection, and Python-based analysis.

The project is designed as both a physics simulation and a foundation for investigating **chaotic dynamics, phase-space behaviour, numerical stability, and machine-learning applications**.

---

## Overview

The N-Pendulum-2D project simulates a chain of connected pendulum rods moving under gravity.

Each rod has its own:

- Angular position
- Angular velocity
- Length
- Mass
- Geometric centre of mass

The simulation numerically integrates the equations of motion over time and renders the resulting motion using [Raylib](https://www.raylib.com/).

Simulation data can be exported to CSV and subsequently analysed using Python tools such as NumPy, Pandas, and Matplotlib.

The long-term goal of the project is to provide a platform for studying the transition from predictable to chaotic motion and to investigate whether machine-learning models can identify or predict particular dynamical states.

---

## Features

- **N-link pendulum simulation**
- Two-dimensional motion
- Configurable number of pendulum rods
- Numerical time integration
- Gravity and drag
- Real-time Raylib visualisation
- Centre-of-mass tracking
- Angular position and velocity tracking
- Configurable data sampling interval
- CSV data export
- Python-based data analysis
- Time-series visualisation
- Centre-of-mass trajectories
- Phase-space visualisation
- Support for future machine-learning experiments

---

## Project Structure

```text
N-Pendulum-2D/
│
├── simulation/
│   ├── include/
│   │   ├── Constants.hpp
│   │   ├── Position.hpp
│   │   ├── State.hpp
│   │   ├── MathUtils.hpp
│   │   ├── Renderer.hpp
│   │   └── Analysis.hpp
│   │
│   ├── src/
│   │   ├── main.cpp
│   │   ├── State.cpp
│   │   ├── MathUtils.cpp
│   │   ├── Renderer.cpp
│   │   └── Analysis.cpp
│   │
│   └── assets/
│
├── analysis/
│   
│
├── data/
│   ├── raw/
│   └── processed/
│
│
├── CMakeLists.txt
├── README.md
├── requirements.txt
├── .gitignore
```

The project is intentionally organised by **function and responsibility** rather than simply separating files by programming language.

---

## Architecture

The project is divided into three main stages:

```text
┌─────────────────────┐
│   C++ Simulation    │
│                     │
│ State               │
│ Physics             │
│ Numerical Integration│
│ Rendering           │
└──────────┬──────────┘
           │
           │ CSV
           ▼
┌─────────────────────┐
│    Data Analysis    │
│                     │
│ Pandas              │
│ NumPy               │
│ Matplotlib          │
└──────────┬──────────┘

```

### Simulation

The C++ simulation is responsible for:

- Maintaining the physical state
- Calculating the equations of motion
- Performing numerical integration
- Updating pendulum geometry
- Rendering the simulation
- Recording simulation data

### Analysis

The Python analysis layer is responsible for:

- Loading simulation output
- Cleaning and transforming data
- Plotting trajectories
- Plotting angular motion
- Investigating phase space
- Measuring dynamical behaviour
- Preparing datasets for machine learning

---

# Requirements

## C++

The simulation requires:

- C++20 compatible compiler
- CMake
- Eigen
- Raylib

Recommended compiler:

```text
GCC 11+
```

or another compiler with good C++20 support.

## Python

The analysis environment requires:

- Python 3.14+
- NumPy
- Pandas
- Matplotlib

Python dependencies are specified in:

```text
requirements.txt
```

---

# Building the Simulation

From the project root:

```bash
mkdir -p build
cd build
cmake ..
cmake --build .
```

The resulting executable will be generated inside the build directory according to the configured CMake target.

To run the simulation:

```bash
./N-Pendulum-2D
```

The exact executable name may depend on the target defined in `CMakeLists.txt`.

---

# Python Environment

It is recommended to use a virtual environment for Python development.

Create the environment:

```bash
python3 -m venv .venv
```

Activate it on Linux/macOS:

```bash
source .venv/bin/activate
```

On Windows PowerShell:

```powershell
.venv\Scripts\Activate.ps1
```

Upgrade `pip`:

```bash
python -m pip install --upgrade pip
```

Install the project dependencies:

```bash
python -m pip install -r requirements.txt
```

Run a Python analysis script from the project root:

```bash
python analysis/~Graphing.py
```

---

# Simulation Configuration

Simulation parameters are centralised in the project's constants/configuration rather than being scattered throughout the codebase.

Typical parameters include:

- Number of rods
- Rod length
- Rod mass
- Gravity
- Drag coefficient
- Integration timestep
- Data sampling interval
- Pixels-per-metre rendering scale

For example:

```cpp
constexpr double GRAVITY = 3.71;
constexpr double DRAG_COEFFICIENT = 1.2;
```

These values can be adjusted depending on the experiment being performed.

---

# Data Collection

The simulation records data at a configurable sampling interval.

For each recorded timestep, the following information can be stored:

### Time

```text
time
```

### Angular position

```text
theta_0
theta_1
theta_2
...
```

### Angular velocity

```text
omega_0
omega_1
omega_2
...
```

### Centre of mass

```text
com_x_0
com_y_0
com_x_1
com_y_1
...
```

The resulting CSV therefore provides a complete time history of the simulated system.

Example:

```text
time,theta_0,theta_1,omega_0,omega_1,com_x_0,com_y_0,...
0.00,...
0.01,...
0.02,...
...
```

---

# Data Pipeline

Raw simulation data should be kept separate from generated analysis results.

```text
data/
├── raw/
│   └── pendulum.csv
│
└── processed/
    ├── ...
    └── ...
```

The intended workflow is:

```text
Simulation
    │
    ▼
data/raw/
    │
    ▼
Python processing
    │
    ▼
data/processed/
    │
    ▼
Analysis / ML
    │
    ▼
results/
```

Raw simulation output should not be modified during analysis. Instead, processed datasets should be generated separately.

This makes experiments reproducible and allows the original simulation output to be preserved.

---

# Analysis

The Python analysis environment can be used to investigate several aspects of the simulated system.

## Centre-of-Mass Trajectory

A rod's centre of mass can be plotted as:

```python
plt.plot(data["com_x_5"], data["com_y_5"])
```

This produces the trajectory of rod 5 through physical space.

---

## Angular Position

Angular position can be plotted against time:

```python
plt.plot(data["time"], data["theta_5"])
```

This allows the evolution of the pendulum's angle to be studied over time.

---

## Angular Velocity

Angular velocity can similarly be plotted:

```python
plt.plot(data["time"], data["omega_5"])
```

This is useful for examining acceleration, oscillation and high-energy behaviour.

---

## Phase Space

A phase-space representation plots angular position against angular velocity:

```python
plt.plot(data["theta_5"], data["omega_5"])
```

For pendulum systems, it can also be useful to wrap the angular coordinate into:

```text
[-π, π]
```

without modifying the underlying simulation data:

```python
theta = np.arctan2(
    np.sin(data["theta_5"]),
    np.cos(data["theta_5"])
)
```

The resulting plot shows the system's state in terms of:

```text
θ vs ω
```

which can reveal oscillatory, rotational and chaotic regimes.

---

# Numerical Considerations

The behaviour of a multi-pendulum system is highly sensitive to the numerical integration method and timestep.

Small numerical errors can accumulate over long simulations and produce artificial changes in system energy.

For this reason, simulation results should be validated before being used for machine-learning experiments.

Important quantities to monitor include:

- Total mechanical energy
- Angular velocity
- Angular displacement
- Numerical stability
- Sensitivity to timestep
- Long-term energy drift

For an undamped system, total energy should remain approximately constant.

When damping is included, energy should generally decrease over time.

Unexpected energy growth can indicate numerical instability or an error in the equations of motion.

---

# Reproducibility

Experiments should record the parameters used to generate each dataset.

At minimum, this should include:

```text
Number of rods
Rod lengths
Rod masses
Gravity
Drag coefficient
Initial angles
Initial angular velocities
Integration timestep
Sampling interval
Simulation duration
Integrator
```

This allows datasets and results to be reproduced later.

---

### Feature Extraction

Potential features include:

- Angular positions
- Angular velocities
- Angular accelerations
- Total energy
- Centre-of-mass positions
- Centre-of-mass velocities
- Phase-space characteristics

The physics simulation should be validated before these datasets are used for ML training.

---

# Development

A typical development workflow is:

```bash
# Build C++
mkdir -p build
cd build
cmake ..
cmake --build .

# Run simulation
./N-Pendulum-2D

# Return to project root
cd ..

# Activate Python environment
source .venv/bin/activate

# Run analysis
python analysis/~Graphing.py
```

---

# Git and Generated Data

Generated files should generally not be committed to version control.

The repository should ignore:

```text
.venv/
__pycache__/
*.pyc
.env
data/*
models/*
```

while retaining placeholder files such as:

```text
data/.gitkeep
models/.gitkeep
```

This keeps the repository lightweight while preserving the intended project structure.

---

# Future Development

Planned improvements include:

- [ ] Improve and validate the numerical integrator
- [ ] Add total-energy calculations
- [ ] Add numerical stability tests
- [ ] Add automated physics tests
- [ ] Improve configurable simulation parameters
- [ ] Add richer CSV metadata
- [ ] Add automated Python analysis
- [ ] Add dataset preprocessing
- [ ] Investigate chaotic regimes
- [ ] Implement equilibrium detection
- [ ] Develop machine-learning models
- [ ] Compare numerical integrators
- [ ] Investigate sensitivity to initial conditions
- [ ] Add experiment configuration files
- [ ] Improve visualisation and plotting
- [ ] Add reproducible experiment generation

---

# Research Direction

The ultimate objective of the project is to use the N-pendulum as a controlled environment for investigating complex dynamical systems.

The project provides a progression from:

```text
Classical Mechanics
       ↓
Numerical Simulation
       ↓
Chaotic Dynamics
       ↓
Data Analysis
       ↓
Machine Learning
```

This makes the project useful not only as a physics simulation, but also as a framework for exploring how computational models can analyse and predict nonlinear dynamical systems.

---

# Author

Tobias Connon

Developed as an ongoing computational physics and machine-learning project.

For questions, suggestions, or collaboration, please open an issue or discussion in the project repository.
