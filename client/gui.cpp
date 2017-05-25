#include <curses.h>
#include <menu.h>
#include <cstdlib>
#include <cstring>
#include <functional>

#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))
#define	CTRLD	4

char * choices[] = {
	"Connect",
	"All Trains",
	"Specific Train",
	"Specific Speed Control",
	"Exit",
	(char *) NULL
};

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);

void set_connected(char * name);
void all_trains(char * name);
void specific_train(char * name);
void specific_velocity(char * name);

int main(void) {

	ITEM ** gen_items;
	int c;
	MENU *gen_menu;
	WINDOW *gen_menu_win;
	int n_choices, i;

	// Init ncurses
	initscr();
	start_color();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	init_pair(1, COLOR_RED, COLOR_BLACK);

	// Create items
	n_choices = ARRAY_SIZE(choices);
	gen_items = (ITEM**) calloc(n_choices, sizeof(ITEM *));
	for (i = 0; i < n_choices; ++i) {
		gen_items[i] = new_item(choices[i], choices[i]);
	}
	
	// Associate functions
	set_item_userptr(gen_items[0], set_connected);
	set_item_userptr(gen_items[1], all_trains);
	set_item_userptr(gen_items[2], specific_train);
	set_item_userptr(gen_items[3], specific_velocity);
	set_item_userptr(gen_items[4], specific_velocity);

	// Create menu
	gen_menu = new_menu((ITEM**) gen_items);

	// The window to be linked to the general menu
	gen_menu_win = newwin(10, 40, 4, 4);
	keypad(gen_menu_win, TRUE);
	set_menu_win(gen_menu, gen_menu_win);
	set_menu_sub(gen_menu, derwin(gen_menu_win, 6, 38, 3, 1));
	set_menu_mark(gen_menu, " * ");
	box(gen_menu_win, 0, 0);
	print_in_middle(gen_menu_win, 1, 0, 40, "My Menu", COLOR_PAIR(1));
	refresh();

	// Post the menu
	post_menu(gen_menu);
	wrefresh(gen_menu_win);

	while((c = wgetch(gen_menu_win)) != KEY_F(1))
	{       switch(c)
			{       case KEY_DOWN:
							menu_driver(gen_menu, REQ_DOWN_ITEM);
							break;
					case KEY_UP:
							menu_driver(gen_menu, REQ_UP_ITEM);
							break;
			}
			wrefresh(gen_menu_win);
	}       

	// Unpost and free
	unpost_menu(gen_menu);
	free_menu(gen_menu);
	for (i = 0; i < n_choices; ++i) 
		free_item(gen_items[i]);
	endwin();

}

void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color)
{       int length, x, y;
        float temp;
        if(win == NULL)
                win = stdscr;
        getyx(win, y, x);
        if(startx != 0)
                x = startx;
        if(starty != 0)
                y = starty;
        if(width == 0)
                width = 80;
        length = strlen(string);
        temp = (width - length)/ 2;
        x = startx + (int)temp;
        wattron(win, color);
        mvwprintw(win, y, x, "%s", string);
        wattroff(win, color);
        refresh();
}

void set_connected(char * name) {

}

void all_trains(char * name) {

}

void specific_train(char * name) {

}

void specific_velocity(char * name) {

}


