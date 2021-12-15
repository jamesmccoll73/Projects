#ifndef BST_H
#define BST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <utility>
#include <cmath>
#include <algorithm>


//A templated class for a Node in a search tree.
template <typename Key, typename Value>
class Node
{
public:
    Node(const Key& key, const Value& value, Node<Key, Value>* parent);
    virtual ~Node();

    const std::pair<const Key, Value>& getItem() const;
    std::pair<const Key, Value>& getItem();
    const Key& getKey() const;
    const Value& getValue() const;
    Value& getValue();

    virtual Node<Key, Value>* getParent() const;
    virtual Node<Key, Value>* getLeft() const;
    virtual Node<Key, Value>* getRight() const;

    void setParent(Node<Key, Value>* parent);
    void setLeft(Node<Key, Value>* left);
    void setRight(Node<Key, Value>* right);
    void setValue(const Value &value);

protected:
    std::pair<const Key, Value> item_;
    Node<Key, Value>* parent_;
    Node<Key, Value>* left_;
    Node<Key, Value>* right_;
};


//Explicit constructor for a node.
template<typename Key, typename Value>
Node<Key, Value>::Node(const Key& key, const Value& value, Node<Key, Value>* parent) :
    item_(key, value),
    parent_(parent),
    left_(NULL),
    right_(NULL)
{

}

//Destructor
template<typename Key, typename Value>
Node<Key, Value>::~Node()
{
}

//A const getter for the item.
template<typename Key, typename Value>
const std::pair<const Key, Value>& Node<Key, Value>::getItem() const
{
    return item_;
}

//A non-const getter for the item.
template<typename Key, typename Value>
std::pair<const Key, Value>& Node<Key, Value>::getItem()
{
    return item_;
}

//A const getter for the key.
template<typename Key, typename Value>
const Key& Node<Key, Value>::getKey() const
{
    return item_.first;
}

//A const getter for the value.
template<typename Key, typename Value>
const Value& Node<Key, Value>::getValue() const
{
    return item_.second;
}


//A non-const getter for the value.
template<typename Key, typename Value>
Value& Node<Key, Value>::getValue()
{
    return item_.second;
}


//An implementation for retreiving the parent.
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getParent() const
{
    return parent_;
}


//An implementation for retreiving the left child.
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getLeft() const
{
    return left_;
}


//An implementation for retreiving the right child.
template<typename Key, typename Value>
Node<Key, Value>* Node<Key, Value>::getRight() const
{
    return right_;
}


//A setter for setting the parent of a node.
template<typename Key, typename Value>
void Node<Key, Value>::setParent(Node<Key, Value>* parent)
{
    parent_ = parent;
}


//A setter for setting the left child of a node.
template<typename Key, typename Value>
void Node<Key, Value>::setLeft(Node<Key, Value>* left)
{
    left_ = left;
}


//A setter for setting the right child of a node.
template<typename Key, typename Value>
void Node<Key, Value>::setRight(Node<Key, Value>* right)
{
    right_ = right;
}


//A setter for the value of a node.
template<typename Key, typename Value>
void Node<Key, Value>::setValue(const Value& value)
{
    item_.second = value;
}


/**
* A templated unbalanced binary search tree.
*/
template <typename Key, typename Value>
class BinarySearchTree
{
public:
    BinarySearchTree(); //TODO
    virtual ~BinarySearchTree(); //TODO
    virtual void insert(const std::pair<const Key, Value>& keyValuePair); //TODO
    virtual void remove(const Key& key); //TODO
    void clear(); //TODO
    bool isBalanced() const; //TODO
    void print() const;
    bool empty() const;
public:
    /**
    * An internal iterator class for traversing the contents of the BST.
    */
    class iterator
    {
    public:
        iterator();

        std::pair<const Key,Value>& operator*() const;
        std::pair<const Key,Value>* operator->() const;

        bool operator==(const iterator& rhs) const;
        bool operator!=(const iterator& rhs) const;

        iterator& operator++();

    protected:
        friend class BinarySearchTree<Key, Value>;
        iterator(Node<Key,Value>* ptr);
        Node<Key, Value> *current_;
    };

public:
    iterator begin() const;
    iterator end() const;
    iterator find(const Key& key) const;

protected:
    Node<Key, Value>* internalFind(const Key& k) const; // TODO
    Node<Key, Value> *getSmallestNode() const;  // TODO
    static Node<Key, Value>* predecessor(Node<Key, Value>* current); // TODO
    virtual void printRoot (Node<Key, Value> *r) const;
    virtual void nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2) ;
    Node<Key, Value>* insertHelper (Node<Key, Value> *node_);
    void updateParentsChild(Node<Key, Value> *child, Node<Key, Value> *parent, Node<Key, Value> *update);
    Node<Key, Value>* removeHelper (const Key& key);
    int isBalancedHelper(const Node<Key, Value> *currNode) const;
    void clearHelper(Node<Key, Value> *root);


protected:
    Node<Key, Value>* root_;
};



//Explicit constructor that initializes an iterator with a given node pointer.
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator(Node<Key,Value> *ptr)
{
    current_ = ptr;
}

//A default constructor that initializes the iterator to NULL.
template<class Key, class Value>
BinarySearchTree<Key, Value>::iterator::iterator()
{
    current_ = NULL;

}

//Provides access to the item.
template<class Key, class Value>
std::pair<const Key,Value> &
BinarySearchTree<Key, Value>::iterator::operator*() const
{
    return current_->getItem();
}

//Provides access to the address of the item.
template<class Key, class Value>
std::pair<const Key,Value> *
BinarySearchTree<Key, Value>::iterator::operator->() const
{
    return &(current_->getItem());
}

/**
* Checks if 'this' iterator's internals have the same value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator==(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    if(rhs.current_ == NULL){
        return current_ == NULL;
    }
    return (current_ ->getKey() == rhs -> first && current_ ->getValue() == rhs -> second);
}

/**
* Checks if 'this' iterator's internals have a different value
* as 'rhs'
*/
template<class Key, class Value>
bool
BinarySearchTree<Key, Value>::iterator::operator!=(
    const BinarySearchTree<Key, Value>::iterator& rhs) const
{
    if(rhs.current_ == NULL){
        if(current_ == NULL){
            return false;
        }
        else{
            return true;
        }
    }
    return !(current_ ->getKey() == rhs -> first && current_ -> getValue() == rhs -> second);
}


//Advances the iterator's location using an in-order sequencing
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator&
BinarySearchTree<Key, Value>::iterator::operator++()
{   
    Node<Key, Value>* next = this->current_;

    if(current_ -> getRight() != NULL){
        next = current_-> getRight();
        while(next -> getLeft() != NULL){
            next = next -> getLeft();
        }
        BinarySearchTree<Key, Value>::iterator it = iterator(next);
        this->current_ = next;
        return it;
    }
    else{
        next = current_ -> getParent();
        if(next == NULL){
            BinarySearchTree<Key, Value>::iterator it = iterator(NULL);
            this->current_ = NULL;
            return it;
        }
        while(current_->getKey() >= next->getKey()){
            if(next -> getParent() == NULL){
                BinarySearchTree<Key, Value>::iterator it = iterator(NULL);
                this->current_ = NULL;
                return it;
            }
            next = next->getParent();
        }
        BinarySearchTree<Key, Value>::iterator it = iterator(next);
        this->current_ = next;
        return it;
    }
}



//Default constructor for a BinarySearchTree, which sets the root to NULL.
template<class Key, class Value>
BinarySearchTree<Key, Value>::BinarySearchTree() 
{
    root_ = NULL;
}

template<typename Key, typename Value>
BinarySearchTree<Key, Value>::~BinarySearchTree()
{
    clear();

}

//Returns true if tree is empty
template<class Key, class Value>
bool BinarySearchTree<Key, Value>::empty() const
{
    return root_ == NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::print() const
{
    printRoot(root_);
    std::cout << "\n";
}

//Returns an iterator to the "smallest" item in the tree
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::begin() const
{
    BinarySearchTree<Key, Value>::iterator begin(getSmallestNode());
    return begin;
}

//Returns an iterator whose value means INVALID
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::end() const
{
    BinarySearchTree<Key, Value>::iterator end(NULL);
    return end;
}

/**
* Returns an iterator to the item with the given key, k
* or the end iterator if k does not exist in the tree
*/
template<class Key, class Value>
typename BinarySearchTree<Key, Value>::iterator
BinarySearchTree<Key, Value>::find(const Key & k) const
{
    Node<Key, Value> *curr = internalFind(k);
    BinarySearchTree<Key, Value>::iterator it(curr);
    return it;
}

/**
* An insert method to insert into a Binary Search Tree.
* The tree will not remain balanced when inserting.
*/
template<class Key, class Value>
void BinarySearchTree<Key, Value>::insert(const std::pair<const Key, Value> &keyValuePair)
{
    Node<Key, Value>* newNode = new Node<Key,Value>(keyValuePair.first, keyValuePair.second, NULL);
    insertHelper(newNode);
}

template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::insertHelper(Node<Key, Value> *keyValuePair){
    if(this->root_ == NULL){
        this->root_ = keyValuePair;
        return keyValuePair;
    }
    
    Node<Key, Value>* current_node = this->root_;
    
    while(true){ //runs until it returns the new node that's been inserted
        if(current_node -> getKey() == keyValuePair -> getKey()){
            current_node -> setValue(keyValuePair -> getValue());
            delete keyValuePair;
            return current_node;
        }
        else if(current_node -> getKey() > keyValuePair -> getKey()){
            if(current_node -> getLeft() == NULL){
                keyValuePair -> setParent(current_node);
                current_node->setLeft(keyValuePair);
                return keyValuePair;
            }
            else{
                current_node = current_node->getLeft();
            }
        }
        else{ //current_node.getKey() < keyValuePair.getKey())
            if(current_node->getRight() == NULL){
                keyValuePair -> setParent(current_node);
                current_node->setRight(keyValuePair);
                return keyValuePair;
            }
            else{
                current_node = current_node->getRight();
            }
        }
    }
}


/**
* A remove method to remove a specific key from a Binary Search Tree.
* The tree may not remain balanced after removal.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::remove(const Key& key)
{
    removeHelper(key);
}

template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::removeHelper (const Key& key){
    
    Node<Key, Value>* temp = internalFind(key);
    if(temp == NULL){ //Return NULL if the node isn't in the tree
        return NULL;
    }

    if(temp->getLeft() == NULL && temp->getRight() == NULL){//no children
        if(this->root_ == temp){
            this->root_ = NULL;
        }
        else{
            updateParentsChild(temp, temp->getParent(), NULL);
        }
    }
    else if(temp -> getRight() == NULL){//one left child
        temp -> getLeft()->setParent(temp->getParent());
        if(this->root_ == temp){
            this->root_ = temp->getLeft();
        }
        else{
            updateParentsChild(temp, temp -> getParent(), temp->getLeft());
        }   
    }
    else if(temp -> getLeft() == NULL){//one right child
        temp->getRight()->setParent(temp->getParent());
        if(this->root_ == temp){
            this->root_ = temp->getRight();
        }
        else{
            updateParentsChild(temp, temp->getParent(), temp->getRight());
        }
    }
    else{ //two children nodes
        Node<Key, Value>* pred = predecessor(temp);
        nodeSwap(temp, pred);
        if(temp -> getRight() == NULL && temp -> getLeft() == NULL){
            updateParentsChild(temp, temp->getParent(), NULL);
        }
        else{ //checks if still has a left child
            nodeSwap(temp, temp->getLeft());
            updateParentsChild(temp, temp->getParent(), NULL);
        }
    } 
    Node<Key, Value>* par = temp->getParent();
    delete temp;
    temp = NULL;
    return par;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::updateParentsChild(Node<Key, Value> *child, Node<Key, Value> *parent, Node<Key, Value> *update){
    if(parent->getRight() == child){ //child is parent's right child
        parent->setRight(update);
    }
    else{ //child is parents left child
        parent->setLeft(update);
    }
}


template<class Key, class Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::predecessor(Node<Key, Value>* current) //returns NULL if biggest item
{
    Node<Key, Value>* target = current->getLeft();
    while(target->getRight() != NULL){
        target = target->getRight();
    }
    return target;
    
}


/**
* A method to remove all contents of the tree and
* reset the values in the tree for use again.
*/
template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clear()
{
    clearHelper(this->root_);
    this->root_ = NULL;
}

template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::clearHelper(Node<Key, Value> *node){
    if(node == NULL){
        return;
    }
    clearHelper(node->getLeft());
    clearHelper(node->getRight());
    delete node;
    node = NULL;
}


/**
* A helper function to find the smallest node in the tree.
*/
template<typename Key, typename Value>
Node<Key, Value>*
BinarySearchTree<Key, Value>::getSmallestNode() const
{
    Node<Key, Value>* smallest = this->root_;
    if(smallest != NULL){
        while(smallest->getLeft() != NULL){
            smallest = smallest->getLeft();
        }
    }
    return smallest;
}

/**
* Helper function to find a node with given key, k and
* return a pointer to it or NULL if no item with that key
* exists
*/
template<typename Key, typename Value>
Node<Key, Value>* BinarySearchTree<Key, Value>::internalFind(const Key& key) const
{
    Node<Key, Value>* current_node = this->root_;
    while(current_node != NULL){
        if(current_node->getKey() == key){
            return current_node;
        }
        else if(current_node->getKey() > key){
            current_node = current_node->getLeft();
        }
        else{ //current_node.getKey() < key
            current_node = current_node->getRight();
        }
    }
    return NULL;
}

//Return true if the BST is balanced.
template<typename Key, typename Value>
bool BinarySearchTree<Key, Value>::isBalanced() const
{
    int result = isBalancedHelper(this->root_);
	if(result >= 0){
		return true;
	}
	return false;
}

template<typename Key, typename Value>
int BinarySearchTree<Key, Value>::isBalancedHelper(const Node<Key, Value> *currNode) const{
    if(currNode == nullptr){
		return 0;
	}
	int leftVal = isBalancedHelper(currNode -> getLeft());
	int rightVal = isBalancedHelper(currNode -> getRight());
	if(abs(leftVal-rightVal) <= 1){
		return std::max(leftVal, rightVal) + 1;
	}
	else{
		return -10000;
	}
}


template<typename Key, typename Value>
void BinarySearchTree<Key, Value>::nodeSwap( Node<Key,Value>* n1, Node<Key,Value>* n2)
{
    if((n1 == n2) || (n1 == NULL) || (n2 == NULL) ) {
        return;
    }
    Node<Key, Value>* n1p = n1->getParent();
    Node<Key, Value>* n1r = n1->getRight();
    Node<Key, Value>* n1lt = n1->getLeft();
    bool n1isLeft = false;
    if(n1p != NULL && (n1 == n1p->getLeft())) n1isLeft = true;
    Node<Key, Value>* n2p = n2->getParent();
    Node<Key, Value>* n2r = n2->getRight();
    Node<Key, Value>* n2lt = n2->getLeft();
    bool n2isLeft = false;
    if(n2p != NULL && (n2 == n2p->getLeft())) n2isLeft = true;


    Node<Key, Value>* temp;
    temp = n1->getParent();
    n1->setParent(n2->getParent());
    n2->setParent(temp);

    temp = n1->getLeft();
    n1->setLeft(n2->getLeft());
    n2->setLeft(temp);

    temp = n1->getRight();
    n1->setRight(n2->getRight());
    n2->setRight(temp);

    if( (n1r != NULL && n1r == n2) ) {
        n2->setRight(n1);
        n1->setParent(n2);
    }
    else if( n2r != NULL && n2r == n1) {
        n1->setRight(n2);
        n2->setParent(n1);

    }
    else if( n1lt != NULL && n1lt == n2) {
        n2->setLeft(n1);
        n1->setParent(n2);

    }
    else if( n2lt != NULL && n2lt == n1) {
        n1->setLeft(n2);
        n2->setParent(n1);

    }


    if(n1p != NULL && n1p != n2) {
        if(n1isLeft) n1p->setLeft(n2);
        else n1p->setRight(n2);
    }
    if(n1r != NULL && n1r != n2) {
        n1r->setParent(n2);
    }
    if(n1lt != NULL && n1lt != n2) {
        n1lt->setParent(n2);
    }

    if(n2p != NULL && n2p != n1) {
        if(n2isLeft) n2p->setLeft(n1);
        else n2p->setRight(n1);
    }
    if(n2r != NULL && n2r != n1) {
        n2r->setParent(n1);
    }
    if(n2lt != NULL && n2lt != n1) {
        n2lt->setParent(n1);
    }


    if(this->root_ == n1) {
        this->root_ = n2;
    }
    else if(this->root_ == n2) {
        this->root_ = n1;
    }

}

/**
   Prints up to 5 levels of the tree rooted at the passed node, in ASCII graphics format.
   Included print function in its own file because it's fairly long
*/
#include "print_bst.h"

#endif
