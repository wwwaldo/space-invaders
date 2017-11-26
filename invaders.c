#include "game.h" // misc game headers

// voo-doo alien spaceships!
// the number of alien ships can be specified in the call to init_fleet.
// note that there is a "bug" where if there is only a single row of aliens
// which is less than maxlen,

int my_max(int a, int b){
	if (a > b) return a;
	else return b;
}

// update the left and right bounds of the fleet by iterating
// through the current ships. Call this function on each animation loop.
void update_bounds(struct fleet *fleet){
	// at most one ship is destroyed per animation loop, so we only need to
	// check the extrema.

	// iterate through the rows. <= instead of < because '/' operator takes floor
	bool l_vanished = 1;
	for (int i = 0; i <= fleet->fleetsize / ALIEN_MAX_WIDTH; i++){
		int l_survivors = i + (fleet->left_bound - SCREEN_MIN_W);
		if (fleet->aliens[l_survivors].hit == 0){
			l_vanished = 0;
			break;
		}
	}
	if (l_vanished == 1){
		fleet->left_bound++;
	}

	// now handle the right bound -- slightly more complicated
	int r_vanished = 1;
	for (int i = 0; i <= fleet->fleetsize / ALIEN_MAX_WIDTH; i++){
		int r_survivors = i - (fleet->right_bound - SCREEN_MAX_W);
		int rem = fleet->fleetsize - i * ALIEN_MAX_WIDTH;

		if (rem < ALIEN_MAX_WIDTH){ // don't give me a segfault
			r_survivors = r_survivors + my_max(rem - 1, 0);
		} else{
			r_survivors = r_survivors + (ALIEN_MAX_WIDTH - 1);
		}

		// now do the same check as the left
		if (fleet->aliens[r_survivors].hit == 0){
			r_vanished = 0;
			break;
		}
	}
	if (r_vanished == 1){
		fleet->right_bound--;
	}

	assert(fleet->right_bound >= fleet->left_bound); // dummy-check this
	return;
}


// update the position of a single alien (don't draw to the screen.)
void update_alien(struct alien *p, int max_left, int max_right){
	if (p->fwd){ // ship moving right to end of screen
		if (p->x != max_right){
			p->x++;
		} else{
			p->y++;
			p->fwd = 0;
		}
	}
	else if (!p->fwd){ // symmetric -- ship moves left
		if (p->x != max_left){
			p->x--;
		} else{
			p->y++;
			p->fwd = 1;
		}
	}
	return;
}

// move everyone in the fleet over one position.
void update_fleet(struct fleet *fleet){
	for (int i = 0; i < fleet->fleetsize; i++){
		if (fleet->aliens[i].hit == 0){
		int x0 = i % ALIEN_MAX_WIDTH;

		// get the right and left screen bounds for this ship
		int max_right = fleet->right_bound - (ALIEN_MAX_WIDTH - (x0 + 1));
		int max_left = fleet->left_bound + x0;

		update_alien(&(fleet->aliens[i]), max_left, max_right);
		}
	}
	return;
}

// draw the alien fleet. initscr should have already been called.
void draw_fleet(WINDOW *window, struct fleet *fleet){
	for (int i = 0; i < fleet->fleetsize; i++){
		if (fleet->aliens[i].hit == 0){
			mvwprintw(window, fleet->aliens[i].y, fleet->aliens[i].x, fleet->aliens[i].repr);
		}
	}
}


void init_alien(struct alien *p, int x, int y, int mode){
	p->x = x + SCREEN_MIN_W; // load the aliens into the window.
	p->y = y + SCREEN_MIN_H;
	p->hit = 0;
	p->fwd = 1;

	switch(mode){ // add more later.
	default: p->repr = "X";
	}

	return;
}


// initialize the fleet of aliens with size fleetsize.
void init_fleet(struct fleet *fleet, size_t fleetsize){
	fleet->aliens = malloc(sizeof(struct alien) * fleetsize);

	for (int i = 0; i < fleetsize; i++){
		init_alien(&(fleet->aliens[i]), i % ALIEN_MAX_WIDTH, i / ALIEN_MAX_WIDTH, 0);
	}

	fleet->left_bound = SCREEN_MIN_W;
	fleet->right_bound = SCREEN_MAX_W;
	fleet->fleetsize = fleetsize;

	return;
}
