#include "Array.h"

template class Array<int>;
template class Array<float>;
template class Array<double>;
template class Array<std::string>;
template class Array<Date>;

// Constructor dynamically allocate free store memory.
template <class T> Array<T>::Array(long asize) : size{ asize }
{
    arrayElements = new T[size];
}

// Deep copy constructor delagate to default constructor.
template <class T> Array<T>::Array(const Array<T>& rhs)
    : Array{ rhs.getSize() }
{
    for (long i = 0; i < size; i++)
    {
        arrayElements[i] = const_cast<Array<T>&>(rhs)[i];
    }
}

// Destructor releases free store memory.
template <class T> Array<T>::~Array()
{
#ifdef DEBUG_TRACE
    std::cout << "Array of " << typeid(T).name() << " destroyed." << std::endl;
#endif
    delete[] arrayElements;
}

template <class T> long Array<T>::getSize() const
{
    return size;
}

template <class T> void Array<T>::display() const
{
    for (long i = 0; i < size; i++)
    {
        std::cout << "\t" << i << ": " << arrayElements[i] << std::endl;
    }
}

// Specialized display function for Date class.
template <> void Array<Date>::display() const
{
    for (long i = 0; i < size; i++)
    {
        std::cout << "\t";
        arrayElements[i].showDate();
    }
}

template <class T> T& Array<T>::operator[](long s)
{
    return arrayElements[s];
}

// Assignment releases original memory, then performs deep copy.
template <class T> Array<T>& Array<T>::operator=(const Array<T>& rhs)
{
    delete[] arrayElements;
    size = rhs.getSize();
    arrayElements = new T[size];
    for (long i = 0; i < size; i++)
    {
        arrayElements[i] = const_cast<Array<T>&>(rhs)[i];
    }
    return *this;
}

template <class T> Array<T> Array<T>::operator+(const Array<T>& rhs)
{
    long shorterSize = (size < rhs.getSize()) ? size : rhs.getSize();
    Array<T> tempArray(shorterSize);
    for (int i = 0; i < shorterSize; i++)
    {
        tempArray[i] = arrayElements[i] + const_cast<Array<T>&>(rhs)[i];
    }
    return tempArray;
}

// Specialized addition (concatenation) operation, which adds space in-between, for string type.
template <> Array<std::string> Array<std::string>::operator+(const Array<std::string>& rhs)
{
    long shorterSize = (size < rhs.getSize()) ? size : rhs.getSize();
    Array<std::string> tempArray(shorterSize);
    for (int i = 0; i < shorterSize; i++)
    {
        tempArray[i] = arrayElements[i] + " " + const_cast<Array<std::string>&>(rhs)[i];
    }
    return tempArray;
}

// Negation
template <class T> Array<T> Array<T>::operator-()
{
    Array<T> tempArray(size);
    for (long i = 0; i < size; i++)
    {
        tempArray[i] = -arrayElements[i];
    }
    return tempArray;
}