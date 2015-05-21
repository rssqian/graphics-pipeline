# 3D Graphics Pipeline

A program to read and show given 3D model files (.obj) with rasterization and lighting.

![Program Flow](program-flow.png)

## Index
1. Source Code
2. How to compile & execute
3. Functions explained

### 1. Source Code

makefile	For compiling

src/		Source code
	main.cpp
	framebuffer.h
	framebuffer.cpp
	model.h
	model.cpp

model/		Model files
	quad.obj
	couch.obj
	blaze.obj
	ateneal.obj
	venusm.obj
	bunnyC.obj
	duck4KN.obj
	happy10KN.obj
	dragon10KN.obj
	elephant16KN.obj
	Statue_of_Liberty.obj
	Nissan_Pathfinder.obj

### 2. How to compile & execute

#### Command Line

OpenGL/freeglut is needed to compile the program.
To compile the program, run command:

`make`

And the executable file will appear in the working directory.

To remove the program, run command:

`make clean`

Run the program:

`./3d-graphics-engine`

#### Visual Studio
1. Open Visual Studio 2010 or newer version of Visual Studio.
2. Add all the header files to the header folder of the solution explorer.
3. Add all the source files to the source folder of the solution explorer.
4. Switch the compiling mode to "Release" mode.
5. Press F5 to start debugging.

### 3. Functions explained
- H/h: Show help menu
- M/m: Select model
- UP/DOWN: Rotate along x-axis
- LEFT/RIGHT: Rotate along y-axis
- C/c: Toggle back-face culling
- B/b: Toggle background color
- L/l: Toggle lighting mode
- W/w: Toggle wireframe mode
- S/s: Save image
- Q/q: Quit

#### Notes

* Wireframe mode doesn't display information for depth of the pixel.
* Lighting mode contains three mode: Shading by depth, Flat shading, Smooth shading.
* Some object file doesn't contain normal information for the vertices of triangles, so smooth shading can be weird on some of the models.
