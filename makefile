#بسم الله الرحمن الرحيم

all:
	gcc src/bismi_allah.c submodules/task_tree_lib/bin/task_tree_lib.o `pkg-config --cflags --libs sdl2 SDL2_ttf` -lm -o bin/task_tree


