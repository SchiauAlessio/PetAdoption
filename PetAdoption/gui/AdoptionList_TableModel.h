//
// Created by Alessio on 29/05/2021.
//


#include <QAbstractTableModel>
#include "../service/service.h"
#include "../service/adoption_service.h"
class TableModelPetList : public QAbstractTableModel
{
private:
    PetService &pet_service;
public:
    explicit TableModelPetList(PetService &pet_service);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
};


class TableModelAdoptedPets: public QAbstractTableModel
{
private:
    AdoptionService &adoption_service;
public:
    explicit TableModelAdoptedPets(AdoptionService &pet_service);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;
};

