//
// Created by Alessio on 25/03/2021.
//

#include "user_interface.h"
#include<iostream>
#include "../validators/exceptions.h"
#include <string>
#include <windows.h>
#include <shellapi.h>

using namespace std;

UIUser::UIUser(AdoptionService &adoption_service, PetService &pet_service) : adoption_service(adoption_service),
                                                                             pet_service(pet_service) {}

void UIUser::print_main_menu_options() {
    cout << "0.Re-print the menu\n";
    cout << "1.See all the pets currently available to adopt\n";
    cout << "2.See all the dogs of a given breed, having an age less than a given number\n";
    cout << "3.See the adoption list\n";
    cout << "4.Exit the application\n";

}

void UIUser::options_for_seeing_pets_one_by_one() {
    cout << "0.Exit\n";
    cout << "1.Next pet\n";
    cout << "2.Add to adoption list\n";
}

void UIUser::pets_one_by_one_operations(PetService &pet_serv, AdoptionService &destination_service) {
    if (pet_serv.pets_count_service() == 0) {
        cout << "No available dogs for adoption!\n";
        return;
    }
    int current_index = 0;
    int option;
    while (true) {
        cout << pet_serv[current_index] << "\n\n";
        //ShellExecuteA(NULL, NULL, "chrome.exe", pet_serv[current_index].get_photograph(), NULL, SW_SHOWMAXIMIZED);
        this->options_for_seeing_pets_one_by_one();
        cout << "Your choice:";
        cin.ignore();
        cin >> option;
        if (option < 0 || option > 2)
            cout << "Invalid option!\n\n";
        if (option == 0) return;
        if (option == 1) {
            if (current_index == pet_serv.pets_count_service() - 1)
                current_index = 0;
            else current_index++;
        }
        if (option == 2) {
            try {
                destination_service.add_pet_to_adoption_list_service(pet_serv[current_index]);
                cout << "The pet has been successfully added!\n\n";
                bool at_the_end = current_index == (pet_serv.pets_count_service() - 1);
                this->pet_service.delete_pet_service(pet_serv[current_index].get_breed(),
                                                     pet_serv[current_index].get_name(),1,"");
                if (pet_serv.pets_count_service() == 0) {
                    cout << "No more pets remaining available for adoption!\n";
                    return;
                }
                if (at_the_end) current_index = 0;
            }
            catch (RepositoryException &re) {
                cout << re.what() << "\n\n";
            }
        }
    }
}

void UIUser::print_all_pets_by_breed_and_age() {
    string breed;
    float age;
    cout << "Enter the breed:";
    cin.ignore();
    getline(cin, breed);
    cout << "Enter the maximum age:";
    cin >> age;
    PetService pets_with_breed_and_age = this->adoption_service.get_dogs_with_breed_and_age(breed, age);
    if (pets_with_breed_and_age.pets_count_service() == 0) {
        cout << "No available pets with these characteristics!\n";
        return;
    }
    this->pets_one_by_one_operations(pets_with_breed_and_age, adoption_service);
}

void UIUser::print_adoption_list() {
    if (this->adoption_service.number_of_adopted_pets_service() == 0){
        cout << "Your adoption list is currently empty!\n";
        return;}
//    for(int i=0;i<this->adoption_service.number_of_adopted_pets_service();i++)
//        cout<<this->adoption_service[i]<<"\n\n";
    for (Pet pet:this->adoption_service.get_adopted_pets_service())
        cout << pet << "\n\n";
    this->adoption_service.open_with_app();
}


void UIUser::options_for_seeing_pets_one_by_one_no_add() {
    cout << "0.Exit\n";
    cout << "1.Next pet\n";
}

void UIUser::pets_one_by_one_operations_no_add() {
    int current_index = 0;
    int option;
    while (true) {
        cout << this->adoption_service[current_index] << "\n\n";
        //ShellExecuteA(NULL, NULL, "chrome.exe", this->adoption_service[current_index].get_photograph(), NULL, SW_SHOWMAXIMIZED);
        this->options_for_seeing_pets_one_by_one_no_add();
        cout << "Your choice:";
        cin.ignore();
        cin >> option;
        if (option < 0 || option > 1)
            cout << "Invalid option!\n\n";
        if (option == 0) return;
        if (option == 1) {
            if (current_index == this->adoption_service.number_of_adopted_pets_service() - 1)
                current_index = 0;
            else current_index++;
        }
    }
}

void UIUser::print_adoption_list_one_by_one() {
    if (this->adoption_service.number_of_adopted_pets_service() == 0) {
        cout << "Your adoption list is currently empty!\n";
        return;
    }
    this->pets_one_by_one_operations_no_add();


}

void UIUser::run_user_program_ui() {
    int choice;
    this->print_main_menu_options();
    cout << "your choice:";
    cin >> choice;
    cout << "\n";
    while (true) {
        if (choice < 0 || choice > 4) cout << "Invalid choice!\n";
        if (choice == 4) return;
        if (choice == 0) this->print_main_menu_options();
        if (choice == 1) this->pets_one_by_one_operations(this->pet_service, this->adoption_service);
        if (choice == 2) this->print_all_pets_by_breed_and_age();
        if (choice == 3) {
            this->print_adoption_list();
            //this->print_adoption_list_one_by_one();
        }
        cout << "your choice:";
        cin >> choice;
        cout << "\n";
    }
}