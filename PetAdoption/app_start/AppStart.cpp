//
// Created by Alessio on 15/05/2021.
//

#include "AppStart.h"
#include "../service/service.h"
#include "../service/adoption_service.h"
#include "ui/admin_interface.h"
#include "ui/user_interface.h"
#include "../tests/program_tests.h"
#include "../repository/file_repo/file_repo.h"
#include "../repository/file_repo/csv/csv_repo.h"
#include "../repository/file_repo/html/html_repo.h"
void AppStart::run_main_program_admin(PetRepository &pet_repo) {
    PetService pet_service(pet_repo);
    UIAdmin ui(pet_service);
    ui.run_user_menu();
}

void AppStart::run_main_program_user(PetRepository &pet_repo, AdoptionRepositoryFile& adoption_repo_file) {
    PetRepository dogs_with_breed_and_service_repo;
    PetService pet_service(pet_repo);
    PetService dogs_with_breed_and_age_service(dogs_with_breed_and_service_repo);
    //AdoptionRepositoryFile adoption_repo("../repository/file_repo/adoption_list.txt");
    AdoptionService adoption_service(adoption_repo_file, pet_repo, dogs_with_breed_and_age_service);
    UIUser ui_user(adoption_service, pet_service);
    ui_user.run_user_program_ui();
}
void AppStart::run_program() {
    run_all_tests();
    PetRepositoryFile pet_repo("../repository/file_repo/file_repo.txt");
    AdoptionRepoCSV adoption_repo_csv("../repository/file_repo/csv/adoption_list.csv");
    AdoptionRepoHTML adoption_repo_html("../repository/file_repo/html/adoption_list.html");
    int choice;
    cout << "0.Admin\n";
    cout << "1.User\n";
    cout << "Choose application start mode:";
    cin >> choice;
    if (choice == 0) run_main_program_admin(pet_repo);
    else if (choice == 1){
        int file_type_choice;
        cout<<"0.CSV\n";
        cout<<"1.HTML\n";
        cout<<"Choose adoption list file type:";
        cin>>file_type_choice;
        if(file_type_choice==0)
            run_main_program_user(pet_repo,adoption_repo_csv);
        if(file_type_choice==1)
            run_main_program_user(pet_repo,adoption_repo_html);
    }
}