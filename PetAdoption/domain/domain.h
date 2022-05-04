//
// Created by Alessio on 21/03/2021.
//

#include<iostream>

class Pet {
private:
    std::string breed;
    std::string name;
    float age;
    std::string photograph;
public:
    //empty constructor
    Pet();

    //explicit constructor
    //@param breed: the breed of the pet
    //@param name: the name of the pet
    //@param age: the age of the pet
    //@param photograph: the photograph of the pet (as a link)
    Pet(const std::string& breed,const std::string& name, float age,const std::string& photograph);

    //constructor
    //@param other_pet: the pet whose attributes are loaded into the current pet
    Pet(const Pet &other_pet);

    //destructor
    //~Pet();

    //overload the == operator
    bool operator==(const Pet &other) const;

    //overload the = operator
    Pet &operator=(const Pet &other);

    //overload the << operator
    friend std::ostream &operator<<(std::ostream &ostream, const Pet &pet);

    //return the breed of the pet
    const std::string& get_breed() const;

    //return the name of the pet
    const std::string& get_name() const;

    //return the age of the pet
    float get_age() const;

    //return the photograph of the pet
    const std::string& get_photograph() const;

    //set the breed of the pet
    void set_breed(const std::string& breed);

    //set the name of the pet
    void set_name(const std::string& name);

    //set the age of the pet
    void set_age(float);

    //set the photograph of the pet
    void set_photograph(const std::string& photograph);

    std::string to_string() const;
};

