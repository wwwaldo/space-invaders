#include "game.h"

// get keyboard input from the user and act accordingly.
void user_response(WINDOW *game_scr, struct player *p){
	int key = wgetch(game_scr);
	switch(key){
		case KEY_LEFT:
			update_player(p, KEY_LEFT);
			break;
		case KEY_RIGHT:
			update_player(p, KEY_RIGHT);
			break;
		case ' ':
			player_shoot(p);
		case 'q': // quit the game
			endwin();
			exit(0);
		default: // Case where no input is provided
			break;
	}
	return;
}

// update the score menu.
void update_score(WINDOW *score_win, int score){
	mvwprintw(score_win, 1, 1, "Press 'q' to quit. YOUR SCORE: %d", score);
}

// display the start menu on mywin.
// seems to bug out when calling on game_win
void display_start_menu(WINDOW *mywin){
	wclear(mywin);
	int win_y = 0; int win_x = 0;
	getmaxyx(mywin, win_y, win_x);

	char *intro_text[5] = {
		"Space Invaders!",
		"Author: Caroline Lin (2017)",
		"Instructions: LEFT and RIGHT arrow keys to move.",
		"Press SPACE to shoot. Press 'q' to quit the game.",
		"Press SPACE to begin the game."
	};

	for (int i = 0; i < 5; i++){
		mvwprintw(mywin, i + (win_y / 2) - 5, (win_x / 2) - 23, "%s", intro_text[i]);
	}

	touchwin(stdscr);
	wrefresh(mywin); // paint the window
	refresh();

	nodelay(mywin, FALSE); // enable block on user input
	int key = 0;
	while(1){
		key = wgetch(mywin);
		if (key == ' '){
			nodelay(mywin, TRUE); // disable block on user input
			return;
		} else if (key == 'q'){
			endwin();
			exit(0);
		}
		sleep(1); // eh?
	}
	assert(0); // not reachable.
}

// check for a game-over. Return TRUE if the end is near.
bool check_game_over(struct player *p, struct fleet *aliens){
	//TODO
	return FALSE;
}

// display the game over menu.
void display_game_over(WINDOW * game_win, int score){
	//TODO
	return;
}


int main(){
	initscr();
	curs_set(FALSE); // turn off the cursor blinking

	int max_y = 0; int max_x = 0;
	getmaxyx(stdscr, max_y, max_x); // get the max window dimensions.
	int smaller = max_y / 8;
	WINDOW *score_win = derwin(stdscr, smaller, max_x, 0, 0);

	// warning: game_win may not correctly display for arbitrary choice
	// of multiplier. 6 is magical here
	WINDOW *game_win = derwin(stdscr, smaller * 6, max_x, 1 + smaller, 0);

	// enable keyboard tracking
 	noecho();
	keypad(game_win, TRUE);

	display_start_menu(game_win);

	// initialize the alien fleet
	struct fleet myfleet;
	size_t fleetsize = 20;
	init_fleet(&myfleet, fleetsize);

	// initialize the player ship
	struct player myship;
	init_player(&myship);

	int myscore = 0;
	int n_frames = 0;
	// main game loop.
	while(1){
		clear();
		touchwin(stdscr); // ready the screen for drawing

		user_response(game_win, &myship); // check for user input

		myscore = myscore + update_bullet(&myship, &myfleet);

		update_bounds(&myfleet); // this should do nothing right now

		if (n_frames >= (_INVADERS_FPS / _ALIEN_SPEED)){
			update_fleet(&myfleet);
			n_frames = 0;
		}

		if (check_game_over(&myship, &myfleet) == TRUE){
			display_game_over(game_win, myscore);
		} else{
			// draw player and fleet
			draw_player(game_win, &myship);
			draw_fleet(game_win, &myfleet);

			box(game_win, '*', '*');
			wrefresh(game_win);

			// update the score
			box(score_win, '|', '-');
			update_score(score_win, myscore);
			wrefresh(score_win);

			n_frames++;
			usleep(1000000 / _INVADERS_FPS);
		}
	}


	endwin();
	return 0;

}
