//
// Created by Alessio on 15/05/2021.
//

#include <QWidget>
#include "../service/service.h"
#include <QListWidget>
#include <QLineEdit>
#include <QPushButton>
#include <QDialog>
#include <QTableView>
#include "../undo_redo/undo_redo.h"
#include "AdoptionList_TableModel.h"
class GUIAdmin:public QDialog{
Q_OBJECT
private:
    PetService &pet_service;
    UndoRedo& undo_redo;
    QListWidget *pet_list_widget;
    QLineEdit *breed_line_edit;
    QLineEdit *name_line_edit;
    QLineEdit *age_line_edit;
    QLineEdit *photograph_line_edit;
    QLineEdit* old_breed_line_edit;
    QLineEdit* old_name_line_edit;

    TableModelPetList* pet_list_table;
    QTableView* pet_list_table_view;

    QPushButton *add_pet;
    QPushButton *update_pet;
    QPushButton *delete_pet;
    QPushButton *undo;
    QPushButton* redo;
    QPushButton *reset;
    QPushButton *back;
public:
    explicit GUIAdmin(PetService &,UndoRedo&, QWidget *parent = 0);
private:
    void init();
    void populate();
    void connect_buttons();
    int get_index() const;
    void add_pet_to_repo_gui();
    void update_pet_repo_gui();
    void delete_pet_repo_gui();
    void reset_text_fields();
    void return_to_main_window();
    void undo_operation();
    void redo_operation();
};
#endif
