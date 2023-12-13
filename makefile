#بسم الله الرحمن الرحيم

all:
	gcc src/main.c src/task_tree_ui.c submodules/task_tree_lib/bin/task_tree_lib.o `pkg-config --cflags gtk4` `pkg-config --libs gtk4` -o bin/main


