!#/bin/bash

gcc -Wall -Wextra -Iinclude src/*.c \
  -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 \
  -o build/dungeon-generator && ./build/dungeon-generator
