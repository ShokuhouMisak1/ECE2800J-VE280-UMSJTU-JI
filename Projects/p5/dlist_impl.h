#ifndef DLIST_IMPL_H
#define DLIST_IMPL_H

#include"dlist.h"

template <class T>
bool Dlist<T>::isEmpty() const{
    if(first == nullptr && last == nullptr) return true;
    return false;
}

template <class T>
void Dlist<T>::insertFront(T *op){
    node* new_op = new node;
    new_op->op = op;
    new_op->next = first;
    new_op->prev = nullptr;
    if(isEmpty()){
        first = last = new_op;
    }
    else{
        first->prev = new_op;
        first = new_op;
    }
}

template <class T>
void Dlist<T>::insertBack(T *op){
    node* new_op = new node;
    new_op->op = op;
    new_op->next = nullptr;
    new_op->prev = last;
    if(isEmpty()){
        first = last = new_op;
    }
    else{
        last->next = new_op;
        last = new_op;
    }
}

template <class T>
T* Dlist<T>::removeFront(){
    if(isEmpty()){
        emptyList e;
        throw e;
    }
    else{
        node* victim = first;
        if(first == last) first = last = nullptr;
        else{
            first = victim->next;
            first->prev = nullptr;
        }
        T* result= victim->op;
        delete victim;
        return result;
    }
}

template <class T>
T* Dlist<T>::removeBack(){
    if(isEmpty()){
        emptyList e;
        throw e;
    }
    else{
        node* victim = last;
        if(first == last) first = last = nullptr;
        else{
            last = victim->prev;
            last->next = nullptr;
        }
        T* result= victim->op;
        delete victim;
        return result;
    }
}

template <class T>
void Dlist<T>::removeAll(){
    while(!isEmpty()){
        T* result = removeFront();
        delete result;
    }
}

template <class T>
void Dlist<T>::copyAll(const Dlist &l){
    node* temp = l.first;
    while(temp != nullptr){
        T* o = new T(*temp->op);
        insertBack(o);
        temp = temp->next;
    }
}

template <class T>
Dlist<T>::Dlist():first(nullptr),last(nullptr){
}

template <class T>
Dlist<T>::Dlist(const Dlist &l):first(nullptr),last(nullptr){
    copyAll(l);
}

template <class T>
Dlist<T>& Dlist<T>::operator=(const Dlist<T>& l){
    if(this != &l){
        removeAll();
        copyAll(l);
    }
    return *this;
}

template <class T>
Dlist<T>::~Dlist(){
    removeAll();
}
#endif