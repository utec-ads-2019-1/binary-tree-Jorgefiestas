#ifndef NODE_H
#define NODE_H

template <typename T>
class BSTree; 

template <typename T>
class Iterator; 

template <typename T>
class Node {
    private:
        T data;
        Node<T> *left = nullptr;
        Node<T> *right = nullptr;

    template<class>
    friend class BSTree; 

    template<class>
    friend class Iterator; 
    
    Node(T data){
        this->data = data;
    }
    void killself(){
        if(left) left->killself();
        if(right) right->killself();
        delete *this;
    }
};

#endif
