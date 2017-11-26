#include <ncurses.h>
#include <unistd.h>
#include <time.h>
// #include <sys/time.h>
// okay nvm gettimeofday is bugging out


// newer version of main.c to handle faster time tracking

int main(){
initscr();

noecho();
keypad(stdscr, TRUE);
nodelay(stdscr, TRUE);
//box(stdscr, 0, 0);

clear();
mvprintw(0, 0, "Game will start in 1 seconds");
refresh();
sleep(1);


int key = 0;
clock_t dt = 0;
clock_t t = clock();
while(1){

	//if (dt > (CLOCKS_PER_SEC / 2) ){ // ~twice a second
	clear();
	mvprintw(0,0,"CLOCK time is %d, %d", t, t / CLOCKS_PER_SEC);
	refresh();
	usleep(500000);
	t = clock();
	//usleep(1000000); // uhm, wow, is that a lot of cpu consumption...

}

endwin();
return 0;

}
