// old main function from invaders.c,
// moved to prevent compiletime errors

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
