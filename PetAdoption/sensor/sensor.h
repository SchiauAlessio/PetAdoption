//
// Created by Alessio on 12/04/2021.
//


#include<string>
#include<iostream>
class Sensor{
private:
    std::string _breed;
    std::string _name;
    float _age;
    std::string _photograph;
public:
    Sensor();
    Sensor(const std::string& breed,const std::string& name, float age,const std::string& photograph);
    bool operator==(const Sensor&);

    const std::string& get_breed() const;

    const std::string& get_name() const;

    float get_age() const;

    const std::string& get_photograph() const;
    friend std::ostream& operator<<(std::ostream&,const Sensor&);
    friend std::istream& operator>>(std::istream&, Sensor&);
};

