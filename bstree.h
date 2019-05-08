#ifndef BSTREE_H
#define BSTREE_H

#include "node.h"
#include "iterator.h"

template <typename T> 
class BSTree {
    private:
        Node<T> *root;

    public:
        BSTree() : root(nullptr) {};

        bool find(T data);
        bool insert(T data);
        bool remove(T data);
        void removeNode(Node<T>**);

        unsigned int size();
        unsigned int sizeRec(Node<T>*);

        void traversePreOrder();
        void traverseInOrder();
        void traversePostOrder();
        void traversePreOrderRec(Node<T>*);
        void traverseInOrderRec(Node<T>*);
        void traversePostOrderRec(Node<T>*);

        Iterator<T> begin() {
            return Iterator<T>(root, size(), true);
        }

        Iterator<T> end() { 
            return Iterator<T>(root, size(), false);
        }

        ~BSTree() {
            // TODO
        }
};

template <typename T>
bool BSTree<T>::find(T data){
    Node<T>* temp = root;
    while(temp != nullptr){
        if(temp->data == data) return true;
        if(temp->data > data) temp = temp->left;
        else temp = temp->right;
    }

    return false;
}

template <typename T>
bool BSTree<T>::insert(T data){
    Node<T>* temp = root;
    while(temp != nullptr){
        if(temp->data == data)
            return false;
        if(temp->data > data){
            if(temp->left == nullptr){
                temp->left = new Node<T>(data);
                return true;
            }
            temp = temp->left;
        }
        else{
            if(temp->right == nullptr){
                temp->right = new Node<T>(data);
                return true;
            }
            temp = temp->right;
        }
    }

    root = new Node<T>(data);
    return true;
}

template <typename T>
void BSTree<T>::removeNode(Node<T>** temp){
    if((*temp)->left && (*temp)->right){
        Node<T>** swp = &((*temp)->right);
        if((*swp)->left == nullptr){
            (*swp)->left = (*temp)->left;
            delete *temp;
            *temp = *swp;
            return;
        }
        while((*swp)->left != nullptr)
            swp = &((*swp)->left);
        Node<T>* r = (*swp)->right;
        (*swp)->left = (*temp)->left;
        (*swp)->right = (*temp)->right;
        delete *temp;
        *temp = *swp;
        *swp = r;
    }
    else if((*temp)->left || (*temp)->right){
        Node<T>* temp2 = (*temp)->left ? (*temp)->left : (*temp)->right;
        delete *temp;
        *temp = temp2;
    }
    else{
        delete *temp;
        *temp = nullptr;
    }
}

template <typename T>
bool BSTree<T>::remove(T data){
    Node<T>** temp = &root;

    while(*temp){
        if((*temp)->data == data){
            removeNode(temp);
            return true;
        }
        if((*temp)->data > data) temp = &((*temp)->left);
        else temp = &((*temp)->right);
    }

    return false;
}

template <typename T>
unsigned int BSTree<T>::size(){
    return sizeRec(root);
}


template <typename T>
unsigned int BSTree<T>::sizeRec(Node<T>* node){
    if(node == nullptr) return 0;
    return 1 + sizeRec(node->left) + sizeRec(node->right);
}

template <typename T>
void BSTree<T>::traversePreOrder(){
    traversePreOrderRec(root); 
    cout<<endl;
}

template <typename T>
void BSTree<T>::traversePreOrderRec(Node<T>* node){
    if(node == nullptr) return;
    cout<<node->data<<" ";
    traversePreOrderRec(node->left);
    traversePreOrderRec(node->right);
}

template <typename T>
void BSTree<T>::traverseInOrder(){
    traverseInOrderRec(root); 
    cout<<endl;
}

template <typename T>
void BSTree<T>::traverseInOrderRec(Node<T>* node){
    if(node == nullptr) return;
    traverseInOrderRec(node->left);
    cout<<node->data<<" ";
    traverseInOrderRec(node->right);
}

template <typename T>
void BSTree<T>::traversePostOrder(){
    traversePostOrderRec(root); 
    cout<<endl;
}

template <typename T>
void BSTree<T>::traversePostOrderRec(Node<T>* node){
    if(node == nullptr) return;
    traversePostOrderRec(node->left);
    cout<<node->data<<" ";
    traversePostOrderRec(node->right);
}

#endif
