//
// Created by Alessio on 25/03/2021.
//
#include<iostream>
#include "adoption_service.h"
#include <vector>
#include <algorithm>
using namespace std;
AdoptionService::AdoptionService(AdoptionRepo &adoption_repo,PetRepository &pet_repo,PetService &dogs_with_breed_and_age): adoption_repo(adoption_repo),pet_repo(pet_repo),dogs_with_breed_and_age(dogs_with_breed_and_age){}

void AdoptionService::add_pet_to_adoption_list_service(const Pet &pet) {
    this->adoption_repo.add_pet_to_adoption_list_repo(pet);
}
int AdoptionService::number_of_adopted_pets_service() {
    return this->adoption_repo.number_of_adopted_pets_repo();
}
const Pet &AdoptionService::operator[](int index) const {
    return this->adoption_repo[index];
}
PetService& AdoptionService::get_dogs_with_breed_and_age(const std::string& breed,float maximum_age) {
    int current_number=this->dogs_with_breed_and_age.pets_count_service();
    int i=0;
    while(i<current_number){
        this->dogs_with_breed_and_age.delete_pet_service(this->dogs_with_breed_and_age[i].get_breed(),this->dogs_with_breed_and_age[i].get_name(),1,"");
        current_number--;
    }
    //vector<Pet> pets_filtered;
    //copy_if(this->pet_repo.get_all_pets().begin(),this->pet_repo.get_all_pets().end(),std::back_inserter(pets_filtered),[=](Pet pet){return pet.get_age()<maximum_age && (breed=="" || breed==pet.get_breed());});
    for(Pet current_pet:this->pet_repo.get_all_pets()){
        if(current_pet.get_age()<maximum_age && (breed==""||breed==current_pet.get_breed())){
        string current_breed=current_pet.get_breed();
        string current_name=current_pet.get_name();
        float age=current_pet.get_age();
        string photo=current_pet.get_photograph();
        this->dogs_with_breed_and_age.add_pet_service(current_breed,current_name,age,photo);}
    }
//    if(breed==""){
//        int index=0;
//        while(index<this->pet_repo.pets_count_repo()){
//            if (this->pet_repo[index].get_age() < maximum_age)
//                this->dogs_with_breed_and_age.add_pet_service(this->pet_repo[index].get_breed(),
//                                                              this->pet_repo[index].get_name(),
//                                                              this->pet_repo[index].get_age(),
//                                                              this->pet_repo[index].get_photograph());
//            index++;
//        }
//
//        }
//    else{
//        int index=0;
//        while(index<this->pet_repo.pets_count_repo()){
//            if(this->pet_repo[index].get_age()<maximum_age && this->pet_repo[index].get_breed()==breed)
//                this->dogs_with_breed_and_age.add_pet_service(this->pet_repo[index].get_breed(),this->pet_repo[index].get_name(),this->pet_repo[index].get_age(),this->pet_repo[index].get_photograph());
//            index++;
//        }
//    }
    return this->dogs_with_breed_and_age;
}

std::vector<Pet> AdoptionService::get_adopted_pets_service(){
    return this->adoption_repo.get_adopted_pets();
}

void AdoptionService::open_with_app() {
    this->adoption_repo.open_app();
}
std::vector<Pet> AdoptionService::get_all_available_pets_to_adopt() {
    return this->pet_repo.get_all_pets();
}

int AdoptionService::total_number_of_pets() {
    return this->pet_repo.pets_count_repo();
}