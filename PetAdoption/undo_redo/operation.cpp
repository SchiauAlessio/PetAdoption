//
// Created by Alessio on 28/05/2021.
//

#include "operation.h"
AdminOperation::AdminOperation(const Pet &pet, const Pet &other_pet): pet{pet},other_pet{other_pet}{}
Undo::Undo(PetService &pet_service, HandlerService service_handler, const Pet &pet,
                             const Pet &other_pet):pet_service{pet_service},service_handler{service_handler},
                                                   AdminOperation(pet,other_pet) {}

void Undo::run_command() {
    if(this->service_handler==&PetService::add_pet_service||this->service_handler==&PetService::delete_pet_service)
        ((this->pet_service).*this->service_handler)(this->pet.get_breed(),this->pet.get_name(),this->pet.get_age(),this->pet.get_photograph());
    else
        ((this->pet_service).*&PetService::update_pet_service)(this->other_pet.get_breed(),this->other_pet.get_name(),this->pet.get_breed(),this->pet.get_name(),this->pet.get_age(),this->pet.get_photograph());
}

Redo *Undo::get_redo_operation() {
    return new Redo{this->pet_service, this->service_handler, this->other_pet, this->pet};
}

Redo::Redo(PetService & pet_service, HandlerService service_handler, const Pet & pet, const Pet & other_pet):pet_service{pet_service},service_handler{service_handler},
                                                                                     AdminOperation{pet,other_pet} {
    this->function=-1;
}

void Redo::run_command() {
    if(this->service_handler==&PetService::add_pet_service)
        ((this->pet_service).*&PetService::delete_pet_service)(this->pet.get_breed(),this->pet.get_name(),this->pet.get_age(),this->pet.get_photograph());
    else
        if(this->service_handler==&PetService::delete_pet_service)
            ((this->pet_service).*&PetService::add_pet_service)(this->pet.get_breed(),this->pet.get_name(),this->pet.get_age(),this->pet.get_photograph());
        else
            ((this->pet_service).*&PetService::update_pet_service)(this->other_pet.get_breed(),this->other_pet.get_name(),this->pet.get_breed(),this->pet.get_name(),this->pet.get_age(),this->pet.get_photograph());
}

Undo *Redo::get_undo_operation() {
    return new Undo{this->pet_service,this->service_handler,this->other_pet,this->pet};
}