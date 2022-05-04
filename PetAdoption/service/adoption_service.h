//
// Created by Alessio on 25/03/2021.
//

#include "../repository/adoption_repo.h"
#include "../repository/repo.h"
#include "service.h"
class AdoptionService{
    friend class AdoptionRepo;
    friend class PetRepository;
    friend class GUIUser;
protected:
    AdoptionRepo& adoption_repo;
    PetRepository& pet_repo;
    PetService& dogs_with_breed_and_age;
public:
    AdoptionService(AdoptionRepo& adoption_repo,PetRepository& pet_repo,PetService &dogs_with_breed_and_age);
    void add_pet_to_adoption_list_service(const Pet& pet);
    int number_of_adopted_pets_service();
    const Pet &operator[](int index) const;
    PetService& get_dogs_with_breed_and_age(const std::string& given_breed,float maximum_age);
    std::vector<Pet> get_adopted_pets_service();
    void open_with_app();
    std::vector<Pet> get_all_available_pets_to_adopt();
    int total_number_of_pets();
};
