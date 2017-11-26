# sample makefile
# recall  $@ -> left of ":"
# 				$^ -> right of ":"
# 				$< -> just the first thing after ":"

# HEADERS = classes.hpp
HEADERS = game.h

space_invaders: ui.o invaders.o player.o $(HEADERS)
	gcc -g -o $@ $^ -lncurses

# make obj files
%.o : %.c $(HEADERS)
	gcc -g -c $<

clean:
	rm -f *.o
	rm -f space_invaders
