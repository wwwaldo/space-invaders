#include <ncurses.h>
#include <unistd.h>

void update_score(WINDOW *score_win, int score){
	mvwprintw(score_win, 1, 1, "Press 'q' to quit. YOUR SCORE: %d", score);
}


int main(){
	initscr();
	curs_set(FALSE); // turn off the cursor blinking

	int max_y = 0; int max_x = 0;
	getmaxyx(stdscr, max_y, max_x); // get the max window dimensions.
	WINDOW *score_win = derwin(stdscr, max_y / 8, max_x, 0, 0);
	WINDOW *game_win = derwin(stdscr, (max_y / 8) * 7, max_x, 1 + (max_y / 8), 0);

	// enable keyboard tracking
 	noecho();
	keypad(game_win, TRUE);

	while(1){
	clear();
	touchwin(stdscr);

	box(score_win, '|', '-');
	update_score(score_win, 0);

	box(game_win, '*', '*');

	// update the game window here 

	wrefresh(score_win);

	touchwin(stdscr);
	wrefresh(game_win);

	usleep(500000);
}

	sleep(10);


	endwin();
	return 0;

}


/**
int main(){
	initscr();
	box(stdscr, '*', '*');
	refresh();
	noecho();
	keypad(stdscr, TRUE);
	// nodelay(stdscr, TRUE);

	// okay, let's try to make a box here
	// WINDOW *subwin(WINDOW *orig, int nlines, int ncols, int begin_y, int begin_x);
	WINDOW *game = subwin(stdscr, 0, 0, 2, 0);
	// clear the screen
	mvprintw(0, 0, "Game will start in 1 seconds");
	refresh();
	sleep(1);
	clear();

	struct fleet myfleet;
	size_t fleetsize = 20;
	init_fleet(&myfleet, fleetsize);

	bool quit = FALSE;
	bool msg = FALSE;
	int key = 0;
	while(quit == FALSE){
		update_bounds(&myfleet);

		key = getch();
		if (key == 'q'){
			quit = TRUE;
		}
		else if (key == ' '){
			update_fleet(&myfleet);
		} else{
			msg = TRUE;
		}

		clear();
		box(stdscr, '|', '-');

		touchwin(stdscr); // yay inefficiency
		box(game, '*', '*'); // box for the game
		wrefresh(game);

		mvprintw(SCREEN_MIN_H +10, SCREEN_MIN_W, "*"); //include borders
		mvprintw(SCREEN_MIN_H + 10, SCREEN_MAX_W, "*");
		mvprintw(SCREEN_MIN_H - 1, 0, "leftbd: %d rightbd: %d", myfleet.left_bound, myfleet.right_bound);
		if (msg == TRUE){
			mvprintw(0, 0, "Invalid key");
			msg = FALSE;
		}
		draw_fleet(&myfleet);
		refresh();

	}
endwin();
return 0;

}**/
