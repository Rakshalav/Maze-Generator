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
3. In the solution click on `Project` -> `Properties` or press `Alt + F7`.
4. Go to `C/C++` -> `General` -> `Additional Include Directories` and change the path of the libraries accordingly.
5. Repeat step **4** for `Linker` -> `Input` -> `Additional Library Directories`.

---

## Project Structure
**Maze-Generator/**

├─ **Maze-Generator/**

│ ├─ **application/** 

│ │ ├─ Applcation.cpp
  
│ │ ├─ Application.hpp
  
│ │ └─ main.cpp

│ ├─ **ImGui/** #for Gui

│ ├─ **include/** 

│ │ ├─ Astar.hpp
  
│ │ ├─ Cell.hpp
  
│ │ ├─ Grid.hpp
  
│ │ └─ Recursive_Backtracker.hpp

│ └─ **src/**

│ │ ├─ Astar.cpp
  
│ │ ├─ Cell.cpp
  
│ │ ├─ Grid.cpp
  
│ │ └─ Recursive_Backtracker.cpp

├─ **SFML-2.6.2/** #SFML Library

├─ .gitattributes

├─ .gitignore

├─ README.md #this file

└─ Maze-Generator.sln
