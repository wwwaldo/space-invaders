# sample makefile
# recall  $@ -> left of ":"
# 				$^ -> right of ":"
# 				$< -> just the first thing after ":"

# HEADERS = classes.hpp
HEADERS =

invaders: main.o
	gcc -g -o $@ $^ -lncurses

# make obj files
%.o : %.c $HEADERS
	gcc -g -c $<

clean:
	rm -f *.o
	rm -f invaders
