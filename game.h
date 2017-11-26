// Keep track of screen stats.

#ifndef _INVADERS_GAME_H
#define _INVADERS_GAME_H

#include <ncurses.h>
#include <stdlib.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>

// keep track of fixed-size game screen dimensions here. These coords
// are **absolute**, so they are relative to the origin of the terminal screen
// (top-left corner). the aliens and player structs should use these
// to determine their valid xy-coords.
#define SCREEN_MIN_W 15
#define SCREEN_MAX_W 45
#define SCREEN_MIN_H 1 // inverted from math y-coord convention
#define SCREEN_MAX_H 15

// frames per second and alien rate of travel per second
#define _INVADERS_FPS 30
#define _ALIEN_SPEED 10

/************************* ALIEN HEADER FILE INFO **************************/

// some alien string representations
#define ALIEN_DEFAULT "X"
#define ALIEN_RED "\x1b[31mX\x1b[0m" //ANSI color code for RED with RESET (need to test)

// number of aliens in a row
#define ALIEN_MAX_WIDTH 10 // please don't make this less than 1

// structs for the aliens

// array of aliens and some metadata
struct fleet{
	struct alien *aliens; // array to the aliens
	int left_bound; // left bound on ships
	int right_bound; // right bound on ships
	size_t fleetsize; // size of this fleet
};

// a single alien ship
struct alien{
	int x;
	int y;
	bool fwd; // is this alien moving rightwards?
	bool hit; // has this alien been hit?
	char *repr; // what's the string representation of this ship?
};

// fleet function signatures to be called in main game loop
// (the ones not included here are 'private')
void init_fleet(struct fleet *fleet, size_t fleetsize);
void update_bounds(struct fleet *fleet);
void update_fleet(struct fleet *fleet);
void draw_fleet(WINDOW *window, struct fleet *fleet);

/********************* PLAYER HEADER FILE INFO *******************************/

// structs
struct player{
	int x;
	int y;
	char *repr;
	struct bullet *b;
};

// bullet class for interview later
struct bullet{
	int x;
	int y;
	bool visible;
};

void init_player(struct player *p);
void player_shoot(struct player *p);
int update_bullet(struct player *p, struct fleet *aliens);
void draw_player(WINDOW *game_win, struct player *p);
void update_player(struct player *p, int dir);

#endif
