//
// Created by Alessio on 28/05/2021.
//

#include <stack>
#include "operation.h"
class UndoRedo{
protected:
    std::stack<Operation*> undo_stack;
    std::stack<Operation*> redo_stack;
public:
    virtual void undo();
    virtual void redo();
    void push_undo_to_stack(Operation *current_operation);
    virtual void empty_redo_stack();
};
