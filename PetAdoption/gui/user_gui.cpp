//
// Created by Alessio on 15/05/2021.
//

#include "user_gui.h"
#include <windows.h>
#include <shellapi.h>
#include <qlayout.h>
#include <QFormLayout>
#include <QLabel>
#include <validators/exceptions.h>
#include <QMessageBox>
#include <gui/initial_state.h>
#include <iostream>
using namespace std;
GUIUser::GUIUser(AdoptionService &adoption_srv, QWidget *parent) : QDialog(parent), adoption_service{adoption_srv}
{
    this->index=0;
    this->main_index=true;
    this->pet_service=new PetService{this->adoption_service.pet_repo};
    this->init();
    this->populate();
    this->connect_buttons();
}

void GUIUser::init()
{
    this->adoption_list_widget = new QListWidget{};
    this->enter_breed = new QLineEdit{};
    this->max_age=new QLineEdit{};
    this->get_breed_and_age = new QPushButton{QString::fromStdString("get")};
    this->current_pet = new QListWidget{};
    this->current_pet->setMaximumHeight(100);

    this->pet_list_table=new TableModelPetList{*this->pet_service};
    this->pet_list_table_view= new QTableView{};
    this->pet_list_table_view->setModel(this->pet_list_table);
    this->pet_list_table_view->resizeColumnsToContents();
    this->pet_list_table_view->resizeRowsToContents();

    this->adopted_pet_list_table=new TableModelAdoptedPets{this->adoption_service};
    this->adopted_pets_table_view= new QTableView{};
    this->adopted_pets_table_view->setModel(this->adopted_pet_list_table);
    this->adopted_pets_table_view->resizeColumnsToContents();
    this->adopted_pets_table_view->resizeRowsToContents();

    this->adopt_pet = new QPushButton{QString::fromStdString("adopt")};
    this->next = new QPushButton{QString::fromStdString("next")};
    this->display_adoption_list = new QPushButton{QString::fromStdString("List the adopted pets")};
    this->redisplay_available_pets = new QPushButton{QString::fromStdString("Re-List all available pets")};
    this->open_file = new QPushButton{"open file in app"};
    this->back = new QPushButton{"back"};

    this->mainLayout = new QVBoxLayout{this};
    mainLayout->addWidget(this->pet_list_table_view);
    //mainLayout->addWidget(this->adoption_list_table_view);
    //mainLayout->addWidget(this->adopted_pets_table_view,100,Qt::AlignRight);

    auto *by_breed_and_age_layout = new QHBoxLayout{};
    by_breed_and_age_layout->addWidget(new QLabel{"Pets by breed and age: "});
    by_breed_and_age_layout->addWidget(this->enter_breed);
    by_breed_and_age_layout->addWidget(this->max_age);
    by_breed_and_age_layout->addWidget(this->get_breed_and_age);
    mainLayout->addLayout(by_breed_and_age_layout);

    mainLayout->addWidget(new QLabel{"Current pet: "});

    auto *current = new QHBoxLayout{};
    current->addWidget(this->current_pet);
    current->addWidget(this->adopt_pet);
    current->addWidget(this->next);
    mainLayout->addLayout(current);

    mainLayout->addWidget(this->display_adoption_list,10,Qt::AlignLeft);
    mainLayout->addWidget(this->redisplay_available_pets,10,Qt::AlignLeft);

    mainLayout->addWidget(this->open_file, 1, Qt::AlignRight);
    mainLayout->addWidget(this->back, 1, Qt::AlignRight);
}
void GUIUser::populate()
{
    if(this->adoption_service.total_number_of_pets()==0){
        this->adoption_list_widget->clear();
        this->current_pet->clear();
        QMessageBox messageBox;
        messageBox.setText("No pets available!");
        messageBox.exec();
        return;}
    this->main_index=true;
    this->pet=this->adoption_service.pet_repo[this->index];
    this->current_pet->clear();
    this->current_pet->addItem(QString::fromStdString(this->pet.to_string()));
    this->adoption_list_widget->clear();
    for (const auto &pet_current:this->adoption_service.get_all_available_pets_to_adopt())
        this->adoption_list_widget->addItem(QString::fromStdString(pet_current.to_string()));
}
void GUIUser::connect_buttons()
{
    QObject::connect(this->get_breed_and_age, &QPushButton::clicked, this, &GUIUser::get_pets_by_breed_and_age);
    QObject::connect(this->adopt_pet, &QPushButton::clicked, this, &GUIUser::add_pet_to_adoption_list);
    QObject::connect(this->next, &QPushButton::clicked, this, &GUIUser::show_next_pet);
    QObject::connect(this->open_file, &QPushButton::clicked, this, [this]() {
        this->adoption_service.open_with_app();
    });
    QObject::connect(this->back, &QPushButton::clicked, this, &GUIUser::go_back_to_main_window);
    QObject::connect(this->display_adoption_list,&QPushButton::clicked,this,&GUIUser::show_adoption_list);
    QObject::connect(this->redisplay_available_pets,&QPushButton::clicked,this,&GUIUser::populate);
}
void GUIUser::get_pets_by_breed_and_age()
{
    try
    {
        this->main_index=false;
        this->index=0;
        const std::string& breed = this->enter_breed->text().toStdString();
        float age=std::stof(this->max_age->text().toStdString());
        PetService pets_breed_age=this->adoption_service.get_dogs_with_breed_and_age(breed,age);
        if(pets_breed_age.pets_count_service()==0){
            QMessageBox messageBox;
            messageBox.setText("No pets available with these characteristics!");
            messageBox.exec();
            return;
        }
        this->pet = pets_breed_age[index];
//        ShellExecuteA(NULL, NULL, "chrome.exe",
//                      this->pet.get_photograph().c_str(), NULL, SW_SHOWMAXIMIZED);
        this->current_pet->clear();
        this->current_pet->addItem(QString::fromStdString(this->pet.to_string()));
    }
    catch (...)
    {
        QMessageBox message;
        message.setText("Invalid input.\n");
        message.exec();
    }
}
void GUIUser::add_pet_to_adoption_list()
{
    try
    {
        this->adoption_service.add_pet_to_adoption_list_service(this->pet);
        this->adoption_service.pet_repo.delete_pet_repo(this->pet);
        this->index--;
        this->show_next_pet();
//        ShellExecuteA(NULL, NULL, "chrome.exe",
//                      this->pet.get_photograph().c_str(), NULL, SW_SHOWMAXIMIZED);
        QMessageBox message;
        message.setText("Pet was adopted successfully!");
        message.exec();
    }
    catch (const RepositoryException &repo_exception)
    {
        QMessageBox message;
        message.setText(repo_exception.what());
        message.exec();

    }
    catch (...)
    {
        QMessageBox message;
        message.setText("Invalid input!\n");
        message.exec();
    }
}
void GUIUser::show_next_pet()
{
    try
    {
        if(this->main_index==true){
        this->index++;
        if(this->index==this->adoption_service.total_number_of_pets())
            this->index=0;
        this->pet = this->adoption_service.pet_repo[this->index];
        this->current_pet->clear();
        this->current_pet->addItem(QString::fromStdString(this->pet.to_string()));}
        else{
            this->index++;
            if(this->index==this->adoption_service.dogs_with_breed_and_age.pets_count_service())
                this->index=0;
            this->pet=this->adoption_service.dogs_with_breed_and_age[this->index];
            this->current_pet->clear();
            this->current_pet->addItem(QString::fromStdString(this->pet.to_string()));
        }
//        ShellExecuteA(NULL, NULL,"chrome.exe",
//                      this->pet.get_photograph().c_str(), NULL, SW_SHOWMAXIMIZED);
    }
    catch (...)
    {
        QMessageBox message;
        message.setText("Invalid input!");
        message.exec();
    }
}
void GUIUser::show_adoption_list()
{
//    this->adoption_list_widget->clear();
//    for (const auto &pet_current:this->adoption_service.get_adopted_pets_service())
//        this->adoption_list_widget->addItem(QString::fromStdString(pet_current.to_string()));
    mainLayout->removeWidget(this->adopted_pets_table_view);
    this->adopted_pet_list_table=new TableModelAdoptedPets{this->adoption_service};
    this->adopted_pets_table_view= new QTableView{};
    this->adopted_pets_table_view->setModel(this->adopted_pet_list_table);
    this->adopted_pets_table_view->resizeColumnsToContents();
    this->adopted_pets_table_view->resizeRowsToContents();
    mainLayout->addWidget(this->adopted_pets_table_view);

    ///make a timed wait before removing the widget
    // does not work yet
//    using namespace std::this_thread;
//    using namespace std::chrono;
//    sleep_until(system_clock::now()+seconds(7));
//    mainLayout->removeWidget(this->adopted_pets_table_view);

}
void GUIUser::go_back_to_main_window()
{
    auto *gui = new MainWindow{};
    this->close();
    gui->setWindowTitle("Pet Shelter");
    gui->resize(800, 600);
    gui->show();
}