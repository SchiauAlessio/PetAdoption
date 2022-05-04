//
// Created by Alessio on 29/05/2021.
//

#include "AdoptionList_TableModel.h"
#include <QFont>
#include <QBrush>
#include <QStyle>
#include <QPushButton>

TableModelPetList::TableModelPetList(PetService &pet_service) : pet_service{pet_service}
{}
int TableModelPetList::rowCount(const QModelIndex &parent) const
{
    return this->pet_service.pets_count_service();
}
int TableModelPetList::columnCount(const QModelIndex &parent) const
{
    return 4;
}
QVariant TableModelPetList::data(const QModelIndex &index, int role) const
{
    int row = index.row(), column = index.column();
    Pet pet = this->pet_service[row];
    if (role == Qt::DisplayRole)
    {
        if (column == 0)return QString::fromStdString(pet.get_breed());
        else if (column == 1)return QString::fromStdString(pet.get_name());
        else if (column == 2)return QString::fromStdString(std::to_string(pet.get_age()));
        else if (column == 3)return QString::fromStdString(pet.get_photograph());

    }
    return QVariant();
}
QVariant TableModelPetList::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            if (section == 0)return QString("BREED");
            else if (section == 1)return QString("NAME");
            else if (section == 2)return QString("AGE");
            else if (section == 3)return QString("PHOTOGRAPH");
        }
    }
    return QVariant();
}



//////////////////////adoption list//////////////////////
TableModelAdoptedPets::TableModelAdoptedPets(AdoptionService &pet_service):adoption_service(pet_service){}
int TableModelAdoptedPets::rowCount(const QModelIndex &parent) const
{
    return this->adoption_service.number_of_adopted_pets_service();
}
int TableModelAdoptedPets::columnCount(const QModelIndex &parent) const
{
    return 4;
}
QVariant TableModelAdoptedPets::data(const QModelIndex &index, int role) const
{
    int row = index.row(), column = index.column();
    Pet pet = this->adoption_service[row];
    if (role == Qt::DisplayRole)
    {
        if (column == 0)return QString::fromStdString(pet.get_breed());
        else if (column == 1)return QString::fromStdString(pet.get_name());
        else if (column == 2)return QString::fromStdString(std::to_string(pet.get_age()));
        else if (column == 3)return QString::fromStdString(pet.get_photograph());

    }
    return QVariant();
}
QVariant TableModelAdoptedPets::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role == Qt::DisplayRole)
    {
        if (orientation == Qt::Horizontal)
        {
            if (section == 0)return QString("BREED");
            else if (section == 1)return QString("NAME");
            else if (section == 2)return QString("AGE");
            else if (section == 3)return QString("PHOTOGRAPH");
        }
    }
    return QVariant();
}