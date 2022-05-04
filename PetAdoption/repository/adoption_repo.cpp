//
// Created by Alessio on 25/03/2021.
//

#include "adoption_repo.h"
#include "../validators/exceptions.h"
#include <algorithm>

void AdoptionRepo::add_pet_to_adoption_list_repo(const Pet &current_pet) {
    auto it = std::find(this->list_of_adopted_pets.begin(), this->list_of_adopted_pets.end(), current_pet);
    if (it != this->list_of_adopted_pets.end())
        throw RepositoryException("The pet has already been added to the adoption list!\n");
    this->list_of_adopted_pets.push_back(current_pet);
}

int AdoptionRepo::search_adoption_list(const Pet &pet) {
    auto it = std::find(this->list_of_adopted_pets.begin(), this->list_of_adopted_pets.end(), pet);
    if (it != this->list_of_adopted_pets.end())
        return it - this->list_of_adopted_pets.begin();
    return -1;
}

int AdoptionRepo::number_of_adopted_pets_repo() {
    return this->list_of_adopted_pets.size();
}

const Pet &AdoptionRepo::operator[](int index) const {
    return this->list_of_adopted_pets[index];
}

std::vector<Pet> AdoptionRepo::get_adopted_pets() {
    return this->list_of_adopted_pets;
}

void AdoptionRepo::remove_adopted_pet_repo(const Pet &pet) {
    auto it = std::find(this->list_of_adopted_pets.begin(), this->list_of_adopted_pets.end(), pet);
    if (it == this->list_of_adopted_pets.end())
        throw RepositoryException("Invalid input! The pet you are trying to delete does not exist!\n");
    this->list_of_adopted_pets.erase(it);
}

void AdoptionRepo::open_app() {

}