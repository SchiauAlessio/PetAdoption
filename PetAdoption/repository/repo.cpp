//
// Created by Alessio on 21/03/2021.
//

#include "repo.h"
#include "../validators/exceptions.h"
#include <algorithm>

void PetRepository::add_pet_repo(const Pet &pet) {
    auto it = std::find(this->array_of_pets.begin(), this->array_of_pets.end(), pet);
    if (it != this->array_of_pets.end())
        throw RepositoryException("Invalid input! Pet already exists!\n");
    this->array_of_pets.push_back(pet);
}

int PetRepository::search_repo(const Pet &pet) {
    auto it = std::find(this->array_of_pets.begin(), this->array_of_pets.end(), pet);
    if (it != this->array_of_pets.end())
        return it - this->array_of_pets.begin();
    return -1;
}

void PetRepository::update_pet(const Pet &pet, const Pet &new_pet) {
    auto it = std::find(this->array_of_pets.begin(), this->array_of_pets.end(), pet);
    if (it == this->array_of_pets.end())
        throw RepositoryException("Invalid input! The pet you are trying to update does not exist!\n");
    //auto it2 = std::find(this->array_of_pets.begin(), this->array_of_pets.end(), new_pet);
    // if (it2 != this->array_of_pets.end())
//       throw RepositoryException("Invalid input! The updated pet already exists!\n");
    for(const Pet& current_pet:this->get_all_pets())
        if(current_pet.get_breed()==new_pet.get_breed()&&current_pet.get_name()==new_pet.get_name()&&current_pet.get_age()==new_pet.get_age()&&current_pet.get_photograph()==new_pet.get_photograph())
            throw RepositoryException("Invalid input! The updated pet already exists!\n");

    this->array_of_pets[it - this->array_of_pets.begin()] = new_pet;
}

void PetRepository::delete_pet_repo(const Pet &pet) {
    auto it = std::find(this->array_of_pets.begin(), this->array_of_pets.end(), pet);
    if (it == this->array_of_pets.end())
        throw RepositoryException("Invalid input! The pet you are trying to delete does not exist!\n");
    this->array_of_pets.erase(it);
}

int PetRepository::pets_count_repo() {
    return this->array_of_pets.size();
}

const Pet &PetRepository::operator[](int index) const {
    return this->array_of_pets[index];
}

std::vector<Pet> PetRepository::get_all_pets() {
    return this->array_of_pets;
}

void PetRepository::open_app() {

}
