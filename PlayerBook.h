#ifndef _PlayerList_h_
#define _PlayerList_h_

#include <fstream>
#include <iostream>
#include <map>
#include <string>

#include "PlayerList.h"

const char clear_comm[] = "cls";

class PlayerBook {
public:
	void run();
	bool printing = false;
	bool showing_stats = false;
	bool in_search_view = false;
	std::string error_msg;
private:
	void display_menu();
	void display_search_menu();
	void execute(char choice, bool& finished);
	void search_execute(char choice, bool& finished);
	PlayerList entry_list_;

};
#endif
