#include <termios.h>
#include <sys/ioctl.h>
#include <signal.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#define MAX_SIZE 50

WINDOW* btmwnd;
int row = 0, col = 0, line = 0, fd, w, h;
char filename[MAX_SIZE];

void sig_winch(int signo){
	struct winsize size;
	ioctl(fileno(stdout), TIOCGWINSZ, (char *) &size);
	resizeterm(size.ws_row, size.ws_col);
}

void start(){
	start_color();
	refresh();
	echo();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	btmwnd = newwin(1, w, h-3, 0);
	wbkgd(btmwnd, COLOR_PAIR(1));
	wprintw(btmwnd, " <F1> - Open file  <F2> - Save changes  <F3> - exit\t");
	wrefresh(btmwnd);
}

int len(int lineno){
	int linelen = COLS - 1;
	while (linelen >= 0 && mvinch(lineno, linelen) == ' ')
	linelen--;
	return linelen + 1;
}

void openfile(){
    WINDOW* win;
	char c;
	refresh();
	echo();
	
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
 	win = newwin(1, MAX_SIZE, h - 5, 0);
	wattron(win, COLOR_PAIR(1));
    wprintw(win, "Filename: ");
	wgetnstr(win, filename, MAX_SIZE);
    	
	wrefresh(win);
	delwin(win);
	clear();
	start();
	fd = open(filename, O_RDONLY);
		if( fd == -1 ){
		    endwin();
		    perror("openfile()");
		    exit(EXIT_FAILURE);
		}
        
	while(1){
		if(read(fd, &c, 1) == 1){
		    addch(c);
		    if(c == '\n'){
		        line ++;
		    }
		} else break;
	}  
	close(fd);
}

void savech() {
	fd = open(filename, O_WRONLY | O_TRUNC);
		if(fd < 0){
		    endwin();
		    perror("savech()");
		    exit(EXIT_FAILURE);
		}
    int length;
    char c;
	for(int i = 0; i < LINES - 4; i ++){
	    length = len(i);
		    for(int j = 0; j < length; j ++){
		        c = mvinch(i, j) & A_CHARTEXT;
		        write(fd, &c, 1);
		    }
	    write(fd, "\n", 1);
	}
    close(fd);
}

void keypad_func(){
    noecho();
    int ch = getch();

	switch(ch){	
		
		case KEY_UP:
		    if (row > 0) row --;
	        break;

		case KEY_DOWN:
		    row ++;
	        break;

		case KEY_LEFT:
		    if (col > 0) col --;
	        break;

		case KEY_RIGHT:
		    col ++;
	        break;

		case KEY_F(1):
		    openfile(O_RDONLY);
	        break;

		case KEY_F(2):
		    savech();
	        break;

		case KEY_F(3):
		    close(fd);
		    delwin(btmwnd);
		    endwin();
		    exit(EXIT_SUCCESS);
	        break;
		case KEY_BACKSPACE:
		    if(col >= 0){
		        delch();
		        col --;
		    }
		    if (col < 0){
		        col ++;
		    }
	        break;

		default:
		    insch(ch);
		    move(row, col ++);
		    refresh();
	    break;
	}
}

int main(int argc, char ** argv){
	initscr();
	signal(SIGWINCH, sig_winch);
	keypad(stdscr, TRUE);

	w=getmaxx(stdscr);
	h=getmaxy(stdscr);

	start();

	while(1){
		move(row, col);
		refresh();
		keypad_func();
	}

	delwin(btmwnd);
	endwin();
    exit(EXIT_SUCCESS);
}
