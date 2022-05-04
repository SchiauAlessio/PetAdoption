//
// Created by Alessio on 12/04/2021.
//

#include "sensor.h"
#include <vector>
using namespace std;
Sensor::Sensor(const std::string &breed, const std::string &name, float age, const std::string &photograph) : _breed{
        breed}, _name{name}, _age{age},_photograph{photograph} {

}
bool Sensor::operator==(const Sensor& s){
    return this->_breed==s._breed&&this->_name==s._name;
}
std::ostream& operator<<(std::ostream& os,const Sensor&s){
    os<<s._breed<<","<<s._name<<","<<s._age<<","<<s._photograph<<"\n";
    return os;
}

std::istream &operator>>(std::istream &is, Sensor &s) {
    string current_line;
    getline(is,current_line);
    string breed,name,photograph;
    float age;
    int index=0;
    if (current_line != "") {
        string delimiter = ",";
        vector<string> split_list;
        size_t pos = 0;
        std::string token;
        while ((pos = current_line.find(delimiter)) != std::string::npos) {
            token = current_line.substr(0, pos);
            if (index == 0)
                breed = token;
            if (index == 1)
                name = token;
            if (index == 2) {
                age = stof(token);
            }
            current_line.erase(0, pos + delimiter.length());
            index++;
        }
        photograph = current_line;
        s._breed=breed;
        s._name=name;
        s._age=age;
        s._photograph=photograph;

    }
    return is;
}

Sensor::Sensor():_breed{""},_name{""},_age{-1}, _photograph("") {

}

const std::string &Sensor::get_breed() const {
    return this->_breed;
}

const std::string &Sensor::get_name() const {
    return this->_name;
}

float Sensor::get_age() const {
    return this->_age;
}

const std::string &Sensor::get_photograph() const {
    return this->_photograph;
}



