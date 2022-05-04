//
// Created by Alessio on 15/05/2021.
//


#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include "../repository/repo.h"
#include "../repository/adoption_repo.h"
#include "../service/service.h"
class MainWindow :public QDialog
{
Q_OBJECT
private:
    std::string password;
    PetRepository *pet_repo;
    AdoptionRepo *adoption_repo;
    PetService* pet_service;
    QLineEdit *pet_repo_file;
    QPushButton *pet_repo_path_select_button;
    QLineEdit *adoption_repo_file;
    QPushButton *adoption_repo_path_select_button;
    QPushButton *user;
    QPushButton *admin;
    QLineEdit *admin_password;
public:
    explicit MainWindow(QWidget *parent = 0);
private:
    void init();
    void connect_slots();
    void get_pet_repo_file_path();
    void get_adoption_repo_file_path();
    void run_user();
    void run_admin();
    bool check_password();
};
