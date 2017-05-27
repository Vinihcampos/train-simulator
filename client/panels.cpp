#include <curses.h>
#include <panel.h>
#include <menu.h>
#include <cstdlib>
#include <cstring>
#include <iostream>

#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

// Commands constants
const int UP_COMMAND = 0; 
const int DOWN_COMMAND = 1; 
const int CHOOSE_COMMAND = 2; 

// Menu options
char * general_choices[] = {
	"Connect",
	"Turn on all trains",
	"Turn off all trains",
	"Specific Train",
	"Specific Speed Control",
	"Exit"
};

char * train_choices[] = {
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"Exit"
};

// Globals
PANEL * panels[4];
MENU * menus[3];
WINDOW * windows[4];

int n_general_choices = ARRAY_SIZE(general_choices);
int n_train_choices = ARRAY_SIZE(train_choices);

// Functions
void (*gen_funcs[3])(void);					// Functions for general menu
void (*train_mturn_funcs[3])(void);			// Functions for turn train menu
void (*train_mspeed_funcs[3])(void);		// Functions for train speed menu
void (*train_speed_funcs[3])(void);			// Function for train speed window

int main(void) {
	// Init ncurses
	initscr();
	start_color();
	cbreak();
	noecho();

	/*------------ Creating elements -------------*/
	// General menu
	ITEM * * general_items = (ITEM **) calloc(n_general_choices + 1, sizeof(ITEM *));
	for (int i = 0; i < n_general_choices; ++i)
		general_items[i] = new_item(general_choices[i], general_choices[i]);
	general_items[n_general_choices] = (ITEM *) NULL;
	menus[0] = new_menu((ITEM * *) general_items);
	windows[0] = newwin(30,50,0,0);
	keypad(windows[0], TRUE);
	set_menu_win(menus[0], windows[0]);
	set_menu_sub(menus[0], derwin(windows[0], 10, 45, 3, 2));
	box(windows[0],0,0);
	post_menu(menus[0]);
	wrefresh(windows[0]);
	panels[0] = new_panel(windows[0]);
	set_panel_userptr(panels[0], gen_funcs);
	
	// Trains menu
	ITEM * * train_turn_items = (ITEM **) calloc(n_train_choices + 1, sizeof(ITEM *));
	ITEM * * train_speed_items = (ITEM **) calloc(n_train_choices + 1, sizeof(ITEM *));
	for (int i = 0; i < n_train_choices; ++i) {
		train_turn_items[i] = new_item(train_choices[i], "ON");
		train_speed_items[i] = new_item(train_choices[i], "100");
	}
	train_turn_items[n_train_choices] = (ITEM *) NULL;
	train_speed_items[n_train_choices] = (ITEM *) NULL;
	menus[1] = new_menu((ITEM * *) train_turn_items);
	menus[2] = new_menu((ITEM * *) train_speed_items);
	windows[1] = newwin(30,50,0,0);
	windows[2] = newwin(30,50,0,0);
	keypad(windows[1], TRUE);
	keypad(windows[2], TRUE);
	set_menu_win(menus[1], windows[1]);
	set_menu_win(menus[2], windows[2]);
	set_menu_sub(menus[1], derwin(windows[1], 10, 45, 3, 2));
	set_menu_sub(menus[2], derwin(windows[2], 10, 45, 3, 2));
	box(windows[1],0,0);
	box(windows[2],0,0);
	post_menu(menus[1]);
	post_menu(menus[2]);
	wrefresh(windows[1]);
	wrefresh(windows[2]);
	panels[1] = new_panel(windows[1]);
	panels[2] = new_panel(windows[2]);
	set_panel_userptr(panels[1], train_mturn_funcs);
	set_panel_userptr(panels[2], train_mspeed_funcs);

	top_panel(panels[0]);

	update_panels();
	doupdate();
	/*------------ Main loop ---------------*/
	// The key pressed
	int command;

	while (true) {
		command = getch();
		switch(command) {	
			case KEY_DOWN: {
				void (*down)(void) = reinterpret_cast<void(*)(void)>(
						panel_userptr(panel_below((PANEL *)0))[DOWN_COMMAND]); // Top panel
				break;
			}
			case KEY_UP: {
				break;
		    }
			case 10: {
				break;		 
			}
		}
		if (command == -1) break;
		refresh();
	}

	endwin();
	return 0;
}
