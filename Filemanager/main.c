#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <sys/wait.h>
#include <unistd.h>
#include <dirent.h>
#include <panel.h>

#define uchar unsigned char

int NLINES = 0;
int NCOLS = 0;
int dY[2];
int ChangeWin = 3;

WINDOW* my_wins[5];
PANEL* my_panels[5];
PANEL* top;

void show_dir(uchar* _absPath, WINDOW* win, int* ddY);
void new_dir(uchar* oldPath, uchar* move, int ddY);
void run_prog(WINDOW* win, uchar* Path, int ddY);

void init_wins(WINDOW **wins, int n);
void win_show(WINDOW *win, char *label, int label_color, int i);
void print_in_middle(WINDOW *win, int starty, int startx, int width, 
                     char *string, chtype color);
void ManagerInit();


int main(void){
    setlocale(LC_ALL, "russian");
    uchar absPath[2][PATH_MAX];
    strcpy(absPath[0], "/");
    strcpy(absPath[1], "/");
  
    int ch=0;
  
    initscr();
    start_color();
    cbreak();
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);

    init_pair(1,  COLOR_YELLOW, COLOR_BLACK);
    init_pair(2,  COLOR_RED,    COLOR_BLACK);
    init_pair(3,  COLOR_BLUE,   COLOR_BLACK);
    init_pair(4,  COLOR_CYAN,   COLOR_BLACK);

    ManagerInit();
    chdir(absPath[0]);
  
    while((ch = getch()) != KEY_F(10)){
        switch(ch){
            case '\t':
                ChangeWin++;
                if(ChangeWin >= 5) {
                    ChangeWin = 3;
                }

                top = (PANEL*)panel_userptr(top);
                top_panel(top);
                wclear(my_wins[ChangeWin]);
                show_dir(absPath[ChangeWin-3], my_wins[ChangeWin], 
                         &dY[ChangeWin-3]);
                wrefresh(my_wins[ChangeWin]);
                break;

            case KEY_DOWN:
                dY[ChangeWin - 3]++;
                wclear(my_wins[ChangeWin]);
                show_dir(absPath[ChangeWin - 3], my_wins[ChangeWin], 
                         &dY[ChangeWin - 3]);
                break;
        
            case KEY_UP:
                dY[ChangeWin - 3]--;
                wclear(my_wins[ChangeWin]);
                show_dir(absPath[ChangeWin - 3], my_wins[ChangeWin], 
                         &dY[ChangeWin - 3]);
                break;

            case KEY_LEFT:
                wclear(my_wins[ChangeWin]);
                new_dir(absPath[ChangeWin - 3], "..", dY[ChangeWin - 3]);
                dY[ChangeWin - 3] = 1;
                show_dir(absPath[ChangeWin - 3], my_wins[ChangeWin], 
                         &dY[ChangeWin - 3]);
                break;
            case KEY_RIGHT:
                wclear(my_wins[ChangeWin]);
                new_dir(absPath[ChangeWin - 3], ".", dY[ChangeWin - 3]);
                dY[ChangeWin - 3] = 1;
                show_dir(absPath[ChangeWin - 3], my_wins[ChangeWin], 
                         &dY[ChangeWin - 3]);
                break;
            case '\n':
                wclear(my_wins[ChangeWin]);
                wrefresh(my_wins[ChangeWin - 3]);
                run_prog(my_wins[ChangeWin], absPath[ChangeWin - 3], 
                         dY[ChangeWin - 3]);
                ManagerInit();
                show_dir(absPath[ChangeWin - 3], my_wins[ChangeWin], 
                         &dY[ChangeWin - 3]);
                break;
        }
        update_panels();
        doupdate();
    }
    endwin();
    return 0;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void ManagerInit(){
    init_wins(my_wins,5);
    my_panels[0] = new_panel(my_wins[0]);
    my_panels[1] = new_panel(my_wins[1]);
    my_panels[2] = new_panel(my_wins[2]);
    my_panels[3] = new_panel(my_wins[3]);
    my_panels[4] = new_panel(my_wins[4]);

    set_panel_userptr(my_panels[3], my_panels[4]);
    set_panel_userptr(my_panels[4], my_panels[3]);
    update_panels();
    attron(COLOR_PAIR(4));
    mvprintw(LINES-2,5,"TAB - Switching between windows, F10 - exit");
    attroff(COLOR_PAIR(4));
    doupdate();
    top = my_panels[3];
    ChangeWin = 3;
}


/* Put all the windows */
void init_wins(WINDOW** wins, int n){	
    int x, y, i;
	char label[80];
	y = 0;
	x = 0;
	
    for(i = 0; i < n; ++i){
    if(i == 0){
      NLINES = LINES;
      NCOLS = COLS;
      y = 0;
      x = 0;
    }
    else if(i == 1){
      NLINES = LINES - 7;
      NCOLS = COLS / 2 - 5;
      y = 3;
      x = 5;
    }
    else if(i == 2){
      NLINES = LINES-7;
      NCOLS = COLS / 2 - 10;
      y = 3;
      x = COLS / 2 + 5;
    }
    else if(i == 3){
      NLINES = LINES - 11;
      NCOLS = COLS / 2 - 9;
      y = 6;
      x = 7;
    }
    else if(i == 4){
      NLINES = LINES - 11;
      NCOLS = COLS / 2 - 14;
      y = 6;
      x = COLS / 2 + 7;
    }
    wins[i] = newwin(NLINES, NCOLS, y, x);
    if(i == 0) sprintf(label, "File manager");
    else if(i == 1) sprintf(label, "Name");
    else if(i == 2) sprintf(label, "Name"); 
    win_show(wins[i], label, i + 1, i);
	}
}

/* Show the window with a border and a label */
void win_show(WINDOW* win, char* label, int label_color, int i){	
    int startx, starty, height, width;

	getbegyx(win, starty, startx);
	getmaxyx(win, height, width);

    if(i >= 0 && i < 3){
	    box(win, 0, 0);
	    mvwaddch(win, 2, 0, ACS_LTEE); 
	    mvwhline(win, 2, 1, ACS_HLINE, width - 2); 
	    mvwaddch(win, 2, width - 1, ACS_RTEE); 

	    print_in_middle(win, 1, 0, width, label, COLOR_PAIR(label_color));
    }
}

void print_in_middle(WINDOW* win, int starty, int startx, int width, 
                     char* string, chtype color)
{	
    int length, x, y;
	float temp;

	if(win == NULL) win = stdscr;
	getyx(win, y, x);
	if(startx != 0) x = startx;
	if(starty != 0)	y = starty;
	if(width == 0)	width = 80;

	length = strlen(string);
	temp = (width - length) / 2;
	x = startx + (int)temp;
	wattron(win, color);
	mvwprintw(win, y, x, "%s", string);
	wattroff(win, color);
	refresh();
}


void show_dir(uchar* _absPath, WINDOW* win, int* ddY){
    int count = 0;
    DIR* d = opendir(_absPath);
    if(d == NULL) return;

    struct dirent* dir;

    while((dir = readdir(d)) != NULL){
        if(dir->d_type == DT_DIR && strcmp(dir->d_name, ".") != 0 && 
            strcmp(dir->d_name, "..") != 0) {
            count++;
            mvwprintw(win, count, 3, "./%s", dir->d_name);
        }
        if(dir->d_type == DT_REG && 
            strcmp(dir->d_name, ".") != 0 && 
            strcmp(dir->d_name, "..") != 0){
            count++;
            mvwprintw(win, count, 3, "%s", dir->d_name);
        }
    }
  
    mvwprintw(win, count+3,1,"%d", *ddY);
    mvwprintw(win, count+4, 1, "%s", _absPath);

    if(*ddY > count) *ddY = count;
    else if(*ddY <= 1) *ddY = 1;

    for(int i = 0; i < count; i++) mvwprintw(win, i,1, "%c", ' ');
  
    mvwprintw(win, *ddY, 1, "%c", '>');
    count = 0;
    closedir(d);
}

void new_dir(uchar* oldPath, uchar* move, int ddY){
    int count = 0;
    DIR* d = opendir(oldPath);
    if(d == NULL) return;
  
    struct dirent* dir;
  
    if(strcmp(move, ".") == 0){
        while((dir = readdir(d)) != NULL){
            if(dir->d_type == DT_DIR && 
                strcmp(dir->d_name, ".") != 0 && 
                strcmp(dir->d_name, "..") != 0){
                count++;
            if(count == ddY){
                sprintf(oldPath, "%s/%s", oldPath, dir->d_name);
                count = 0;
                break;
            }
        }
        if(dir->d_type == DT_REG && 
            strcmp(dir->d_name, ".") != 0 && 
            strcmp(dir->d_name, "..") != 0){
            count++;
        }
    }
  } else {
        unsigned char newPath[PATH_MAX];
        strcpy(newPath, oldPath);
        for(int t = strlen(newPath); t > 1; t--){
            if(newPath[t] != '/') newPath[t] = 0;
            else {
                newPath[t] = 0;
                newPath[t + 1] = 0;
                break;
            }
        }
        strcpy(oldPath, newPath);
  }
  closedir(d);
}

void run_prog(WINDOW* win, uchar* Path, int ddY){
    int count = 0;
    uchar PathToProg[PATH_MAX];
    DIR* d = opendir(Path);
    if(d == NULL){
        return;
    }
    struct dirent* dir;

    while((dir = readdir(d)) != NULL){
        if(dir->d_type == DT_REG && 
            strcmp(dir->d_name, ".") != 0 && 
            strcmp(dir->d_name, "..") != 0){
            count++;
            if(count == ddY){
                sprintf(PathToProg,"%s/%s", Path, dir->d_name);
                count = 0;
                break;
            }
        } else if(dir->d_type == DT_DIR && 
                    strcmp(dir->d_name, ".") != 0 && 
                    strcmp(dir->d_name, "..") != 0){
                    count++;
        }
    }
    endwin();
    closedir(d);
  
    pid_t pid = 0;
    int rv;
    pid = fork();
    if(pid < 0){
        perror("fork");
        return;
    }
    else if(pid == 0){
        execv(PathToProg, NULL);
        exit(rv);
    } else {
        wait(&rv);
    }
}
