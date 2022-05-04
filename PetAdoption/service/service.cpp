//
// Created by Alessio on 21/03/2021.
//

#include <algorithm>
#include "../validators/exceptions.h"
#include "../validators/validating.h"
#include "service.h"

PetService::PetService(PetRepository &pet_repository) : pet_repository(pet_repository) {}

void PetService::add_pet_service(const std::string& breed, const std::string& name, float age, const std::string& photograph) {
    Pet pet(breed, name, age, photograph);
    try {
        PetValidator::validate_given_pet(pet);
        this->pet_repository.add_pet_repo(pet);
    } catch (ValidatorException &val_exc) {
        throw ValidatorException(val_exc.what());
    }
}

void PetService::update_pet_service(const std::string& old_breed, const std::string& old_name,const std::string& breed, const std::string& name, float age, const std::string& photograph) {
    Pet pet(old_breed, old_name, age, photograph);
    Pet new_pet(breed,name,age,photograph);
    try {
        PetValidator::validate_given_pet(pet);
        PetValidator::validate_given_pet(new_pet);
        this->pet_repository.update_pet(pet,new_pet);
    } catch (ValidatorException &val_exc) {
        throw ValidatorException(val_exc.what());
    }

}

void PetService::delete_pet_service(const std::string& breed, const std::string& name,float age,const std::string& photograph) {
    Pet pet(breed, name, 1,  "");
    try {
        this->pet_repository.delete_pet_repo(pet);
    } catch (RepositoryException &rep_exc) {
        throw RepositoryException(rep_exc.what());
    }
}

int PetService::search_pet_service(const std::string &breed, const std::string &name) {
    Pet pet(breed,name,1,"");
    return this->pet_repository.search_repo(pet);
}
int PetService::pets_count_service() {
    return this->pet_repository.pets_count_repo();
}

const Pet &PetService::operator[](int index) const {
    return this->pet_repository[index];
}

void PetService::initialize_array_list() {
    if (this->pets_count_service() == 0) {
        this->add_pet_service("Rottweiler","Rex", 3.5,
                              "https://www.kingrottweilers.com/rottweiler/");
        this->add_pet_service("Pitbull", "BigBoy", 5,
                              "https://www.petfinder.com/dog/mr-big-44442236/wa/seattle/forgotten-dogs-rescue-wa368/");
        this->add_pet_service( "Chihuahua", "Pepe", 2,
                               "http://www.petchidog.com/rescued-chihuahuas-care-and-info");
        this->add_pet_service( "Labrador",  "Luke", 3,
                               "https://www.keystonepuppies.com/puppy-breeds/labrador-retriever-yellow-puppies-for-sale");
        this->add_pet_service( "Husky",  "Canelo", 8,
                               "https://www.adoptapet.com/pet/30504091-oakland-california-husky");
        this->add_pet_service( "Pomeranian",  "Preston", 4,
                               "https://www.adoptapet.com/pet/26475473-mississauga-ontario-pomeranian");
        this->add_pet_service( "Corgi",  "Carson", 0.5,
                               "https://www.keystonepuppies.com/puppy/welsh-corgi-pembroke-puppies-for-sale/carson-49");
        this->add_pet_service( "Bichpoo",  "Polly", 0.4,
                               "https://www.keystonepuppies.com/puppy/bichpoo-puppies-for-sale/polly-35");
        this->add_pet_service( "Samoyed",  "Bubba", 1,
                               "https://www.keystonepuppies.com/puppy/samoyed-puppies-for-sale/bubba-87");
        this->add_pet_service( "Cavapoo",  "Sheba", 0.7,
                               "https://www.keystonepuppies.com/puppy/cavapoo-puppies-for-sale/sheba-4");
        this->add_pet_service( "Cavapoo",  "Hoops", 0.25,
                               "https://www.keystonepuppies.com/puppy/cavapoo-puppies-for-sale/hoops-25");
    }
}

std::vector<Pet> PetService::get_all_pets_service() {
    return this->pet_repository.get_all_pets();
}

void PetService::empty_function_for_undo_redo(const std::string &breed, const std::string &name, float age,
                                              const std::string &photograph) {
    //nothing
}
//std::vector<std::string> PetService::get_breed_pets_with_age_less(float maximum_age) {
//    std::vector<std::string> breed_vector;
//    for(Pet pet:this->pet_repository.get_all_pets()){
//        if(pet.get_age()<maximum_age)
//            breed_vector.push_back(pet.get_breed());}
//    std::sort(breed_vector.begin(),breed_vector.end(),std::greater<std::string>());
//    //breed_vector.erase(unique(breed_vector.begin(),breed_vector.end()));
//    return breed_vector;
//}