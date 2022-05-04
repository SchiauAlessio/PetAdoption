//
// Created by Alessio on 21/03/2021.
//
#include<iostream>
#include "ui/admin_interface.h"
#include "tests/program_tests.h"
#include "ui/user_interface.h"
#include "service/adoption_service.h"
#include "repository/adoption_repo.h"
#include "repository/file_repo/file_repo.h"
#include "repository/file_repo/file_repo_adoption.h"
#include "repository/file_repo/csv/csv_repo.h"
#include "repository/file_repo/html/html_repo.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QPushButton>
#include "app_start/AppStart.h"
#include "gui/initial_state.h"
using namespace std;

int main(int argc,char* argv[]) {
    //run_all_tests();
    QApplication a(argc, argv);

    auto *gui = new MainWindow{};
    gui->setWindowTitle("Dogs Shelter");
    gui->resize(800, 600);
    gui->show();
    return QApplication::exec();
    //return 0;
}
