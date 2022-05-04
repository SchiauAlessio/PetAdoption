//
// Created by Alessio on 15/04/2021.
//


#include "../file_repo.h"
#include "../file_repo_adoption.h"
class AdoptionRepoCSV : public AdoptionRepositoryFile
{
public:
    explicit AdoptionRepoCSV(const std::string& file_name);
    void open_app();
    ~AdoptionRepoCSV();

};