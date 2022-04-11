#include <iostream>
#include <fstream>
#include <map>
#include <string>

using namespace std;

#define CONDITION str.at(i) != ' ' && str.at(i) != ',' && str.at(i) != '.' && str.at(i) != ')' && str.at(i) != ';'
#define SECOND_COND str.at(iposotion + name.size()) == '.' || str.at(iposotion + name.size()) == ' ' || str.at(iposotion + name.size()) == ';'

class Identefictor{
private:
    string type;
    string name;
public:
    Identefictor() = default;
    Identefictor(const string& type, const string& name){
        this->name = name;
        this->type = type;
    }
    string getname() const {
        return name;
    }

    void Print() const {
        cout << "Identeficator of " << type << " type: (" << name << ") appear in lines: ";
    }

};

class Appearanse{
private:
    string where_appear;
    int number_of_apperannse;
public:
    Appearanse() = default;
    Appearanse(const string& where_appear, int number_of_apperannse = 0){
        this->where_appear = where_appear;
        this->number_of_apperannse = number_of_apperannse;
    }
    
    void AddApperance(const string& other){
        where_appear += ", " + other;
        number_of_apperannse++;
    }

    void Print() const {
        cout << where_appear << " number of apperanse is: " << number_of_apperannse << endl;
    }

    string getApperanse() const {
        return where_appear;
    }
};

bool operator < (Identefictor a, Identefictor b){
    return a.getname() < b.getname();
}

string getIndendefi(string& str, string tofind, bool& pr){
    string name;
    unsigned int iposition = str.find(tofind);
    if(iposition > 1024 || str.find('#') < 1024){
        return name;
    }
    unsigned int spaceposition = str.find(' ', iposition);
    if(spaceposition > 1024){
        return name;
    }
    unsigned int slashposition = str.find("//");
    if(spaceposition > slashposition){
        return name;
    }
    for(int i = spaceposition + 1; CONDITION; i++){
        name.push_back(str.at(i));
        pr = true;
    }
    if(name.find('(') < 1024){
        pr = false;
    }
    str.erase(spaceposition - tofind.size(), tofind.size() + name.size());
    return name;
}

void find_allready_exisited(map<Identefictor, Appearanse>& mapa, string& str, int i){
    map<Identefictor, Appearanse>::iterator p = mapa.begin();
    int prev_pos = 0;
    while(p != mapa.end()){
        string name = p->first.getname();
        unsigned int iposotion = str.find(p->first.getname(), prev_pos);
        if(iposotion < 1024){
            unsigned int slashposition = str.find("//");
            if(slashposition < 1024 && slashposition < iposotion){
                str.erase(iposotion, name.size());
                continue;
            }
            if(iposotion != 0 && str.at(iposotion - 1) >= 'A' && str.at(iposotion - 1) <= 'z'){
                prev_pos = iposotion + 1;
                iposotion = str.find(p->first.getname(), prev_pos);
                continue;
            }
            if(SECOND_COND){
                str.erase(iposotion, name.size());
                p->second.AddApperance(to_string(i + 1));
                continue;
            }
        }
        prev_pos = 0;
        ++p;
    }
}

void ifinsert(map<Identefictor, Appearanse>& mapa, string& str, string& name, string tofind, int i){
    string prevstr;
    do{
        prevstr = str;
        bool pr = false;
        find_allready_exisited(mapa, str, i);
        name = getIndendefi(str, tofind, pr);
        if(pr){
            map<Identefictor, Appearanse>::iterator p;
            p = mapa.find(Identefictor(tofind, name));
            if(p == mapa.end()){
                mapa.insert(pair<Identefictor, Appearanse>(Identefictor(tofind, name), Appearanse(to_string(i + 1), 1)));
            } else {
                p->second.AddApperance(to_string(i + 1));
            }
        }
    } while(prevstr != str);
}

int main(){
    ifstream file("./for11_5.cpp");
    if(!file){
        cout << "Smt wrong!";
        return 1;
    }
    map<Identefictor, Appearanse> mapa;
    string name;
    string str;
    for(int i = 0; getline(file, str); i++){
        ifinsert(mapa, str, name, "int", i);
        ifinsert(mapa, str, name, "string", i);
        ifinsert(mapa, str, name, "double", i);
        ifinsert(mapa, str, name, "float", i);
    }
    file.close();

    map<Identefictor, Appearanse>::iterator p = mapa.begin();
    while(p != mapa.end()){
        p->first.Print();
        p->second.Print();
        p++;
    }
    return 0;
}