CC       = g++
CFLAGS   = -c
C11      = -std=c++11
DBGFLAGS = -g
# include OpenGL/freeglut
INC    = -lGL -lGLU -lglut

all:3d-graphics-engine
	@echo -n ""

3d-graphics-engine	: ui.o model.o framebuffer.o main.o transform.o rasterize.o lighting.o
			$(CC) $(INC) ui.o model.o framebuffer.o main.o transform.o rasterize.o lighting.o -o 3d-graphics-engine
transform.o		: src/transform.cpp src/transform.h src/framebuffer.h
			$(CC) $(CFLAGS) $(C11) $< -o $@
rasterize.o		: src/rasterize.cpp src/rasterize.h src/lighting.h src/framebuffer.h
			$(CC) $(CFLAGS) $(C11) $< -o $@
lighting.o		: src/lighting.cpp src/lighting.h src/framebuffer.h
			$(CC) $(CFLAGS) $(C11) $< -o $@
main.o		: src/main.cpp src/ui.h src/model.h src/framebuffer.h
			$(CC) $(CFLAGS) $(C11) $< -o $@
model.o		: src/model.cpp src/model.h
			$(CC) $(CFLAGS) $(C11) $< -o $@
framebuffer.o: src/framebuffer.cpp src/framebuffer.h
			$(CC) $(CFLAGS) $(C11) $< -o $@
ui.o: src/ui.cpp src/ui.h
			$(CC) $(CFLAGS) $(C11) $< -o $@
			
debug:3d-graphics-engine_dbg
	@echo -n ""

3d-graphics-engine_dbg	: model_dbg.o framebuffer_dbg.o main_dbg.o transform_dbg.o rasterize_dbg.o lighting_dbg.o ui_dbg.o
			$(CC) $(INC) model_dbg.o framebuffer_dbg.o main_dbg.o transform_dbg.o rasterize_dbg.o lighting_dbg.o ui_dbg.o -o 3d-graphics-engine_dbg
transform_dbg.o		: src/transform.cpp src/transform.h src/framebuffer.h
			$(CC) $(CFLAGS) $(C11) $(DBGFLAGS) $< -o $@
rasterize_dbg.o		: src/rasterize.cpp src/rasterize.h src/lighting.h src/framebuffer.h
			$(CC) $(CFLAGS) $(C11) $(DBGFLAGS) $< -o $@
lighting_dbg.o		: src/lighting.cpp src/lighting.h src/framebuffer.h
			$(CC) $(CFLAGS) $(C11) $(DBGFLAGS) $< -o $@
main_dbg.o		: src/main.cpp src/model.h src/framebuffer.h src/ui.h
			$(CC) $(CFLAGS) $(C11) $(DBGFLAGS) $< -o $@
model_dbg.o		: src/model.cpp src/model.h
			$(CC) $(CFLAGS) $(C11) $(DBGFLAGS) $< -o $@
framebuffer_dbg.o: src/framebuffer.cpp src/framebuffer.h
			$(CC) $(CFLAGS) $(C11) $(DBGFLAGS) $< -o $@
ui_dbg.o		: src/ui.cpp src/ui.h src/framebuffer.h
			$(CC) $(CFLAGS) $(C11) $(DBGFLAGS) $< -o $@

clean:
	rm -rf *.o 3d-graphics-engine 3d-graphics-engine_dbg

