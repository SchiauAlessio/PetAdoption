//
// Created by Alessio on 21/03/2021.
//

#include <cstring>
#include "domain.h"




Pet::Pet(const std::string& breed,const std::string& name, float age, const std::string& photograph) {
    this->breed=breed;
    this->name=name;
    this->age=age;
    this->photograph=photograph;
}
//Pet::~Pet() {
//    delete[] this->breed;
//    delete[] this->name;
//    delete[] this->photograph;
//}

Pet::Pet() {
    this->breed="";
    this->name="";
    this->age=0;
    this->photograph="";
}
const std::string& Pet::get_breed() const {
    return this->breed;
}
const std::string& Pet::get_name() const {
    return this->name;
}
float Pet::get_age() const {
    return this->age;
}
const std::string& Pet::get_photograph() const {
    return this->photograph;
}
void Pet::set_breed(const std::string& new_breed) {
    this->breed=new_breed;

}
void Pet::set_name(const std::string& new_name) {

    this->name=new_name;
}
void Pet::set_age(float new_age) {
    this->age=new_age;
}
void Pet::set_photograph(const std::string& new_photograph) {
    this->photograph=new_photograph;
}

Pet::Pet(const Pet &other) {
    this->breed="";
    this->name="";
    this->photograph="";
    this->breed=other.breed;
    this->name=other.name;
    this->set_age(other.age);
    this->photograph=other.photograph;
}

bool Pet::operator==(const Pet &other) const {
    return (this->breed==other.breed&&this->name==other.name);
}

Pet &Pet::operator=(const Pet &other){
    this->breed=other.breed;
    this->name=other.name;
    this->set_age(other.age);
    this->photograph=other.photograph;
    return *this;
}

std::ostream &operator<<(std::ostream &ostream, const Pet &pet) {
    ostream<<"Breed: "<<pet.get_breed()<<"|| "<<"Name: "<<pet.get_name()<<"|| Age: "<<pet.get_age()<<"||Photograph: "<<pet.get_photograph();
    return ostream;
}

std::string Pet::to_string() const {
    std:: string pet_to_string="";
    pet_to_string=pet_to_string+"BREED: "+this->breed+" ||NAME: "+this->name+" ||AGE: "+std::to_string(this->age)+" ||PHOTOGRAPH: "+this->photograph;
    return pet_to_string;
}
