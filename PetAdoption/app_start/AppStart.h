//
// Created by Alessio on 15/05/2021.
//


#include "../repository/repo.h"
#include "../repository/file_repo/file_repo_adoption.h"
using namespace std;
class AppStart {
private:
    void run_main_program_admin(PetRepository &pet_repo);
    void run_main_program_user(PetRepository &pet_repo, AdoptionRepositoryFile& adoption_repo_file);
public:
    void run_program();
};


#endif
