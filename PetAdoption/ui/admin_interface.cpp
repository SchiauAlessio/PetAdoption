//
// Created by Alessio on 22/03/2021.
//

#include "admin_interface.h"
#include <iostream>
#include <cstring>
#include <string>
#include "../validators/exceptions.h"
using namespace std;
UIAdmin::UIAdmin(PetService &pet_service): pet_service(pet_service){}
void UIAdmin::print_main_menu() {
    cout<<"0.Re-print menu.\n1.Add a pet.\n2.Delete a pet.\n3.Update a pet.\n4.Print all pets.\n5.Exit\n";
}
void UIAdmin::add_pet_ui() {
    string breed,name,photograph;
    float age;
    cout<<"breed:";
    cin.ignore();
    getline(cin,breed);
    //cin>>breed;
    cout<<"name:";
    //cin.ignore();
    getline(cin,name);
    //cin>>name;
    cout<<"age:";
    cin>>age;
    cout<<"photograph:";
    //cin>>photograph;
    cin.ignore();
    getline(cin,photograph);
    this->pet_service.add_pet_service(breed,name,age,photograph);
    cout<<"Operation executed successfully\n";
}
void UIAdmin::delete_pet_ui() {
    string name,breed;
    cout<<"breed:";
    cin.ignore();
    getline(cin,breed);
    //cin>>breed;
    cout<<"name:";
    //cin.ignore();
    getline(cin,name);
    //cin>>name;
    this->pet_service.delete_pet_service(breed,name,1,"");
    cout<<"Operation executed successfully!\n";
}
void UIAdmin::update_pet_ui() {
    string name,breed,photograph,old_breed,old_name;
    float age;
    cout<<"Enter the breed of the pet to be updated: ";
    cin.ignore();
    getline(cin,old_breed);
    cout<<"Enter the name of the pet to be updated: ";
    getline(cin,old_name);
    cout<<"new breed:";
    //cin.ignore();
    getline(cin,breed);
    //cin>>breed;
    cout<<"new name:";
    //cin.ignore();
    getline(cin,name);
    //cin>>name;
    cout<<"new age:";
    cin>>age;
    cout<<"new photograph:";
    cin.ignore();
    getline(cin,photograph);
    //cin>>photograph;
    this->pet_service.update_pet_service(old_breed,old_name,breed,name,age,photograph);
    cout<<"Operation executed successfully!\n";
}
//void UIAdmin::ui_breeds_for_dogs_with_age_less_than() {
//    float maximum_age;
//    cout<<"enter the maximum age(k):";
//    cin>>maximum_age;
//    vector<string> breeds=this->pet_service.get_breed_pets_with_age_less(maximum_age);
//    for(int index=0;index<breeds.size()-1;index++)
//        if(breeds[index]==breeds[index+1])
//            breeds.erase(breeds.begin()+index);
//    for(auto breed:breeds){
//        cout<<breed<<" ";
//    }
//    cout<<endl;
//}
void UIAdmin::print_pets_ui() {
    int number_of_pets=this->pet_service.pets_count_service();
    if(number_of_pets==0){
        cout<<"No pets available!\n";
    }
    else{
        cout<<"------------------------------------------------------------------------------------------------------------\n";
//        for(int index=0;index<number_of_pets;index++)
//            cout<<this->pet_service[index]<<"\n\n";
        for(Pet pet:this->pet_service.get_all_pets_service())
            cout<<pet<<"\n\n";
        cout<<"------------------------------------------------------------------------------------------------------------\n";
    }
    cout<<"\n";
}
void UIAdmin::run_user_menu() {
    this->print_main_menu();
    while(true){
        string user_choice;
        cout<<"your choice:";
        cin>>user_choice;
        //if(user_choice<0||user_choice>5)
            //cout<<"Choice does not exist\n";
        if(user_choice=="0")
                this->print_main_menu();
        else if(user_choice=="1"){
            try{
            this->add_pet_ui();}
            catch(const ValidatorException &valid_exc)
            {
                cout<<valid_exc.what();
            }
            catch(const RepositoryException &repo_exc)
            {
                cout<<repo_exc.what();
            }
        }
        else if(user_choice=="2"){
            try {this->delete_pet_ui();}
            catch(const ValidatorException &valid_exc)
            {
                cout<<valid_exc.what();
            }
            catch(const RepositoryException &repo_exc)
            {
                cout<<repo_exc.what();
            }
        }
        else if(user_choice=="3"){
            try{
            this->update_pet_ui();}
            catch(const ValidatorException &valid_exc)
        {
            cout<<valid_exc.what();
        }
        catch(const RepositoryException &repo_exc)
        {
            cout<<repo_exc.what();
        }}
        else if(user_choice=="4"){
            try{this->print_pets_ui();}
            catch(const ValidatorException &valid_exc)
            {
                cout<<valid_exc.what();
            }
            catch(const RepositoryException &repo_exc)
            {
                cout<<repo_exc.what();
            }
        }
        else if(user_choice=="5")
            return;
        else cout<<"Invalid option!\n";
    }
}