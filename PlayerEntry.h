#ifndef _PlayerEntry_h_
#define _PlayerEntry_h_
#include <fstream>
#include <string>
class PlayerEntry{
public:
    PlayerEntry() : fname("no name"),lname("no name"), age("no age"), paid("payment unknown") {}
    PlayerEntry(const std::string& fname0, const std::string& lname0, 
        const std::string& age0,const std::string& paid0, const std::string& category0) :
        fname(fname0), lname(lname0), age(age0), paid(paid0),category(category0) {}
    std::string fname;
    std::string lname;
    std::string age;
    std::string paid;
    std::string category;
};
    inline std::istream& operator>>(std::istream& in,
        PlayerEntry &x){
        getline(in, x.fname);
        getline(in, x.lname);
        getline(in, x.age);
        getline(in, x.paid);
        getline(in, x.category);
        return in;
    }
    inline std::ostream& operator<<(std::ostream& out,
        const PlayerEntry &x){
        out << x.fname << std::endl <<
            x.lname << std::endl <<
            x.age << std::endl
            << x.paid << std::endl
            << x.category << std::endl;
        return out;
    }
#endif