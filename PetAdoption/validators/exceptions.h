//
// Created by Alessio on 21/03/2021.
//


#include <stdexcept>

class RepositoryException : public std::runtime_error
{
public:
    RepositoryException(const std:: string& operation_error) : runtime_error(operation_error)
    {}
};

class ValidatorException : public std::runtime_error
{
public:
    ValidatorException(const std::string& validation_fail) : runtime_error(validation_fail)
    {}
};

class UndoRedoException : public std::runtime_error
{
public:
    UndoRedoException(const std::string& validation_fail) : runtime_error(validation_fail)
    {}
};

