# Sand Simulation

The simulation is a simple 2D falling sand simulation built with C++ and the **SFML** library. It features a grid-based system where individual particles are updated to create the visual effect of falling sand.

***

## Description

This project implements a basic physics simulation on a grid. The simulation's logic is decoupled from the rendering loop, allowing for a fixed number of updates per second to ensure consistent behavior regardless of the frame rate. The `Grid` class manages the state of all particles, while the `Renderer` class handles the window creation and drawing of the grid to the screen.

***

## Getting Started

### Dependencies

* A C++ compiler that supports C++17 or newer.
* **SFML** 3 or higher. You can find installation instructions on the [official SFML website](https://www.sfml-dev.org/download.php).

### Building and Running

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/sagivmarzini/SandSimulation.git
    cd SandSimulation
    ```

2.  **Compile the source code:**
    Make sure to link the SFML graphics and window libraries.

    ```bash
    g++ -o SandSimulation main.cpp Grid.cpp Renderer.cpp -lsfml-graphics -lsfml-window -lsfml-system
    ```

3.  **Run the executable:**
    ```bash
    ./SandSimulation
    ```

***

## How It Works

The core of the application is a fixed-step game loop.

* **`main.cpp`**: This file contains the main entry point of the program. It initializes the `Grid` and `Renderer` objects and contains the main loop.
* **`Grid.h` & `Grid.cpp`**: These files define the `Grid` class, which holds the logic for the simulation. It manages a 2D array of particles and contains an `update()` method that is called at a fixed interval to advance the simulation one step at a time.
* **`Renderer.h` & `Renderer.cpp`**: These files define the `Renderer` class, which is responsible for all rendering tasks. It creates the application window and draws the current state of the grid to the screen in each frame.

The main loop uses a time accumulator to ensure that the grid's update logic (`grid.update()`) is called at a consistent rate, defined by `DELTA_TIME`, independent of the rendering frame rate.
