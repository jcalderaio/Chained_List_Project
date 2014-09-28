#ifndef _SSLL_H_
#define _SSLL_H_


#include <iostream>
#include <stdexcept>
using namespace std;

namespace COP3530 {
    
    template <class T>
    class SSLL {
        
    private:
        
        struct Node {
            
            Node(T d) : data(d) {}     //Node constructor
            T data;
            Node *next = NULL;      //Defines the pointer that this node is pointing to
            
        };
        
        Node *head = NULL;    //Root node
        Node *tail = NULL;    //Tail node
        
    public:
        
        SSLL() {}
        
        SSLL(const SSLL& src ) {
            
            for(int i = 0; i < src.size(); ++i) {    // populate this SSLL with copies of the other SSLL's    contents
                this->push_back(src.item_at(i));
            }
        }
        
        ~SSLL() {
            
            if(!is_empty()) {
                clear();
            }
            
        }
        
        SSLL& operator=(const SSLL& rhs) {
            if ( &rhs == this ) // check for self-assignment
                return *this;     // do nothing
            
            this->~SSLL();      // safely dispose of this SSLL's contents
            
            for(int i = 0; i < rhs.size(); ++i) {    // populate this SSLL with copies of the other SSLL's contents
                this->push_back(rhs.item_at(i));
            }
            return *this;
        }
        
        T replace(const T& element, int position) {
            
            if(position> size()-1 || position < 0 || is_empty()) {
                throw domain_error("not a valid position!");
            }
            
            Node * currentNode = head;
            
            for(int i = 0; i < position; ++i) {
                currentNode = currentNode->next;
            }
            
            T temp = currentNode->data;
            currentNode->data = element;
            return temp;
        }
        
        void insert(const T& element, int position) {
            
            if(position> size() || position < 0 || is_empty()) {
                throw domain_error("not a valid position!");
            }
            
            if(head == NULL) {
                head = new Node(element);
                tail=head;
            }
            
            else if(position == 0) {
                push_front(element);
            }
            
            else {
                
                Node * currentNode = head;
                
                for(int i = 0; i < position-1; ++i) {
                    currentNode = currentNode->next;
                }
                
                Node * temp = currentNode->next;
                Node * newNode = new Node(element);
                currentNode->next = newNode;
                newNode->next = temp;
            }
            
        }
        
        void push_front(const T& element) {
            
            if(head == NULL) {
                head = new Node(element);
                tail=head;
            }
            
            else {
                Node * newNode = new Node(element);
                newNode->next = head;
                head = newNode;
            }
        }
        
        void push_back(const T& element) {
            
            if(head == NULL) {
                head = new Node(element);
                tail=head;
            }
            
            else {
                tail->next = new Node(element);
                tail = tail->next;
            }
        }
        
        T pop_front() {
            
            if(head ==  NULL) {
                throw out_of_range("List is empty, cannot remove from front");
            }
            
            T temp = head->data;
            Node * tempHead = head;
            head = tempHead->next;
            tempHead->next = NULL;
            delete tempHead;
            return temp;
        }
        
        T pop_back() {
            
            if(head ==  NULL) {
                throw out_of_range("List is empty, cannot remove from back");
            }
            
            if(head->next == NULL) {
                T temp = head->data;
                delete head;
                head = NULL;
                return temp;
            }
            
            Node * currentNode = head;
            Node * previousNode = NULL;
            
            while(currentNode->next != NULL) {
                previousNode = currentNode;
                currentNode = currentNode->next;
            }
            
            T temp = currentNode->data;
            delete currentNode;
            previousNode->next = NULL;
            return temp;
        }
        
        T remove(int position) {
            
            if(position < 0 || position > size() - 1) {
                throw out_of_range("Invalid position!");
            }
            
            if(position == 0) {
                T tempData = head->data;
                Node * tempHead = head;
                head = tempHead->next;
                delete tempHead;
                return tempData;
            }
            
            else if(position == size() - 1) {
                Node * currentNode = head;
                Node * previousNode = NULL;
                
                while(currentNode->next != NULL) {
                    previousNode = currentNode;
                    currentNode = currentNode->next;
                }
                
                T temp = currentNode->data;
                delete currentNode;
                previousNode->next = NULL;
                tail = previousNode;
                return temp;
            }
            else {
                
                Node *currentNode = head;
                Node *previousNode = NULL;
                
                for(int i = 0; i < position; ++i) {
                    previousNode = currentNode;
                    currentNode = currentNode->next;
                }
                
                T temp = currentNode->data;
                previousNode->next = currentNode->next;
                delete currentNode;
                return temp;
            }
        }
        
        T item_at(int position) const {
            
            Node * currentNode = head;
            
            for(int i = 0; i < position; ++i) {
                currentNode = currentNode->next;
            }
            
            return currentNode->data;
        }
        
        bool is_empty() const {
            
            return size() == 0;
        }
        
        int size() const {
            
            int count = 0;
            Node * currentNode = head;
            while(currentNode != NULL) {
                currentNode = currentNode->next;
                ++count;
            }
            return count;
        }
        
        void clear() {
            
            if(head == NULL) {
                return;
            }
            
            Node * currentNode = head;
            Node * next = NULL;
            
            while(currentNode != NULL) {
                
                next = currentNode->next;
                delete currentNode;
                currentNode = NULL;
                currentNode = next;
            }
            
            head = NULL;
            tail = NULL;
        }
        
        bool contains(const T& element, bool (*fpr)(const T& a,const T& b)) const   {
            
            bool ans = false;
            
            Node * currentNode = head;
            
            while(currentNode != NULL) {
                ans = fpr(element, currentNode->data);
                
                if(ans) {
                    return true;
                }
                
                else {
                    currentNode = currentNode->next;
                }
            }
            
            return false;
            
        }
        
        ostream& print(ostream& out) {
            if(is_empty()) {
                out << "<empty list>";
            }
            
            else {
                Node * currentNode = head;
                out << "<" << "[" << currentNode->data;
                currentNode=currentNode->next;
                while(currentNode != NULL) {
                    
                    out << "," << currentNode->data;
                    currentNode = currentNode->next;
                }
                out << "]>";
            }
            return out;
        }
        
    };
}

#endif