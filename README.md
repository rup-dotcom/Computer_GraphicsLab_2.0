# Toll Booth Project

This is a simple **2D computer graphics animation project** made using **C++** and the **OpenGL (GLUT/freeglut)** library. It simulates a car approaching a toll booth, the gate opening, and the car passing through it. The project is built and run using **Code::Blocks IDE** on Windows.

---

## 1. Installation Guide

Follow these steps carefully to set up and run the project on your computer.

### Step 1: Install Code::Blocks (with MinGW compiler)
1. Download **Code::Blocks** from the official website: https://www.codeblocks.org/downloads/
2. Choose the version that says **"codeblocks-xx.xx-mingw-setup.exe"** — this version comes with the GCC/MinGW compiler already bundled, so you don't need to install it separately.
3. Install it like a normal Windows application (Next → Next → Finish).

### Step 2: Download and Set Up freeglut
This project uses the **freeglut** library to create the window and handle graphics/animation, so it must be installed separately.

1. Download the **freeglut** library (MinGW version) from: https://www.transmissionzero.co.uk/software/freeglut-devel/
2. Extract the downloaded folder and rename/place it as `freeglut` (for example: `C:/Users/<YourName>/freeglut`).
3. Inside the `freeglut` folder, you should see three important folders: `include`, `lib`, and `bin`.
4. Copy the file `freeglut.dll` from the `bin` folder into:
   - `C:\Windows\System32` (for 64-bit systems), **and/or**
   - The same folder where your project's `.exe` file will be generated (`bin/Debug` folder of this project).

> **Note:** This project's `.cbp` file currently points to a fixed path (`C:/Users/Jannat/freeglut`). If your freeglut folder is in a different location, you must update this path — see **Step 4** below.

### Step 3: Open the Project
1. Extract the `Toll_booth.zip` file to any folder on your computer.
2. Open **Code::Blocks**.
3. Go to **File → Open**, then select the file named **`Toll booth.cbp`** inside the extracted folder.

### Step 4: Configure Compiler & Linker Paths (Important!)
Since the project was originally created on another computer, you need to point it to your own freeglut folder:

1. Go to **Project → Build Options**.
2. Under the **Search Directories** tab:
   - **Compiler** tab → add the path to your `freeglut/include` folder.
   - **Linker** tab → add the path to your `freeglut/lib` folder.
3. Under the **Linker Settings** tab, make sure these libraries are listed under "Link libraries":
   - `freeglut`
   - `opengl32`
   - `glu32`
   - `winmm`
   - `gdi32`

### Step 5: Build and Run
1. Click the **Build** button (gear icon) or press `Ctrl + F9` to compile the code.
2. Click the **Run** button (green play icon) or press `Ctrl + F10` to run the program.
3. If everything is set up correctly, a window titled **"Toll Booth Project (2D)"** will open showing the animation.

---

## 2. What I Did in This Project (Explanation with Screenshot)

The screenshot below shows the output of the program when it is run:
<img width="998" height="623" alt="image" src="https://github.com/user-attachments/assets/cd3a3cb5-d86d-4b16-8c79-b88c237c9db2" />
<img width="1001" height="622" alt="image" src="https://github.com/user-attachments/assets/4c2ff0a0-49ec-4714-ab32-eb727e82d7c1" />




- **Sky background**: A blue gradient rectangle is drawn at the top of the screen to represent the sky.
- **Road**: A dark grey rectangle represents the road, and a yellow strip in the middle acts as the road's lane divider line.
- **Toll Booth**: On the right side of the screen, a grey booth structure is drawn using rectangles — it has a light blue "window" and a dark grey "base/leg" to make it look like a small booth building.
- **Gate (Boom Barrier)**: A red horizontal bar is attached at the base of the booth. This bar can rotate — it acts like a toll gate that opens (rotates upward) and closes (rotates back down).
- **Car**: A red rectangular car (with a smaller rectangle on top as the car's cabin/roof, and two black rectangles as wheels) is drawn on the left side of the screen.

**How the animation works (the story of the scene):**
1. When the program starts, the car is positioned far to the left, and the gate is closed (lying flat, angle = 0).
2. The car automatically moves to the right, frame by frame, until it reaches the toll booth and stops just before the gate.
3. When the **`p`** key is pressed (meaning "pass"/"open"), the gate starts rotating upward (like a real boom barrier lifting).
4. Once the gate has rotated fully open, the car starts moving again and passes through the toll booth.
5. Once the car goes off-screen (past the booth), the scene automatically resets: the car goes back to its starting position on the left, and the gate closes again, so the animation can repeat.
6. The user can also press **`s`** to stop/close the gate manually, or **`r`** to reset the whole scene (car and gate) back to the starting state at any time.

This basically demonstrates **2D transformations (translation and rotation)** and **keyframe/frame-based animation** using OpenGL, which is a common concept taught in Computer Graphics courses.

---

## 3. Functions Used and How They Work

### A) Custom Functions 

| Function | What it does |
|---|---|
| `drawRectangle(x1, y1, x2, y2)` | A reusable helper function that draws a filled rectangle (using `GL_QUADS`) between two corner points `(x1, y1)` and `(x2, y2)`. Almost every shape in this project (car, booth, gate, road) is built by calling this function with different coordinates and colors, instead of writing repetitive `glBegin`/`glEnd` code again and again. |
| `drawCar()` | Draws the car using three `drawRectangle()` calls: one large rectangle for the car's body, a smaller rectangle on top for the cabin/roof, and two small black rectangles at the bottom for the wheels. The car's horizontal position depends on the global variable `carX`, so as `carX` changes over time, the car appears to move. |
| `drawGate()` | Draws the toll gate (the red horizontal bar). It uses `glPushMatrix()` and `glPopMatrix()` to isolate its own transformations from the rest of the scene, `glTranslatef()` to move the gate's rotation point (pivot) to the correct position near the booth, and `glRotatef(gateAngle, 0, 0, 1)` to rotate the bar around the Z-axis based on the `gateAngle` variable — this is what makes the gate open and close. |
| `drawBooth()` | Draws the toll booth structure using three rectangles: the outer grey booth body, an inner light-blue "window", and a dark grey base/stand — all built using `drawRectangle()`. |
| `display()` | This is the main rendering function, registered with `glutDisplayFunc()`. It is called by GLUT every time the screen needs to be redrawn. It: (1) clears the previous frame with `glClear()`, (2) draws the sky using a color-gradient quad, (3) draws the road and the yellow lane marking, (4) calls `drawBooth()`, `drawGate()`, and `drawCar()` to draw all objects, and (5) calls `glutSwapBuffers()` to display the finished frame smoothly (double buffering, so there's no flickering). |
| `timer(value)` | This is the function responsible for the **animation logic** — it's registered with `glutTimerFunc()` so it runs automatically every 16 milliseconds (~60 times per second). Each time it runs, it: <br>• Moves the car forward (`carX += 1`) if the gate isn't open yet and the car hasn't reached the booth. <br>• Increases `gateAngle` (rotates the gate open) if the gate has been triggered open (`gateOpen == 1`) and it hasn't reached its maximum angle (70°) yet. <br>• Once the gate is fully open, moves the car forward faster (`carX += 2`) so it passes through. <br>• Resets everything (`carX`, `gateOpen`, `gateAngle`) once the car goes off-screen, so the animation loops. <br>• Calls `glutPostRedisplay()` to tell GLUT to redraw the screen with the updated values, and calls itself again via `glutTimerFunc(16, timer, 0)` to keep the animation loop going continuously. |
| `keyboard(key, x, y)` | Handles keyboard input, registered with `glutKeyboardFunc()`. Pressing **`p`** sets `gateOpen = 1` (opens the gate so the timer function starts rotating it). Pressing **`s`** sets `gateOpen = 0` and resets `gateAngle = 0` (closes/stops the gate). Pressing **`r`** resets the entire scene (`carX`, `gateOpen`, `gateAngle`) back to the initial state. After handling the key, it calls `glutPostRedisplay()` to refresh the screen immediately. |
| `init()` | Sets up the initial OpenGL state before rendering starts: `glClearColor()` sets the default background clear color, and `gluOrtho2D()` sets up a 2D orthographic projection/coordinate system (from -500 to 500 on the X-axis and -300 to 300 on the Y-axis), which defines what part of the "world" is visible in the window. |
| `main(argc, argv)` | The entry point of the program. It initializes GLUT (`glutInit`), sets the display mode to double-buffered RGB color (`glutInitDisplayMode`), sets the window size and title (`glutInitWindowSize`, `glutCreateWindow`), calls `init()` to set up the projection, registers the callback functions (`display`, `keyboard`, `timer`), and finally starts the GLUT event loop with `glutMainLoop()`, which keeps the program running and responding to events until the window is closed. |

### B) Built-in OpenGL / GLUT Functions Used

| Function | Purpose |
|---|---|
| `glutInit()` | Initializes the GLUT library — must be called first, before any other GLUT function. |
| `glutInitDisplayMode()` | Chooses the display mode — here, `GLUT_DOUBLE` (double buffering, for smooth animation) and `GLUT_RGB` (color mode). |
| `glutInitWindowSize()` | Sets the width and height of the window (1000 x 600 pixels here). |
| `glutCreateWindow()` | Creates the actual window with the given title. |
| `glutDisplayFunc()` | Registers the function that should be called whenever the window needs to be redrawn (here, `display`). |
| `glutKeyboardFunc()` | Registers the function that handles normal keyboard key presses (here, `keyboard`). |
| `glutTimerFunc()` | Schedules a function to be called after a certain delay in milliseconds — used here to create the continuous animation loop (here, `timer`). |
| `glutPostRedisplay()` | Tells GLUT that the screen needs to be redrawn on the next loop iteration (i.e., marks the current frame as "dirty"). |
| `glutSwapBuffers()` | Swaps the back buffer (just-drawn frame) with the front buffer (currently shown frame) — this is what makes double-buffered animation appear smooth without flickering. |
| `glutMainLoop()` | Starts the main event-processing loop of GLUT; the program stays inside this loop, listening for events (redraw, keyboard, timer) until the window is closed. |
| `glClearColor()` | Sets the RGBA color used when clearing the screen. |
| `glClear(GL_COLOR_BUFFER_BIT)` | Clears the color buffer (the screen) before drawing the next frame. |
| `glColor3f(r, g, b)` | Sets the current drawing color (values from 0.0 to 1.0) for whatever shape is drawn next. |
| `glBegin()` / `glEnd()` | Marks the start and end of defining a shape's vertices — here `GL_QUADS` is used to draw 4-sided shapes (rectangles). |
| `glVertex2f(x, y)` | Defines a single 2D point (corner) of a shape being drawn between `glBegin()`/`glEnd()`. |
| `glPushMatrix()` / `glPopMatrix()` | Saves and restores the current transformation matrix — used so that transformations applied to one object (like the gate) don't affect other objects drawn afterward. |
| `glTranslatef(x, y, z)` | Moves (translates) the coordinate system's origin — used to position the gate's pivot point correctly before rotating it. |
| `glRotatef(angle, x, y, z)` | Rotates the coordinate system around a given axis by a given angle — used to rotate the gate open/closed around the Z-axis. |
| `gluOrtho2D(left, right, bottom, top)` | Sets up a 2D orthographic (flat, no perspective) projection, defining the visible coordinate range of the scene. |

---

## Controls Summary

| Key | Action |
|---|---|
| `p` | Open the gate (car will pass through once fully open) |
| `s` | Stop/close the gate |
| `r` | Reset the scene (car and gate back to start) |

---
