#ifndef _PSLL_H_
#define _PSLL_H_

#include <iostream>
#include <stdexcept>
using namespace std;

namespace COP3530 {
    
    template <class T>
    class PSLL {
        
    private:
        
        struct Node {
            
            Node(T d) : data(d) {}     //Node constructor
            T data;
            Node *next = NULL;      //Defines the pointer that this node is pointing to
            
        };
        
        Node *head = NULL;    //Root node
        Node *tail = NULL;    //Tail node
        
        Node * poolHead = NULL;   //Pool's head
        Node * poolTail = NULL;   //Pool's tail
        
        
        void add_to_pool(Node * n) {       //List adds node to pool when not needed
            
            clean_up();
            
            if(poolHead == NULL) {
                poolHead = n;
                poolTail = n;
                return;
            }
            
            else {
                poolTail->next = n;
                poolTail = poolTail->next;
            }
        }
        
        Node * remove_from_pool(T data) {   //If available, removes a node from pool and adds to list
            //or else allocates a new one
            if(pool_is_empty()) {
                return new Node(data);
            }
            
            else if(pool_size() == 1) {
                poolHead->data = data;
                Node * temp = poolHead;
                poolHead = NULL;
                poolTail = NULL;
                return temp;
            }
            
            else {
                Node *currentNode = poolHead;
                Node *previousNode = NULL;
                
                while(currentNode->next != NULL) {
                    previousNode = currentNode;
                    currentNode = currentNode->next;
                }
                
                currentNode->data = data;
                Node * temp = currentNode;
                previousNode->next = NULL;
                return temp;
            }
        }
        
        
        int pool_size() const {       //Returns pools current size
            
            int count = 0;
            Node * currentNode = poolHead;
            while(currentNode != NULL) {
                currentNode = currentNode->next;
                ++count;
            }
            return count;
        }
        
        bool pool_is_empty() const {    //Returns true if pool empty, else false
            
            return pool_size() == 0;
        }
        
        void clear_pool() {
            
            if(poolHead == NULL) {
                return;
            }
            
            Node * currentNode = poolHead;
            Node * next = NULL;
            
            while(currentNode != NULL) {
                
                next = currentNode->next;
                delete currentNode;
                currentNode = NULL;
                currentNode = next;
            }
            
            poolHead = NULL;
            poolTail = NULL;
        }
        
        ostream& print_pool(ostream& out) const {   //Prints out members of pool
            if(is_empty()) {
                out << "<empty list>";
            }
            
            else {
                Node * currentNode = poolHead;
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
        
        void clean_up() {              //If Linked List size >= 100 AND pool has greater than half of lists nodes
            if(size() >= 100 && pool_size() > size()/2) {    //reduces pools nodes to hald of lists size
                
                int count = size()/2;
                
                Node * currentNode = poolHead;
                for(int i = 0; i < count; ++i) {
                    currentNode = currentNode->next;
                }
                
                poolTail = currentNode;
                currentNode = currentNode->next;
                Node * next = NULL;
                
                while(currentNode != NULL) {
                    
                    next = currentNode->next;
                    delete currentNode;
                    currentNode = NULL;
                    currentNode = next;
                }
                
            }
        }
        
        //---------------------------------------------------------------------------------------------------------
        
    public:
        
        PSLL() {}        //Must explicitly define default constructor
        
        PSLL( PSLL& src ) {
            
            for(int i = 0; i < src.size(); ++i) {    // populate this SSLL with copies of the other SSLL's    contents
                this->push_back(src.item_at(i));
            }
        }
        
        ~PSLL() {
            
            if(!is_empty()) {
                clear();
                clear_pool();
            }
            
            
        }
        
        PSLL& operator=(const PSLL& rhs) {
            if ( &rhs == this ) // check for self-assignment
                return *this;     // do nothing
            
            this->~PSLL();      // safely dispose of this SSLL's contents
            
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
                head = remove_from_pool(element);
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
                Node * newNode = remove_from_pool(element);
                currentNode->next = newNode;
                newNode->next = temp;
            }
            
        }
        
        void push_front(const T& element) {
            
            if(head == NULL) {
                head = remove_from_pool(element);
                tail=head;
            }
            
            else {
                Node * newNode = remove_from_pool(element);
                newNode->next = head;
                head = newNode;
            }
        }
        
        void push_back(const T& element) {
            
            if(head == NULL) {
                head = remove_from_pool(element);
                tail=head;
            }
            
            else {
                tail->next = remove_from_pool(element);
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
            add_to_pool(tempHead);
            return temp;
        }
        
        T pop_back() {
            
            if(head ==  NULL) {
                throw out_of_range("List is empty, cannot remove from back");
            }
            
            if(head->next == NULL) {
                T temp = head->data;
                add_to_pool(head);
                head = NULL;
                tail = NULL;
                return temp;
            }
            
            Node * currentNode = head;
            Node * previousNode = NULL;
            
            while(currentNode->next != NULL) {
                previousNode = currentNode;
                currentNode = currentNode->next;
            }
            
            T temp = currentNode->data;
            add_to_pool(currentNode);
            previousNode->next = NULL;
            return temp;
        }
        
        T remove(int position) {
            
            if(position < 0 || position > size() - 1) {
                throw out_of_range("Invalid position!");
            }
            
            if(position == 0) {
                T temp = head->data;
                Node * tempHead = head;
                head = tempHead->next;
                tempHead->next = NULL;
                add_to_pool(tempHead);
                return temp;
            }
            
            else if(position == size() - 1) {
                Node * currentNode = head;
                Node * previousNode = NULL;
                
                while(currentNode->next != NULL) {
                    previousNode = currentNode;
                    currentNode = currentNode->next;
                }
                
                T temp = currentNode->data;
                add_to_pool(currentNode);
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
                currentNode->next = NULL;
                add_to_pool(currentNode);
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
                add_to_pool(currentNode);
                currentNode = NULL;
                currentNode = next;
            }
            
            head = NULL;
            tail = NULL;
        }
        
        bool contains(const T& element, bool (*fpr)(const T& a,const T& b)) const    {
            
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
        
        ostream& print(ostream& out) const {
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
