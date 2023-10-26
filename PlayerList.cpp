#include "PlayerList.h"
//void PlayerList::read_file(const std::string& name) {
//std::ifstream in(name);
//PlayerEntry temp;
//while (in >> temp) {
//    m_entries_.insert({ temp.name, temp });
//}
//in.close();
//}
void PlayerList::read_file(const std::string& file_name) {
    std::fstream in(file_name);
    int num_entries;
    in >> current_season;
    in.get();
    in >> num_entries;
    in.get(); // \n
    for (int i = 0; i < num_entries; i++) {
        PlayerEntry new_entry;
        in >> new_entry;
        if (new_entry.paid == "paid") {
            ++number_paid;
        }
        m_entries_.insert(m_entries_.end(),
            { new_entry.fname, new_entry });
    }
    itr_current_entry_ = m_entries_.begin();
}
void PlayerList::write_file(const std::string& file_name) const 
{
    std::ofstream out(file_name);
    out << current_season<< std::endl;
    out << m_entries_.size() << std::endl;
    for (auto itr = m_entries_.begin(); itr != m_entries_.end(); itr++) {
        out << itr->second;
    }
    out.close();
}
void PlayerList :: next() {
    if (itr_current_entry_ == (--m_entries_.end())) {
        itr_current_entry_ = m_entries_.begin();
    }
    else {
        itr_current_entry_++;
    }
}
void PlayerList:: prev() {
    if (itr_current_entry_ == m_entries_.begin()) {
        itr_current_entry_ = (--m_entries_.end());
    }
    else {
        itr_current_entry_--;
    }
}
void PlayerList::s_next() {
    if (itr_current_search_entry_ == (--search_results_.end())) {
        itr_current_search_entry_ = search_results_.begin();
        result_number = 1;
    }
    else {
        itr_current_search_entry_++;
        result_number++;
    }
}
void PlayerList::s_prev() {
    if (itr_current_search_entry_ == search_results_.begin()) {
        itr_current_search_entry_ = (--search_results_.end());
        result_number = search_results_.size();
    }
    else {
        itr_current_search_entry_--;
        result_number--;
    }
}
void PlayerList::print_players() {
    int count = 0;
    for (count; count < m_entries_.size(); count++) {
        std::cout << itr_current_entry_->second;
        itr_current_entry_++;
    }
    for (int i = 0; i < count; i++) {
        itr_current_entry_--;
    }
}
void PlayerList::print_search() {
   /* int count = 0;
    for (count; count < search_results_.size(); count++) {
        std::cout << itr_current_search_entry_->second;
        itr_current_search_entry_++;
    }
    for (int i = 0; i < count; i++) {
        itr_current_search_entry_--;
    }*/
    for (auto itr = search_results_.begin(); itr != search_results_.end(); itr++) {
        std::cout << itr->second;
    }
}
std::string PlayerList::get_U(const int &age) {
    std::string U = "U";
    std::string year = std::to_string(current_season - age);
    if (stoi(year) < 4) {
        return "fail";
    }
    else if (stoi(year) < 6) {
        year = "6";
    }
    else if (stoi(year) < 8) {
        year = "8";
    }
    else if (stoi(year) < 10) {
        year = "10";
    }
    else if (stoi(year) < 12) {
        year = "12";
    }
    else if (stoi(year) < 14) {
        year = "14";
    }
    else
    return "fail";
    return (U+year);
}
int PlayerList::search(const std::string& term, const char& type) {
    int count = 0;
    search_results_.clear();
    switch (type) {
    case 'f': {
        for (auto itr = m_entries_.begin(); itr != m_entries_.end(); itr++) {
            if (itr->second.fname == term) {
                search_results_.insert(*itr);
                //if (count == 0)
                count++;
            }
        }
        itr_current_search_entry_ = search_results_.begin();
        return count;
        break;
    }
    case 'l': {
        for (auto itr = m_entries_.begin(); itr != m_entries_.end(); itr++) {
            if (itr->second.lname == term) {
                search_results_.insert(*itr);
                //if (count == 0)
                count++;
            }
        }
        itr_current_search_entry_ = search_results_.begin();
        return count;
        break;
    }
    case 'a': {
        for (auto itr = m_entries_.begin(); itr != m_entries_.end(); itr++) {
            if (itr->second.age == term) {
                search_results_.insert(*itr);
                //if (count == 0)
                count++;
            }
        }
        itr_current_search_entry_ = search_results_.begin();
        return count;
        break;
    }
    case 'p': {
        for (auto itr = m_entries_.begin(); itr != m_entries_.end(); itr++) {
            if (itr->second.paid == term) {
                search_results_.insert(*itr);
                //if (count == 0)               
                count++;
            }
        }
        itr_current_search_entry_ = search_results_.begin();
        return count;
        break;
    }
    case 'c': {
        for (auto itr = m_entries_.begin(); itr != m_entries_.end(); itr++) {
            if (itr->second.category == term) {
                search_results_.insert(*itr);
                //if (count == 0)
                count++;
            }
        }
        itr_current_search_entry_ = search_results_.begin();
        return count;
        break;
    }
    default: {
        return count;
    }
    }
}
bool PlayerList::edit(const char& option, const std::string& change) {
    switch (option) {
    case 'f': {
        itr_current_search_entry_->second.fname = change;
        m_entries_[itr_current_search_entry_->first] = itr_current_search_entry_->second;
        return true;
        break;
    }
    case 'l': {
        itr_current_search_entry_->second.lname = change;
        m_entries_[itr_current_search_entry_->first] = itr_current_search_entry_->second;
        return true;
        break;
    }
    case 'a': {
        std::string temp = get_U(current_season - stoi(change));
        itr_current_search_entry_->second.age = change;
        if (temp != "fail") {
            itr_current_search_entry_->second.category = temp;
            m_entries_[itr_current_search_entry_->first] = itr_current_search_entry_->second;
                return true;
            break;
        }
        else {
            return false;
            break;
        }
    }
    case 'p': {
        itr_current_search_entry_->second.paid = change;
        m_entries_[itr_current_search_entry_->first] = itr_current_search_entry_->second;
        return true;
        break;
    }
    case 'c': {
        itr_current_search_entry_->second.category = change;
        m_entries_[itr_current_search_entry_->first] = itr_current_search_entry_->second;
        return true;
        break;
    }
    default: {
        return false;
        break;
    }
    }
    }
int PlayerList::keysearch(const std::string& term, const char& type) {
    int count = 0;
    search_results_.clear();
    switch (type) {
    case 'f': {
        for (auto itr = m_entries_.begin(); itr != m_entries_.end(); itr++) {
            if (itr->second.fname.find(term)!=std::string::npos) {
                search_results_.insert(*itr);
                //if (count == 0)
                count++;
            }
        }
        itr_current_search_entry_ = search_results_.begin();
        return count;
        break;
    }
    case 'l': {
        for (auto itr = m_entries_.begin(); itr != m_entries_.end(); itr++) {
            if (itr->second.lname.find(term) != std::string::npos) {
                search_results_.insert(*itr);
                //if (count == 0)
                count++;
            }
        }
        itr_current_search_entry_ = search_results_.begin();
        return count;
        break;
    }
    case 'a': {
        for (auto itr = m_entries_.begin(); itr != m_entries_.end(); itr++) {
            if (itr->second.age.find(term) != std::string::npos) {
                search_results_.insert(*itr);
                //if (count == 0)
                count++;
            }
        }
        itr_current_search_entry_ = search_results_.begin();
        return count;
        break;
    }
    case 'p': {
        for (auto itr = m_entries_.begin(); itr != m_entries_.end(); itr++) {
            if (itr->second.paid.find(term) != std::string::npos) {
                search_results_.insert(*itr);
                //if (count == 0)               
                count++;
            }
        }
        itr_current_search_entry_ = search_results_.begin();
        return count;
        break;
    }
    case 'c': {
        for (auto itr = m_entries_.begin(); itr != m_entries_.end(); itr++) {
            if (itr->second.category.find(term) != std::string::npos) {
                search_results_.insert(*itr);
                //if (count == 0)
                count++;
            }
        }
        itr_current_search_entry_ = search_results_.begin();
        return count;
        break;
    }
    default: {
        return count;
    }
    }
}