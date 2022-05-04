//
// Created by Alessio on 10/04/2021.
//

#include "../repo.h"
#include "../adoption_repo.h"
class PetRepositoryFile : public PetRepository
{
private:
    std::string file_name;
    void read_data();
    void append_data(const Pet &pet);
    void write_data();
public:
    explicit PetRepositoryFile(const std::string& file_name);
    void add_pet_repo(const Pet &pet);
    void update_pet(const Pet &pet,const Pet& new_pet);
    void delete_pet_repo(const Pet &pet);
};
