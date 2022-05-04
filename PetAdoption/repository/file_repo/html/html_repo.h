//
// Created by Alessio on 15/04/2021.
//

#include "../file_repo_adoption.h"
#include "../file_repo.h"
class AdoptionRepoHTML : public AdoptionRepositoryFile
{
public:
    explicit AdoptionRepoHTML(const std::string &);
    ~AdoptionRepoHTML();
    void write_data() override;
    void add_pet_to_adoption_list_repo(const Pet &pet) override;
    void remove_adopted_pet_repo(const Pet &) override;
    void open_app();
};


