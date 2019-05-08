#ifndef ITERATOR_H
#define ITERATOR_H

#include "node.h"
#include <stack>
using namespace std;

template <typename T> 
class Iterator {
    private:
        Node<T> *current;
        int size = 0;
        int idx = 0;
        stack<Node<T>*> over;
        bool end = false;

    public:
        Iterator(Node<T> *node, int size, bool s) {
            this->size = size;
            if(!node){
                end = true;
                current = nullptr;
            }
            else if(s){
                idx = 0;
                while(node->left){
                    over.push(node);
                    node = node->left;
                }
                current = node;
            }
            else{
                idx = size;
                while(node){
                    over.push(node);
                    node = node->right;
                }
                current = nullptr;
                end = true;
            }
        }

        Iterator<T> operator=(Iterator<T> other) {          
            current = other.current;
            over = other.over;
            return *this;
        }

        bool operator!=(Iterator<T> other) {
            return current != other.current || end != other.end;
        }

        Iterator<T> operator++() {
            if(end)
                throw out_of_range("Seg Fault!");
            if(idx == size-1){
                if(current->right){
                    size++;
                    return ++(*this);
                }
                over.push(current);
                end = true;
                current = nullptr;
            }
            else if(!current->right){
                while(over.top()->data < current->data)
                    over.pop();
                current = over.top();
                over.pop();
            }
            else{
                over.push(current);
                current = current->right;
                while(current->left){
                    over.push(current);
                    current = current->left;
                }
            }
            idx++;
            return *this;
        }

        Iterator<T> operator--() {
            if(idx == 0){
                if(current->left){
                    size++;
                    idx = 1;
                    return --(*this);
                }
                throw out_of_range("Seg Fault!");
            }
            if(end){
                current = over.top();
                over.pop();
                end = false;
            }
            else if(!current->left){
                while(over.top()->data > current->data)
                    over.pop();
                current = over.top();
                over.pop();
            }
            else{
                over.push(current);
                current = current->left;
                while(current->right){
                    over.push(current);
                    current = current->right;
                }
            }
            idx--;
            return *this;
        }

        T operator*() {
            return current->data;
        }
};

#endif
