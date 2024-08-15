# this makefile compiles all files in dir src/

FLAGS = -Wpointer-integer-compare $(shell pkg-config --cflags gtk4)
LIBS = $(shell pkg-config --libs gtk4)

# CC = gcc
СС = llvm-gcc

EXCLUDE_FILES :=

SRCS := $(filter-out $(EXCLUDE_FILES), $(wildcard src/*.c))
OBJS := $(patsubst src/%.c, build/obj/%.o, $(SRCS))

all: install

install: eqiuty-viewer

eqiuty-viewer: $(OBJS)
	$(CC) -O3 $(FLAGS) -o $@ $^ $(LIBS)

build/obj/%.o: src/%.c src/*.h | build/obj
	$(CC) $(FLAGS) -c $< -o $@


build/obj:
	mkdir -p build/obj

run: eqiuty-viewer
	./eqiuty-viewer

clean:
	rm -f build/obj/*.o eqiuty-viewer