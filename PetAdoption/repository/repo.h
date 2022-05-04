//
// Created by Alessio on 21/03/2021.
//


#include "../dynamic_vector/dynamic_vector.h"
#include "../domain/domain.h"
#include <vector>
class PetRepository{
protected:
    std::vector<Pet> array_of_pets;
public:
    //add a pet to the dynamic array
    //@param pet: the pet object that is added
    //an exception is thrown if the pet is not found
    virtual void add_pet_repo(const Pet &pet);

    //search the repository for a given pet
    //@param pet: the pet object that is searched
    int search_repo(const Pet &pet);

    //update a pet found in the repository
    //@param old_pet: the pet that will be updated
    //@param new_pet: the updated version of the old_pet
    //RepositoryException is thrown if the old pet does not exist or the new one already does
    virtual void update_pet(const Pet &old_pet,const Pet &new_pet);

    //delete a pet from the repository
    //@param pet: the pet that will be deleted
    //RepositoryException will be thrown if the pet does not exist
    virtual void delete_pet_repo(const Pet &pet);

    //return the number of pets in the repository
    int pets_count_repo();

    //overload the [] operator
    const Pet &operator[](int index) const;

    std::vector<Pet> get_all_pets();

    virtual void open_app();
};

