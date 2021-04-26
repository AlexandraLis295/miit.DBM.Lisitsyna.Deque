
#include "Deque.h"
#include <iostream>
using namespace std;
int main()
{
	auto object = new Deque <int>();
	object->insert_back(2);
	object->insert_front(1);
	object->insert_front(0);
	object->insert_back(3);
	object->insert_back(4);
	cout << object->deque_to_string() << endl;
	object->remove_front();
	object->remove_back();
	cout << object->deque_to_string() << endl;
	object->insert_front(0);
	//object->insert_back(5);
	cout << object->deque_to_string() << endl;
	delete object;
}
