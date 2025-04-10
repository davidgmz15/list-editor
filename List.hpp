#ifndef LIST_HPP
#define LIST_HPP
/* List.hpp
 *
 * doubly-linked, double-ended list with Iterator interface
 * EECS 280 List/Editor Project
 */

#include <iostream>
#include <iterator> //std::bidirectional_iterator_tag
#include <cassert>  //assert


template <typename T>
class List {
  //OVERVIEW: a doubly-linked, double-ended list with Iterator interface
public:

  // default constructor
  List() : first(nullptr),  last(nullptr), count(0) {}

  // destructor
  ~List() {
    clear();
  }

  // copy constructor
  List<T>& operator=(const List<T>& other) {
    if (this != &other) {
      clear();
      copy_all(other);
    }
    return *this;
  }

  //EFFECTS:  returns true if the list is empty
  bool empty() const {
    return first == nullptr;
  }

  //EFFECTS: returns the number of elements in this List
  //HINT:    Traversing a list is really slow. Instead, keep track of the size
  //         with a private member variable. That's how std::list does it.
  int size() const {
    return count;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the first element in the list by reference
  T & front() {
    assert(!empty());
    return first->datum;
  }

  //REQUIRES: list is not empty
  //EFFECTS: Returns the last element in the list by reference
  T & back() {
    assert(!empty());
    return last->datum;
  }

  //EFFECTS:  inserts datum into the front of the list
  void push_front(const T &datum) {
    Node *new_node = new Node(datum);
    new_node->next = first;
    new_node->prev = nullptr;
    if (first != nullptr) { // if list isn't empty, link previous first node to new node
      first->prev = new_node;
    }
    else { // if list is empty, last and first node are both new node
      last = new_node;
    }
    first = new_node;
    count++;

  }

  //EFFECTS:  inserts datum into the back of the list
  void push_back(const T &datum) {
    Node *new_node = new Node(datum);
    new_node->next = nullptr;
    new_node->prev = last;
    if (last != nullptr) { // if list isn't empty, link previous last node to new node
      last->next = new_node;
    }
    else { //  if list is empty, first and last are both new node
      first = new_node;
    }
    last = new_node;
    count++;
  }

  //REQUIRES: list is not empty
  //MODIFIES: invalidates all iterators to the removed element
  //EFFECTS:  removes the item at the front of the list
  void pop_front() {
    assert(!empty());
    Node *temp = first;
    first = first->next;
    if (first != nullptr) { // if list isn't empty, 
      first->prev = nullptr;
    }
    else {
      last = nullptr; // list becomes empty;
    }
    delete temp;
    count--;
  }

  //REQUIRES: list is not empty
  //MODIFIES: invalidates all iterators to the removed element
  //EFFECTS:  removes the item at the back of the list
  void pop_back() {
    assert(!empty());
    Node *temp = last;
    last = last->prev;
    if (last != nullptr) { // if list isn't empty
      last->next = nullptr;
    }
    else {
      first = nullptr; // list becomes empty;
    }
    delete temp;
    count--;
  }

  //MODIFIES: invalidates all iterators to the removed elements
  //EFFECTS:  removes all items from the list
  void clear() {
    while (!empty()) {
      pop_front();
    }
  }

  // You should add in a default constructor, destructor, copy constructor,
  // and overloaded assignment operator, if appropriate. If these operations
  // will work correctly without defining these, you should omit them. A user
  // of the class must be able to create, copy, assign, and destroy Lists.

private:
  //a private type
  struct Node {
    Node *next;
    Node *prev;
    T datum;
    Node(const T &d) : next(nullptr), prev(nullptr), datum(d) { }
  };

  //REQUIRES: list is empty
  //EFFECTS:  copies all nodes from other to this
  void copy_all(const List<T> &other) {
    for (Node* current = other.first; current != nullptr; current++) {
      push_back(current->datum);
    }
  }

  Node *first;   // points to first Node in list, or nullptr if list is empty
  Node *last;    // points to last Node in list, or nullptr if list is empty
  int count;

public:
  ////////////////////////////////////////
  class Iterator {
  public:
    //OVERVIEW: Iterator interface to List

    // Add a default constructor here. The default constructor must set both
    // pointer members to null pointers.
    Iterator() : list_ptr(nullptr), node_ptr(nullptr) {}



    // Add custom implementations of the destructor, copy constructor, and
    // overloaded assignment operator, if appropriate. If these operations
    // will work correctly without defining these, you should omit them. A user
    // of the class must be able to copy, assign, and destroy Iterators.

    // Your iterator should implement the following public operators:
    // *, ++ (both prefix and postfix), == and !=.
    // Equality comparisons must satisfy the following rules:
    // - two default-constructed iterators must compare equal
    // - a default-constructed iterator must compare unequal to an
    //   iterator obtained from a list, even if it is the end iterator
    // - two iterators to the same location in the same list must
    //   compare equal
    // - two iterators to different locations in the same list must
    //   compare unequal
    // - comparing iterators obtained from different lists results in
    //   undefined behavior
    //   - Your implementation can handle this however you like, but
    //     don't assume any particular behavior in your test cases --
    //     comparing iterators from different lists essentially
    //     violates the REQURES clause.
    // Note: comparing both the list and node pointers should be
    // sufficient to meet these requirements.

    // dereference operator - returns datum of current node
    T& operator*() const {
      assert(node_ptr != nullptr);
      return node_ptr->datum;
    }

    // prefix increment - moves iterator forward
    Iterator& operator++() {
      assert(list_ptr);
      if (node_ptr) {
        node_ptr = node_ptr->next;
      }
      return *this;
    }

    // inequality comparison operator
    bool operator==(const Iterator &other) const {
      return ((list_ptr == other.list_ptr) && (node_ptr == other.node_ptr));
    }

    // inequality comparison operator
    bool operator!=(const Iterator &other) const {
      return !(*this == other);
    }


    // Type aliases required to work with STL algorithms. Do not modify these.
    using iterator_category = std::bidirectional_iterator_tag;
    using value_type = T;
    using difference_type = std::ptrdiff_t;
    using pointer = T*;
    using reference = T&;

    // This operator will be used to test your code. Do not modify it.
    // REQUIRES: Iterator is decrementable. All iterators associated with a
    //           list are decrementable, including end iterators, except for
    //           begin iterators (those equal to begin() on the list)
    // EFFECTS:  moves this Iterator to point to the previous element
    //           and returns a reference to this Iterator
    Iterator& operator--() { // prefix -- (e.g. --it)
      assert(list_ptr);
      assert(*this != list_ptr->begin());
      if (node_ptr) {
        node_ptr = node_ptr->prev;
      } else { // decrementing an end Iterator moves it to the last element
        node_ptr = list_ptr->last;
      }
      return *this;
    }

    // This operator will be used to test your code. Do not modify it.
    // REQUIRES: Iterator is decrementable. All iterators associated with a
    //           list are decrementable, including end iterators, except for
    //           begin iterators (those equal to begin() on the list)
    // EFFECTS:  moves this Iterator to point to the previous element
    //           and returns a copy of the original Iterator
    Iterator operator--(int /*dummy*/) { // postfix -- (e.g. it--)
      Iterator copy = *this;
      operator--();
      return copy;
    }

    // REQUIRES: Iterator is dereferenceable
    // EFFECTS: returns the underlying element by pointer
    // NOTE: T must be a class type to use the syntax it->. If T has a
    //       member variable f, then it->f accesses f on the
    //       underlying T element.
    T* operator->() const {
      return &operator*();
    }

  private:
    const List *list_ptr; //pointer to the List associated with this Iterator
    Node *node_ptr; //current Iterator position is a List node

    // add any friend declarations here
    friend class List<T>;

    // construct an Iterator at a specific position in the given List
    Iterator(const List *lp, Node *np) : list_ptr(lp), node_ptr(np) {}

  };//List::Iterator
  ////////////////////////////////////////

  // return an Iterator pointing to the first element
  Iterator begin() const {
    return Iterator(this, first);
  }

  // return an Iterator pointing to "past the end"
  Iterator end() const {
    return Iterator(this, nullptr);
  }

  //REQUIRES: i is a valid, dereferenceable iterator associated with this list
  //MODIFIES: invalidates all iterators to the removed element
  //EFFECTS: Removes a single element from the list container.
  //         Returns An iterator pointing to the element that followed the
  //         element erased by the function call
  Iterator erase(Iterator i) {
    assert(i.list_ptr == this);
    assert(i.node_ptr != nullptr);
    Node* targetNode = i.node_ptr;
    Node* prevNode = targetNode->prev;
    Node* nextNode = targetNode->next;
    Iterator nextIt(this, targetNode->next);
    if (targetNode->prev) { // if node isn't first element
      prevNode->next = targetNode->next;
    }
    else { // if node is first element
      first = targetNode->next;
    }
    if (targetNode->next) { // if node isn't last element
      nextNode->prev = targetNode->prev;
    }
    else { // if node is last element
      last = targetNode->prev;
    }
    delete targetNode;
    count--;
    return nextIt;
  }

  //REQUIRES: i is a valid iterator associated with this list
  //EFFECTS: Inserts datum before the element at the specified position.
  //         Returns an iterator to the the newly inserted element.
  Iterator insert(Iterator i, const T &datum) {
    assert(i.list_ptr == this);
    // special case if insert is at beggining
    if (i.node_ptr == first) {
      push_front(datum);
      return begin();
    }
    // special case if insert is at end
    if (i.node_ptr == nullptr) {
      push_back(datum);
      Iterator it = end();
      --it; // point to newly added element
      return it;
    }
    // insert before node_ptr
    Node* insertNode = new Node(datum);
    Node* current = i.node_ptr;
    Node* prev = current->prev;
    insertNode->next = current;
    insertNode->prev = current->prev;
    if (current->prev) {
      prev->next = insertNode;
    }
    current->prev = insertNode;
    count++;
    return Iterator(this, insertNode);
  }

};//List


////////////////////////////////////////////////////////////////////////////////
// Add your member function implementations below or in the class above
// (your choice). Do not change the public interface of List, although you
// may add the Big Three if needed.  Do add the public member functions for
// Iterator.


#endif // Do not remove this. Write all your code above this line.