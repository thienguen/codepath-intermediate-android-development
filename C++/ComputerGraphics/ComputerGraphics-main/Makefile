CXX:= g++
SDL2_CFLAGS:= $(shell pkg-config sdl2 --cflags)
SDL2_LIBS:= $(shell pkg-config sdl2 --libs)
CXXFLAGS:= -g -O0 -std=c++20 -Wall -Wextra -pedantic -Werror -Wshadow -Wconversion -fmax-errors=3 -fsanitize=address

BINS:= mandelbrot life sand rotating_cube emitter explode scrolling sort

.PHONY: all clean

all: $(BINS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(SDL2_CFLAGS) -c -o $@ $<

$(BINS): %: %.o
	$(CXX) $(CXXFLAGS) $(LIBS) $(SDL2_LIBS) -o ./bin/$@.out $<

clean:
	rm -f -- *.o
delete:
	rm -f -- ./bin/*.out
