CC      = gcc
CFLAGS  = -Wall -Wextra -std=c99 -Iinclude
SRC     = $(wildcard src/*.c)
OBJ     = $(SRC:src/%.c=build/%.o)
TARGET  = build/smartpark

all: dirs $(TARGET)

dirs:
	mkdir -p build data laporan backup

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $@

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

run: all
	./$(TARGET)

clean:
	rm -rf build/*.o $(TARGET)
