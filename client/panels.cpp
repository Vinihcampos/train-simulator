#include <curses.h>
#include <panel.h>
#include <menu.h>
#include <mutex>
#include <cstdlib>
#include <sstream>
#include <unistd.h>
#include <thread>
#include <cstring>
#include <map>
#include <iostream>
#include "connection.cpp"
#include "bbb_gpio.cpp"

#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))
#define SERVER_IP "127.0.0.1"

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

char train_enable_desc[7][1024];
char train_vel_desc[7][1024];

// Globals
PANEL * panels[4];
MENU * menus[3];
WINDOW * windows[4];
bool connected = false;
int command = 0;
std::map<PANEL *, int> panels_id;
std::string sleep_time_vel = "200";
int velocity_pot = 10;
std::mutex mtx;
int socket_id;
char * default_message_user = "";
char * messages_user = default_message_user;
char * client_message = "";
std::string server_ip = "127.0.0.1";
std::string cur_speed_window_name;

void write_user_message(char *);
void set_menu_item(MENU * m, WINDOW * winmenu, int nitem, char * name, char * description, void * userptr);

int n_general_choices = ARRAY_SIZE(general_choices);
int n_train_choices = ARRAY_SIZE(train_choices);

// Arrays of functions for each panel
void (*gen_funcs[3])(int);					// Functions for general menu
void (*train_mturn_funcs[3])(int);			// Functions for turn train menu
void (*train_mspeed_funcs[3])(int);		// Functions for train speed menu
void (*train_speed_funcs[3])(int);			// Function for train speed window
//-----------------------------------
// Train turn panel
// ---------------------------------
//--- Itens actions ---//
void turn_train_menu(char * name);
void exit_train_panel(char * name);

//-----------------------------------
// Train menu speed panel
// ---------------------------------
//--- Itens actions ---//
void speed_train_menu(char * name);

/*------------- Functions for each panel ----------------*/
// General panel
//--------------------------------------------------------
//-- Commands --//
void up_general_menu(int);
void down_general_menu(int);
void choose_general_menu(int);

void up_general_menu(int p) {
	menu_driver(menus[p], REQ_UP_ITEM);	
}

void down_general_menu(int p) {
	menu_driver(menus[p], REQ_DOWN_ITEM);	
}

void choose_general_menu(int i) {
	ITEM * cur = (ITEM *) current_item(menus[i]);
	void (*p) (char *) = reinterpret_cast<void (*) (char *)>
		(item_userptr(cur));	
	if (p != nullptr)
		p((char *) item_name(cur));
}
//-- Items actions --//
void connection_management(char * name);
void turn_on_all(char * name);
void turn_off_all(char * name);
void turn(char * name);
void set_speed(char * name);
void exit_client(char * name);

void connection_management(char * name) {
	bool before = connected;

	if (!connected) {
		if ((socket_id = connect_client((char *)server_ip.c_str())) > 0) {
			connected = true;
			general_choices[0] = "Disconnect";
		} else {
			if (socket_id == -1) 
				messages_user = "Socket error.";
			else 
				messages_user = "Connection error.";
			write_user_message(messages_user);
			return;
		} 
			
	} else {
		close(socket_id);
		connected = false;
		general_choices[0] = "Connect";
	}

	if (before != connected) {
		set_menu_item(menus[0],windows[0],0,general_choices[0],general_choices[0],reinterpret_cast<void *>(connection_management));
	}
}

void set_menu_item(MENU * m, WINDOW * winmenu, int nitem, char * name, char * description, void * userptr) {
		ITEM ** items = menu_items(m);
		unpost_menu(m);
		free_item(items[nitem]);
		items[nitem] = new_item(name, description);
		set_item_userptr(items[nitem], reinterpret_cast<void *>(userptr));
		set_menu_items(m, items);
		post_menu(m);
		wrefresh(winmenu);
}

void turn_on_all(char * name) {
	if (!connected) {
		write_user_message("You are not connected to the server.");
		return;
	}
	
	client_message = "ON A";
	if(send(socket_id, client_message, strlen(client_message), 0) == -1) {
		write_user_message("An error occurred.");
	}
}

void turn_off_all(char * name) {
	if (!connected) {
		write_user_message("You are not connected to the server.");
		return;
	}

	client_message = "OFF A";
	if(send(socket_id, client_message, strlen(client_message), 0) == -1) {
		write_user_message("An error occurred.");
	}
}

void turn(char * name) {
	if (!connected) {
		write_user_message("You are not connected to the server.");
		return;
	}

	client_message = "INFO E";
	if(send(socket_id, client_message, strlen(client_message), 0) == -1) {
		write_user_message("An error occurred.");
	}
	char enableinfo[1024];
	int readbytes = recv(socket_id, enableinfo, 1024, 0);
	std::string enableinfos {enableinfo};
	std::stringstream ss {enableinfos};
	std::string s;
	for (int i = 0; i < 7; ++i) {
		ss >> s;
		std::strcpy(train_enable_desc[i], s.c_str());
		set_menu_item(menus[1], windows[1], i, train_choices[i], train_enable_desc[i], reinterpret_cast<void *>(turn_train_menu));
	}
	top_panel(panels[1]);
}

void set_speed(char * name) {
	if (!connected) {
		write_user_message("You are not connected to the server.");
		return;
	}
	client_message = "INFO V";
	if(send(socket_id, client_message, strlen(client_message), 0) == -1) {
		write_user_message("An error occurred.");
	}
	char enableinfo[1024];
	int readbytes = recv(socket_id, enableinfo, 1024, 0);
	std::string enableinfos {enableinfo};
	std::stringstream ss {enableinfos};
	std::string s;
	for (int i = 0; i < 7; ++i) {
		ss >> s;
		std::strcpy(train_vel_desc[i], s.c_str());
		set_menu_item(menus[2], windows[2], i, train_choices[i], train_vel_desc[i], reinterpret_cast<void *>(speed_train_menu));
	}
	top_panel(panels[2]);
}

void exit_client(char * name) {
	command = -1;
	endwin();
}
//-----------------------------------
// Train turn panel
// ---------------------------------
//--- Itens actions ---//
void turn_train_menu(char * name) {
	int i = stoi(std::string(name)) - 1;
	ITEM * c = current_item(menus[1]);
	char * itemdesc = (char *)item_description(c);
	std::string s {itemdesc};
	std::string out;
	if (s == "OFF") {
		out = "ON";
		std::strcpy(train_enable_desc[i], out.c_str());
		out = "ON " + std::string(name);
	} else {
		out = "OFF";
		std::strcpy(train_enable_desc[i], out.c_str());
		out = "OFF " + std::string(name);
	}

	if(send(socket_id,(char *) (out.c_str()), out.size(), 0) == -1) {
		write_user_message("An error occurred.");
	} else {
		set_menu_item(menus[1], windows[1], i, train_choices[i], train_enable_desc[i], reinterpret_cast<void *>(turn_train_menu));
	}
}

void exit_train_panel(char * name) {
	top_panel(panels[0]);
}

//-----------------------------------
// Train menu speed panel
// ---------------------------------
//--- Itens actions ---//
void speed_train_menu(char * name);

void speed_train_menu(char * name) {
	cur_speed_window_name = std::string(name);
	box(windows[3], 0, 0);
	show_panel(panels[3]);
	mvwprintw(windows[3], 0, 0, name);
	wrefresh(windows[3]);
}
//-----------------------------------
// Train speed panel
// ---------------------------------
//-- Commands --//
void speed_window_confirm(int);

void speed_window_confirm(int k) {
	hide_panel(panels[3]);
	wrefresh(windows[3]);
	top_panel(panels[2]);

	ITEM * c = current_item(menus[2]);
	int i = stoi(std::string(item_name(c))) - 1;
	
	std::string curvelpot = std::to_string((int) ((10.0/velocity_pot)*1000));

	//client_message = strcat(strcat("SPEED ", sleep_time_vel.c_str()), name);
	std::string out = "SPEED " + std::to_string(i) + " " + curvelpot;
	if(send(socket_id, out.c_str(), out.size(), 0) == -1) {
		write_user_message("An error occurred.");
	} else {
		std::string velocity_pot_str = std::to_string(velocity_pot);
		std::strcpy(train_vel_desc[i], velocity_pot_str.c_str());
		set_menu_item(menus[2], windows[2], i, train_choices[i], train_vel_desc[i], reinterpret_cast<void *>(speed_train_menu));
	}
}

/* Potentiometer thread
 * ---------------------- */
void potentiometer_update() {
	mtx.lock();
	while (panel_below((PANEL *)0) == panels[3]) {
		double pot_value = readAnalog(5) + 0.0;
		pot_value = pot_value <= 20 ? 20 : pot_value >= 4000 ? 4000 : pot_value;
		double oldMin = 4, oldMax = 4000;
		double newMin = 10, newMax = 1000;
		double new_value_pot = (((pot_value - oldMin)*(newMax-newMin)) / (oldMax-oldMin)) + newMin;
		velocity_pot = new_value_pot;
		sleep_time_vel = std::to_string(velocity_pot);
		werase(windows[3]);
		box(windows[3], 0, 0);
		mvwprintw(windows[3], 0, 0, cur_speed_window_name.c_str());
		mvwprintw(windows[3], 1, 2, sleep_time_vel.c_str());
		wrefresh(windows[3]);
		usleep(100000);
	}
	mtx.unlock();
}

/* Write message at the bottom.
------------------------------------------------*/
void write_user_message(char * message) {
	move(LINES-2,0);
	clrtoeol();
	mvprintw(LINES-2, 0, message);
}

/* Main method.
 -----------------------------------------------*/
int main(int nargs, char * args[]) {

	if (nargs < 2) {
		std::cout << "Error: You must provide an IP address.\n";
		return 0;
	}

	server_ip = std::string(args[1]);

	// Init ncurses
	initscr();
	start_color();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	/*------------ Creating elements -------------*/
	// General menu
	ITEM * * general_items = (ITEM **) calloc(n_general_choices + 1, sizeof(ITEM *));
	for (int i = 0; i < n_general_choices; ++i)
		general_items[i] = new_item(general_choices[i], general_choices[i]);
	general_items[n_general_choices] = (ITEM *) NULL;
	set_item_userptr(general_items[0], reinterpret_cast<void *>(connection_management));
	set_item_userptr(general_items[1], reinterpret_cast<void *>(turn_on_all));
	set_item_userptr(general_items[2], reinterpret_cast<void *>(turn_off_all));
	set_item_userptr(general_items[3], reinterpret_cast<void *>(turn));
	set_item_userptr(general_items[4], reinterpret_cast<void *>(set_speed));
	set_item_userptr(general_items[5], reinterpret_cast<void *>(exit_client));
	menus[0] = new_menu((ITEM * *) general_items);
	windows[0] = newwin(20,50,0,0);
	keypad(windows[0], TRUE);
	set_menu_win(menus[0], windows[0]);
	set_menu_sub(menus[0], derwin(windows[0], 10, 45, 3, 2));
	box(windows[0],0,0);
	post_menu(menus[0]);
	wrefresh(windows[0]);
	panels[0] = new_panel(windows[0]);
	panels_id.insert(std::make_pair(panels[0], 0));
	gen_funcs[DOWN_COMMAND] = down_general_menu;
	gen_funcs[UP_COMMAND] = up_general_menu;
	gen_funcs[CHOOSE_COMMAND] = choose_general_menu;
	set_panel_userptr(panels[0], reinterpret_cast<void *>(gen_funcs));
	
	// Trains menu
	ITEM * * train_turn_items = (ITEM **) calloc(n_train_choices + 1, sizeof(ITEM *));
	ITEM * * train_speed_items = (ITEM **) calloc(n_train_choices + 1, sizeof(ITEM *));
	for (int i = 0; i < n_train_choices; ++i) {
		train_turn_items[i] = new_item(train_choices[i], "ON");
		set_item_userptr(train_turn_items[i], reinterpret_cast<void *>(turn_train_menu));
		train_speed_items[i] = new_item(train_choices[i], "100");
		set_item_userptr(train_speed_items[i], reinterpret_cast<void *>(speed_train_menu));
	}
	set_item_userptr(train_turn_items[7], reinterpret_cast<void *>(exit_train_panel));
	set_item_userptr(train_speed_items[7], reinterpret_cast<void *>(exit_train_panel));
	train_turn_items[n_train_choices] = (ITEM *) NULL;
	train_speed_items[n_train_choices] = (ITEM *) NULL;
	menus[1] = new_menu((ITEM * *) train_turn_items);
	menus[2] = new_menu((ITEM * *) train_speed_items);
	windows[1] = newwin(20,50,0,0);
	windows[2] = newwin(20,50,0,0);
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
	panels_id.insert(std::make_pair(panels[1], 1));
	panels_id.insert(std::make_pair(panels[2], 2));
	set_panel_userptr(panels[1], train_mturn_funcs);
	set_panel_userptr(panels[2], train_mspeed_funcs);
	train_mturn_funcs[DOWN_COMMAND] = down_general_menu;
	train_mturn_funcs[UP_COMMAND] = up_general_menu;
	train_mturn_funcs[CHOOSE_COMMAND] = choose_general_menu;
	train_mspeed_funcs[DOWN_COMMAND] = down_general_menu;
	train_mspeed_funcs[UP_COMMAND] = up_general_menu;
	train_mspeed_funcs[CHOOSE_COMMAND] = choose_general_menu;

	// Speed window
	windows[3] = newwin(5, 20, (LINES-5)/2, (COLS-20)/2);
	box(windows[3], 0, 0);
	keypad(windows[3], TRUE);
	panels[3] = new_panel(windows[3]);
	train_speed_funcs[DOWN_COMMAND] = nullptr;
	train_speed_funcs[UP_COMMAND] = nullptr;
	train_speed_funcs[CHOOSE_COMMAND] = speed_window_confirm;
	set_panel_userptr(panels[3], train_speed_funcs);
	hide_panel(panels[3]);

	top_panel(panels[0]);

	update_panels();
	doupdate();
	refresh();
	/*------------ Main loop ---------------*/
	while (true) {
		PANEL * top = panel_below((PANEL *)0);

		// Throws update potentiometer thread
		if (command == 10 && top == panels[3]) {
			std::thread tupdatepot (potentiometer_update);
			tupdatepot.detach();
		}

		void (**funcs)(int) = reinterpret_cast<void (**)(int)>(const_cast<void *>(panel_userptr(top)));

		// Keyboard press
		//command = wgetch(panel_window(top));

		// Beaglebone press
		bool button_up = false;
		bool button_down = false;
		bool button_choose = false;

		try {
			bbb_button("P9_30", button_up);
			bbb_button("P9_27", button_down);
			bbb_button("P9_23", button_choose);

			if (button_up) {
					if (funcs[DOWN_COMMAND] != nullptr)
						funcs[DOWN_COMMAND](panels_id[top]);
					write_user_message(default_message_user);
			} else if(button_down) {
					if (funcs[UP_COMMAND] != nullptr)
						funcs[UP_COMMAND](panels_id[top]);
					write_user_message(default_message_user);
			} else if(button_choose) {
					command = 10;
					if (funcs[CHOOSE_COMMAND] != nullptr)
						funcs[CHOOSE_COMMAND](panels_id[top]);
			}
		} catch (std::exception & e) {
			write_user_message("Error at reading input from BeagleBone.");
		}

		/*
		switch(command) {	
			case KEY_DOWN: {
					if (funcs[DOWN_COMMAND] != nullptr)
						funcs[DOWN_COMMAND](panels_id[top]);
					write_user_message(default_message_user);
				break;
			}
			case KEY_UP: {
					if (funcs[UP_COMMAND] != nullptr)
						funcs[UP_COMMAND](panels_id[top]);
					write_user_message(default_message_user);
				break;
		    }
			case 10: {
					if (funcs[CHOOSE_COMMAND] != nullptr)
						funcs[CHOOSE_COMMAND](panels_id[top]);
				break;		 
			}
		}*/
		if (command == -1) break;

		top = panel_below((PANEL *)0);
		
		refresh();
		wrefresh(panel_window(top));
		update_panels();
		doupdate();
		
		usleep(200000);
	}

	endwin();
	return 0;
}

