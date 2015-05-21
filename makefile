CC       = g++
CFLAGS   = -c
C11      = -std=c++11
DBGFLAGS = -g
# include OpenGL/freeglut
INC    = -lGL -lGLU -lglut

all:3dmm_hw1
	@echo -n ""

3dmm_hw1	: model.o framebuffer.o main.o
			$(CC) $(INC) model.o framebuffer.o main.o -o 3dmm_hw1
main.o		: src/main.cpp src/model.h src/framebuffer.h
			$(CC) $(CFLAGS) $(C11) $< -o $@
model.o		: src/model.cpp src/model.h
			$(CC) $(CFLAGS) $(C11) $< -o $@
framebuffer.o: src/framebuffer.cpp src/framebuffer.h
			$(CC) $(CFLAGS) $(C11) $< -o $@
			
debug:3dmm_hw1_dbg
	@echo -n ""

3dmm_hw1_dbg: model_dbg.o framebuffer_dbg.o main_dbg.o
			$(CC) $(INC) model_dbg.o framebuffer_dbg.o main_dbg.o -o 3dmm_hw1_dbg
main_dbg.o	: src/main.cpp src/model.h src/framebuffer.h
			$(CC) $(CFLAGS) $(C11) $(DBGFLAGS) $< -o $@
model_dbg.o	: src/model.cpp src/model.h
			$(CC) $(CFLAGS) $(C11) $(DBGFLAGS) $< -o $@
framebuffer_dbg.o: src/framebuffer.cpp src/framebuffer.h
			$(CC) $(CFLAGS) $(C11) $(DBGFLAGS) $< -o $@

clean:
	rm -rf *.o 3dmm_hw1 3dmm_hw1_dbg

