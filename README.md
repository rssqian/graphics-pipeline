# 3D Graphics Pipeline

## Index
1.Source Code
2.How to compile & execute
3.Functions explained

### 1.Source Code
Header file:
    - framebuffer.h
    - model.h
Source file:
    - framebuffer.cpp
    - model.cpp
    - main.cpp

### 2.How to compile & execute
(1) Open Visual Studio 2010 or newer version of Visual Studio.
(2) Add all the header files to the header folder of the solution explorer.
(3) Add all the source files to the source folder of the solution explorer.
(4) Switch the compiling mode to "Release" mode.
(5) Press F5 to start debugging.

### 3.Functions explained
H/h: Show help menu            
M/m: Select model              
UP/DOWN: Rotate along x-axis   
LEFT/RIGHT: Rotate along y-axis
C/c: Toggle back-face culling  
B/b: Toggle background color   
L/l: Toggle lighting mode       
W/w: Toggle wireframe mode     
S/s: Save image                
Q/q: Quit            

*Wireframe mode doesn't display information for depth of the pixel.
*Lighting mode contains three mode: Shading by depth, Flat shading, Smooth shading.
*Some object file doesn't contain normal information for the vertices of triangles, so smooth shading can be weird on some of the models.
