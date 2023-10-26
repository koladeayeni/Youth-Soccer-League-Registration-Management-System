#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include "PlayerEntry.h"
class PlayerList {
public:
    void add(PlayerEntry &x);
    int search(const std::string &term, const char &type);
    int keysearch(const std::string& term, const char& type);

    void read_file(const std::string &file_name);
    void write_file(const std::string &file_name) const;
    void print_players();
    void print_search();
    inline void clear();
    inline int size() { return m_entries_.size(); }
    inline int s_size() { return search_results_.size(); }
    void next();
    void prev();
    void s_next();
    void s_prev();
    void display_search_entry() const;
    void display_entries() const;
    bool edit(const char& option, const std::string& change);
    int current_season = 2022;
    int number_paid = 0;
    int result_number = 1;
    std::string get_U(const int &age);
    bool empty() const { return m_entries_.empty(); }
private:
    std::map<std::string, PlayerEntry> m_entries_;
    std::map<std::string, PlayerEntry>::iterator
        itr_current_entry_;
    std::map<std::string, PlayerEntry> search_results_;
    std::map<std::string, PlayerEntry>::iterator
        itr_current_search_entry_;
};
inline void PlayerList::display_entries() const
{
    if (m_entries_.empty())
        return;
    for (auto itr = m_entries_.begin(); itr != m_entries_.end(); itr++) {
        std::cout << itr->second.age << ' ';
        std::cout << itr->second.fname << ' ';
        std::cout << itr->second.lname << ' ';
        std::cout << itr->second.paid << ' ';
        std::cout << itr->second.category;
        std::cout << std::endl;
    }
}
inline void PlayerList::display_search_entry() const
{
    if (search_results_.empty())
        return;
    std::cout << itr_current_search_entry_->second.age << ' ';
    std::cout << itr_current_search_entry_->second.fname << ' ';
    std::cout << itr_current_search_entry_->second.lname << ' ';
    std::cout << itr_current_search_entry_->second.paid << ' ';
    std::cout << itr_current_search_entry_->second.category;
    std::cout << std::endl;
}
inline void PlayerList::add(PlayerEntry& x) {
   auto result = m_entries_.insert({ x.fname, x });
   itr_current_entry_ = result.first;
}

inline void PlayerList::clear() {
    m_entries_.clear();
    return;
}
