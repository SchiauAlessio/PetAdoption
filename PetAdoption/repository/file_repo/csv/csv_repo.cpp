//
// Created by Alessio on 15/04/2021.
//

#include <fstream>
#include "csv_repo.h"

AdoptionRepoCSV::AdoptionRepoCSV(const std::string &file_name){
    this->file_name=file_name;
    std::ofstream out;
    out.open(file_name, std::ios_base::trunc);
    out.close();
}
AdoptionRepoCSV::~AdoptionRepoCSV()
{
    AdoptionRepoCSV::write_data();
}
void AdoptionRepoCSV::open_app()
{
    std::string path="notepad \"" + this->file_name + "\"";
    system(path.c_str());
}
