#include <curses.h>
#include <menu.h>
#include <cstdlib>
#include <cstring>
#include <iostream>

#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))
#define	CTRLD	4


/* General menu reactions */
void set_connected(char * name);
void all_trains(char * name);
void specific_train(char * name);
void specific_velocity(char * name);
void exit_client( char * name);

/* Turn Train menu reactions */
void turn (char * name, bool on);
void exit_turn_train( char * name,  bool on);

/* Speed train menu reactions */
void change_speed(char * name);

char * choices[] = {
	"Connect",
	"Turn on all trains",
	"Turn off all trains",
	"Specific Train",
	"Specific Speed Control",
	"Exit"
};

ITEM ** gen_items;
int c;
MENU *gen_menu;
int n_choices, i;
ITEM * cur;

bool connected = false;

int main(void) {
	// Init ncurses
	initscr();
	start_color();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_MAGENTA, COLOR_BLACK);

	// Create items
	n_choices = ARRAY_SIZE(choices);
	gen_items = (ITEM**) calloc(n_choices + 1, sizeof(ITEM *));
	for (i = 0; i < n_choices; ++i) {
		gen_items[i] = new_item(choices[i], choices[i]);
	}
	gen_items[n_choices] = (ITEM *) NULL;
	
	// Associate functions
	set_item_userptr(gen_items[0], reinterpret_cast<void *>(set_connected));
	set_item_userptr(gen_items[1], reinterpret_cast<void *>(all_trains));
	set_item_userptr(gen_items[2], reinterpret_cast<void *>(all_trains));
	set_item_userptr(gen_items[3], reinterpret_cast<void *>(specific_train));
	set_item_userptr(gen_items[4], reinterpret_cast<void *>(specific_velocity));
	set_item_userptr(gen_items[5], reinterpret_cast<void *>(exit_client));

	// Create menu
	gen_menu = new_menu((ITEM**) gen_items);

	// Post the menu
	post_menu(gen_menu);
	refresh();

	while(true)
	{       
			c = getch();
			switch(c)
			{       case KEY_DOWN:
							menu_driver(gen_menu, REQ_DOWN_ITEM);
							break;
					case KEY_UP:
							menu_driver(gen_menu, REQ_UP_ITEM);
							break;
					/* ENTER */
					case 10: {
							void (*p) (char *);
							cur = current_item(gen_menu);
							p = reinterpret_cast<void (*)(char *)>(item_userptr(cur));
							p((char *) item_name(cur));				// Call
							//pos_menu_cursor(gen_menu);
							break;
					}
					break;
			}
			if (c == KEY_F(1)) break;
			refresh();
	}       

	endwin();

	return 0;
}

// Trains menu
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

ITEM ** trains_items;
MENU *trains_menu;
int n_train_choices, j;
ITEM * cur_train;

// s = speed, t = turn
void create_train_menu(char purpose) {
	unpost_menu(gen_menu);
	// Create items
	n_train_choices = ARRAY_SIZE(train_choices);
	trains_items = (ITEM**) calloc(n_train_choices + 1, sizeof(ITEM *));
	for (i = 0; i < n_train_choices - 1; ++i) {
		if (purpose == 't') {
			trains_items[i] = new_item(train_choices[i], "ON");
			set_item_userptr(trains_items[i], reinterpret_cast<void *>(turn));
		} else if (purpose == 's') {
			trains_items[i] = new_item(train_choices[i], "100");
			set_item_userptr(trains_items[i], reinterpret_cast<void *>(change_speed));
		}
	}
	trains_items[n_train_choices-1] = new_item(train_choices[n_train_choices-1], "Close");
	set_item_userptr(trains_items[7], reinterpret_cast<void *>(exit_turn_train));
	trains_items[n_train_choices] = (ITEM *) NULL;

	// Create menu
	trains_menu = new_menu((ITEM**) trains_items);

	// Post the menu
	post_menu(trains_menu);

	while(true)
	{       
			c = getch();
			switch(c)
			{       case KEY_DOWN:
							menu_driver(trains_menu, REQ_DOWN_ITEM);
							break;
					case KEY_UP:
							menu_driver(trains_menu, REQ_UP_ITEM);
							break;
					/* ENTER */
					case 10: {
							cur = current_item(trains_menu);
							if (purpose == 't') {
								void (*p) (char *, bool);
								p = reinterpret_cast<void (*)(char *, bool)>(item_userptr(cur));
								p((char *) item_name(cur), true);	// Call
							} else if (purpose == 's') {
								void (*p) (char *);
								p = reinterpret_cast<void (*)(char *)>(item_userptr(cur));
								p((char *) item_name(cur));	// Call
							}
							break;
					}
			}
			if (c == -1) break;
	}

	refresh();
}


/* General menu reactions */
void set_connected(char * name) {
	
	bool before = connected;

	if (!connected) {
		connected = true;
		choices[0] = "Disconnect";
	} else {
		connected = false;
		choices[0] = "Connect";
	}

	if (before != connected) {
		unpost_menu(gen_menu);
		free_item(gen_items[0]);
		gen_items[0] = new_item(choices[0], choices[0]);
		set_item_userptr(gen_items[0], reinterpret_cast<void *>(set_connected));
		set_menu_items(gen_menu, gen_items);
		post_menu(gen_menu);
		refresh();
	}
}

void all_trains(char * name) {

}

void specific_train(char * name) {

	create_train_menu('t');
}

void specific_velocity(char * name) {

	create_train_menu('s');
}

void exit_client(char * name) {
	// Unpost and free
	unpost_menu(gen_menu);
	free_menu(gen_menu);
	for (i = 0; i < n_choices; ++i) 
		free_item(gen_items[i]);
	refresh();
	c = KEY_F(1);
}


/* Train menu reactions */
void turn (char * name, bool on) {



}

void exit_turn_train(char * name, bool on) {
	unpost_menu(trains_menu);
	free_menu(trains_menu);
	for (i = 0; i < n_train_choices; ++i) 
		free_item(trains_items[i]);
	refresh();
	post_menu(gen_menu);
	c = -1;
}

/* Speed train menu reactions */
void change_speed(char * name) {


}

