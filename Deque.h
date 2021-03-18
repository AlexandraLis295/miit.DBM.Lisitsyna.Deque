#pragma once
#include <sstream>
using namespace std;
template <class T>
class Deque
{
public:
	Deque();
	~Deque();
	Deque<T>* insert_back(const T& value);
	Deque<T>* insert_front(const T& value);
	T* remove(int number, int shift);
	void remove_front();
	void remove_back();
	void Overwrite_Deque(int number, int shift);
	bool dequeIsEmpty() const;
	bool dequeIsFull() const;
	void Expand_Capacity();
	string DequeToString();
private:
	T* deque;
	size_t capacity = 4;
	size_t count;
	const int expandFactor = 2;
};
template <class T>
Deque<T>::Deque()
{
	this->deque = new T[this->capacity];
	this->count = 0;
}
template <class T>
Deque<T>::~Deque()
{
	if (deque != nullptr)
	{
		delete[] this->deque;
		deque = nullptr;
	}
}
template<class T>
Deque<T>* Deque<T>::insert_back(const T& value)
{
	if (this->dequeIsFull())
		this->Expand_Capacity();
	this->deque[this->count++] = value;
	return this;
}
template<class T>
Deque<T>* Deque<T>::insert_front(const T& value)
{
	if (this->dequeIsFull())
		this->Expand_Capacity();
	this->Overwrite_Deque(0, 1);
	this->deque[0] = value;
	this->count++;
	return this;
}
template<class T>
T* Deque<T>::remove(int number, int shift)
{
	if (this->dequeIsEmpty()) return nullptr;
	else
	{
		T& value = this->deque[number];
		this->Overwrite_Deque(number, shift);
		this->count--;
		return &value;
	}
}
template<class T>
void Deque<T>::remove_front()
{
	remove(0, 0);
}
template<class T>
void Deque<T>::remove_back()
{
	remove(count, 0);
}
template <class T>
void Deque<T>::Overwrite_Deque(int number, int shift)
{
	auto buffer = new T[this->capacity];
	copy(this->deque, this->deque + number, buffer);
	for (int i = 0; i <= count - number; i++)
		buffer[number + i + shift] = deque[number + i + 1 - shift];
	delete[] this->deque;
	this->deque = buffer;
}
template <class T>
bool Deque<T>::dequeIsEmpty() const
{
	return (this->count == 0);
}
template <class T>
bool Deque<T>::dequeIsFull() const
{
	return (this->count == this->capacity);
}
template<class T>
void Deque<T>::Expand_Capacity()
{
	this->capacity *= this->expandFactor;
	auto buffer = new T[this->capacity];
	copy(this->deque, this->deque + this->count, buffer);
	delete[] this->deque;
	this->deque = buffer;
}
template<class T>
string Deque<T>::DequeToString()
{
	if (this->dequeIsEmpty())
		return "";
	stringstream Deque_Stream;
	int final = this->count - 1;
	for (int i = 0; i <= final; i++)
		Deque_Stream << this->deque[i] << " ";
	return Deque_Stream.str();
}
