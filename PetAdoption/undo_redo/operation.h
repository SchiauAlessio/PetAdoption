//
// Created by Alessio on 28/05/2021.
//

#include "../service/service.h"
#include "../service/adoption_service.h"
#include <string>

typedef void (PetService::*HandlerService)(const std::string& breed,const std::string& name,float age,const std::string& photograph);
typedef void (PetService::*HandlerUpdateService)(const std::string& old_breed,const std::string& old_name,const std::string& breed,const std::string& name,float age,const std::string& photograph);

class Operation{
public:
    virtual void run_command()=0;

};

class AdminOperation:public Operation{
protected:
    Pet pet;
    Pet other_pet;
public:
    AdminOperation(const Pet& pet,const Pet& other_pet);
};

class Redo;

class Undo:public AdminOperation{
private:
    PetService& pet_service;
    HandlerService service_handler;
public:
    explicit Undo(PetService& pet_service,HandlerService service_handler,const Pet& pet,const Pet& other_pet);
    void run_command() override;
    Redo* get_redo_operation();
};

class Redo : public AdminOperation
{
private:
    PetService &pet_service;
    HandlerService service_handler;
    int function;
public:
    explicit Redo(PetService &pet_service, HandlerService service_handler, const Pet &pet, const Pet &other_pet);
    void run_command() override;
    Undo *get_undo_operation();
};
