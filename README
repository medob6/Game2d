# 🎮 Game2D

A 2D game built with C and a custom mini game engine.

## 📖 Description

**Game2D** is an enhanced 2D game project built from the ground up using the C language and the MiniLibX graphics library. Originally inspired by the 42 school's so_long project, this implementation features a custom mini game engine with advanced features including smooth animations, collision detection, enemy AI, and dynamic rendering.

This project demonstrates:
- 🎨 Custom game engine architecture
- 🖼️ Advanced sprite rendering and animation systems
- 🎮 Event-driven game loop implementation
- 🗺️ Tile-based map system with custom parser
- 🤖 Enemy behavior and pathfinding
- 💾 Memory management and optimization

---

## 🎬 Game Preview

<!-- Add your gameplay screenshot here -->
![Game Screenshot](path/to/screenshot.png)

<!-- Add gameplay GIF or video here -->
![Gameplay Demo](path/to/demo.gif)

*Or add a video link:*
[🎥 Watch Gameplay Video](your-video-link-here)

---

## ✨ Features

### Core Gameplay
- 🗺️ **Custom Map System**: Load and play custom maps using a simple text-based format
- 🎯 **Objective-Based Gameplay**: Collect all items and reach the exit to win
- 🚪 **Smart Collision Detection**: Prevents movement through walls and detects interactions
- 🤖 **Enemy AI**: Enemies with animated sprites and intelligent behavior
- 🏆 **Win/Lose Conditions**: Clear visual feedback for game outcomes
- 📊 **Move Counter**: Tracks player movements displayed on screen

### Technical Features
- 🎨 **Custom Animation System**: Smooth frame-based animations for all sprites
- 🖼️ **Optimized Rendering**: Background buffer system for efficient rendering
- 🎮 **Responsive Controls**: Smooth keyboard input handling
- 💾 **Memory Management**: Clean resource allocation and deallocation
- 🔄 **Game Loop Architecture**: Non-blocking game loop with proper timing
- 📦 **Modular Engine**: Reusable game engine components

---

## 🚀 Getting Started

### Prerequisites

- **Compiler**: `gcc` or `clang` supporting C99 standard or later
- **MiniLibX**: Graphics library (included or install system-specific version)
- **Make**: Build automation tool
- **Operating System**: Linux or macOS

### Installation

1. **Clone the repository:**
```bash
git clone https://github.com/medob6/Game2d.git
cd Game2d
```

2. **Build the project:**
```bash
make
```

3. **Run the game:**
```bash
./game2d maps/map1.ber
```

### Available Maps

The `maps/` directory contains several pre-designed levels. Try them all!

```bash
./game2d maps/easy.ber
./game2d maps/medium.ber
./game2d maps/hard.ber
```

---

## 🕹️ How to Play

### Objective
Collect all collectibles (💎) scattered across the map and reach the exit (🚪) to complete the level. Avoid enemies (👾) or you'll lose!

### Controls

| Key | Action |
|-----|--------|
| `W` or `↑` | Move Up |
| `A` or `←` | Move Left |
| `S` or `↓` | Move Down |
| `D` or `→` | Move Right |
| `ESC` | Quit Game |

### Game Elements

- **Player (🧑)**: Your character
- **Wall (🧱)**: Impassable obstacles
- **Collectible (💎)**: Items you need to collect
- **Exit (🚪)**: The goal (only opens when all collectibles are gathered)
- **Enemy (👾)**: Dangerous creatures to avoid
- **Empty Space**: Walkable ground

---

## 🎮 Game Engine Architecture

### Core Systems

#### 1. **Rendering Engine**
- Tile-based rendering system (64x64 pixel tiles)
- Off-screen background buffer for performance
- Layer-based sprite rendering
- Double-buffering for smooth visuals

#### 2. **Animation System**
- Frame-based sprite animation
- Independent animation timers for different entities
- Smooth transitions between animation states

#### 3. **Game Loop**
- Fixed timestep game loop
- Separate update and render phases
- Non-blocking input handling

#### 4. **Collision System**
- Grid-based collision detection
- Entity interaction handling
- Movement validation

#### 5. **Map Parser**
- Text-based map format (.ber files)
- Map validation and error checking
- Dynamic map loading

---

## 📂 Project Structure

```
Game2d/
├── src/                    # Source code
│   ├── main.c             # Entry point and initialization
│   ├── game_loop.c        # Game loop and state management
│   ├── rendering.c        # Rendering engine
│   ├── animation.c        # Animation system
│   ├── input.c            # Input handling
│   ├── collision.c        # Collision detection
│   ├── map_parser.c       # Map loading and validation
│   ├── enemy.c            # Enemy AI and behavior
│   └── cleanup.c          # Memory management
├── include/               # Header files
│   └── game2d.h          # Main header file
├── textures/              # Game assets
│   ├── player/           # Player sprites
│   ├── enemies/          # Enemy sprites
│   ├── collectibles/     # Item sprites
│   ├── tiles/            # Environment sprites
│   └── ui/               # UI elements
├── maps/                  # Level files
│   ├── map1.ber
│   ├── map2.ber
│   └── ...
├── Makefile              # Build configuration
└── README.md             # This file
```

---

## 🗺️ Creating Custom Maps

Maps are text files with `.ber` extension using the following characters:

| Character | Element |
|-----------|---------|
| `1` | Wall |
| `0` | Empty space |
| `P` | Player starting position |
| `C` | Collectible |
| `E` | Exit |
| `X` | Enemy (optional) |

### Map Rules:
- Must be rectangular (all rows same length)
- Must be surrounded by walls (`1`)
- Must contain exactly one player (`P`)
- Must contain exactly one exit (`E`)
- Must contain at least one collectible (`C`)
- File extension must be `.ber`

### Example Map:
```
111111
1P0C01
100001
1C0E01
111111
```

---

## 🔧 Technical Details

### MiniLibX Integration

The game uses MiniLibX for graphics rendering and event handling:

```c
// Key functions used
mlx_init()                    // Initialize MLX
mlx_new_window()              // Create game window
mlx_xpm_file_to_image()       // Load sprites
mlx_put_image_to_window()     // Render images
mlx_hook()                    // Register event handlers
mlx_loop_hook()               // Register game loop
mlx_loop()                    // Start event loop
```

### Performance Optimizations

- **Background Buffer**: Static elements rendered once to an off-screen buffer
- **Dirty Rectangle**: Only redraw changed areas when possible
- **Sprite Caching**: Pre-load all sprites at initialization
- **Efficient Collision**: Grid-based lookup instead of entity iteration

### Memory Management

- Proper cleanup on game exit
- Image destruction before window closure
- Memory leak detection tested with Valgrind

---

## 🎨 Screenshots & Media

### Main Menu
<!-- Add main menu screenshot -->
![Main Menu](path/to/main-menu.png)

### Gameplay
<!-- Add gameplay screenshots -->
![Level 1](path/to/level1.png)
![Level 2](path/to/level2.png)
![Level 3](path/to/level3.png)

### Victory Screen
<!-- Add victory screen -->
![Victory](path/to/victory.png)

### Game Over Screen
<!-- Add game over screen -->
![Game Over](path/to/gameover.png)

---

## 🏆 Achievements

- ✅ Custom game engine built from scratch
- ✅ Smooth animations at 60 FPS
- ✅ Multiple levels with increasing difficulty
- ✅ Enemy AI implementation
- ✅ Zero memory leaks
- ✅ Cross-platform compatibility (Linux/macOS)

---

## 🛠️ Building from Source

### Standard Build
```bash
make
```

### Debug Build
```bash
make debug
```

### Clean Build
```bash
make clean      # Remove object files
make fclean     # Remove all generated files
make re         # Clean and rebuild
```

---

## 🧪 Testing

Run the game with different maps to test:

```bash
# Easy maps (small, few enemies)
./game2d maps/easy.ber

# Medium maps (moderate size and enemies)
./game2d maps/medium.ber

# Hard maps (large, many enemies)
./game2d maps/hard.ber
```

---

## 🐛 Known Issues & Future Improvements

### Potential Improvements
- [ ] Add sound effects and background music
- [ ] Implement different enemy types
- [ ] Add power-ups and special abilities
- [ ] Create a level editor
- [ ] Add multiplayer support
- [ ] Implement save/load system

---

## 🤝 Contributing

This is a personal learning project, but suggestions and feedback are welcome! Feel free to:
- Report bugs via GitHub Issues
- Suggest new features
- Share your custom maps

---

## 📝 License

This project is part of the 42 school curriculum. Free to use for educational purposes.

---

## 🙏 Acknowledgments

- **42 Network**: For the project concept and learning opportunity
- **MiniLibX**: The lightweight graphics library that powers this game
- **42 Community**: For guidance, resources, and peer support
- **Game Development Resources**: Various tutorials and documentation that helped in building the engine

---

**Enjoy the game! 🎮✨**
