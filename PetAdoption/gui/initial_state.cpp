//
// Created by Alessio on 15/05/2021.
//

#include "initial_state.h"
#include <QVBoxLayout>
#include <QFileDialog>
#include <QDebug>
#include <QFormLayout>
#include <QMessageBox>
#include <sstream>
#include "../repository/file_repo/file_repo.h"
#include "../repository/file_repo/file_repo_adoption.h"
#include "../repository/file_repo/csv/csv_repo.h"
#include "../repository/file_repo/html/html_repo.h"
#include "../service/service.h"
#include "../service/adoption_service.h"
#include "../gui/admin_gui.h"
#include "../gui/user_gui.h"
#include <iostream>
using namespace std;
MainWindow::MainWindow(QWidget *parent) : QDialog(parent)
{
    this->init();
    this->connect_slots();
}
void MainWindow::init()
{
    this->pet_repo_file = new QLineEdit{};
    this->pet_repo_file->setText("C:/Users/alfbu/Documents/GitHub/a10-916-Schiau-Alessio-1/repository/file_repo/file_repo.txt");
    this->pet_repo_path_select_button = new QPushButton{"Select pet repository path"};
    this->adoption_repo_file = new QLineEdit{};
    this->adoption_repo_file
            ->setText("C:/Users/alfbu/Documents/GitHub/a10-916-Schiau-Alessio-1/repository/file_repo/html/adoption_list.html");
    this->adoption_repo_path_select_button = new QPushButton{"Select watchlist output file path"};
    this->user = new QPushButton{"User"};
    this->admin = new QPushButton{"Admin"};
    this->admin_password = new QLineEdit{};
    this->admin_password->setText("PASSWORD");

    auto *main_window_layout = new QVBoxLayout{this};

    auto *pet_repo_upper_window_part = new QHBoxLayout{};
    pet_repo_upper_window_part->addWidget(this->pet_repo_file);
    pet_repo_upper_window_part->addWidget(this->pet_repo_path_select_button);
    main_window_layout->addLayout(pet_repo_upper_window_part);

    auto *adoption_list_upper_window_part = new QHBoxLayout{};
    adoption_list_upper_window_part->addWidget(this->adoption_repo_file);
    adoption_list_upper_window_part->addWidget(this->adoption_repo_path_select_button);
    main_window_layout->addLayout(adoption_list_upper_window_part);

    this->user->setFixedSize(300,100);
    this->admin->setFixedSize(300,100);
    main_window_layout->addWidget(this->user, 20, Qt::AlignRight);
    main_window_layout->addWidget(this->admin, 20, Qt::AlignLeft);

    auto *password_layout = new QFormLayout{};
    password_layout->addRow("Admin password: ", this->admin_password);
    this->password="admin";
    main_window_layout->addLayout(password_layout);
}
void MainWindow::connect_slots()
{
    QObject::connect(this->pet_repo_path_select_button, &QPushButton::clicked, this, &MainWindow::get_pet_repo_file_path);
    QObject::connect(this->adoption_repo_path_select_button, &QPushButton::clicked, this,
                     &MainWindow::get_adoption_repo_file_path);
    QObject::connect(this->user, &QPushButton::clicked, this, &MainWindow::run_user);
    QObject::connect(this->admin, &QPushButton::clicked, this, &MainWindow::run_admin);
}
void MainWindow::get_pet_repo_file_path()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Select .txt file for pet repo", "../repository",
                                                  "Repo Files (*.txt)");
    if (file_name != "")
        this->pet_repo_file->setText(file_name);
}
void MainWindow::get_adoption_repo_file_path()
{
    QString file_name = QFileDialog::getOpenFileName(this, "Select .csv or .html file for adoption repo", "../repository", "Text Files (*.csv *.html)");
    if (file_name != "")
        this->adoption_repo_file->setText(file_name);
}
std::vector<std::string> split_string_by_token(std::string given_string, std::string delimiter)
{
    std::string copy=given_string;
    std::vector<std::string> split_array;
    if (copy!= "") {
        vector<string> split_list;
        size_t pos = 0;
        std::string token;
        while ((pos = copy.find(delimiter)) != std::string::npos) {
            token = copy.substr(0, pos);
            split_array.push_back(token);
            copy.erase(0, pos + delimiter.length());
        }
        split_array.push_back(copy);

    }
    return split_array;
}
void MainWindow::run_user()
{
    std::string pet_repo_file_path = this->pet_repo_file->text().toStdString();
    std::string adoption_repo_file_path = this->adoption_repo_file->text().toStdString();
    if (pet_repo_file_path.empty() || adoption_repo_file_path.empty())
    {
        QMessageBox message;
        message.setText("Invalid Path!It can not be empty!");
        message.exec();
        return;
    }
    std::vector<std::string> split_array = split_string_by_token(pet_repo_file_path, ".");
    std::string pet_repo_path_extension = split_array[split_array.size() - 1];
    split_array = split_string_by_token(adoption_repo_file_path, ".");
    std::string adoption_repo_path_extension = split_array[split_array.size() - 1];
    if (pet_repo_path_extension == "txt")
        this->pet_repo = new PetRepositoryFile(pet_repo_file_path);
    else
    {
        QMessageBox message;
        message.setText("Only valid extension for pet repo files is .txt!");
        message.exec();
        return;
    }
    if (adoption_repo_path_extension == "csv")
        this->adoption_repo = new AdoptionRepoCSV(adoption_repo_file_path);
    else if (adoption_repo_path_extension == "html")
        this->adoption_repo = new AdoptionRepoHTML(adoption_repo_file_path);
    else
    {
        QMessageBox message;
        message.setText("The only valid extensions for the adoption repo file are .html and .csv!");
        message.exec();
        return;
    }
    if(this->pet_repo->pets_count_repo()==0){
        QMessageBox message;
        message.setText("It seems our catalogue is empty!");
        message.exec();
        return;
    }
    auto* temporary_pet_repo=new PetRepository();
    this->pet_service= new PetService(*(temporary_pet_repo)); //"empty service" use for dogs with breed and age
    AdoptionService serv{ *(this->adoption_repo),*(this->pet_repo),*(this->pet_service)};
    GUIUser userGui{serv};
    this->close();
    userGui.setModal(true);
    userGui.resize(1000, 600);
    userGui.setWindowTitle("Pet Adoption Center");

    userGui.exec();
}
void MainWindow::run_admin()
{
    if (!this->check_password())
    {
        QMessageBox message;
        message.setText("Wrong password!");
        message.exec();
        return;
    }
    std::string pet_repo_file_path = this->pet_repo_file->text().toStdString();
    if (pet_repo_file_path.empty())
    {
        QMessageBox message;
        message.setText("Path seems to be empty!");
        message.exec();
        return;
    }
    std::vector<std::string> split_array = split_string_by_token(pet_repo_file_path, ".");
    std::string pet_path_extension = split_array[split_array.size() - 1];
    if (pet_path_extension == "txt")
        this->pet_repo = new PetRepositoryFile(pet_repo_file_path);
    else
    {
        QMessageBox message;
        message.setText("Invalid pet repo path!");
        message.exec();
        return;
    }
    PetService service{*(this->pet_repo)};
    UndoRedo undo_redo;
    GUIAdmin adminGui{service,undo_redo};
    this->close();
    adminGui.setModal(true);
    adminGui.setWindowTitle("Pet Shelter");
    adminGui.resize(800, 600);
    adminGui.exec();
}
bool MainWindow::check_password()
{

    std::string input_password = this->admin_password->text().toStdString();
    return MainWindow::password == input_password;
}