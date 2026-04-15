# 🧱 cub3D

> A simple 3D raycasting engine inspired by Wolfenstein 3D, built in C using MiniLibX.

---

## 📌 Description

**cub3D** is a 3D rendering project developed as part of the 42 curriculum.

It is based on the **raycasting technique**, allowing the player to navigate through a pseudo-3D world from a first-person perspective.

This project focuses on low-level graphics programming, game mechanics, and engine logic built entirely in C.

---

## 🕹️ Gameplay

* Move in a 3D environment (W/A/S/D)
* Rotate camera (← / →) or mouse
* Inspect your knife 🔪 using **F key**
* Collect a key 🗝️ to unlock doors
* Open doors 🚪
* Navigate around obstacles (barrels 🛢️)

⚠️ There is **no exit** — the project focuses on exploration and mechanics.

---

## 🎮 Features

* Raycasting engine (3D projection)
* Real-time rendering
* Minimap 🗺️
* Collision system
* Interactive objects:

  * Doors 🚪
  * Barrels 🛢️ (obstacles)
  * Key system 🗝️
* Weapon inspection system (knife 🔪)
* Texture mapping
* Player movement & camera rotation

---

## 🛠️ Technologies

* C
* MiniLibX
* Math (trigonometry, vectors)
* Makefile

---

## 📂 Project Structure

```
cub3D/
├── srcs/
├── includes/
├── textures/
├── Makefile
```

---

## ⚙️ Installation & Usage

### 1. Clone the repository

```bash
git clone https://github.com/ulmagner/cub3D.git
cd cub3D
```

### 2. Compile

```bash
make
```

### 3. Run the program

```bash
./cub3D maps/map.cub path_to_texture/texture_file
```

---

## 🧠 Learning Outcomes

* Raycasting fundamentals
* 3D projection on 2D screen
* Event handling & real-time input
* Parsing and map validation
* Memory management in C
* Game engine architecture basics

---

## 📸 Preview

---

## 🚀 Possible Improvements

* Enemy AI 👾
* Shooting mechanics 🔫
* Better lighting system
* Sound effects 🔊
* UI / HUD improvements

---

## 👨‍💻 Author

* 42 Student passionate about low-level programming & game development

---

## 📄 License

This project is for educational purposes (42 school).
