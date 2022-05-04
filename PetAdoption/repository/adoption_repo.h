//
// Created by Alessio on 25/03/2021.
//

#ifndef SRC_ADOPTION_REPO_H
#define SRC_ADOPTION_REPO_H

#include "../domain/domain.h"
#include "../dynamic_vector/dynamic_vector.h"
#include <vector>

class AdoptionRepo{
protected:
    std::vector<Pet>list_of_adopted_pets;
public:
    virtual void add_pet_to_adoption_list_repo(const Pet &current_pet);
    int number_of_adopted_pets_repo();
    int search_adoption_list(const Pet &pet);
    virtual void remove_adopted_pet_repo(const Pet& pet);
    const Pet &operator[](int index) const;
    std::vector<Pet> get_adopted_pets();
    virtual void open_app();
};

#endif //SRC_ADOPTION_REPO_H
