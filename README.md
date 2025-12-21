# 🧱 cub3D

> A **raycasting 3D engine** inspired by *Wolfenstein 3D*, developed as part of the **42 Common Core**.

<p align="center">
  <img src="assets/demo.gif" width="700" alt="cub3D demo">
</p>

---

## 📌 Overview

**cub3D** is a graphical project written in **C** that implements a basic **3D game engine** using the **raycasting technique**.  
The goal is to render a 3D view of a maze from a 2D map, handling player movement, wall collisions, and texture mapping.

This project focuses on:
- Computer graphics fundamentals
- Mathematical precision
- Low-level performance
- Event-driven programming

---

## 🎮 Features

- 🔭 Real-time **raycasting engine**
- 🧱 Wall rendering with textures
- 🧭 Player movement & rotation
- 🚧 Collision detection
- 🎨 Floor & ceiling colors
- 🗺️ Configurable map via `.cub` file
- ⌨️ Keyboard controls

### ⭐ Bonus
- 🖱️ Mouse movement
- 🗺️ Minimap
- 🔄 Animated textures (moving hands)
- 🚪 Doors
- 🧱 Wall collisions

---

## 🕹️ Controls

| Key | Action |
|----|-------|
| `W` | Move forward |
| `S` | Move backward |
| `A` | Strafe left |
| `D` | Strafe right |
| `← →` | Rotate camera |
| `ESC` | Exit game |

---

## 🗺️ Map Configuration (`.cub`)

## ▶️ How to Play
### 🛠️ Compilation

Compile the mandatory part:
```
make
```
Compile with bonus features:
```
make bonus
```
### 🎮 Run the Game
Mandatory
```
./cub3D map.cub
```
Bonus
```
./cub3D_bonus map_b.cub
or
./cub3D_bonus map1.cub
```

---

## ⚠️ Notes

### You can create your own map, but it must follow these constraints.

* The map file must have a .cub extension

* Only one player start position is allowed

* The map must be fully closed by walls

* Invalid maps or configurations will result in an error message