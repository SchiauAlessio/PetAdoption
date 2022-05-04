//
// Created by Alessio on 21/03/2021.
//

#pragma once
#include <cstdlib>
#include <cstring>
template<class TElem>

class DynamicVector {
private:
    int number_of_added_elements = 0;
    int current_max_capacity = 500;
    TElem *array_elements;

    //void resize_dynamic_array();

public:
    //constructor
    explicit DynamicVector(int capacity = 500);

    //destructor
    ~DynamicVector();

    //overload the [] operator to return the element at the given index
    TElem &operator[](int index) const;

    //add an element to the dynamically allocated array
    //@param element: the element that is added
    void add_element(TElem element);

    //update an element in the dynamically allocated array
    //@param index: the index at which the element to be updated is found
    //@param element: the element that is updated
    void update_element(int index,TElem element);

    //delete an element from the dynamically allocated array
    //@param element: the element that is removed
    void delete_element(TElem element);

    //find an element in the dynamically allocated array
    //@param element: the element that is searched for
    int find_element(TElem element);

    //return the current number of added elements in the array
    int dimension();
};

template<class TElem>
DynamicVector<TElem>::DynamicVector(int capacity) {
    this->number_of_added_elements = 0;
    this->current_max_capacity = capacity;
    this->array_elements = new TElem[capacity];
}

template<class TElem>
DynamicVector<TElem>::~DynamicVector() {
    delete[] this->array_elements;
}

template<class TElem>
void DynamicVector<TElem>::add_element(TElem element) {
    //this->array_elements[this->number_of_added_elements] = element;
    //this->number_of_added_elements = this->number_of_added_elements + 1;
    if (this->number_of_added_elements == this->current_max_capacity) {
        this->current_max_capacity <<= 1;
        TElem *copy = new TElem[this->current_max_capacity];
        memcpy(copy, this->array_elements, this->current_max_capacity * sizeof(int));
        delete[]this->array_elements;
        this->array_elements = copy;
    }
    this->array_elements[this->number_of_added_elements] = element;
    this->number_of_added_elements++;
}

template<class TElem>
void DynamicVector<TElem>::update_element(int index,TElem element) {
    this->array_elements[index]=element;
}

template<class TElem>
int DynamicVector<TElem>::dimension() {
    return this->number_of_added_elements;
}

//template<class TElem>
//void DynamicVector<TElem>::resize_dynamic_array() {
//    if (this->number_of_added_elements == this->current_max_capacity) {
//        this->current_max_capacity = this->current_max_capacity * 2;
//        TElem *copy_of_current_array = new TElem[this->current_max_capacity];
//        memcpy(copy_of_current_array, this->array_elements, this->current_max_capacity * sizeof(int));
//        delete[] this->array_elements;
//        this->array_elements = copy_of_current_array;
//    }
//}

template<class TElem>
TElem &DynamicVector<TElem>::operator[](int index) const {
    return this->array_elements[index];
}

template<class TElem>
int DynamicVector<TElem>::find_element(TElem element) {
    int not_found = -1;
    for (int index = 0; index < this->number_of_added_elements; index++)
        if (this->array_elements[index] == element)
            return index;
    return not_found;
}

template<class TElem>
void DynamicVector<TElem>::delete_element(TElem element) {
    int index_found_at=this->find_element(element);
    if(index_found_at!=-1){
        for(int current_index=index_found_at;current_index<this->number_of_added_elements-1;current_index++)
            this->array_elements[current_index]=this->array_elements[current_index+1];
        this->number_of_added_elements--;
    }
}


