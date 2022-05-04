//
// Created by Alessio on 28/05/2021.
//

#include "undo_redo.h"
#include "../validators/exceptions.h"
void UndoRedo::push_undo_to_stack(Operation * current_operation) {
    this->undo_stack.push(current_operation);
}

void UndoRedo::undo() {
    if (this->undo_stack.empty())
        throw UndoRedoException("No more undo operations available to execute!\n");
    auto *current_operation = (Undo *) this->undo_stack.top();
    this->undo_stack.pop();
    current_operation->run_command();
    Redo *redo_op = current_operation->get_redo_operation();
    this->redo_stack.push(redo_op);
    delete current_operation;
}

void UndoRedo::redo()
{
    if (this->redo_stack.empty())
        throw UndoRedoException("No more redo operations available to execute!\n");
    auto *current_operation = (Redo *) this->redo_stack.top();
    this->redo_stack.pop();
    current_operation->run_command();
    Undo *undo_op = current_operation->get_undo_operation();
    this->undo_stack.push(undo_op);
    delete current_operation;
}

void UndoRedo::empty_redo_stack()
{
    while (not this->redo_stack.empty())
    {
        auto *current_operation = (Redo *) this->redo_stack.top();
        this->redo_stack.pop();
        delete current_operation;
    }
}