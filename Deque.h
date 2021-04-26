#pragma once
#include <sstream>
using namespace std;
template <class T>
class Deque
{
public:
	Deque();
	~Deque();
	void insert_back(const T& value);
	void insert_front(const T& value);
	T* remove_front();
	T* remove_back();
	bool deque_is_empty() const;
	bool deque_is_full() const;
	string deque_to_string();
private:
	T* deque;
	size_t capacity = 4;
	size_t count;
	const int expandFactor = 2;
	void expand_capacity();
	void overwrite_deque(int number, int shift); //numder - то, что будем сдвигать, shift - на сколько
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
void Deque<T>::insert_back(const T& value)
{
	if (this->deque_is_full())
		this->expand_capacity();
	this->deque[this->count++] = value;
}
template<class T>
void Deque<T>::insert_front(const T& value)
{
	if (this->deque_is_full())
		this->expand_capacity();
	this->overwrite_deque(0, 1); //сдвигаем первый (нулевой) на 1 вправо 
	this->deque[0] = value;
	this->count++;
}

template<class T>
T* Deque<T>::remove_front()
{
	if (this->deque_is_empty()) return nullptr;
	else
	{
		T& value = this->deque[0];
		this->overwrite_deque(0, 0); //сдвигаем первый (нулевой) влево на 1
		this->count--;
		return &value;
	}
}
template<class T>
T* Deque<T>::remove_back()
{
	if (this->deque_is_empty()) return nullptr;
	else
	{
		T& value = this->deque[count];
		this->overwrite_deque(count, 0);
		this->count--;
		return &value;
	}
}
template <class T>
void Deque<T>::overwrite_deque(int number, int shift)
{
	auto buffer = new T[this->capacity];
	copy(this->deque, this->deque + number, buffer);
	for (int i = 0; i <= count - number; i++)
		buffer[number + i + shift] = deque[number + i + 1 - shift];
	delete[] this->deque;
	this->deque = buffer;
}
template <class T>
bool Deque<T>::deque_is_empty() const
{
	return (this->count == 0);
}
template <class T>
bool Deque<T>::deque_is_full() const
{
	return (this->count == this->capacity);
}
template<class T>
void Deque<T>::expand_capacity()
{
	this->capacity *= this->expandFactor;
	auto buffer = new T[this->capacity];
	copy(this->deque, this->deque + this->count, buffer);
	delete[] this->deque;
	this->deque = buffer;
}
template<class T>
string Deque<T>::deque_to_string()
{
	if (this->deque_is_empty())
		return "";
	stringstream deque_stream;
	int final = this->count - 1;
	for (int i = 0; i <= final; i++)
		deque_stream << this->deque[i] << " ";
	return deque_stream.str();
}
