// Chevano Gordon

#include <iostream>
#include <cstdlib>
#include <cassert>
#include <iterator>
#include <algorithm>
#include <cstddef>

using namespace std;

template <typename T> class SA;
template <typename T> ostream& operator<< (ostream& os, const SA<T>& s);

template <typename T>
class SA {
  private:
    int low, high, size;
    T* p;

  public:
    SA();
    SA(int);
    SA(int,int);
    SA(const SA<T>&);
    ~SA();

    int length();

    operator T*();
    T& operator[](int);
    SA<T> & operator=(const SA<T> &);

    friend ostream& operator<< <T>(ostream& os, const SA<T>& s);

    class const_iterator;

    class iterator: public std::iterator<std::random_access_iterator_tag, T> {

        private: 
            T* ptr;
            friend class const_iterator;

        public:
            iterator();
            iterator(T*);
            iterator(const iterator&);

            const iterator& operator=(const iterator& obj) {
                ptr = obj.ptr;
                return *this; 
            }

            iterator& operator++() {
                ptr++;
                return *this;
            }

            iterator operator++(int) {
                iterator temp(*this);
                ++(*this);
                return temp;
            }

            iterator& operator--() {
                ptr--; 
                return *this;
            }

            iterator operator--(int) {
                iterator temp(*this);
                --(*this);
                return temp;
            }

            void operator+=(const int& num) {
                ptr += num;
            }

            void operator+=(const iterator& rhs) {
                ptr += rhs.p;
            }

            iterator operator+(const int& num) {
                iterator temp(*this);
                temp += num;
                return temp;
            }

            iterator operator+(const iterator& rhs) {
                iterator temp(*this);
                temp += rhs;

                return temp;
            }

            void operator-=(const int& num) {
                ptr -= num;
            }

            void operator-=(const iterator& rhs) {
                ptr -= rhs.p;
            }

            iterator operator-(const int& num) {
                iterator temp(*this);
                temp -= num;
                return temp;
            }

            int operator-(const iterator& rhs) {
                return ptr - rhs.ptr;
            }

            bool operator<(const iterator& rhs) {
                return (ptr - rhs.ptr) < 0;
            }

            bool operator<=(const iterator& rhs) {
                return (ptr - rhs.ptr) <= 0;
            }

            bool operator>(const iterator& rhs) {
                return (ptr - rhs.ptr) > 0;
            }

            bool operator>=(const iterator& rhs) {
                return (ptr - rhs.ptr) >= 0;
            }

            bool operator==(const iterator& rhs) {
                return (ptr == rhs.ptr);
            }

            bool operator!=(const iterator& obj) {
                return (ptr != obj.ptr);
            }

            T& operator[](const int& num) {
                return *(ptr+num);
            }

            T& operator*() {
                return *ptr;
            }

            T* operator->() {
                return ptr;
            }
    };

    class const_iterator: public std::iterator<std::random_access_iterator_tag, T> {

        private: 
            const T* ptr;
    
        public:
            const_iterator();
            const_iterator(const T*);
            const_iterator(const iterator&);
            const_iterator(const const_iterator&);

            const const_iterator& operator=(const const_iterator& obj) {
                ptr = obj.ptr;
                return obj;
            }

            const const_iterator& operator=(const iterator& obj) {
                ptr = obj.ptr;
                return obj;
            }

            const_iterator& operator++() {
                ptr++;
                return *this;
            }

            const_iterator operator++(int) {
                const_iterator temp(*this);
                ++(*this);
                return temp;
            }

            const_iterator& operator--() {
                ptr--; 
                return *this;
            }

            const_iterator operator--(int) {
                const_iterator temp(*this);
                --(*this);
                return temp;
            }

            void operator+=(const int& num) {
                ptr += num;
            }

            void operator+=(const const_iterator& obj) {
                ptr += obj.ptr;
            }

            const_iterator operator+(const int& num) const{
                const_iterator temp(*this);
                temp += num;
                return temp;
            }

            const_iterator operator+(const const_iterator& obj) const{
                const_iterator temp(*this);
                temp += obj;
                return temp;
            }

            void operator-=(const int& num) {
                ptr -= num;
            }

            void operator-=(const const_iterator& obj) {
                ptr -= obj.ptr;
            }

            const_iterator operator-(const int& num) const{
                const_iterator temp(*this);
                temp -= num;
                return temp;
            }

            int operator-(const const_iterator& obj) const{
                return ptr - obj.ptr;
            }

            bool operator<(const const_iterator& obj) const{
                return (ptr - obj.ptr) < 0;
            }

            bool operator<=(const const_iterator& obj) const{
                return (ptr - obj.ptr) <= 0;
            }

            bool operator>(const const_iterator& obj) const{
                return (ptr - obj.ptr) > 0;
            }

            bool operator>=(const const_iterator& obj) const{
                return (ptr - obj.ptr) >= 0;
            }

            bool operator==(const const_iterator& obj) const{
                return (ptr == obj.ptr);
            }

            bool operator!=(const const_iterator& obj) const{
                return (ptr != obj.ptr);
            }

            const T& operator[](const int& num) const{
                return *(ptr+num);
            }

            const T& operator*() const{
                return *ptr;
            }

            const T* operator->() const{
                return ptr;
            }
    };

    iterator begin() {
        return iterator(p);
    }

    iterator end() {
        return iterator(p + size);
    }

    const_iterator begin() const{
        return const_iterator(p);
    }

    const_iterator end() const {
        return const_iterator(p + size);
    }

    SA(const const_iterator& first, const const_iterator& last);

};

int main() {

    int B[] = {2,3,2,1,33,44,221,5};
    SA<int> Arr( B, B + (sizeof(B) / sizeof(B[0])) );
    cout << "Printing Arr using <<" << endl << Arr << endl << endl;


    cout << "Printing Arr using the const_iterator" << endl;
    for(SA<int>::const_iterator it = Arr.begin(); it != Arr.end(); ++it)
        cout << *it << " ";
    cout << endl << endl;

    SA<int> Brr(Arr.length());
    copy(Arr.begin(), Arr.end(), Brr.begin());
    cout << "Printing Brr after copying from Arr using the copy algorithm" << endl << Brr << endl << endl;

    reverse(Brr.begin(), Brr.end());
    cout << "Reversing the elements in Brr using reverse algorithm" << endl << Brr << endl << endl;

    sort(Brr.begin(), Brr.end());
    cout << "Sorting Brr using sort algorithm" << endl << Brr << endl << endl;

    cout << "Using the find algorithm to check if an element exist" << endl;
    int element = 4;
    SA<int>::iterator it;
    it = find(Brr.begin(), Brr.end(), element);

    if(it != Brr.end())
        cout << "Element " << element << " found" << endl << endl;
    else
        cout << "Element " << element << " not found! " << endl << endl;

    element = 44;
    it = find(Brr.begin(), Brr.end(), element);

    if(it != Brr.end())
        cout << "Element " << element << " found" << endl << endl;
    else
        cout << "Element " << element << " not found! " << endl << endl;

    element = 2;
    cout << "Count the number of occurence of " << element << " present in Brr" << endl;
    cout << count(Brr.begin(), Brr.end(), element) << endl;
    
  return 0;
}

 /******************************
  *     Default Constructor
  ******************************/
template<typename T>
SA<T>::SA() {
    low = 0; 
    high = -1;
    size = 0;
    p = NULL;
}

/******************************
  *     Generic Constructor 1
******************************/
template<typename T>
SA<T>::SA(int low, int high){   
    if((high-low+1) <= 0) {
        cout<< "constructor error in bounds definition" << endl;
        exit(1);
    }
    
    this->low = low;
    this->high = high;
    size = high-low+1;
    p = new T[size];
}

/******************************
  *     Generic Constructor 2
******************************/
template<typename T>
SA<T>::SA(int i) {
    low = 0;
    high = i-1;
    size = i;
    p = new T[size];
}

template<typename T>
SA<T>::SA(const const_iterator& first, const const_iterator& last) {
    size = last - first;
    p = new T[size];

    for(int i = 0; i < size; i++)
        p[i] = first[i];
}

/******************************
  *     Copy Constructor
******************************/
template<typename T>
SA<T>::SA(const SA<T>& s){
    size = s.high - s.low + 1;
    p = new T[size];

    for(int i = 0; i < size; i++)
        p[i] = s.p[i];
    low = s.low;
    high = s.high;
}

/******************************
  *      Destructor
******************************/
template<typename T>
SA<T>::~SA() {
    delete [] p;
}

/******************************
*   Overload [] lets us write
*   SA r(12,31); r[14] = 1
******************************/
template<typename T>
T& SA<T>::operator[](int i) {
    if(i < low || i > high) {
        cout << "index "<< i <<" out of range" << endl;
        exit(1);
    }

    return p[i - low];
}

/******************************
*   Overload = lets us assign
*   one SA object to another
******************************/
template<typename T>
SA<T>& SA<T>::operator=(const SA<T> & s){
    if(this == &s)
        return *this;

    delete [] p;
    size = s.high - s.low + 1;
    p = new T[size];

    for(int i = 0; i < size; i++)
        p[i] = s.p[i];

    low = s.low;
    high = s.high;

    return *this;
}

/******************************
*   Returns the number of 
*   elements in SA
******************************/
template<typename T>
int SA<T>::length() {
    return size;
}

/******************************
*   Conversion function
******************************/
template<typename T>
SA<T>::operator T*() {
    return p;
}

/**********************************
*   Overloading operator << allows
*   us to display SA objects
***********************************/
template <typename T>
ostream& operator<<(ostream& os, const SA<T>& s) {

    for(int i = 0; i < s.size; i++)
        os << s.p[i] << " ";
    return os;
}

template <typename T>
SA<T>::iterator::iterator() {
    ptr = NULL;
}

template <typename T>
SA<T>::iterator::iterator(T* p) {
    ptr = p;
}

template <typename T>
SA<T>::iterator::iterator(const iterator& obj) {
    ptr = obj.ptr;
}

// Doesn't compile, not sure why
// template <typename T>
// const iterator& SA<T>::iterator::operator=(const iterator& obj) {
//     ptr = obj.ptr;
//     return *this; 
// }

template <typename T>
SA<T>::const_iterator::const_iterator() {
    ptr = NULL;
}

template <typename T>
SA<T>::const_iterator::const_iterator(const T* p) {
    ptr = p;
}

template <typename T>
SA<T>::const_iterator::const_iterator(const iterator& obj) {
    ptr = obj.ptr;
}

template <typename T>
SA<T>::const_iterator::const_iterator(const const_iterator& obj) {
    ptr = obj.ptr;
}