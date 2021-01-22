

#include <iostream>

using namespace std;

const int Max = 1000;		// максимально допустимое число элементов в малом деке

struct node {
	node* prev;  //указатель на предыдущее значение
	node* next;   //указатель на следующее значение
	int* dequeue;

	node(node* Pr, node* Ne) {
		prev = Pr;
		next = Ne;
		dequeue = new int[Max]();
	}

	void print() {
		for (int k = 0; k < Max; k++)
			cout << dequeue[k] << " ";
		cout << endl;
	}
};

struct Dequeue {
	node* first;
	node* last;
	int f;		// индекс первого свободного элемента в первой деке
	int l;		// индекс последнего свободного элемента в последней деке
	int Size;

	Dequeue() {
		node* N = new node(nullptr, nullptr);
		first = N;
		last = N;
		f = Max / 2 - 1;
		l = Max / 2;
		Size = 0;
	}

	// Управление двусвязным списком
	void add_first() {			// добавляет новый узел в начало списка
		node* N = new node(nullptr, first);
		first->prev = N;
		first = N;
		f = Max - 1;
	}

	void add_last() {		// добавляет новый узел в конец списка
		node* N = new node(last, nullptr);
		last->next = N;
		last = N;
		l = 0;
	}

	void delete_first() {		// удаляет первый узел списка
		node* N = first->next;
		delete first;
		first = N;
		first->prev = nullptr;
		f = 0;
	}

	void delete_last() {		// удаляет последний узел списка
		node* N = last->prev;
		delete last;
		last = N;
		last->next = nullptr;
		l = Max - 1;
	}

	// Управление деком
	void push_front(int n) {
		(first->dequeue)[f] = n;
		f--;
		Size++;
		if (f == -1)		// если первый дек переполнен
			add_first();	// добавляем в начало списка новый дек
	}

	void push_back(int n) {
		(last->dequeue)[l] = n;
		l++;
		Size++;
		if (l == Max)		// если последний дек переполнен
			add_last();		// добавляем в конец списка новый дек
	}

	int pop_front() { // вынимает первый узел списка
		Size--;
		if (f == Max - 1)
			delete_first();
		else
			f++;
		return (first->dequeue)[f];
	}

	int pop_back() {  // вынимает последний узел списка
		Size--;
		if (l == 0)
			delete_last();
		else
			l--;
		return (last->dequeue)[l];
	}

	int front() {        //печать первого элемента
		if (f == Max - 1)
			return ((first->next)->dequeue)[0];
		else
			return (first->dequeue)[f + 1];
	}

	int back() {     //печать последнего элемента
		if (l == 0)
			return ((last->prev)->dequeue)[Max - 1];
		else
			return (last->dequeue)[l - 1];
	}

	int size() {
		return Size;
	}

	bool empty() { return (Size == 0); }

	void clear() {
		node* N = first;
		while (N) {
			node* M = N->next;
			delete N->prev;
			delete N;
			N = M;
		}

		N = new node(nullptr, nullptr);

		first = N;
		last = N;
		Size = 0;
		f = Max / 2 - 1;
		l = Max / 2;
	}

	void print() {
		node* N = first;
		while (N) {
			N->print();
			N = N->next;
		}
	}
};


int main() {
	Dequeue D;
	string comand;
	int x, value;

	do
	{
		cout << "  enter '1' to push value on front \n";
		cout << "  enter '2' to push value on back \n";
		cout << "  enter '3' to pop value on front \n";
		cout << "  enter '4' to pop value on back \n";
		cout << "  enter '5' to view the value in front of the list \n";
		cout << "  enter '6' to view the value in back of the list\n";
		cout << "  enter '7' to view size of the list \n";
		cout << "  enter '8' to clear the list\n";
		cout << "  enter '9' to print the list\n";
		cout << "  enter '10' to exit\n";

		cout << endl;
		cin >> value;

		switch (value)
		{
		case 1:
			cout << "enter the value:  ";
			cin >> x;
			D.push_front(x);
			cout << "ok\n";
			break;

		case 2:
			cout << "enter the value:  ";
			cin >> x;
			D.push_back(x);
			cout << "ok\n";
			break;
		case 3:
			if (D.empty())
				cout << "error\n";
			else
				cout << D.pop_front() << "\n";
			break;

		case 4:
			if (D.empty())
				cout << "error\n";
			else
				cout << D.pop_back() << "\n";
			break;

		case 5:
			if (D.empty())
				cout << "error\n";
			else
				cout << D.front() << "\n";
			break;

		case 6:
			if (D.empty())
				cout << "error\n";
			else
				cout << D.back() << "\n";
			break;

		case 7:
			cout << "size:  ";
			cout << D.size() << "\n";
			break;

		case 8:
			D.clear();
			cout << "ok\n";
			break;

		case 9:
			D.print();
			cout << "ok\n";
			break;

		default:cout << value << "is not a valid menu item.\n";
			break;
		}

	} while (value != 10);
}
