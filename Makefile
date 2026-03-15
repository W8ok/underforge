RAYLIB_DIR = ./vendor/raylib
RAYLIB_INCLUDE = $(RAYLIB_DIR)/src
RAYLIB_STATIC = $(RAYLIB_DIR)/libraylib.a

CC = gcc
CFLAGS = -std=c23 -Wall -Wextra -O0 -g -I$(RAYLIB_INCLUDE)
LIBS = $(RAYLIB_STATIC) -lraygui -lpthread -ldl -lm \
		-lX11 -lXrandr -lXinerama -lXi -lXxf86vm -lXcursor \
		-lGL -lGLX -lOpenGL

SRCS := $(shell find src -name "*.c")
OBJS := $(patsubst src/%.c,obj/%.o,$(SRCS))
TARGET = underforge

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

obj/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(TARGET)
	rm -rf obj/

run: $(TARGET)
	./$(TARGET)

debug: $(TARGET)
	gdb ./$(TARGET)

.PHONY: clean run debug
