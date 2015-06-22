CC       = g++
CFLAGS   = -c
C11      = -std=c++11
DBGFLAGS = -g
# include OpenGL/freeglut
INC    = -lGL -lGLU -lglut -lIL

all:3d-graphics-engine
	@echo -n ""

3d-graphics-engine	: ui.o model.o framebuffer.o main.o transform.o rasterize.o lighting.o material.o texture.o
			$(CC) $(INC) ui.o model.o framebuffer.o main.o transform.o rasterize.o lighting.o material.o texture.o -o 3d-graphics-engine
transform.o		: src/transform.cpp src/transform.h src/framebuffer.h
			$(CC) $(CFLAGS) $(C11) $< -o $@
rasterize.o		: src/rasterize.cpp src/rasterize.h src/lighting.h src/framebuffer.h
			$(CC) $(CFLAGS) $(C11) $< -o $@
lighting.o		: src/lighting.cpp src/lighting.h src/framebuffer.h
			$(CC) $(CFLAGS) $(C11) $< -o $@
texture.o		: src/texture.cpp src/texture.h src/material.h src/framebuffer.h
			$(CC) $(CFLAGS) $(C11) $< -o $@
material.o		: src/material.cpp src/material.h
			$(CC) $(CFLAGS) $(C11) $< -o $@
main.o		: src/main.cpp src/ui.h src/model.h src/framebuffer.h
			$(CC) $(CFLAGS) $(C11) $< -o $@
model.o		: src/model.cpp src/model.h
			$(CC) $(CFLAGS) $(C11) $< -o $@
framebuffer.o: src/framebuffer.cpp src/framebuffer.h
			$(CC) $(CFLAGS) $(C11) $< -o $@
ui.o: src/ui.cpp src/ui.h src/lighting.h
			$(CC) $(CFLAGS) $(C11) $< -o $@
			
clean:
	rm -rf *.o 3d-graphics-engine
