// Collection class used to perform operations on a list
// Description of this can be found in the README file
// Nicholas Stafford
// Due: 2/8/18

#ifndef COLLECTION_H_
#define COLLECTION_H_
#include <iostream>
#include "list.h"

// forward declaration of class
template <typename T>
class Collection;

// forward declaration of friend fucntion
template <typename T>
bool equal(const Collection<T>&, const Collection<T>&);

template <typename T>
class Collection {
public:
  Collection();
  void addItem(const T& item);
  void removeItem(const T&);
  T lastItem();
  void printCollection();
  //friend bool a();
  friend bool equal<T>(const Collection<T>&, const Collection<T>&);
private:
  node<T> *head;
};

template <typename T>
Collection<T>::Collection() {
  head = nullptr;
}

template <typename T>
void Collection<T>::addItem(const T& item) {
  // add to the front of the list
  node<T> *temp = new node<T>;
  temp->setData(item);
  temp->setNext(head);
  head = temp;
}

template<typename T>
void Collection<T>::removeItem(const T& item){

  node<T> *previous = nullptr;
  node<T> *current = head;
  node<T> *next;
  while (current != nullptr) {
    next = current->getNext();
    if (current->getData() == item) {
      if (previous != nullptr)
	previous->setNext(current->getNext());
      delete current; 
    }
    // do not change previous if current has been deleted.
    if (current != nullptr) 
      previous = current;
    current = next;
  }
}

template <typename T>
T Collection<T>::lastItem() {
  return head->getData();
}

template<typename T>
void Collection<T>::printCollection(){
  node<T> *current = head;
  while (current != nullptr) {
    std::cout << current->getData() << " ";
    current = current->getNext();
  }
  std::cout << std::endl;
}

template<typename T>
bool equal(const Collection<T>& lhs, const Collection<T>& rhs) {
  // class used to test if two collections are the same
  node<T> *left = lhs.head;
  node<T> *right = rhs.head;
  if (left == nullptr && right == nullptr) return true;
  else if (left == nullptr && right != nullptr) return false;
  else if (left != nullptr && right == nullptr) return false;
  else {
    while (left != nullptr && right != nullptr) {
      if (left->getData() != right->getData())  return false;
      left = left->getNext();
      right = right->getNext();
    }
    // it is possible that only one is null. if only one is null return false
    if (left == nullptr && right != nullptr) return false;
    else if (left != nullptr && right == nullptr) return false;
  }
  /* if all elements are the same, and the linked lists are the same
     size. return true*/
  return true;
}
#endif // LIST_H_

