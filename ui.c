#include "game.h"

/********************* ASCII assets, heyo! ***********************************/

char *title_text[6] = {
" ____                         ___                     _                ",
"/ ___| _ __   __ _  ___ ___  |_ _|_ ____   ____ _  __| | ___ _ __ ___  ",
"\\___ \\| '_ \\ / _` |/ __/ _ \\  | || '_ \\ \\ / / _` |/ _` |/ _ \\ '__/ __| ",
" ___) | |_) | (_| | (_|  __/  | || | | \\ V / (_| | (_| |  __/ |  \\__ \\ ",
"|____/| .__/ \\__,_|\\___\\___| |___|_| |_|\\_/ \\__,_|\\__,_|\\___|_|  |___/ ",
"      |_|                                                              "
};

char *game_over_banner[6] = {
"  ____                         ___                 ",
" / ___| __ _ _ __ ___   ___   / _ \\__   _____ _ __ ",
"| |  _ / _` | '_ ` _ \\ / _ \\ | | | \\ \\ / / _ \\ '__|",
"| |_| | (_| | | | | | |  __/ | |_| |\\ V /  __/ |   ",
" \\____|\\__,_|_| |_| |_|\\___|  \\___/  \\_/ \\___|_|   ",
"                                                   "
};

char *win_banner[6] = {
"	__     __                               _ 				",
"\\ \\   / /                              | |				",
" \\ \\_/ /__  _   _  __      _____  _ __ | |				",
"  \\   / _ \\| | | | \\ \\ /\\ / / _ \\| '_ \\| |	",
"   | | (_) | |_| |  \\ V  V / (_) | | | |_|				",
"   |_|\\___/ \\__,_|   \\_/\\_/ \\___/|_| |_(_)		"
};

/************************* End ASCII assets ***********************************/

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
			break;
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

	// doing this in the main window
	for (int i = 0; i < 6; i++){
		mvwprintw(stdscr, i + 1, 3, "%s", title_text[i]);
	}

	char *intro_text[4] = {
		"Author: Caroline Lin (2017)",
		"Instructions: LEFT and RIGHT arrow keys to move.",
		"Press SPACE to shoot. Press 'q' to quit the game.",
		"Press SPACE to begin the game."
	};

	for (int i = 0; i < 4; i++){
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
			wclear(mywin); // clear the window now.
			wclear(stdscr);
			refresh();
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
bool check_game_over(struct player *p, struct fleet *fleet){
	bool game_over = FALSE;
	for (int i = 0; i < fleet->fleetsize ; i++){
		if (fleet->aliens[i].y == SCREEN_MAX_H){
			game_over = TRUE;
			break;
		}
	}
	return game_over;
}

// display the game over menu.
void display_game_over(WINDOW * game_win, int score){
	wclear(game_win);
	int win_y = 0; int win_x = 0;
	getmaxyx(game_win, win_y, win_x);

	for (int i = 0; i < 6; i++)
		mvwprintw(game_win, i + 1, (win_x / 2) - 28, "%s", game_over_banner[i]);
	mvwprintw(game_win, SCREEN_MAX_H, (win_x / 2) - 10, "FINAL SCORE: %d", score);

	touchwin(stdscr);
	wrefresh(game_win);

	// yet another check for quit key
	bool quit = FALSE;
	nodelay(game_win, FALSE); // enable block on user input
	int key = 0;
	while(quit == FALSE){
		key = wgetch(game_win);
		if (key == 'q'){
			endwin();
			exit(0);
		}
		sleep(1); // eh?
	}
	return;
}

// check for a win -- ie. if all the aliens are gone.
bool check_win(struct fleet *fleet){
	bool win = TRUE;
	for (int i = 0; i < fleet->fleetsize ; i++){
		if (fleet->aliens[i].hit == FALSE){
			win = FALSE;
			break;
		}
	}
	return win;
}

// display the win menu.
// literally the same as the game over menu, next time just modify the
// display *** menu
void display_win(WINDOW * game_win, int score){
	wclear(game_win);
	int win_y = 0; int win_x = 0;
	getmaxyx(game_win, win_y, win_x);

	for (int i = 0; i < 6; i++)
		mvwprintw(game_win, i + 1, (win_x / 2) - 28, "%s", win_banner[i]);
	mvwprintw(game_win, SCREEN_MAX_H, (win_x / 2) - 10, "FINAL SCORE: %d", score);

	touchwin(stdscr);
	wrefresh(game_win);

	// yet another check for quit key
	bool quit = FALSE;
	nodelay(game_win, FALSE); // enable block on user input
	int key = 0;
	while(quit == FALSE){
		key = wgetch(game_win);
		if (key == 'q'){
			endwin();
			exit(0);
		}
		sleep(1); // eh?
	}
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
		}
		else if (check_win(&myfleet) == TRUE){
			display_win(game_win, myscore);
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
