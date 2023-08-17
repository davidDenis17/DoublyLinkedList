//
//  LinkedList.h
//  Project 1: Doubly Linked List
//
//  Created by David Denis on 2/16/23.
//

#define LinkedList_h
#include <iostream>
#include <vector>

using namespace std;

template <typename T>
class LinkedList {
  
public:
    struct Node
    {
        T data;
        Node* next;
        Node* prev;
    };
    
    // Insertion
    
    void AddHead(const T& data);
    void AddTail(const T& data);
    void AddNodesHead(const T* data, unsigned int count);
    void AddNodesTail(const T* data, unsigned int count);
    void InsertAfter(Node* node, const T& data);
    void InsertBefore(Node* node, const T& data);
    void InsertAt(const T& data, unsigned int index);
    
    
    // Accessors
    
    unsigned int NodeCount() const;
    void FindAll(vector<Node*>& outData, const T& value) const;
    const Node* Find(const T& data) const;
    Node* Find(const T& data);
    const Node* GetNode(unsigned int index) const;
    Node* GetNode(unsigned int index);
    Node* Head();
    const Node* Head() const;
    Node* Tail();
    const Node* Tail() const;
    
    
    // Behaviors
    
    void PrintForward() const;
    void PrintReverse() const;
    void PrintForwardRecursive(const Node* node) const;
    void PrintReverseRecursive(const Node* node) const;
    
    
    // Removal
    
    bool RemoveHead();
    bool RemoveTail();
    unsigned int Remove(const T& data);
    bool RemoveAt(unsigned int index);
    void Clear();
    
    
    // Operators
    
    const T& operator[](unsigned int index) const;
    T& operator[](unsigned int index);
    bool operator==(const LinkedList<T>& rhs) const;
    LinkedList<T>& operator=(const LinkedList<T>& rhs);
    
    
    // Construction / Destruction
    
    LinkedList();
    LinkedList(const LinkedList<T>& list);
    ~LinkedList();
    
private:
    Node* _head;
    Node* _tail;
    unsigned int counter;
};

                                                                        // ========== Construction / Destruction Methods ==========

// Default Constructor
template <typename T>
LinkedList<T>:: LinkedList()
{
    _head = nullptr;
    _tail = nullptr;
    counter = 0;
}

template <typename T>
LinkedList<T>:: ~LinkedList()
{
    Node* toDestroy = _head;                    // create a traverser node that will destroy the nodes in the linked list
    
    while (toDestroy != nullptr)                // go to the next value as long != nullptr
    {
        Node* temp = toDestroy;                 // assign temp node -> toDestroy node
        toDestroy = toDestroy->next;            // next node
        delete temp;                            // destroy last node (temp node)
    }
}

// Copy Constructor
template <typename T>
LinkedList<T>:: LinkedList(const LinkedList<T>& list)
{
    if(list._head == nullptr)                   // Check if list is empty
    {
        _head = nullptr;
        _tail = nullptr;
        counter = 0;
    }
    else
    {
        _head = nullptr;                        // initialize head and tail to nullptr
        _tail = nullptr;
        
        Node* traverser = list._head;           // assign a traverser node to the head of the passed list

        while (traverser != nullptr)            // copy the data until the end is reached
        {
            AddTail(traverser->data);
            traverser = traverser->next;
        }
        
    }
    
  
}

// Copy Assignment Operator
template <typename T>
LinkedList<T>& LinkedList<T>::operator=(const LinkedList<T>& rhs)
{
   
    Clear();                                    // free memory
    
    
    if(rhs._head == nullptr)
    {
        _head = nullptr;
        _tail = nullptr;
        counter = 0;
    }
    else
    {
        _head = nullptr;                        // initialize head and tail to nullptr
        _tail = nullptr;
        
        Node* traverser = rhs._head;            // assign a traverser node to the head of the passed list

        while (traverser != nullptr)            // copy the data until the end is reached
        {
            AddTail(traverser->data);
            traverser = traverser->next;
        }
        
    }
    
    return *this;                               // return pointer of new copied list
}


                                                                        // ========== Insertion Methods ==========

template <typename T>
void LinkedList<T>:: AddHead(const T& data)
{
    
    Node* newNode = new Node;                   // allocate memory and create new node
    newNode->data = data;                       // set data
    newNode->prev = nullptr;
    
    
    if(_head == nullptr)                        // is the head nullptr
    {
        _head = newNode;
        _tail = newNode;
    }
    else
    {
        newNode->next = _head;                  // if not, next is the previous head
        _head->prev = newNode;                  // previous head's previous is the new node
        _head = newNode;                        // new node is the new head
    }
        
    counter += 1;                               // node counter ++
    
    _head->prev = nullptr;
}


template <typename T>
void LinkedList<T>:: AddTail(const T& data)
{
    Node* newNode = new Node;                   // allocate memory for new Tail
    newNode->data = data;                       // set data
    newNode->next = nullptr;
  
    
    if(_head == nullptr)                        // if the list is empty, make the newNode the head
    {
        _tail = newNode;
        _head = newNode;
        
    }
    
    if(_tail)                                   // check if tail is a nullptr
        _tail->next = newNode;                  // previous tail's next is the new Tail
    newNode->prev = _tail;                      // New Tail's previous is the old tail
    _tail = newNode;                            // new node (tail) is the new tail
    

    
    counter += 1;                               // node counter ++
    
    _head->prev = nullptr;
}



template <typename T>
void LinkedList<T>:: AddNodesHead(const T *data, unsigned int count)
{
    for(int i = count - 1; i >= 0; i--)
    {
        AddHead(data[i]);                       // create a new head for each of the passed values
    }
    
}


template <typename T>
void LinkedList<T>:: AddNodesTail(const T *data, unsigned int count)
{
    for(unsigned int i = 0; i < count; i++)
    {
        AddTail(data[i]);                       // create a new tail for each of the passed values
    }
}


// Insert data into a new node before the given one
template <typename T>
void LinkedList<T>:: InsertBefore(Node *node, const T &data)
{
    
    if(node == _head)                           // check if passed node is the head of the linked list & AddHead new it is
        AddHead(data);
    else
    {
        Node* newNode = new Node;               // allocate memory for new node
        newNode->data = data;                   // assign data
        
        node->prev->next = newNode;             // next of node's previous is equal to the newNode (INSERTING IN THE MIDDLE OF THE TWO)
        newNode->prev = node->prev;             // previous of newNode is equal to the passed's previous ptr
        newNode->next = node;                   // next of newNode is the passed node (MIDDLE)
        node->prev = newNode;                   // connect prev node's ptr to newNode (INSERTED BEFORE IT)
        
        counter++;                              // node counter up
    }
    
}


// Insert data into a new node after the given one
template <typename T>
void LinkedList<T>:: InsertAfter(Node *node, const T &data)
{
    
    if(node == _tail)                           // check if passed node is the tail of the linked list * AddTail if it is
        AddTail(data);
    else
    {
        Node* newNode = new Node;               // allocate memory for new node
        newNode->data = data;                   // assign data
        
        node->next->prev = newNode;             // previous of node's next is now equal to the new Node (INSERTING)
        newNode->next = node->next;             // next of newNode is now the next of the passed node
        newNode->prev = node;                   // prev of newNode is now the passed node (INSERTING AFTER)
        node->next = newNode;                   // connect the passed node's next ptr to the new created ptr
        
        counter++;                              // node counter up
    }
}


// Insert a data into a new node at the given index
template <typename T>
void LinkedList<T>:: InsertAt(const T &data, unsigned int index)
{
    if(index < 0)                               // check if index is valid
        throw out_of_range(" ");
    else if (index == 0)                        // check if passed index is the head
        AddHead(data);
    else if (index == counter)                  // check if passed index is the tail
        AddTail(data);
    else
    {
        Node* finder = GetNode(index);          // create a finder and use get node method to get address
        
        InsertBefore(finder, data);
            
    }
}

                                                                        // ========== Accessor Methods ==========

template <typename T>
unsigned int LinkedList<T>:: NodeCount() const
{
    return counter;                             // return node counter
}


template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Head()
{
    return _head;                               // return head pointer
}


template <typename T>
const typename LinkedList<T>:: Node* LinkedList<T>:: Head() const
{
    return _head;                               // return head ptr constant version
}


template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::Tail()
{
    return _tail;                               // return tail pointer
}


template <typename T>
const typename LinkedList<T>:: Node* LinkedList<T>:: Tail() const
{
    return _tail;                               // return tail ptr constant version
}



// Returns node ptr given an index
template <typename T>
typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index)
{
   
    
    Node* finder = _head;                       // create new node ptr finder to iterate through the linked list
    
    unsigned int count = 0;                     // counter to compare to index
    
    while (finder != nullptr)                   // iterate the linked list and return finder ptr when index is reached
    {
        if(count == index)
            return finder;
        
        count++;
        finder = finder->next;
    }
    
    return nullptr;;
}


// CONST version of above's method
template <typename T>
const typename LinkedList<T>::Node* LinkedList<T>::GetNode(unsigned int index) const
{
    if(index >= counter || index < 0)
        throw out_of_range(" ");
    
    Node* finder = _head;
    
    unsigned int count = 0;
    
    while (finder != nullptr)
    {
        if(count == index)
            return finder;
        
        count++;
        finder = finder->next;
    }
    
    return nullptr;
}


// takes in a data anad returns the pointer of the node containing such data
template <typename T>
typename LinkedList<T>:: Node* LinkedList<T>::Find(const T &data)
{
    Node* valuePtr = _head;                     // assign valuePtr to the head
    
    while (valuePtr != nullptr)                 // iterate throught the linked list
    {
        if(valuePtr->data == data)              // if the value of the data stored in valuePtr is = to the data passed
            return valuePtr;                    // return pointer
        
        valuePtr = valuePtr->next;
    }
    
    return nullptr;                             // return nullptr if no match is found
    
}


// CONST versions of above's method
template <typename T>
const typename LinkedList<T>:: Node* LinkedList<T>::Find(const T &data) const
{
    Node* valuePtr = _head;
    
    while (valuePtr != nullptr)
    {
        if(valuePtr->data == data)
            return valuePtr;
        
        valuePtr = valuePtr->next;
    }
    
    return nullptr;
    
}


// Finds all nodes containing the passed value and stores the pointers in the passed vector for future use (OUTPUT PARAMETER)
template <typename T>
void LinkedList<T>:: FindAll(vector<Node *> &outData, const T &value) const
{
    Node* valuePtr = _head;                     // assign valuePtr to the beginning of the linked list
    
    while (valuePtr != nullptr)                 // iterate through the list
    {
        if(valuePtr->data == value)             // if the data stored in current node is equal to the value passed
            outData.push_back(valuePtr);        // store the node ptr in the vector
        
        valuePtr = valuePtr->next;
    }
}



                                                                        // ========== Behavior Methods ==========

// prints linked lists values starting at the head
template <typename T>
void LinkedList<T>:: PrintForward() const
{
    Node* traverser = _head;                    // assign traverser to the beginning of the linked list
    
    while (traverser != nullptr)                // print the data as long as the next value is not a nullptr (TAIL is reached))
    {
        cout << traverser->data << endl;
        traverser = traverser->next;            // assign traverser to next value in the linked list
    }
    
}


// prints linked lists values starting at the tail and going in reverse
template <typename T>
void LinkedList<T>:: PrintReverse() const
{
    Node* traverser = _tail;                    // assign traverser to the end of the linked list (TAIL)
    
    while (traverser != nullptr)                // print the data as long as the previous value is not nullptr (HEAD is reached)
    {
        cout << traverser->data << endl;
        traverser = traverser->prev;            // assign traverser to the previous value in the linked list
    }
}


template <typename T>
void LinkedList<T>:: PrintForwardRecursive(const Node *node) const
{
    if(node == nullptr)                         // if tail is reached, STOP
        return;
    
    cout<< node->data << endl;                  // print data
    PrintForwardRecursive(node->next);          // call again with next
}


template <typename T>
void LinkedList<T>:: PrintReverseRecursive(const Node *node) const
{
    if(node == nullptr)                         // if head is reached, STOP
        return;
    
    cout << node->data << endl;                 // print data
    PrintReverseRecursive(node->prev);          // call again with prev
}



                                                                        // ========== Operator Methods ==========


// Overloads the [] operator to return the data of the node at nth index
template <typename T>
T& LinkedList<T>::operator[](unsigned int index)
{
    if(index > counter || index < 0)            // check if index is within the limits
        throw out_of_range("");
    
    Node* finder = GetNode(index);              // create new node ptr finder and use get node method to get adress of index
    
    return finder->data;
}

// CONST version of aboves' method
template <typename T>
const T& LinkedList<T>::operator[](unsigned int index) const
{
    if(index > counter || index < 0)
        throw out_of_range("");
    
    Node* finder = GetNode(index);
    
    return finder->data;
}


// determines if 2 lists are equal
template <typename T>
bool LinkedList<T>::operator==(const LinkedList<T> &rhs) const
{
    if(counter != rhs.counter)                  // check if the lists have the same size
        return false;
    
    
    Node* thisListT = _head;                    // create atraverser node for each list
    Node* givenListT = rhs._head;
    
    while (thisListT != nullptr)                // iterate through the list
    {
        if(thisListT->data != givenListT->data) // if the data does not match in both lists, return false
            return false;
        
        thisListT = thisListT->next;            // next node
        givenListT = givenListT->next;
    }
    
    return true;                                // if all tests fail, return true
}



                                                                        // ========== Removal Methods ==========

// Deletes the head of the list
template <typename T>
bool LinkedList<T>:: RemoveHead()
{
    if(_head == nullptr)                        // check if the list is empty
         return false;
    
    Node* temp = _head;                         // store address of head into temporary node
    
    _head = temp->next;                         // new head is temp's next
    
    if(counter == 1)                            // If there is only one node on the list, -> next will cause an ERROR since _head is already null (previous argument)
        _head = nullptr;
    else
        _head->prev = nullptr;
    
    delete temp;                                // delete temporary node

    counter--;                                  // decrease node counter
    
    if(counter == 0)                            // check if list is empty after deleting node
        _head = _tail = nullptr;
    
    
    return true;
}


// Deletes the tail of the list
template <typename T>
bool LinkedList<T>:: RemoveTail()
{
    if(_tail == nullptr)                        // check whether the list is empty
        return false;
    
    Node* temp = _tail;                         // store tail in temporary node
    
    _tail = temp->prev;                         // new tail is temp's prev
    
    if(counter == 1)                            // If there is only one node on the list, -> next will cause an ERROR since _tail is already null (previous argument)
        _tail = nullptr;
    else
        _tail->next = nullptr;
    
    delete temp;                                // delete temporary node

    
    counter--;                                  // decrease node counter
    
    if(counter == 0)                            // check if list is empty after deleting node
        _head = _tail = nullptr;
    
    
    return true;
    
}

// Deletes the node at passed index from the list
template <typename T>
bool LinkedList<T>:: RemoveAt(unsigned int index)
{
    if(index > counter || index < 0)            // check if index is within the limits
        return false;
    
    if(_head == nullptr)
        return false;
    
    
    Node* toRemove = GetNode(index);            // create new Node to remove and use get node method to get address of index passed
    
    
    
    if(toRemove == _head)
        RemoveHead();
    else if(toRemove == _tail)
        RemoveTail();
    else
    {
        toRemove->prev->next = toRemove->next;  // link toRemove node's prev to node's next
        toRemove->next->prev = toRemove->prev;  // link toRemove node's next to node's prev
        delete toRemove;                        // delete the node in the passed index
        
        counter--;                              // decrease node counter
    }
    
    if(counter == 0)                            // check if list is empty after deleting node
        _head = _tail = nullptr;
    
    return true;
    
    
}


// Deletes all nodes containing the paseed data and returns how many nodes were deleted
template <typename T>
unsigned int LinkedList<T>:: Remove(const T &data)
{
    unsigned int index = 0;                     // tracks nodes' index
    unsigned int nodes_removed = 0;             // tracks nodes removed
    vector<unsigned int> vec;
    Node* trav = _head;
    
    while (trav != nullptr)
    {
        if(trav->data == data)
        {
            trav = trav->next;
            
            RemoveAt(index);                     
            nodes_removed++;
            index--;
            
        }
        else
        {
            trav = trav->next;
        }
        index++;
    }
    return nodes_removed;
    
}

// Clears all memory
template <typename T>
void LinkedList<T>:: Clear()
{
    Node* toDestroy = _head;                    // create a traverser node that will destroy the nodes in the linked list
    
    while (toDestroy != nullptr)                // go to the next value as long != nullptr
    {
        Node* temp = toDestroy;                 // assign temp node -> toDestroy node
        toDestroy = toDestroy->next;            // next node
        delete temp;                            // destroy last node (temp node)
    }
    
    _head = nullptr;
    _tail = nullptr;
    counter = 0;
}
