//
// Created by Alessio on 15/05/2021.
//


#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QTextEdit>
#include <QRadioButton>
#include <QDialog>
#include <QListView>
#include <QTableView>
#include <QFormLayout>
#include "../service/adoption_service.h"
#include "AdoptionList_TableModel.h"
class GUIUser:public QDialog{
Q_OBJECT
private:
    AdoptionService &adoption_service;
    Pet pet;
    PetService* pet_service;
    QListWidget *adoption_list_widget;

    TableModelPetList* pet_list_table;
    QTableView* pet_list_table_view;
    TableModelAdoptedPets* adopted_pet_list_table;
    QTableView* adopted_pets_table_view;

    QLineEdit *enter_breed;
    QLineEdit* max_age;
    QPushButton *get_breed_and_age;
    QListWidget *current_pet;
    QPushButton *adopt_pet;
    QPushButton *next;
    QPushButton *open_file;
    QPushButton *back;
    QPushButton *display_adoption_list;
    QPushButton* redisplay_available_pets;

    QVBoxLayout* mainLayout;
    int index;
    bool main_index;
public:
    explicit GUIUser(AdoptionService &adoption_srv, QWidget *parent = 0);
private:
    void init();
    void populate();
    void connect_buttons();
    void get_pets_by_breed_and_age();
    void add_pet_to_adoption_list();
    void show_next_pet();
    void show_adoption_list();
    void go_back_to_main_window();
};

