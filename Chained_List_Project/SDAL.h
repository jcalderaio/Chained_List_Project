#ifndef _SDAL_H_
#define _SDAL_H_


#include <iostream>
#include <stdexcept>
using namespace std;

namespace COP3530 {
    
    template <class T>
    class SDAL {
        
    private:
        
        int head = -1;    //Head
        int tail = -1;    //Tail
        T *array;
        int capacity;
        
        
        void growArray() {
            
            int newCap = capacity * 1.5;
            T *newArray = new T[newCap];
            for(int i = 0; i < size(); ++i) {
                newArray[i] = array[i];
            }
            delete []array;
            capacity = newCap;
            array = newArray;
            
        }
        
        void shrinkArray() {
            
            if(capacity >= 100 && size() < capacity/2) {
                int newCap = capacity * .5;
                T *newArray = new T[newCap];
                for(int i = 0; i < size(); ++i) {
                    newArray[i] = array[i];
                }
                delete[] array;
                capacity = newCap;
                array = newArray;
                
            }
            
        }
        
        
    public:
        
        SDAL() {                          //Default constructor creates array of capacity 50
            array = new T[50];
            capacity = 50;
        };
        
        SDAL(int capacity) : capacity (capacity) {    //Constructor with custom array capacity
            array = new T[capacity];
        }
        
        SDAL(const SDAL& src ) {           //Copy constructor
            
            array = new T[src.capacity];
            capacity = src.capacity;
            for(int i = 0; i < src.size(); ++i) {
                this->push_back(src.item_at(i));
            }
        }
        
        ~SDAL() {              //Array destructor
            delete[] array;
            head = -1;
            tail = -1;
        }
        
        SDAL& operator=( const SDAL& rhs ) {
            if ( &rhs == this )                   // check for self-assignment
                return *this;                             // do nothing
            
            this->~SDAL();                // safely dispose of this SSLL's contents
            this->array = new T[rhs.capacity];   //create new array
            this->capacity = rhs.capacity;
            for(int i = 0; i<rhs.size(); ++i) {    // populate this SSLL with copies of the other SSLL's contents
                this->push_back(rhs.item_at(i));
            }
            
            return *this;
            
        }
        
        T replace(const T& element, int position) {
            
            if(position> size()-1 || position < 0 || is_empty()) {
                throw domain_error("not a valid position!");
            }
            
            T temp = array[position];      //temporarily stores item at original index
            
            array[position] = element;   //replaces item at desired index with new element
            
            return temp;    //returns original element
        }
        
        void insert(const T& element, int position) {
            if(position> size()  || position < 0) {
                throw domain_error("not a valid position!");
            }
            
            if(capacity == size()) {
                growArray();
            }
            
            if (is_empty()){                      //if empty, set index 0 to new element
                array[0] = element;
                tail = 0;
                head = 0;
                if(capacity >= 100 && size() < capacity/2) {
                    shrinkArray();
                }
                return;
            }
            
            
            else if(size() < capacity) {              //If valid index inserts new element at desired position
                for(int i = size() - 1; i >= position; --i) {
                    swap(array[i+1], array[i]);    //Shifts elements in array to the right
                }
                array[position] = element;
                ++tail;
                if(capacity >= 100 && size() < capacity/2) {
                    shrinkArray();
                }
            }
        }
        
        void push_front(const T& element) {      //Prepends element to front of array
            
            if(capacity == size()) {
                growArray();
            }
            
            if (is_empty()){                //If array empty, points head and tail to first item (index 0)
                array[0] = element;
                tail = 0;
                head = 0;
                if(capacity >= 100 && size() < capacity/2) {
                    shrinkArray();
                }
                
            }
            
            else if (size() < capacity)  {              //If size allows, appends item to end of array
                
                for(int i = size() - 1; i >= 0; --i) {
                    swap(array[i+1], array[i]);      //Shifts all elements in array to the right
                }
                array[0] = element;
                ++tail;
                if(capacity >= 100 && size() < capacity/2) {
                    shrinkArray();
                }
            }
            
        }
        
        void push_back(const T& element) {   //Appends an item to the end of array
            
            if(capacity == size()) {
                growArray();
            }
            
            if (is_empty()){            //If array empty, points head and tail to first item (index 0)
                array[0] = element;
                tail = 0;
                head = 0;
                if(capacity >= 100 && size() < capacity/2) {
                    shrinkArray();
                }
                
            }
            
            else if(size() < capacity)  {       //If size allows, appends item to end of array
                ++tail;
                array[tail] = element;
                if(capacity >= 100 && size() < capacity/2) {
                    shrinkArray();
                }
            }
        }
        
        T pop_front() {
            if(head ==  -1) {
                throw out_of_range("List is empty, cannot remove from back");
            }
            
            else if(tail == 0) {
                T temp = array[0];
                head = -1;
                tail = -1;
                if(capacity >= 100 && size() < capacity/2) {
                    shrinkArray();
                }
                return temp;
            }
            
            else {
                T temp = array[head];
                for(int i = 0; i < size(); ++i) {
                    swap(array[i+1], array[i]);
                }
                --tail;
                if(capacity >= 100 && size() < capacity/2) {
                    shrinkArray();
                }
                return temp;
            }
        }
        
        T pop_back() {
            if(head ==  -1) {
                throw out_of_range("List is empty, cannot remove from back");
            }
            
            else if(tail == 0) {
                T temp = array[0];
                head = -1;
                tail = -1;
                if(capacity >= 100 && size() < capacity/2) {
                    shrinkArray();
                }
                return temp;
            }
            
            else {
                T temp = array[tail];
                --tail;
                if(capacity >= 100 && size() < capacity/2) {
                    shrinkArray();
                }
                return temp;
            }
        }
        
        T remove(int position) {
            if(position < 0 || position > size() - 1) {
                throw domain_error("Invalid position!");
            }
            
            if(position == 0) {
                if(size() > 1) {
                    T temp = array[head];
                    for(int i = 0; i < size(); ++i) {
                        swap(array[i+1], array[i]);
                    }
                    --tail;
                    if(capacity >= 100 && size() < capacity/2) {
                        shrinkArray();
                    }
                    return temp;
                }
                
                else {
                    T temp = array[0];
                    head = -1;
                    tail = -1;
                    if(capacity >= 100 && size() < capacity/2) {
                        shrinkArray();
                    }
                    return temp;
                }
                
                
            }
            
            else if(position == size() -1) {
                T temp = array[tail];
                --tail;
                if(capacity >= 100 && size() < capacity/2) {
                    shrinkArray();
                }
                return temp;
            }
            
            else {
                T temp = array[position];
                for(int i = position; i < size(); ++i) {
                    swap(array[i+1], array[i]);
                }
                --tail;
                if(capacity >= 100 && size() < capacity/2) {
                    shrinkArray();
                }
                return temp;
            }
        }
        
        T item_at(int position) const {
            
            if(position >size() - 1 || position < 0) {
                throw domain_error("not a valid position");
                
            }
            else {
                return array[position];
            }
        }
        
        bool is_empty() const {           //Returns true if array is empty, false otherwise
            return (head == -1);
        }
        
        int size() const {             //Returns size of array
            return (tail + 1);
        }
        
        void clear() {               //Resets head and tail to -1, essentially "clearing" the list
            head = -1;
            tail = -1;
            if(capacity >= 100 && size() < capacity/2) {
                shrinkArray();
            }
        }
        
        bool contains(const T& element, bool (*fpr)(const T& a,const T& b)) const   {
            
            bool ans = false;
            
            for(int i = 0; i<size(); ++i) {
                ans = fpr(element, item_at(i));
                
                if(ans) {
                    return true;
                }
            }
            
            return false;
            
        }
        
        ostream& print(ostream& out) const {     //Prints out all items in array
            if(is_empty()) {
                out << "<empty list>";
            }
            
            else {
                out << "<" << "[" << array[0];
                
                for(int i = 1; i<size(); ++i) {
                    
                    out << "," << array[i];
                }
                out << "]>";
            }
            return out;
        }
        
    };
}

#endif
