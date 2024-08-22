# this makefile compiles all files in dir src/

FLAGS = -Wpointer-compare $(shell pkg-config --cflags gtk4)
LIBS = $(shell pkg-config --libs gtk4) -lcurl

CC = gcc
# СС = llvm-gcc

EXCLUDE_FILES :=

SRCS := $(filter-out $(EXCLUDE_FILES), $(wildcard src/*.c))
OBJS := $(patsubst src/%.c, build/obj/%.o, $(SRCS))

all: install

install: equity-viewer

equity-viewer: $(OBJS)
	$(CC) -O3 $(FLAGS) -o $@ $^ $(LIBS)

build/obj/%.o: src/%.c src/*.h | build/obj
	$(CC) $(FLAGS) -c $< -o $@

build/obj:
	mkdir -p build/obj

run: equity-viewer
	./equity-viewer

clean:
	rm -f build/obj/*.o eqiuty-viewer