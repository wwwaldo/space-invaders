#include <ncurses.h>
#include <unistd.h>
#include <time.h>


struct ship{
	int x;
	int y;
	bool fwd; // only for enemy ships
	char *repr;
};

struct ship player;
struct ship enemy;
int sc_width = 0; int sc_height = 0;

void init_player(){
	player.x = sc_width / 2;
	player.y = sc_height - 1;
	player.repr = "SHIP";
}

void init_enemy(){
	enemy.x = 1;
	enemy.y = 1;
	enemy.fwd = 1;
	enemy.repr = "X";
	return;
}

// draw the player (you need to clear the screen yourself.)
void mv_player(struct ship *p, int dir){
	if (dir == KEY_LEFT && p->x != 0){
		p->x--;
	} else if (dir == KEY_RIGHT && p->x != sc_width){
		p->x++;
	}
	return;
}

void mv_enemy(struct ship *p){
	if (p->fwd){ // ship moving right to end of screen
		if (p->x != sc_width){
			p->x++;
		} else{
			p->y++;
			p->fwd = 0;
		}
	}
	else if (!p->fwd){ // symmetric -- ship moves left
		if (p->x != 0){
			p->x--;
		} else{
			p->y++;
			p->fwd = 1;
		}
	}
	return;
}

int main(){
initscr();
getmaxyx(stdscr, sc_height, sc_width);

init_player();
init_enemy();

noecho();
keypad(stdscr, TRUE);
nodelay(stdscr, TRUE);
box(stdscr, 0, 0);

clear();
mvprintw(0, 0, "Game will start in 1 seconds");
refresh();
sleep(1);

int key = 0; bool quit = FALSE;
time_t t = time(NULL);
time_t delta = 0;
while(quit != TRUE){
	getmaxyx(stdscr, sc_height, sc_width);

	if (delta > (time_t)1){
		mv_enemy(&enemy);
		t = time(NULL);
		delta = 0;
	}

	// okay, you'll need to make this a nonblocking call later.
	key = getch();
	switch(key){
		case KEY_LEFT:
			mv_player(&player, KEY_LEFT);
			break;
		case KEY_RIGHT:
			mv_player(&player, KEY_RIGHT);
			break;
		case ' ':
			break;
		case 'q':
			quit = TRUE;
		default:
			break;
	}

	clear();
	mvprintw(player.y, player.x, player.repr);
	mvprintw(enemy.y, enemy.x, enemy.repr);
	refresh();

	delta = time(NULL) - t;
 	usleep(33000); // approx. 30fps.
}

endwin();
return 0;

}
