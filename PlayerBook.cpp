#include "PlayerBook.h"
using namespace std;

void PlayerBook::run() {
	bool finished = false;
	while (!finished) {
		if (in_search_view == false) {
			display_menu();
			cout << "option:";
			char choice;
			cin >> choice;
			cin.get();
			execute(choice, finished);
			cout << endl;
		}
		if (in_search_view) {
			display_search_menu();
			cout << "option:";
			char s_choice;
			cin >> s_choice;
			cin.get();
			search_execute(s_choice, finished);
		}
	}
}
void PlayerBook::display_search_menu() {
	string long_sep(50, '-');
	string short_sep(20, '-');
	system(clear_comm);
	if (!error_msg.empty()) {
		cout << error_msg << endl;
	}
	cout << "Search View " << entry_list_.current_season << endl;
	cout << "Showing Result " << entry_list_.result_number << "/" << entry_list_.s_size() << endl;
	if (printing) {
		entry_list_.print_search();
	}
	else {
		entry_list_.display_search_entry();
	}
	cout << long_sep << endl
		<< "  (n)ext      (b)previous  (e)dit players    (q)uit\n"
		<< "  (s)earch (x)exit search     (p)rint players\n"
		<< short_sep << endl;
	}
	void PlayerBook::display_menu() {
		entry_list_.number_paid = 0;
		entry_list_.read_file("playerbook.txt");
		string long_sep(50, '-');
		string short_sep(20, '-');
		system(clear_comm);
		if (!error_msg.empty()) {
			cout << error_msg << endl;;
		}
		cout << "Main View " << entry_list_.current_season << endl;
		if (showing_stats) {
			cout << "total number of players: " << entry_list_.size() << endl;
			cout << "total paid: " << entry_list_.number_paid << endl;
		}
		if (printing) {
			//entry_list_.print_players();
			entry_list_.display_entries();
		}
			cout << long_sep << endl
			<< "  (n)ew Season      (s)earch for player  (p)rint players    (q)uit\n"
			<< "  (a)dd a player     (d)isplay stats\n"
			<< short_sep << endl;
	}
	void PlayerBook::search_execute(char choice, bool& finished){
		switch (choice) {
		case 's': {
			char type;
			string term;
			cout << "search for what? (f)irst name, (l)ast name, (a)ge, (p)ayment status, (c)ategory" << endl;
			cin >> type;
			cin.get();
			cout << endl << "Search Term?" << endl;
			getline(cin, term);
				if (entry_list_.search(term, type) != 0) {
					in_search_view = true;
					printing = false;
					showing_stats = false;
					entry_list_.result_number = 1;
				}
				else {
					error_msg = "error!: no search results";
				}
			break;
		}
		case 'n': {
			entry_list_.s_next();
			break;
		}
		case 'b': {
			entry_list_.s_prev();
			break;
		}
		case 'q': {
			entry_list_.write_file("playerbook.txt");
			finished = true;
			break;
		}
		case 'e': {
			char option;
			string change;
			cout << "Edit what? (f)irst name, (a)ge, (p)ayment status, (c)ategory" << endl;
			cin >> option;
			cin.get();
			cout << "Change to what?" << endl;
			getline(cin, change);
			if (entry_list_.edit(option, change) == false) {
				error_msg = "error!: could not edit player";
			}
			break;
		}
		case 'x': {
			in_search_view = false;
			printing = false;
			break;
		}
		case 'p': {
			printing = true;
			break;
		}
		}
	}
	void PlayerBook::execute(char choice, bool& finished) {
		error_msg.clear();
		switch (choice) {
		case 'n': {
			int year;
			char yn;
			cout << "Are you sure you want to start a new season? ALL DATA WILL BE DELETED (y/n)" << endl;
			cin >> yn;
			cin.get();
			if (yn == 'y') {
				cout << "year:";
				cin >> year;
				entry_list_.current_season = year;
				entry_list_.clear();
				entry_list_.write_file("playerbook.txt");
				printing = false;
				break;
			}
			else {
				break;
			}
		}
		case 's': {
			char type;
			string term;
			char yorn;
			cout << "search for what? (f)irst name, (l)ast name, (a)ge, (p)ayment status, (c)ategory" << endl;
				cin >> type;
				cin.get();
				cout << endl << "Search Term?" << endl;
				getline(cin, term);
				cout << "Is that a keyword? (y/n)" << endl;
				cin >> yorn;
				cin.get();
				if (yorn != 'y') {
					if (entry_list_.search(term, type) != 0) {
						in_search_view = true;
						printing = false;
						showing_stats = false;
					}
					else {
						error_msg = "error!: no search results";
					}
				}
				else {
				if (entry_list_.keysearch(term, type) != 0) {
					in_search_view = true;
					printing = false;
					showing_stats = false;
					entry_list_.result_number = 1;
				}
				else {
					error_msg = "error!: no search results";
				}
			}
				break;
			/*cout << "name:";
			string name;
			getline(cin, name);
			if (entry_list_.find(name)) {
				in_search_view = true;
				printing = false;
			}
			else {
				error_msg = "error!: no search results";
			}
			break;*/
		}
		case 'a': {
			PlayerEntry x;
			string temp;
			cout << "first name:";
			getline(cin, x.fname);
			cout << "last name: ";
			getline(cin, x.lname);
			cout << "yob:";
			getline(cin, x.age);
			cout << "paid?(y/n):";
			getline(cin, temp);
			if (temp == "y") {
				temp = "paid";
				x.paid = temp;
			}
			else if (temp == "n") {
				temp = "unpaid";
				x.paid = temp;
			}
			else {
				error_msg = "error!: paid was undetermined";
				break;
			}
			temp = entry_list_.get_U(stoi(x.age));
			if (temp != "fail") {
				x.category = temp;
				entry_list_.add(x);
			}
			else {
				error_msg = "error!: player was too old or too young";
			}
			break;
		}
		case 'q': {
			entry_list_.write_file("playerbook.txt");
			finished = true;
			break;
		}
		case 'p': {
			printing = true;
			break;
		}
		case 'd': {
			showing_stats = true;
			break;
		}
		}
	}