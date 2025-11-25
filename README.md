# Maze Generator

A C++ maze generator and pathfinding project using **SFML 2.6**.  
It supports maze generation with the **Recursive Backtracker** algorithm and pathfinding with **A\***. You can optionally visualize the algorithms in action (visualization may be slow on low-end PCs for large mazes).  

> **Note:** GUI is planned for a future update but is not yet implemented.

---

## Features

- Maze generation using **Recursive Backtracker**.
- Pathfinding using **A\***.
- Optional visualization for both algorithms.
- Future goal: a full-featured GUI.

---

## Controls

- **Start maze generation:** `Space`
- **Start pathfinding:** `Enter`

---

## Tech Stack

- **Language:** C++
- **Libraries:** SFML 2.6 (currently used for rendering), ImGui + ImGui-SFML (planned for GUI)
  
> GUI is not implemented yet, so ImGui is currently not used.

---

## How to build (Visual Studio)

### Note: This project was made and built on Visual Studio so the steps are for Visual Studio.

1. Download the source code.
2. Open the `Maze-Generator.sln`.
3. And simply build the project.

---

## Demonstration

### Grid Movement
![grid_movement](https://github.com/user-attachments/assets/611a5dd8-06b7-48c8-8eea-685253d8ca73)

### Maze Generation
![maze_generator](https://github.com/user-attachments/assets/e9c873bd-47a7-4aa9-b1ae-7e74e516acc1)

### Path Finding
![Pathfinding](https://github.com/user-attachments/assets/8d1354ee-6e3c-4657-aaf2-bb9d5336ced0)
