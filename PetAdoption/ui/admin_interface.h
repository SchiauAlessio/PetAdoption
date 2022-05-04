//
// Created by Alessio on 22/03/2021.
//
#include "../service/service.h"
class UIAdmin{
    friend class PetService;
private:
    PetService &pet_service;
    void print_main_menu();
    void add_pet_ui();
    void update_pet_ui();
    void delete_pet_ui();
    void print_pets_ui();
    //void ui_breeds_for_dogs_with_age_less_than();
public:
    explicit UIAdmin(PetService &pet_service);
    void run_user_menu();

};

