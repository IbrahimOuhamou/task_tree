#بسم الله الرحمن الرحيم

all:
	gcc src/main.c submodules/task_tree_lib/bin/task_tree_lib.o src/ui_view_focus.c `pkg-config --cflags gtk4` `pkg-config --libs gtk4` -o bin/main


