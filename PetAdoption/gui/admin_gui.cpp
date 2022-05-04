//
// Created by Alessio on 15/05/2021.
//

#include "admin_gui.h"
#include <QVBoxLayout>
#include <QFormLayout>
#include <validators/exceptions.h>
#include <QMessageBox>
#include <gui/initial_state.h>
#include <QShortcut>

GUIAdmin::GUIAdmin(PetService &s,UndoRedo& undo_redo, QWidget *parent) : QDialog(parent), pet_service{s},undo_redo{undo_redo}
{
    this->init();
    this->populate();
    this->connect_buttons();
}
void GUIAdmin::init()
{
    this->pet_list_widget = new QListWidget{};
    this->breed_line_edit = new QLineEdit{};
    this->name_line_edit = new QLineEdit{};
    this->age_line_edit = new QLineEdit{};
    this->photograph_line_edit = new QLineEdit{};
    this->old_breed_line_edit = new QLineEdit{};
    this->old_name_line_edit = new QLineEdit{};

//    this->pet_list_table=new TableModelPetList{this->pet_service};
//    this->pet_list_table_view= new QTableView{};
//    this->pet_list_table_view->setModel(this->pet_list_table);
//    this->pet_list_table_view->resizeColumnsToContents();
//    this->pet_list_table_view->resizeRowsToContents();

    this->add_pet = new QPushButton{"add"};
    this->update_pet = new QPushButton{"update"};
    this->delete_pet = new QPushButton{"delete"};
    this->undo= new QPushButton{"undo"};
    this->redo= new QPushButton{"redo"};
    this->reset = new QPushButton{"reset"};
    this->back = new QPushButton{"back"};

    auto *main_layout = new QVBoxLayout{this};
    main_layout->addWidget(this->pet_list_widget);
    //main_layout->addWidget(this->pet_list_table_view);

    auto *pet_details = new QFormLayout{};
    pet_details->addRow("BREED: ",this->breed_line_edit);
    pet_details->addRow("NAME: ",this->name_line_edit);
    pet_details->addRow("AGE: ",this->age_line_edit);
    pet_details->addRow("PHOTOGRAPH: ",this->photograph_line_edit);
    pet_details->addRow("OLD BREED: ",this->old_breed_line_edit);
    pet_details->addRow("OLD NAME: ",this->old_name_line_edit);

    main_layout->addLayout(pet_details);
    auto *actions = new QHBoxLayout{};
    actions->addWidget(this->add_pet);
    actions->addWidget(this->update_pet);
    actions->addWidget(this->delete_pet);
    actions->addWidget(this->undo);
    actions->addWidget(this->redo);
    actions->addWidget(this->reset);

    main_layout->addLayout(actions);

    auto *back_layout = new QHBoxLayout{};

    back_layout->addWidget(this->back);
    main_layout->addLayout(back_layout);
}
void GUIAdmin::populate()
{
    this->pet_list_widget->clear();
    for (const auto &m:this->pet_service.get_all_pets_service())
        this->pet_list_widget->addItem(QString::fromStdString(m.to_string()));
}
void GUIAdmin::connect_buttons()
{
    QObject::connect(this->pet_list_widget, &QListWidget::itemSelectionChanged, [this]() {
        int index = this->get_index();
        if (index < 0)
            return;
        Pet pet = this->pet_service[index];
        //auto text=QString::fromStdString(pet.get_breed());

        this->breed_line_edit->setText(QString::fromStdString(pet.get_breed()));
        this->name_line_edit->setText(QString::fromStdString(pet.get_name()));
        this->age_line_edit->setText(QString::fromStdString(std::to_string(pet.get_age())));
        this->photograph_line_edit->setText(QString::fromStdString(pet.get_photograph()));
        this->old_breed_line_edit->setText(QString::fromStdString(pet.get_breed()));
        this->old_name_line_edit->setText(QString::fromStdString(pet.get_name()));
    });
//    QObject::connect(this->pet_list_table_view->selectionModel(), &QItemSelectionModel::selectionChanged, [this]() {
//        int index = this->get_index();
//        if (index < 0)
//            return;
//        Pet pet = this->pet_service[index];
//
//        this->breed_line_edit->setText(QString::fromStdString(pet.get_breed()));
//        this->name_line_edit->setText(QString::fromStdString(pet.get_name()));
//        this->age_line_edit->setText(QString::fromStdString(std::to_string(pet.get_age())));
//        this->photograph_line_edit->setText(QString::fromStdString(pet.get_photograph()));
//        this->old_breed_line_edit->setText(QString::fromStdString(pet.get_breed()));
//        this->old_name_line_edit->setText(QString::fromStdString(pet.get_name()));
//    });


    QObject::connect(this->add_pet, &QPushButton::clicked, this, &GUIAdmin::add_pet_to_repo_gui);
    QObject::connect(this->delete_pet, &QPushButton::clicked, this, &GUIAdmin::delete_pet_repo_gui);
    QObject::connect(this->update_pet, &QPushButton::clicked, this, &GUIAdmin::update_pet_repo_gui);
    QObject::connect(this->undo, &QPushButton::clicked, this, &GUIAdmin::undo_operation);
    QObject::connect(this->redo, &QPushButton::clicked, this, &GUIAdmin::redo_operation);
    QObject::connect(new QShortcut(QKeySequence("Ctrl+Z"), undo), &QShortcut::activated,
                     [this]() { undo->animateClick(); });
    QObject::connect(new QShortcut(QKeySequence("Ctrl+Y"), redo), &QShortcut::activated,
                     [this]() { redo->animateClick(); });
    QObject::connect(this->reset, &QPushButton::clicked, this, &GUIAdmin::reset_text_fields);
    QObject::connect(this->back, &QPushButton::clicked, this, &GUIAdmin::return_to_main_window);
}
int GUIAdmin::get_index() const
{
    QModelIndexList selected_indexes = this->pet_list_widget->selectionModel()->selectedIndexes();
    //QModelIndexList selected_indexes = this->pet_list_table_view->selectionModel()->selectedRows();
    if (selected_indexes.empty())
    {
        int invalid_index=-1;
        this->breed_line_edit->clear();
        this->name_line_edit->clear();
        this->age_line_edit->clear();
        this->photograph_line_edit->clear();
        this->old_breed_line_edit->clear();
        this->old_name_line_edit->clear();
        return invalid_index;
    }
    int selected_index = selected_indexes.at(0).row();
    return selected_index;
}
void GUIAdmin::add_pet_to_repo_gui()
{
    try
    {
        std::string breed = this->breed_line_edit->text().toStdString();
        std::string name = this->name_line_edit->text().toStdString();
        float age = this->age_line_edit->text().toFloat();
        std::string photograph = this->photograph_line_edit->text().toStdString();
        this->pet_service.add_pet_service(breed,name,age,photograph);
        this->populate();
        this->pet_list_widget->setCurrentRow(this->pet_service.pets_count_service() - 1);

        this->undo_redo.empty_redo_stack();
        Pet pet{breed, name, age, photograph};
        auto *operation = new Undo{this->pet_service, &PetService::delete_pet_service, pet, pet};
        this->undo_redo.push_undo_to_stack(operation);
        QMessageBox messageBox;
        messageBox.setText("Pet was added successfully!");
        messageBox.exec();
    }
    catch (const RepositoryException &repo_exception)
    {
        QMessageBox message;
        message.setText(repo_exception.what());
        message.exec();
    }
    catch (const ValidatorException &validator_exception)
    {
        QMessageBox message;
        message.setText(validator_exception.what());
        message.exec();
    }
    catch (...)
    {
        QMessageBox message;
        message.setText("An error has occurred!");
        message.exec();
    }
}
void GUIAdmin::update_pet_repo_gui()
{
    try
    {
        std::string old_pet_breed=this->old_breed_line_edit->text().toStdString();
        std::string old_pet_name=this->old_name_line_edit->text().toStdString();
        std::string breed = this->breed_line_edit->text().toStdString();
        std::string name = this->name_line_edit->text().toStdString();
        float age = this->age_line_edit->text().toFloat();
        std::string photograph = this->photograph_line_edit->text().toStdString();
        Pet old_pet;
        int index=this->pet_service.search_pet_service(old_pet_breed,old_pet_name);
        if(index!=-1)
            old_pet=this->pet_service[index];
        Pet new_pet{breed,name,age,photograph};
        this->pet_service.update_pet_service(old_pet_breed, old_pet_name, breed, name, age, photograph);
        this->populate();
        this->pet_list_widget->setCurrentRow(this->pet_service.pets_count_service() - 1);

        this->undo_redo.empty_redo_stack();
        auto *operation = new Undo{this->pet_service, &PetService::empty_function_for_undo_redo, old_pet, new_pet};
        this->undo_redo.push_undo_to_stack(operation);
        QMessageBox messageBox;
        messageBox.setText("Pet was updated successfully!");
        messageBox.exec();
    }
    catch (const RepositoryException &repo_exception)
    {
        QMessageBox message;
        message.setText(repo_exception.what());
        message.exec();
    }
    catch (const ValidatorException &validator_exception)
    {
        QMessageBox message;
        message.setText(validator_exception.what());
        message.exec();
    }
    catch (...)
    {
        QMessageBox message;
        message.setText("An error has occurred!");
        message.exec();
    }
}
void GUIAdmin::delete_pet_repo_gui()
{
    try
    {
        std::string breed = this->breed_line_edit->text().toStdString();
        std::string name = this->name_line_edit->text().toStdString();
        int index_found_at=this->pet_service.search_pet_service(breed,name);
        Pet pet;
        Pet wrong_pet("","",0,"");
        if(index_found_at!=-1)
            pet=this->pet_service[index_found_at];
        else
            pet=wrong_pet;
        this->pet_service.delete_pet_service(breed,name,1,"");
        this->populate();
        this->pet_list_widget->setCurrentRow(this->pet_service.pets_count_service() - 1);
        this->undo_redo.empty_redo_stack();
        auto *operation = new Undo{this->pet_service, &PetService::add_pet_service, pet, pet};
        this->undo_redo.push_undo_to_stack(operation);
        QMessageBox messageBox;
        messageBox.setText("Pet removed successfully!");
        messageBox.exec();
    }
    catch (const RepositoryException &repo_exception)
    {
        QMessageBox message;
        message.setText(repo_exception.what());
        message.exec();
    }
    catch (const ValidatorException &validator_exception)
    {
        QMessageBox message;
        message.setText(validator_exception.what());
        message.exec();
    }
    catch (...)
    {
        QMessageBox message;
        message.setText("An error has occurred!");
        message.exec();
    }
}
void GUIAdmin::reset_text_fields()
{
    this->breed_line_edit->clear();
    this->name_line_edit->clear();
    this->age_line_edit->clear();
    this->photograph_line_edit->clear();
    this->old_breed_line_edit->clear();
    this->old_name_line_edit->clear();
}
void GUIAdmin::return_to_main_window()
{
    auto *gui = new MainWindow{};
    this->close();
    gui->setWindowTitle("Pet Shelter");
    gui->resize(900, 600);
    gui->show();
}

void GUIAdmin::undo_operation() {
    try {
        this->undo_redo.undo();
        this->populate();
        QMessageBox message;
        message.setText("Undo successfully executed!");
        message.exec();
    }catch (const UndoRedoException &undo_exception)
    {
        QMessageBox message;
        message.setText(undo_exception.what());
        message.exec();
    }
}

void GUIAdmin::redo_operation() {
    try
    {
        this->undo_redo.redo();
        this->populate();

        QMessageBox message;
        message.setText("Redo successfully executed!");
        message.exec();
    }
    catch (const UndoRedoException &redo_exception)
    {
        QMessageBox message;
        message.setText(redo_exception.what());
        message.exec();
    }
}

