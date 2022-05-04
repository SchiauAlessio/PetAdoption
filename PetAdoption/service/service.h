//
// Created by Alessio on 21/03/2021.
//


#include "../repository/repo.h"

class PetService {
    friend class PetRepository;

private:
    PetRepository &pet_repository;
public:
    //constructor
    PetService(PetRepository &pet_repository);

    //add a pet to the repository
    //@param breed: the breed of the pet that will be added
    //@param name: the name of the pet that will be added
    //@param age: the age of the pet that will be added
    //@param photograph: the photograph of the pet that will be added
    //throw exception if the validation of the pet characteristics fails
    void add_pet_service(const std::string& breed, const std::string& name, float age, const std::string& photograph);

    //update a pet from the repository
    //@param old_breed: old breed of the pet that will be updated
    //@param old_name: old name of the pet that will be updated
    //@param breed: the new breed of the pet that will be updated
    //@param name: the new name of the pet that will be updated
    //@param age: the new age of the pet that will be updated
    //@param photograph: the new photograph of the pet that will be updated
    //throw exception if the validation of the pet characteristics fails
    void update_pet_service(const std::string& old_breed,const std::string& old_name,const std::string& breed, const std::string& name, float age, const std::string& photograph);

    //delete a pet from the repository
    //@param breed: the first unique identifier of the pet that will be deleted
    //@param name: the second unique identifier of the pet that will be deleted
    void delete_pet_service(const std::string& breed, const std::string& name,float age,const std::string& photograph);

    int search_pet_service(const std::string& breed,const std::string& name);

    //return the number of pets that are currently in the repository
    int pets_count_service();

    //overload the [] operator
    const Pet &operator[](int index) const;

    void initialize_array_list();

    std::vector<Pet> get_all_pets_service();

    void empty_function_for_undo_redo(const std::string& breed,const std::string& name, float age, const std::string& photograph);
    //std::vector<std::string> get_breed_pets_with_age_less(float maximum_age);
};

