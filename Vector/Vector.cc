// Implementation of the templated Vector class
// ECE4893/8893 lab 3
// Chris Turner

#include <iostream> // debugging
#include "Vector.h"

// Your implementation here
// Fill in all the necessary functions below
using namespace std;

// Default constructor
template <typename T>
Vector<T>::Vector()
{
	elements = (T*)malloc(0); //memory alloc of elements pointer.
	count = 0; //# of elements in vector.
	reserved = 0; //reserved memory count
	
}

// Copy constructor
template <typename T>
Vector<T>::Vector(const Vector& rhs)
{
	count = rhs.count; //count is equal to count of passed vector.
	reserved = rhs.reserved; //reserved is equal to reserved of passed vector.
	elements = (T*)malloc(sizeof(T) * count); //the total element memory is equal to the size of each element * count.
	for ( int i = 0; i < count; i++) {
		new (&elements[i]) T(rhs.elements[i]);
	}
}

// Assignment operator
template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& rhs)
{
	count = rhs.count; //count is equal to count of passed vector.
	reserved = rhs.reserved; //reserved is equal to reserved of passed vector.
	elements = (T*)malloc(sizeof(T) * count); //the total element memory is equal to the size of each element * count.
	return *this;
}

#ifdef GRAD_STUDENT
// Other constructors
template <typename T>
Vector<T>::Vector(size_t nReserved)
{ // Initialize with reserved memory
}

template <typename T>
Vector<T>::Vector(size_t n, const T& t)
{ // Initialize with "n" copies of "t"
}

template <typename T>
void Vector<T>::Reserve(size_t n)
{ // Reserve extra memory
}

#endif

// Destructor
template <typename T>
Vector<T>::~Vector()
{
	Clear();
	free(elements);
}

// Add and access front and back
template <typename T>
void Vector<T>::Push_Back(const T& rhs)
{
	if ( reserved > count) {
		new (&elements[count]) T(rhs);
		count++;
	} else {	
		reserved++;
		T* temp = (T*)malloc(reserved * sizeof(T));
		count++;
		for ( int i = 0; i < (count - 1); i++) {
			new(&temp[i]) T(elements[i]);
			elements[i].~T();
		}
		new(&temp[count - 1]) T(rhs);
		free(elements);
		elements = temp;
	}
}

template <typename T>
void Vector<T>::Push_Front(const T& rhs)
{ //Add elements to begining of vecotr.
	if (count < reserved) { //Space is availble.
		for (size_t i = count; i > count; i--) {
			new (&elements[i]) T(elements[i - 1]);
			elements[i-1].~T();
		}
		
		new (&elements) T(rhs);
		count++;
	} else {
		count++;
		reserved++;
		T* temp = (T*)malloc(reserved * sizeof(T));
		for ( size_t i  = 1; i < count; i++ ) {
			new (&temp[i]) T(elements[i - 1]);
			elements[i - 1].~T();
		}
		new (temp) T(rhs);
		free(elements);
		elements = temp;
		
	}
	
}

template <typename T>
void Vector<T>::Pop_Back()
{ // Remove last element
	if (count == 0) {
		cout << "No elements in array.";
		abort();
	} else {
		//count--;
		elements[--count].~T(); //Move back and clear out current element.
	}
}

template <typename T>
void Vector<T>::Pop_Front()
{ // Remove first element
	if (count == 0) {
		abort();
	} else {
		T* temp = (T*)malloc(reserved * sizeof(T));
		for ( size_t i = 0; i < (count - 1); i++) {
			new(&temp[i]) T(elements[i + 1]);
			elements[i + 1].~T();
		}
		elements[0].~T();
		free(elements);
		elements = temp;
		count--;
	}
}

// Element Access
template <typename T>
T& Vector<T>::Front() const
{
	return elements[0]; //Returns first vector entry.
}

// Element Access
template <typename T>
T& Vector<T>::Back() const
{
	return elements[count - 1]; //Returns last vector entry.
}

template <typename T>
const T& Vector<T>::operator[](size_t i) const
{ // const element access
	if ( (i <= count) && (i >= 0)) {
		return elements[i];
	} else {
		cout << "Error, index outside of vector size.";
		abort();
	}
	
}

template <typename T>
T& Vector<T>::operator[](size_t i)
{//nonconst element access
	if ( (i <= count) && (i >= 0)) {
		return elements[i];
	} else {
		cout << "Error, index outside of vector size.";
		abort();
	}
}


template <typename T>
size_t Vector<T>::Size() const
{
	return count;
}

template <typename T>
bool Vector<T>::Empty() const
{
	return count == (0);
}

// Implement clear
template <typename T>
void Vector<T>::Clear()
{
	for ( int i = 0 ; i < count; i++) {
		elements[i].~T();
	}
	count = 0;
}

// Iterator access functions
template <typename T>
VectorIterator<T> Vector<T>::Begin() const
{
  return VectorIterator<T>(elements);
}

template <typename T>
VectorIterator<T> Vector<T>::End() const
{
	return VectorIterator<T>(&elements[count]);
}

#ifdef GRAD_STUDENT
// Erase and insert
/*template <typename T>
void Vector<T>::Erase(const VectorIterator<T>& it)
{
}

template <typename T>
void Vector<T>::Insert(const T& rhs, const VectorIterator<T>& it)
{
}*/
#endif

// Implement the iterators

// Constructors
template <typename T>
VectorIterator<T>::VectorIterator() //Empty init.
{
	current = NULL;
}

template <typename T>
VectorIterator<T>::VectorIterator(T* c) //Init to variable c.
{
	current = c;
}

// Copy constructor
template <typename T>
VectorIterator<T>::VectorIterator(const VectorIterator<T>& rhs) //Copy iterator value.
{
	current = (rhs.current);
}

// Iterator defeferencing operator
template <typename T>
T& VectorIterator<T>::operator*() const //Return pointer operator.
{
	return *current;
}

// Prefix increment
template <typename T>
VectorIterator<T>  VectorIterator<T>::operator++()
{
	++current;
	return VectorIterator<T>(current);
}

// Postfix increment
template <typename T>
VectorIterator<T> VectorIterator<T>::operator++(int)
{
	current++;
	return VectorIterator<T>(current);
}

// Comparison operators
template <typename T>
bool VectorIterator<T>::operator !=(const VectorIterator<T>& rhs) const
{
	return current != (rhs.current);
}

template <typename T>
bool VectorIterator<T>::operator ==(const VectorIterator<T>& rhs) const
{
	return current == (rhs.current);
}




