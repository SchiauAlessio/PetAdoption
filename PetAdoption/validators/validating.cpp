//
// Created by Alessio on 21/03/2021.
//

#include "validating.h"
#include<cstring>
#include "exceptions.h"
void PetValidator::validate_given_pet(const Pet &pet) {
    std::string operation_exceptions="";
    if(pet.get_breed()=="")
        operation_exceptions+="Invalid input!The breed of an animal can not be an empty string!\n";
    if(pet.get_name()=="")
        operation_exceptions+="Invalid input!The name of an animal can not be an empty string!\n";
    if(pet.get_photograph()=="")
        operation_exceptions+="Invalid input!The link can not be an empty string!\n";
    if(pet.get_age()<=0)
        operation_exceptions+="Invalid input!The age must be a positive input!\n";
    if(operation_exceptions.size()!=0)
        throw ValidatorException(operation_exceptions);
}