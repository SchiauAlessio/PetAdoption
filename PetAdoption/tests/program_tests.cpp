//
// Created by Alessio on 22/03/2021.
//

#include "program_tests.h"
#include "../service/service.h"
#include "../validators/validating.h"
#include "../validators/exceptions.h"
#include "../repository/adoption_repo.h"
#include "../service/adoption_service.h"
#include "../repository/file_repo/file_repo.h"
#include "../repository/file_repo/file_repo_adoption.h"
#include <cassert>
#include <cmath>
#include <cstring>
#include <vector>

using namespace std;

void test_dynamic_array() {
    DynamicVector<int> dynamic_array(1);
    assert(dynamic_array.dimension() == 0);
    dynamic_array.add_element(1000);
    assert(dynamic_array.dimension() == 1);
    assert(dynamic_array[0] == 1000);
    dynamic_array.add_element(2000);
    assert(dynamic_array.dimension() == 2);
    assert(dynamic_array[1] == 2000);
    dynamic_array.add_element(30000);
    assert(dynamic_array.dimension() == 3);
    assert(dynamic_array[2] == 30000);
    assert(dynamic_array.find_element(30000) == 2);
    assert(dynamic_array.find_element(3) == -1);
    dynamic_array.delete_element(30000);
    assert(dynamic_array.find_element(30000) == -1);
    assert(dynamic_array.dimension() == 2);
    assert(dynamic_array[1] == 2000);
    assert(dynamic_array[0] == 1000);
    dynamic_array.update_element(0, 1);
    assert(dynamic_array.find_element(1000) == -1);
    assert(dynamic_array[0] == 1);

    DynamicVector<Pet> dynamic_vector;
    assert(dynamic_vector.dimension() == 0);
    Pet pet("test_breed", "test_name", 1, "test_photograph");
    dynamic_vector.add_element(pet);
    assert(dynamic_vector.dimension() == 1);
    assert(dynamic_vector.find_element(pet) == 0);
    assert(dynamic_vector[0] == pet);
    dynamic_vector.delete_element(pet);
    assert(dynamic_vector.dimension() == 0);
    assert(dynamic_vector.find_element(pet) == -1);
    dynamic_vector.add_element(pet);
    Pet new_pet("test_breed2", "test_name2", 1, "test_photograph2");
    dynamic_vector.update_element(0, new_pet);
    assert(dynamic_vector[0] == new_pet);
    cout << "Dynamic vector tests passed!\n";

}

void test_domain() {
    Pet pet("test_breed", "test_name", 1, "test_photograph");
    cout << pet << "\n";

    assert(fabs(pet.get_age() - 1) < 0.0001);
    assert(pet.get_breed() == "test_breed");
    assert(pet.get_photograph() == "test_photograph");
    assert(pet.get_name() == "test_name");
    assert(pet == pet);
    Pet new_pet("test_breed", "test_name", 1, "test_photograph");
    assert(pet == new_pet);
    Pet pet3;
    assert(pet3.get_name() == "");
    assert(pet3.get_photograph() == "");
    assert(pet3.get_breed() == "");
    assert(pet3.get_age() == 0);
    Pet pet4("test_breed2", "test_name2", 1, "test_photograph");
    Pet pet5 = pet4;
    assert(fabs(pet5.get_age() - 1) < 0.0001);
    assert(pet5.get_breed() == "test_breed2");
    assert(pet5.get_photograph() == "test_photograph");
    assert(pet5.get_name() == "test_name2");
    pet5.set_name("random_name");
    pet5.set_age(10);
    pet5.set_breed("Random_breed");
    pet5.set_photograph("random_photograph");
    assert(pet5.get_name() == "random_name");
    assert(pet5.get_breed() == "Random_breed");
    assert(pet5.get_photograph() == "random_photograph");
    assert(pet5.get_age() == 10);
    cout << "Domain tests passed!\n";

}

void test_repo() {
    PetRepository pet_repository;
    assert(pet_repository.pets_count_repo() == 0);
    assert(pet_repository.get_all_pets().size() == 0);
    Pet pet("test_breed", "test_name", 1, "test_photo");
    pet_repository.add_pet_repo(pet);
    assert(pet_repository.pets_count_repo() == 1);
    assert(pet_repository.get_all_pets().size() == 1);
    assert(pet_repository[0] == pet);
    Pet pet2("test_breed2", "test_name2", 1, "test_photo");
    pet_repository.update_pet(pet, pet2);
    assert(pet_repository[0] == pet2);
    assert(pet_repository.get_all_pets()[0] == pet2);
    assert(pet_repository.search_repo(pet2) == 0);
    pet_repository.delete_pet_repo(pet2);
    assert(pet_repository.pets_count_repo() == 0);
    assert(pet_repository.search_repo(pet2) == -1);
    pet_repository.add_pet_repo(pet2);
    try {
        pet_repository.delete_pet_repo(pet);
    } catch (const RepositoryException &re) {
        assert(strcmp(re.what(), "Invalid input! The pet you are trying to delete does not exist!\n") == 0);
    }
    try {
        pet_repository.add_pet_repo(pet2);
    } catch (const RepositoryException &re) {
        assert(strcmp(re.what(), "Invalid input! Pet already exists!\n") == 0);
    }
    try {
        pet_repository.update_pet(pet, pet2);
    } catch (const RepositoryException &re) {
        assert(strcmp(re.what(), "Invalid input! The pet you are trying to update does not exist!\n") == 0);
    }
    try {
        pet_repository.update_pet(pet2, pet2);
    } catch (const RepositoryException &re) {
        assert(strcmp(re.what(), "Invalid input! The updated pet already exists!\n") == 0);
    }

    cout << "Repository tests passed\n";
}

void test_service() {
    PetRepository pet_repository;
    PetService pet_service(pet_repository);
    assert(pet_service.pets_count_service() == 0);
    pet_service.add_pet_service("test_breed", "test_name", 1, "test_photo");
    assert(pet_service.pets_count_service() == 1);
    Pet pet("test_breed", "test_name", 1, "test_photo");
    assert(pet_service.get_all_pets_service()[0] == pet);
    assert(pet_service[0] == pet);
    pet_service.update_pet_service("test_breed", "test_name", "test_breed2", "test_name2", 1, "test_photo");
    Pet pet2("test_breed2", "test_name2", 1, "test_photo");
    assert(pet_service[0] == pet2);
    assert(pet_service.get_all_pets_service()[0] == pet2);
    assert(pet_service.get_all_pets_service().size() == 1);
    pet_service.delete_pet_service("test_breed2", "test_name2",0,"");
    assert(pet_service.pets_count_service() == 0);
    assert(pet_service.get_all_pets_service().size() == 0);
    pet_service.add_pet_service("test_breed", "test_name", 1, "test_photo");
    assert(pet_service[0] == pet);
    try {
        pet_service.add_pet_service("", "", 0, "");
    } catch (ValidatorException &ve) {
        assert(strcmp(ve.what(),
                      "Invalid input!The breed of an animal can not be an empty string!\nInvalid input!The name of an animal can not be an empty string!\nInvalid input!The link can not be an empty string!\nInvalid input!The age must be a positive input!\n") ==
               0);
    }
    try {
        pet_service.update_pet_service("", "", "", "", 0, "");
    }
    catch (ValidatorException &ve) {
        assert(strcmp(ve.what(), "") != 0);
    }
    try {
        pet_service.delete_pet_service("mama", "tata",1,"");
    } catch (RepositoryException &re) {
        assert(strcmp(re.what(), "") != 0);
    }
    pet_service.delete_pet_service("test_breed", "test_name",1,"");
    pet_service.initialize_array_list();
    assert(pet_service.pets_count_service() == 11);
    assert(pet_service.get_all_pets_service().size() == 11);
    assert(pet_service[0].get_breed() == "Rottweiler");
    assert(pet_service[10].get_breed() == "Cavapoo");
    assert(pet_service[10].get_age()==0.25);
    assert(fabs(pet_service[7].get_age()-0.4)<0.0001);
    assert(pet_service[7].get_breed()=="Bichpoo");
    //vector<string> breeds=pet_service.get_breed_pets_with_age_less(10);
    //assert(breeds.size()==11);
    //vector<string> breeds2=pet_service.get_breed_pets_with_age_less(0.5);
    //assert(breeds2.size()==2);
    cout << "Service tests passed!\n";
}

void test_adoption_repo() {
    AdoptionRepo adoption_repo;
    assert(adoption_repo.number_of_adopted_pets_repo() == 0);
    Pet pet("test_breed", "test_name", 1, "test_photo");
    adoption_repo.add_pet_to_adoption_list_repo(pet);
    assert(adoption_repo.number_of_adopted_pets_repo() == 1);
    assert(adoption_repo[0] == pet);
    assert(adoption_repo.get_adopted_pets()[0] == pet);
    assert(adoption_repo.get_adopted_pets().size() == 1);
    assert(adoption_repo.search_adoption_list(pet) == 0);
    Pet pet2("test_breed2", "test_name", 1, "test_photo");
    assert(adoption_repo.search_adoption_list(pet2) == -1);
    adoption_repo.remove_adopted_pet_repo(pet);
    assert(adoption_repo.number_of_adopted_pets_repo()==0);
    try{
        adoption_repo.remove_adopted_pet_repo(pet);

    }catch(RepositoryException &re){
        assert(strcmp(re.what(),"")!=0);
    }
    cout << "Adoption Repo tests passed!\n";
}

void test_adoption_service() {
    AdoptionRepo adoption_repo;
    PetRepository pet_repo;
    PetRepository test_repo;
    PetService pet_service(pet_repo);
    pet_service.initialize_array_list();
    assert(pet_repo.pets_count_repo() == 11);
    PetService array_dogs_with_breed_and_age(test_repo);
    Pet pet("test_breed", "test_name", 1, "test_photo");
    AdoptionService adoption_service(adoption_repo, pet_repo, array_dogs_with_breed_and_age);
    assert(adoption_service.number_of_adopted_pets_service() == 0);
    assert(adoption_service.get_adopted_pets_service().size() == 0);
    adoption_service.add_pet_to_adoption_list_service(pet);
    assert(adoption_service[0] == pet);
    try {
        adoption_service.add_pet_to_adoption_list_service(pet);
    } catch (RepositoryException &re) {
        assert(strcmp(re.what(), "The pet has already been added to the adoption list!\n") == 0);
    }
    PetService pet_serv = adoption_service.get_dogs_with_breed_and_age("Cavapoo", 10);
    assert(pet_serv.pets_count_service() == 2);
    PetService pet_serv2 = adoption_service.get_dogs_with_breed_and_age("", 30);
    assert(pet_serv2.pets_count_service() == 11),

            cout << "Adoption Service tests passed!\n";
}

void test_file_repo() {
    PetRepositoryFile file_repo("../tests/file_for_tests.txt");
    assert(file_repo[0].get_breed() == "test_breed_1");
    assert(file_repo[1].get_breed() == "test_breed_2");
    assert(file_repo[2].get_breed() == "test_breed_3");
    Pet pet1("test_breed_1", "test_name_1", 1, "test_photo_1");
    Pet pet3("test_breed_3", "test_name_3", 3, "test_photo_3");
    Pet pet2("test_breed_2", "test_name_2", 2, "test_photo_2");
    Pet new_pet_2("up", "up", 22.5, "up");
    file_repo.update_pet(file_repo[1], new_pet_2);
    assert(file_repo[1] == new_pet_2);
    assert(file_repo[1].get_age() == 22.5);
    file_repo.delete_pet_repo(new_pet_2);
    file_repo.delete_pet_repo(pet1);
    file_repo.delete_pet_repo(pet3);
    assert(file_repo.pets_count_repo() == 0);
    file_repo.add_pet_repo(pet1);
    assert(file_repo[0] == pet1);
    file_repo.add_pet_repo(pet2);
    assert(file_repo[1] == pet2);
    file_repo.add_pet_repo(pet3);
    assert(file_repo[2] == pet3);
    cout << "File Repo tests passed!\n";
}

void test_adoption_file_repo() {
    AdoptionRepositoryFile adoption_repo("../tests/file_tests_adoption.txt");
    assert(adoption_repo.number_of_adopted_pets_repo() == 1);
    AdoptionRepositoryFile adoption_repo2("../tests/file_for_tests2.txt");
    Pet pet("random_breed", "random_name", 100, "random_photo");
    try {
        adoption_repo2.add_pet_to_adoption_list_repo(pet);
        assert(adoption_repo2[3] == pet);

    } catch (RepositoryException &re) {
        assert(strcmp(re.what(), "") != 0);
    }
    cout << "Adoption file repo tests passed!\n";
}

void run_all_tests() {
    test_domain();
    test_dynamic_array();
    test_repo();
    test_service();
    test_adoption_repo();
    test_adoption_service();
    test_file_repo();
    test_adoption_file_repo();
}