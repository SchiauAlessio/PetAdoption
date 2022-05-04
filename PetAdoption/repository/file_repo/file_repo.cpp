//
// Created by Alessio on 10/04/2021.
//

#include "file_repo.h"
#include <fstream>
#include <cstring>
#include <algorithm>
#include <sstream>
#include "../../sensor/sensor.h"
using namespace std;

PetRepositoryFile::PetRepositoryFile(const string &file) {
    this->file_name = file;
    this->read_data();
}

void PetRepositoryFile::add_pet_repo(const Pet &pet) {
    PetRepository::add_pet_repo(pet);
    //this->append_data(pet);
    this->write_data();
}

void PetRepositoryFile::update_pet(const Pet &pet, const Pet &new_pet) {
    PetRepository::update_pet(pet, new_pet);
    this->write_data();
}

void PetRepositoryFile::delete_pet_repo(const Pet &pet) {
    PetRepository::delete_pet_repo(pet);
    this->write_data();
}

void PetRepositoryFile::read_data() {
    ifstream in;
    in.open(this->file_name);
    Sensor s;
    while(in>>s){
        string breed=s.get_breed();
        string name=s.get_name();
        float age=s.get_age();
        string photograph=s.get_photograph();
        if(!breed.empty()&&!name.empty()&&!photograph.empty())
        {Pet pet(breed,name,age,photograph);
            PetRepository::add_pet_repo(pet);}
    }
}


void PetRepositoryFile::append_data(const Pet &pet) {
    ofstream out;
    out.open(this->file_name, ios_base::app);
    string breed=pet.get_breed();
    string name=pet.get_name();
    float age=pet.get_age();
    string photograph=pet.get_photograph();
    Sensor s(breed,name,age,photograph);
    //out << pet.get_breed() << ',' << pet.get_name() << ',' << pet.get_age() << ',' << pet.get_photograph() << '\n';
    out<<s;
    out.close();
}

void PetRepositoryFile::write_data() {
    ofstream out;
    out.open(this->file_name, ios_base::trunc);
    out.close();
    int pets_count = PetRepository::pets_count_repo();
    for (int index = 0; index < pets_count; index++)
        this->append_data(PetRepository::array_of_pets[index]);
}


//Rottweiler,Rex,3.5,https://www.kingrottweilers.com/rottweiler/
//Pitbull,BigBoy,5,https://www.petfinder.com/dog/mr-big-44442236/wa/seattle/forgotten-dogs-rescue-wa368/
//Chihuahua,Pepe,2,http://www.petchidog.com/rescued-chihuahuas-care-and-info
//Labrador,Luke,3,https://www.keystonepuppies.com/puppy-breeds/labrador-retriever-yellow-puppies-for-sale
//Husky,Canelo,8,https://www.adoptapet.com/pet/30504091-oakland-california-husky
//Pomeranian,Preston,4,https://www.adoptapet.com/pet/26475473-mississauga-ontario-pomeranian
//Corgi,Carson,0.5,https://www.keystonepuppies.com/puppy/welsh-corgi-pembroke-puppies-for-sale/carson-49
//Bichpoo,Polly,0.4,https://www.keystonepuppies.com/puppy/bichpoo-puppies-for-sale/polly-35
//Samoyed,Bubba,1,https://www.keystonepuppies.com/puppy/samoyed-puppies-for-sale/bubba-87
//Cavapoo,Sheba,0.7,https://www.keystonepuppies.com/puppy/cavapoo-puppies-for-sale/sheba-4
//Cavapoo,Hoops,0.25,https://www.keystonepuppies.com/puppy/cavapoo-puppies-for-sale/hoops-25