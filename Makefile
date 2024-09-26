# this makefile compiles all files in dir src/

CC = gcc
CFLAGS = -Wpointer-compare -O3 -Icjson $(shell pkg-config --cflags gtk4)
LDFLAGS = $(shell pkg-config --libs gtk4) -lcurl

SRCS := $(wildcard src/*.c) cjson/cJSON.c
OBJS := $(patsubst src/%.c, build/obj/%.o, $(SRCS))
OBJS := $(OBJS:cjson/%.c=build/obj/%.o)

all: equity-viewer

equity-viewer: $(OBJS)
	$(CC) $(OBJS) -o $@ $(LDFLAGS)

build/obj/%.o: src/%.c | build/obj
	$(CC) $(CFLAGS) -c $< -o $@

build/obj/cJSON.o: src/cjson/cJSON.c | build/obj
	$(CC) $(CFLAGS) -c $< -o $@

build/obj:
	mkdir -p build/obj

run: equity-viewer
	./equity-viewer

clean:
	rm -f build/obj/*.o equity-viewer
