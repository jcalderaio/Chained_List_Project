#ifndef _CDAL_H_
#define _CDAL_H_

#include <iostream>
#include <stdexcept>
using namespace std;

namespace COP3530 {
    
    template <class T>
    class CDAL {
        
    private:
        
        struct Node {
            
            int array_size = 0;     //Array 's current number of items
            T *array;             //Pointer to Node's array
            
            Node *next = NULL;      //Defines the pointer that this node is pointing to
            
            Node()  {                //Node constructor
                array = new T[50];  //Dynamically allocates a new array of size 50
            }
            ~Node() {              //Array destructor
                delete[] array;
            }
            
        };
        //---------------------------------------------------------------------------------------------------------
        
        Node *head = NULL;      //Head node
        Node *tail = NULL;      //Tail node
        T * tempArr;
        
    public:
        
        CDAL() {}        //Must explicitly define default constructor
        
        CDAL(const CDAL& src ) {
            
            for(int i = 0; i < src.size(); ++i) {    // populate this SSLL with copies of the other CDAL's contents
                this->push_back(src.item_at(i));
            }
        }
        
        ~CDAL() {
            if(!is_empty()) {
                clear();
            }
        }
        
        CDAL& operator=(const CDAL& rhs) {
            if ( &rhs == this ) // check for self-assignment
                return *this;     // do nothing
            
            this->~CDAL();      // safely dispose of this SSLL's contents
            
            for(int i = 0; i < rhs.size(); ++i) {    // populate this SSLL with copies of the other SSLL's contents
                this->push_back(rhs.item_at(i));
            }
            return *this;
        }
        
        T replace(const T& element, int position) {
            if(position> size() || position < 0 || is_empty()) {     //If invalid position, throws exception
                throw domain_error("not a valid position!");
            }
            
            else {
                int nodeNum = position / 50;     //Position of node to insert at
                int index = position % 50;       //Position of index in node to insert at
                
                Node * currentNode = head;
                
                for(int i = 0; i < nodeNum; ++i) {     //Traverse the node until desired node is reached
                    currentNode = currentNode->next;
                }
                
                T temp = currentNode->array[index];
                currentNode->array[index] = element;
                return temp;
            }
        }
        
        void insert(const T& element, int position) {
            if(position> size() || position < 0) {     //If invalid position, throws exception
                throw domain_error("not a valid position!");
            }
            
            else if (is_empty()){                      //if empty, set index 0 to new element
                if(head == NULL) {
                    head = new Node();
                    tail = head;
                    head->array[head->array_size] = element;
                    ++head->array_size;
                }
            }
            
            else if(position == size()) {       //If could get this to work, would run faster when adding to end of list
                push_back(element);
                
            }
            
            else {
                Node * currentNode = head;
                
                tempArr = new T[size() + 1];   //Creates new array of size of chained list plus one
                
                int totalSize = 0;
                while(currentNode != NULL) {
                    for(int j = 0; j < currentNode->array_size; ++j) {
                        
                        tempArr[totalSize] = currentNode->array[j];                 //Copies contents of chained list into temporary array
                        ++totalSize;
                    }
                    currentNode =currentNode->next;
                }
                
                for(int i = size(); i >= position; --i) {
                    swap(tempArr[i+1], tempArr[i]);                                 //Shifts elements in array to the right
                }
                
                tempArr[position] = element;                                //Inserts element into temp array at desired position
                
                //                            cout <<"Temp Array: " <<  "<[" << tempArr[0];         //Prints out temporary array for testing
                //                            for(int i = 1; i <= size(); ++i) {
                //                                cout << "," << tempArr[i];
                //                            }
                //
                //                            cout << "]>";
                
                currentNode = head;
                int tempCount = 0;
                while(currentNode != NULL) {                                //Replaces Chained List with temp array, in the correct order
                    for(int j = 0; j < currentNode->array_size; ++j) {
                        currentNode->array[j] = tempArr[tempCount];
                        ++tempCount;
                        
                    }
                    currentNode =currentNode->next;
                }
                
                push_back(tempArr[tempCount]);
                delete []tempArr;
            }
        }
        
        void push_front(const T& element) {
            if(head == NULL) {
                head = new Node();
                tail = head;
                head->array[head->array_size] = element;
                ++head->array_size;
            }
            
            else {
                insert(element, 0);
            }
        }
        
        void push_back(const T& element) {      //Appends element to last position
            if(head == NULL) {
                head = new Node();          //If head is NULL, sets head to a new node with array sized 50
                tail = head;
                head->array[head->array_size] = element;
                ++head->array_size;         //Increases Head nodes array size
            }
            
            else if(size() % 50 == 0) {      //If at end of current nodes array, creates a new link in chain
                tail->next = new Node();
                tail = tail->next;
                tail->array[tail->array_size] = element;
                ++tail->array_size;
            }
            
            else {
                tail->array[tail->array_size] = element;     //Else, adds to back of list
                ++tail->array_size;
            }
        }
        
        T pop_front() {
            T temp = remove(0);
            return temp;
        }
        
        T pop_back() {
            
            if(head ==  NULL) {
                throw out_of_range("List is empty, cannot remove from back");
            }
            
            if(size() == 1) {
                T temp = head->array[--head->array_size];
                head = NULL;
                tail = NULL;
                return temp;
            }
            
            else if((size() - 1) % 50 == 0) {
                int nodeNum = size() / 50;     //Position of node to insert at
                
                Node * currentNode = head;
                
                for(int i = 0; i < nodeNum-1; ++i) {     //Traverse the node until desired node is reached
                    currentNode = currentNode->next;
                }
                
                T temp = currentNode->next->array[0];
                --currentNode->next->array_size;
                tail = currentNode;
                return temp;
                
            }
            
            else {
                T temp = tail->array[--tail->array_size];
                return temp;
            }
        }
        
        T remove (int position) {
            if(position> size() || position < 0) {     //If invalid position, throws exception
                throw domain_error("not a valid position!");
            }
            
            else if(is_empty()) {
                throw out_of_range("list already empty!");
            }
            
            else if(size() == 1) {
                T temp = head->array[--head->array_size];
                head = NULL;
                tail = NULL;
                return temp;
            }
            
            else if(position == size() - 1) {
                T temp = pop_back();
                return temp;
                
            }
            
            else {
                Node * currentNode = head;
                
                tempArr = new T[size()];   //Creates new array of size of chained list plus one
                
                int totalSize = 0;
                while(currentNode != NULL) {
                    for(int j = 0; j < currentNode->array_size; ++j) {
                        
                        tempArr[totalSize] = currentNode->array[j];                 //Copies contents of chained list into temporary array
                        ++totalSize;
                    }
                    currentNode =currentNode->next;
                }
                
                T temp = tempArr[position];
                
                for(int i = position; i < size(); ++i) {                        //Shifts elements in array to the right
                    swap(tempArr[i+1], tempArr[i]);
                }
                
                //                cout <<"Temp Array: " <<  "<[" << tempArr[0];         //Prints out temporary array for testing
                //                for(int i = 1; i <= size(); ++i) {
                //                    cout << "," << tempArr[i];
                //                }
                //
                //                cout << "]>";
                
                currentNode = head;
                int tempCount = 0;
                while(currentNode != NULL) {                                //Replaces Chained List with temp array, in the correct order
                    for(int j = 0; j < currentNode->array_size; ++j) {
                        currentNode->array[j] = tempArr[tempCount];
                        ++tempCount;
                        
                    }
                    currentNode =currentNode->next;
                }
                pop_back();
                delete []tempArr;
                return temp;
            }
            
        }
        
        T item_at(int position) const {
            if(position> size() || position < 0 || is_empty()) {     //If invalid position, throws exception
                throw domain_error("not a valid position!");
            }
            
            else {
                int nodeNum = position / 50;     //Position of node to insert at
                int index = position % 50;       //Position of index in node to insert at
                
                Node * currentNode = head;
                
                for(int i = 0; i < nodeNum; ++i) {     //Traverse the node until desired node is reached
                    currentNode = currentNode->next;
                }
                
                T temp = currentNode->array[index];
                return temp;
            }
            
        }
        
        bool is_empty() const {    //Returns true if list is empty, else false
            return (head == NULL);
        }
        
        int size() const {    //Returns number of items in list
            
            
            if(head == NULL) {
                return 0;
            }
            
            int count = 0;
            Node * currentNode = head;
            
            while(currentNode != NULL) {
                for(int j = 0; j < currentNode->array_size; ++j) {
                    ++count;
                }
                currentNode =currentNode->next;
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
                for(int j = 0; j < currentNode->array_size; ++j) {
                    
                    ans = fpr(element, currentNode->array[j]);
                    if(ans) {
                        return true;
                    }
                    
                }
                currentNode =currentNode->next;
            }
            
            return false;
            
        }
        
        ostream& print(ostream& out) {    //Prints out all items in list
            if(is_empty()) {
                out << "<empty list>";
            }
            
            else if(size() == 1) {
                out << "<[" << head->array[0] << "]>";
            }
            
            else {
                
                Node * currentNode = head;
                
                out << "<" << "[" << currentNode->array[0];
                
                int set = 0;
                
                if(size() >= 1) {
                    
                    while(currentNode != NULL) {
                        for(int j = 0; j < currentNode->array_size; ++j) {
                            if(set == 0) {
                                j = 1;
                                ++ set;
                            }
                            out << "," << currentNode->array[j];
                            
                        }
                        currentNode =currentNode->next;
                    }
                    
                }
                
                out << "]>";
            }
            return out;
        }
    };
}

#endif