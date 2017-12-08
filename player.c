#include "game.h"

// initialize the player on the SCREEN with default representation.
void init_player(struct player *p){
	p->x = (SCREEN_MAX_W - SCREEN_MIN_W) / 2;
	p->y = SCREEN_MAX_H; // debugging
	p->repr = "M";

	// also initialize the bullet
	p->b = malloc(sizeof(struct bullet));
	p->b->x = p->x;
	p->b->y = p->y;
	p->b->visible = FALSE;
}

// event where the player shoots a bullet.
void player_shoot(struct player *p){
	// TODO
	// update the coordinates of the bullet to the player
	p->b->x = p->x;
	p->b->y = p->y - 1;

	// and set the bullet to be visible
	p->b->visible = TRUE;
	return;
}

// update the bullet position, and also update the fleet if an alien has been
// hit. Return the increase in the score.
int update_bullet(struct player *p, struct fleet *aliens){
	int incr = 0;

	// TODO
	// call this only if the bullet is currently visible

	if (p->b->y < SCREEN_MIN_H){
		p->b->visible = FALSE;
		return incr;
	}

	// update the bullet's position
	p->b->y--;

	if (p->b->visible == TRUE){
		// iterate through the aliens to see if someone has been hit
		// if hit, update alien array and set bullet to invisible
		// also set incr to 100 or whatever you want the score to increase by
		for (int i = 0; i < aliens->fleetsize; i++){
			if (aliens->aliens[i].x == p->b->x && aliens->aliens[i].y == p->b->y){
				if (aliens->aliens[i].hit == FALSE){
					aliens->aliens[i].hit = TRUE;
					p->b->visible = FALSE;
					incr = 100;
					break;
				}
			}
		}
	}

	return incr;
}

// draw the player and their bullet.
void draw_player(WINDOW *game_win, struct player *p){
	mvwprintw(game_win, p->y, p->x, p->repr);
	if (p->b->visible == TRUE){
		mvwprintw(game_win, p->b->y, p->b->x, ".");
	}
	return;
}

// update the player position based on the user's input
void update_player(struct player *p, int dir){
	if (dir == KEY_LEFT && p->x != SCREEN_MIN_W){
		p->x--;
	} else if (dir == KEY_RIGHT && p->x != SCREEN_MAX_W){
		p->x++;
	}
	return;
}
