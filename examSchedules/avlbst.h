#ifndef RBBST_H
#define RBBST_H

#include <iostream>
#include <exception>
#include <cstdlib>
#include <algorithm>
#include "bst.h"

struct KeyError { };


//A special kind of node for an AVL tree, adds the height as a data member
template <typename Key, typename Value>
class AVLNode : public Node<Key, Value>
{
public:
    // Constructor/destructor.
    AVLNode(const Key& key, const Value& value, AVLNode<Key, Value>* parent);
    virtual ~AVLNode();

    // Getter/setter for the node's height.
    int getHeight () const;
    void setHeight (int height);

    // Getters for parent, left, and right. 
    virtual AVLNode<Key, Value>* getParent() const override;
    virtual AVLNode<Key, Value>* getLeft() const override;
    virtual AVLNode<Key, Value>* getRight() const override;

protected:
    int height_;
};


/**
* An explicit constructor to initialize the elements by calling the base class constructor
*/
template<class Key, class Value>
AVLNode<Key, Value>::AVLNode(const Key& key, const Value& value, AVLNode<Key, Value> *parent) :
    Node<Key, Value>(key, value, parent), height_(1)
{

}

/**
* A destructor which does nothing.
*/
template<class Key, class Value>
AVLNode<Key, Value>::~AVLNode()
{

}

/**
* A getter for the height of a AVLNode.
*/
template<class Key, class Value>
int AVLNode<Key, Value>::getHeight() const
{
    return height_;
}

/**
* A setter for the height of a AVLNode.
*/
template<class Key, class Value>
void AVLNode<Key, Value>::setHeight(int height)
{
    height_ = height;
}

/**
* An overridden function for getting the parent since a static_cast is necessary to make sure
* that the node is a AVLNode.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getParent() const
{
    return static_cast<AVLNode<Key, Value>*>(this->parent_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getLeft() const
{
    return static_cast<AVLNode<Key, Value>*>(this->left_);
}

/**
* Overridden for the same reasons as above.
*/
template<class Key, class Value>
AVLNode<Key, Value> *AVLNode<Key, Value>::getRight() const
{
    return static_cast<AVLNode<Key, Value>*>(this->right_);
}


template <class Key, class Value>
class AVLTree : public BinarySearchTree<Key, Value>
{
public:
    virtual void insert (const std::pair<const Key, Value> &new_item); // TODO
    virtual void remove(const Key& key);  // TODO
protected:
    virtual void nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2);
    void rotate(AVLNode<Key,Value>* z, AVLNode<Key,Value>* y, AVLNode<Key,Value>* x);
    void leftSingleRotation(AVLNode<Key,Value>* z, AVLNode<Key,Value>* y, AVLNode<Key,Value>* x);
    void rightSingleRotation(AVLNode<Key,Value>* z, AVLNode<Key,Value>* y, AVLNode<Key,Value>* x);
    void rightLeftZigZag(AVLNode<Key,Value>* z, AVLNode<Key,Value>* y, AVLNode<Key,Value>* x);
    void leftRightZigZag(AVLNode<Key,Value>* z, AVLNode<Key,Value>* y, AVLNode<Key,Value>* x);
    bool balancedHeight(AVLNode<Key,Value>* x);
    bool insertDidntUpdateHeight(AVLNode<Key,Value>* x);
    bool needToChangeHeight(AVLNode<Key,Value>* x);
    AVLNode<Key, Value>* getLowerNode(AVLNode<Key,Value>* z);
    void updateParentsChild(Node<Key, Value> *child, Node<Key, Value> *parent, Node<Key, Value> *update);

};

template<class Key, class Value>
void AVLTree<Key, Value>::insert (const std::pair<const Key, Value> &new_item)
{
    AVLNode<Key, Value>* newAVLNode = new AVLNode<Key, Value>(new_item.first, new_item.second, NULL);
    AVLNode<Key, Value>* inserted = static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key,Value>::insertHelper(newAVLNode));
    
    if(inserted -> getParent() == NULL){
        this->root_ = inserted;
        return;
    }
    AVLNode<Key, Value>* currentAVLNode = inserted -> getParent();
    bool alreadyRotated = false;

    while(!(currentAVLNode == NULL || insertDidntUpdateHeight(currentAVLNode) || alreadyRotated)){
        if(!balancedHeight(currentAVLNode))
        {
            AVLNode<Key, Value>* y = getLowerNode(currentAVLNode);
            AVLNode<Key, Value>* x = getLowerNode(y);
            rotate(currentAVLNode, y, x);
            alreadyRotated = true;
        }
        else{
            currentAVLNode->setHeight(currentAVLNode->getHeight() +1);
        }
        currentAVLNode = currentAVLNode -> getParent();
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>:: remove(const Key& key)
{
    AVLNode<Key, Value>* removed = static_cast<AVLNode<Key, Value>*>(BinarySearchTree<Key,Value>::removeHelper(key));
    AVLNode<Key, Value>* currentAVLNode = removed;
    while(currentAVLNode != NULL){
        if(!balancedHeight(currentAVLNode))
        {
            AVLNode<Key, Value>* y = getLowerNode(currentAVLNode);
            AVLNode<Key, Value>* x = getLowerNode(y);
            rotate(currentAVLNode, y, x);
        }
        currentAVLNode = currentAVLNode -> getParent();
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::nodeSwap( AVLNode<Key,Value>* n1, AVLNode<Key,Value>* n2)
{
    BinarySearchTree<Key, Value>::nodeSwap(n1, n2);
    int tempH = n1->getHeight();
    n1->setHeight(n2->getHeight());
    n2->setHeight(tempH);
}


template<class Key, class Value>
void AVLTree<Key, Value>::rotate(AVLNode<Key,Value>* z, AVLNode<Key,Value>* y, AVLNode<Key,Value>* x){
    if(z->getKey() > y->getKey()){
        if(x == NULL){
            rightSingleRotation(z, y, x);
        }
        else if(y->getKey() > x->getKey()){
            rightSingleRotation(z, y, x);
        }
        else{ //y->getKey() < x->getKey()
            leftRightZigZag(z, y, x);
        }
    }
    else{ //z->getKey() < y->getKey
        if(x == NULL){
            leftSingleRotation(z, y, x);
        }
        else if(y->getKey() < x->getKey()){
            leftSingleRotation(z, y, x);
        }
        else{ //y->getKey() > x->getKey()
            rightLeftZigZag(z, y, x);
        }
    }
}

template<class Key, class Value>
void AVLTree<Key, Value>::leftSingleRotation(AVLNode<Key,Value>* z, AVLNode<Key,Value>* y, AVLNode<Key,Value>* x){
    if(z->getParent() == NULL){
        this->root_ = y;
    }
    else{
        updateParentsChild(z, z->getParent(), y);
    }
    
    y->setParent(z->getParent());
    z->setParent(y);
    if(y->getLeft() != NULL){
        y->getLeft()->setParent(z);
    }
    z->setRight(y->getLeft());
    y->setLeft(z);

    z->setHeight(z->getHeight() - 1);
    needToChangeHeight(z);
    needToChangeHeight(x);
    needToChangeHeight(y);
}

template<class Key, class Value>
void AVLTree<Key, Value>::rightSingleRotation(AVLNode<Key,Value>* z, AVLNode<Key,Value>* y, AVLNode<Key,Value>* x){
    if(z->getParent() == NULL){
        this->root_ = y;
    }
    else{
        updateParentsChild(z, z->getParent(), y);
    }

    y->setParent(z->getParent());
    z->setParent(y);
    if(y->getRight() != NULL){
        y->getRight()->setParent(z);
    }
    z->setLeft(y->getRight());
    y->setRight(z);

    z->setHeight(z->getHeight() - 1);
    needToChangeHeight(z);
    needToChangeHeight(x);
    needToChangeHeight(y);
}

template<class Key, class Value>
void AVLTree<Key, Value>::rightLeftZigZag(AVLNode<Key,Value>* z, AVLNode<Key,Value>* y, AVLNode<Key,Value>* x){
    if(z->getParent() == NULL){
        this->root_ = x;
    }
    else{
        updateParentsChild(z, z->getParent(), x);
    }
    if(x->getLeft() != NULL){
        x->getLeft()->setParent(z);
    }
    if(x->getRight() != NULL){
        x->getRight()->setParent(y);
    }

    x->setParent(z->getParent());
    y->setParent(x);
    z->setParent(x);
    y->setLeft(x->getRight());
    z->setRight(x->getLeft());
    x->setLeft(z);
    x->setRight(y);



    x->setHeight(x->getHeight() + 1);
    z->setHeight(z->getHeight() - 1);
    needToChangeHeight(z);
    needToChangeHeight(y);
    needToChangeHeight(x);
}

template<class Key, class Value>
void AVLTree<Key, Value>::leftRightZigZag(AVLNode<Key,Value>* z, AVLNode<Key,Value>* y, AVLNode<Key,Value>* x){
    if(z->getParent() == NULL){
        this->root_ = x;
    }
    else{
        updateParentsChild(z, z->getParent(), x);
    }
    if(x->getLeft() != NULL){
        x->getLeft()->setParent(y);
    }
    if(x->getRight() != NULL){
        x->getRight()->setParent(z);
    }
    
    x->setParent(z->getParent());
    y->setParent(x);
    z->setParent(x);
    y->setRight(x->getLeft());
    z->setLeft(x->getRight());
    x->setRight(z);
    x->setLeft(y);

    x->setHeight(x->getHeight() + 1);
    z->setHeight(z->getHeight() - 1);
    needToChangeHeight(z);
    needToChangeHeight(y);
    needToChangeHeight(x);
}

template<typename Key, typename Value>
void AVLTree<Key, Value>::updateParentsChild(Node<Key, Value> *child, Node<Key, Value> *parent, Node<Key, Value> *update){
    if(parent->getRight() == child){ //child is parent's right child
        parent->setRight(update);
    }
    else{ //child is parents left child
        parent->setLeft(update);
    }
}

template<class Key, class Value>
AVLNode<Key, Value>* AVLTree<Key, Value>::getLowerNode(AVLNode<Key,Value>* z){
    AVLNode<Key,Value>* zLeft = z -> getLeft();
    AVLNode<Key,Value>* zRight = z -> getRight();
    if(zLeft == NULL){
        return zRight;
    }
    else if(zRight == NULL){
        return zLeft;
    }
    else if(zRight->getHeight() > zLeft->getHeight()){
        return zRight;
    }
    else if(zLeft->getHeight() > zRight->getHeight()){
        return zLeft;
    }
    else{ //zLeft->getHeight() == zRight->getHeight(), only applies to finding x
        if(z -> getKey() <= z->getParent()->getKey()){
            return zLeft;
        }
        else{
            return zRight;
        }
    }
}


template<class Key, class Value>
bool AVLTree<Key, Value>::balancedHeight(AVLNode<Key,Value>* x){
    if(x -> getRight() == NULL && x -> getLeft() == NULL){
        return true;
    }
    else if(x -> getRight() == NULL){
        if(x->getLeft()->getHeight() >= 2){
            return false;
        }
        return true;
    }
    else if(x -> getLeft() == NULL){
        if(x->getRight()->getHeight() >= 2){
            return false;
        }
        return true;
    }
    else if(std::abs(x->getLeft()->getHeight() - x->getRight()->getHeight()) >= 2){
        return false;
    }
    else{
        return true;
    }
}

template<class Key, class Value>
bool AVLTree<Key, Value>::insertDidntUpdateHeight(AVLNode<Key,Value>* x){
    if(x -> getLeft() != NULL && x -> getRight() != NULL){
        if(x->getLeft()->getHeight() == x->getRight()->getHeight()){
            return true;
        }
    }
    return false;
}

template<class Key, class Value>
bool AVLTree<Key, Value>::needToChangeHeight(AVLNode<Key,Value>* x){
    if(x == NULL){
        return false;
    }

    int leftChildHeight;
    int rightChildHeight;
    if(x -> getLeft() == NULL){
        leftChildHeight = 0;
    }
    else{
        leftChildHeight = x -> getLeft()->getHeight();
    }
    if(x -> getRight() == NULL){
        rightChildHeight = 0;
    }
    else{
        rightChildHeight = x -> getRight()->getHeight();
    }

    if(x->getHeight() !=  std::max(leftChildHeight, rightChildHeight) + 1){
        x->setHeight(std::max(leftChildHeight, rightChildHeight) + 1);
        return true;
    }
    else{
        return false;
    }
}






#endif
