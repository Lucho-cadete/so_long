<h1 align="center" style="font-size: 3em;">🎮 so_long</h1>

<p align="center"><i>A 2D top-down game built in C using the MiniLibX graphics library</i></p>

<p align="center">
  <img src="https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c" alt="Language">
  <img src="https://img.shields.io/badge/Norminette-passing-brightgreen?style=for-the-badge" alt="Norminette">
  <img src="https://img.shields.io/badge/Status-In_Progress-orange?style=for-the-badge" alt="Status">
</p>

---

**📹 Gameplay demo coming soon** (![Game Preview](assets/gameplay.gif))

## 📖 About

**so_long** is a Codam Coding College project focused on 2D game development, graphics rendering, and event handling. The player must collect all collectibles on the map and reach the exit while avoiding obstacles.

### Key Learning Objectives
- Window management and keyboard event handling
- 2D sprite rendering and animation
- Map parsing and validation algorithms
- Game loop implementation
- Memory management with graphical resources

---

## ✨ Features

- 🎯 Smooth player movement with WASD or arrow keys
- 🗺️ Map validation system (flood fill pathfinding)
- 💎 Collectible items system
- 🚪 Exit mechanism (unlocks after collecting all items)
- 📊 Move counter displayed in real-time
- 🎨 Custom sprite assets
- 🔴 Enemy patrol system *(bonus)*
- 🏆 Victory and game over screens *(bonus)*

---

## 🎮 Controls

| Key | Action |
|:---:|--------|
| `W` or `↑` | Move up |
| `A` or `←` | Move left |
| `S` or `↓` | Move down |
| `D` or `→` | Move right |
| `ESC` | Exit game |

---

## 🚀 Installation

### Prerequisites
- **OS:** Linux or macOS
- **Compiler:** gcc or clang
- **Make**
- **MiniLibX** (included)

### Build
```bash
# Clone the repository
git clone https://github.com/Lucho-cadete/so_long.git
cd so_long

# Compile
make

# Run with a map
./so_long maps/map1.ber
```

---

## 🗺️ Map Format

Maps are `.ber` files with the following components:
```
111111
1P0C01
100001
1C0E01
111111
```

### Components
- `1` → Wall
- `0` → Empty space
- `P` → Player start (exactly 1 required)
- `C` → Collectible (minimum 1 required)
- `E` → Exit (exactly 1 required)
- `X` → Enemy *(bonus)*

### Validation Rules
✅ Map must be rectangular  
✅ Map must be surrounded by walls  
✅ Must contain valid path: P → all C → E  
✅ Must have exactly 1 player and 1 exit  
✅ Must have at least 1 collectible  

---

## 💡 Technical Highlights

### Pathfinding Algorithm
Implemented **flood fill** to validate map solvability before game starts. Ensures all collectibles and the exit are reachable from the player's starting position.

### Rendering Optimization
- Sprites loaded once into memory
- Only visible tiles rendered each frame
- Maintains consistent 60 FPS performance

### Memory Management
- Proper cleanup of all allocated resources
- No memory leaks (verified with Valgrind)
- Texture caching system

### Error Handling
- Comprehensive map validation with clear error messages
- Graceful handling of invalid file formats
- Robust file descriptor management

---

## 📁 Project Structure
```
so_long/
├── src/
│   ├── main.c                 # Entry point and game initialization
│   ├── map_parser.c           # Map file reading and parsing
│   ├── map_validator.c        # Map validation and pathfinding
│   ├── game_loop.c            # Main game loop and rendering
│   ├── player.c               # Player movement and collision
│   ├── render.c               # Sprite rendering functions
│   └── utils.c                # Helper functions
├── includes/
│   └── so_long.h              # Header file
├── maps/
│   ├── valid/                 # Valid test maps
│   │   ├── map1.ber
│   │   └── map2.ber
│   └── invalid/               # Invalid test maps
├── assets/
│   └── sprites/               # Game sprites (PNG/XPM)
├── libft/                     # Custom C library
├── mlx/                       # MiniLibX library
└── Makefile
```

---

## 🧪 Testing

### Valid Maps
```bash
./so_long maps/valid/map1.ber
./so_long maps/valid/map2.ber
```

### Invalid Maps (should display error)
```bash
./so_long maps/invalid/no_walls.ber
./so_long maps/invalid/unreachable.ber
```

### Memory Leak Check
```bash
make valgrind
# or
valgrind --leak-check=full ./so_long maps/map1.ber
```

---

## 📊 Project Status

**Status:** In Development 🚧  
**Current Phase:** Implementing game mechanics  
**Expected Completion:** December 2024

<!-- Cuando termines, actualiza a:
**Grade:** `125/100` ⭐  
**Status:** `Completed`  
**Completion Date:** `December 2024`
-->

---

## 🎨 Screenshots

<!-- Añade tus capturas aquí cuando las tengas -->
<p align="center">
  <img src="assets/screenshot1.png" width="45%" alt="Gameplay 1">
  <img src="assets/screenshot2.png" width="45%" alt="Gameplay 2">
</p>

---

## 🔮 Future Enhancements

- [ ] Add background music and sound effects
- [ ] Implement scoring system based on moves
- [ ] Create in-game map editor
- [ ] Add multiple difficulty levels
- [ ] Port to web using Emscripten

---

## 📚 Resources

- [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx)
- [42 Network Projects](https://github.com/jotavare/42-resources)

---

## 👤 Author

**Luis Martinez**  
Codam Coding College - Cohort Februari 2025

[![GitHub](https://img.shields.io/badge/GitHub-181717?style=flat&logo=github&logoColor=white)](https://github.com/Lucho-cadete)

---

<p align="center">
  <i>This project is part of the Codam Coding College curriculum (42 Network)</i>
</p>
