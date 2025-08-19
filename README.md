# Pac‑Man (Multi‑Threaded, C) 🎮

A multi-threaded version of the classic **Pac‑Man** game written in **C**, using **pthreads** for concurrency and either **GLUT** or **SFML** for graphics.

> Each entity (Pac‑Man + multiple ghosts) runs on its **own thread**, with proper synchronization to avoid data races and ensure smooth gameplay.

---

## ✨ Features
- Pac‑Man + N ghosts running concurrently (1 thread per entity)
- Thread‑safe game state (grid, pellets, power‑ups, score)
- Synchronization with **pthread mutexes/condition variables**
- Deterministic tick/update loop to avoid busy‑waiting
- Pluggable rendering backend: **GLUT** *or* **SFML**
- Pausing, resetting, and clean shutdown (join all threads)

---

## 🧩 Tech Stack
- **Language:** C (C11 recommended)
- **Concurrency:** POSIX Threads (**pthreads**)
- **Graphics:** **GLUT** (FreeGLUT) *or* **SFML**
- **Build:** Make or CMake

---

## 📦 Dependencies

### Common
- C compiler (GCC/Clang)
- POSIX Threads (`-pthread`)

### If you choose **GLUT**
- **Linux:** freeglut (`libglut`), OpenGL (`libGL`, `libGLU`)
- **Windows (MSYS2/MinGW):** `freeglut` packages
- **macOS:** system GLUT is deprecated; use freeglut via Homebrew

### If you choose **SFML**
- **SFML 2.6+** (modules: `system`, `window`, `graphics`, `audio` optional)

---

## 🛠️ Build & Run

> Choose **one** backend. Both examples assume sources live in `src/`.

### Linux (GLUT)
```bash
sudo apt-get update
sudo apt-get install -y build-essential freeglut3-dev
gcc -std=c11 -O2 -Wall -Wextra -Iinclude \
  src/main.c src/game.c src/ai.c src/render_glut.c src/threads.c \
  -o pacman_glut \
  -lglut -lGL -lGLU -lm -pthread
./pacman_glut
```

### Linux (SFML)
```bash
sudo apt-get install -y libsfml-dev
gcc -std=c11 -O2 -Wall -Wextra -Iinclude \
  src/main.c src/game.c src/ai.c src/render_sfml.c src/threads.c \
  -o pacman_sfml \
  -lsfml-graphics -lsfml-window -lsfml-system -lm -pthread
./pacman_sfml
```

### Windows (MSYS2 MinGW, GLUT)
```bash
# In MSYS2 shell:
pacman -S --needed mingw-w64-x86_64-toolchain mingw-w64-x86_64-freeglut
gcc -std=c11 -O2 -Wall -Wextra -Iinclude \
  src/main.c src/game.c src/ai.c src/render_glut.c src/threads.c \
  -o pacman_glut.exe \
  -lfreeglut -lopengl32 -lglu32 -lm -pthread
./pacman_glut.exe
```

### Windows (MSYS2 MinGW, SFML)
```bash
pacman -S --needed mingw-w64-x86_64-toolchain mingw-w64-x86_64-sfml
gcc -std=c11 -O2 -Wall -Wextra -Iinclude \
  src/main.c src/game.c src/ai.c src/render_sfml.c src/threads.c \
  -o pacman_sfml.exe \
  -lsfml-graphics -lsfml-window -lsfml-system -lm -pthread
./pacman_sfml.exe
```

### macOS (Homebrew)

**GLUT (freeglut via XQuartz is limited)** – prefer **SFML**.

SFML:
```bash
brew install sfml
clang -std=c11 -O2 -Wall -Wextra -Iinclude \
  src/main.c src/game.c src/ai.c src/render_sfml.c src/threads.c \
  -o pacman_sfml \
  -L/opt/homebrew/lib -I/opt/homebrew/include \
  -lsfml-graphics -lsfml-window -lsfml-system -lm -pthread
./pacman_sfml
```

---

## 🧱 Project Structure
```
pacman-mt/
├─ include/
│  ├─ game.h
│  ├─ threads.h
│  ├─ render.h        # Abstract renderer API
│  ├─ backend_glut.h  # GLUT impl
│  └─ backend_sfml.h  # SFML impl
├─ src/
│  ├─ main.c          # parse args, init, game loop
│  ├─ game.c          # world/grid, pellets, collisions
│  ├─ ai.c            # ghost behavior (scatter/chase/frightened)
│  ├─ threads.c       # pthreads: spawn/join, sync
│  ├─ render_glut.c   # GLUT drawing
│  └─ render_sfml.c   # SFML drawing
├─ assets/            # fonts/sounds (SFML), optional
├─ CMakeLists.txt     # optional (see below)
└─ README.md
```

---

## 🧠 Concurrency Design (Overview)
- **Threads**
  - `pacman_thread`: reads input, updates Pac‑Man position
  - `ghost_thread[i]`: one per ghost, runs simple AI (BFS/A* optional)
  - `renderer_thread` (optional): consumes frame snapshots
  - `ticker_thread`: emits fixed‑rate ticks (e.g., 60 Hz) via condition variable
- **Shared State**
  - `GameState { grid[][], pacman, ghosts[], score, pellets_left, mode }`
- **Sync Primitives**
  - `pthread_mutex_t state_mtx`
  - `pthread_cond_t tick_cv`
- **Update Protocol**
  1. `ticker_thread` broadcasts `tick_cv`
  2. Each entity thread: lock → read state → propose move → write → unlock
  3. Resolve collisions deterministically (e.g., via move queue)
- **Shutdown**
  - Set `running = false`, broadcast, join all threads, free resources

---

## 🎮 Controls (suggested defaults)
- **Arrow Keys**: Move
- **P**: Pause / Resume
- **R**: Reset
- **Esc**: Quit

---

## 🧪 Run Options (example)
```bash
./pacman_sfml --ghosts 4 --seed 42 --fps 60 --map maps/classic.map --backend sfml
```

---

## 🧰 CMake (optional)
`CMakeLists.txt` (choose backend via option):
```cmake
cmake_minimum_required(VERSION 3.16)
project(pacman_mt C)

set(CMAKE_C_STANDARD 11)
option(USE_SFML "Use SFML instead of GLUT" ON)

if (USE_SFML)
  find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)
  add_definitions(-DUSE_SFML)
  add_executable(pacman src/main.c src/game.c src/ai.c src/render_sfml.c src/threads.c)
  target_include_directories(pacman PRIVATE include)
  target_link_libraries(pacman PRIVATE sfml-graphics sfml-window sfml-system m pthread)
else()
  find_package(OpenGL REQUIRED)
  find_package(GLUT REQUIRED)
  add_executable(pacman src/main.c src/game.c src/ai.c src/render_glut.c src/threads.c)
  target_include_directories(pacman PRIVATE include)
  target_link_libraries(pacman PRIVATE GLUT::GLUT OpenGL::GL OpenGL::GLU m pthread)
endif()
```

Build:
```bash
mkdir -p build && cd build
cmake -DUSE_SFML=ON ..   # or -DUSE_SFML=OFF for GLUT
cmake --build . --config Release
./pacman   # or pacman.exe on Windows
```

---

## 🐛 Troubleshooting
- **undefined reference to `pthread_*`** → add `-pthread` to both compile and link
- **GLUT not found** → install freeglut dev packages and ensure headers/libs on path
- **SFML unresolved externals (Windows)** → ensure MinGW toolchain matches SFML build
- **Nothing renders** → run from project root so assets resolve, or set absolute paths
- **High CPU** → use a fixed tick with `pthread_cond_timedwait` instead of busy loops

---

## 📄 License
MIT – see `LICENSE` (or change to your preferred license).

---

## 🙌 Credits
Built by **Your Name**. Inspired by the original Pac‑Man.
