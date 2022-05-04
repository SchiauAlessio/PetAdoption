//
// Created by Alessio on 11/04/2021.
//

#include "../adoption_repo.h"
class AdoptionRepositoryFile : public AdoptionRepo
{
protected:
    std::string file_name;
    virtual void write_data();
private:
    void read_data();
    void append_data(const Pet &pet);
public:
    AdoptionRepositoryFile();
    explicit AdoptionRepositoryFile(const std::string& file_name);
    virtual void remove_adopted_pet_repo(const Pet& pet);
    void add_pet_to_adoption_list_repo(const Pet& pet_to_be_added);
};
