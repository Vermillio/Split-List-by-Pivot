//Create a simply-connected linear list (each node has 1 informational field of type Integer), with the ability to add and delete nodes. 
//After completing the editing of the list, request the number N and split the list into two others, 
//without changing the location of the elements in memory, as follows: if the value of the inform. field node> N, include it in 1 list, 
//otherwise include it in 2 list. After the work is finished, all the lists are destroyed.


#include <iostream>
#include <utility>
using namespace std;

typedef struct List
{
	int data;
	List *next;

	List() : next(nullptr) {};
	List(int x) : data(x), next(nullptr) {};
};

void print(List *list)
{
	cout << "{ ";
	while (list)
	{
		cout << list->data;
		if (list->next)
			cout << ", ";
		list = list->next;
	}
	cout << " }" << endl;
}

void push_back(List *&list, int data)
{
	if (!list)
	{
		list = new List(data);
		return;
	}
	List *p = list;
	while (p->next)
		p = p->next;
	List *elem = new List(data);
	p->next = elem;
}

int pop(List *list)
{
	if (!list)
		return 0;
	List *p = list;
	while (p->next->next)
		p = p->next;
	int dat = p->next->data;
	delete p->next;
	p->next = nullptr;
	return dat;
}

bool remove(List *&list, int data)
{
	if (!list)
		return 0;
	List *prev = nullptr;
	List *it = list;
	while (it)
	{
		if (it->data == data)
		{
			if (prev)
				prev->next = it->next;
			else list = it->next;
			delete it;
			return 1;
		}
		prev = it;
		it = it->next;
	}
	return 0;
}

void delete_list(List *list)
{
	while (list)
		delete_list(list->next);
	delete list;
}

pair<List*, List*> splitIntoTwo(List* list, int N)
{
	pair<List*, List*> res;
	res.second = res.first = nullptr;

	if (!list)
		return res;
	while (list)
	{
		if (list->data > N)
			push_back(res.first, list->data);
		else push_back(res.second, list->data);
		list = list->next;
	}
	return res;
}

int main()
{
	List *list = nullptr;
	pair<List*, List*> result;

	int data, choise;
	while (true)
	{
		cout << "1 - push, 2 - remove, 3 - pop (to finish editing press any symbol key):" << endl;
		if (cin >> choise)
			if (choise == 1)
			{
				//bool tmp = false;
				cout << "Enter data :" << endl;
				if (cin >> data)
				{
					push_back(list, data);
					//tmp = true;
				}
				//if (!tmp)
					//continue;
			}
			else if (choise == 2)
			{
				cout << "Enter data :" << endl;
				if (cin >> data)
					remove(list, data);
				//else break;
		
			}
			else if (choise == 3)
				cout << pop(list) << endl;
			else break;
		else break;
		cout << endl;
		print(list);
		cout << endl;
		cin.ignore(cin.rdbuf()->in_avail());
		fflush(stdin);
		cin.clear();
	}
	//print(list);

	int N;
	cout << "Enter N: " << endl;
	cin >> N;
	cin.ignore(cin.rdbuf()->in_avail());
	fflush(stdin);
	cin.clear();
	_flushall();
	cin.tellg();

	cin >> data;
	cin >> N;
	result = splitIntoTwo(list, N);
	cout << "Result: " << endl;
	print(result.first);
	print(result.second);

	delete_list(list);
	delete_list(result.first);
	delete_list(result.second);
	//delete result;
	system("pause");
	return 0;
}