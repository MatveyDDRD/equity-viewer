# this makefile compiles all files in dir src/

FLAGS = -Wpointer-compare -Icjson $(shell pkg-config --cflags gtk4)
LIBS = $(shell pkg-config --libs gtk4) -lcurl

CC = gcc

SRCS := $(wildcard src/*.c) cjson/cJSON.c
OBJS := $(patsubst src/%.c, build/obj/%.o, $(SRCS))
OBJS := $(OBJS:cjson/%.c=build/obj/%.o)

all: install

install: equity-viewer

equity-viewer: $(OBJS)
	$(CC) -O3 $(FLAGS) -o $@ $^ $(LIBS)

build/obj/%.o: src/%.c | build/obj
	$(CC) $(FLAGS) -c $< -o $@

build/obj/cJSON.o: cjson/cJSON.c | build/obj
	$(CC) $(FLAGS) -c $< -o $@

build/obj:
	mkdir -p build/obj

run: equity-viewer
	./equity-viewer

clean:
	rm -f build/obj/*.o equity-viewer
