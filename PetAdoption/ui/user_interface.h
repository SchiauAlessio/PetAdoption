//
// Created by Alessio on 25/03/2021.
//

#include "../service/service.h"
#include "../service/adoption_service.h"

class UIUser{
private:
    AdoptionService &adoption_service;
    PetService &pet_service;
    void print_main_menu_options();
    void print_all_pets_by_breed_and_age();
    void print_adoption_list();
    void options_for_seeing_pets_one_by_one();
    void pets_one_by_one_operations(PetService& pet_service,AdoptionService& destination_service);
    void print_adoption_list_one_by_one();
    void pets_one_by_one_operations_no_add();
    void options_for_seeing_pets_one_by_one_no_add();
public:
    explicit UIUser(AdoptionService& adoption_service,PetService& pet_service);
    void run_user_program_ui();

};
