//
// Created by Alessio on 15/04/2021.
//
#include <fstream>
#include "html_repo.h"
#include <windows.h>

AdoptionRepoHTML::AdoptionRepoHTML(const std::string &file_name) {
    this->file_name = file_name;
    std::ofstream out;
    out.open(file_name, std::ios_base::trunc);
    out.close();
}

AdoptionRepoHTML::~AdoptionRepoHTML() {
    AdoptionRepoHTML::write_data();
}

void AdoptionRepoHTML::add_pet_to_adoption_list_repo(const Pet &pet) {
    AdoptionRepo::add_pet_to_adoption_list_repo(pet);
    AdoptionRepoHTML::write_data();
}

void AdoptionRepoHTML::remove_adopted_pet_repo(const Pet &pet) {
    AdoptionRepo::remove_adopted_pet_repo(pet);
    AdoptionRepoHTML::write_data();
}

void AdoptionRepoHTML::open_app() {
    //LPCTSTR pointer to const TCHAR(TCHAR being a char)
//    LPCTSTR path = "../html/adoption_list.html"; CHANGE WITH ABSOLUTE PATH
//    ShellExecute(NULL, "open", path,
//                 NULL, NULL, SW_SHOWNORMAL);
}

void AdoptionRepoHTML::write_data() {
    std::ofstream out;
    out.open(this->file_name, std::ios_base::trunc);
    out << "<!DOCTYPE html>\n";
    out << "<html>\n";
    out << "<head>\n";
    out << "\t<title>Adoption List</title>\n";
    out << "</head>\n";
    out << "<body>\n";
    out << "<table border=\"1\">";
    out << "\t<tr>\n";
    out << "\t\t<td>Breed</td>\n";
    out << "\t\t<td>Name</td>\n";
    out << "\t\t<td>Age</td>\n";
    out << "\t\t<td>Photograph</td>\n";
    out << "\t</tr>\n";
    for (Pet pet:AdoptionRepo::get_adopted_pets()) {
        out << "\t<tr>\n";
        out << "\t\t<td>" + pet.get_breed() + "</td>\n";
        out << "\t\t<td>" + pet.get_name() + "</td>\n";
        out << "\t\t<td>" + std::to_string(pet.get_age()) + "</td>\n";
        out << "\t\t<td><a href=" + pet.get_photograph() + ">Link</a></td>\n";
        out << "\t</tr>\n";
    }
    out << "</table>\n";
    out << "</body>\n";
    out << "</html>\n";
    out.close();
}
