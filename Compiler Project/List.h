#pragma once
#include<iostream>
using namespace std;
class List
{
	string type;
	List* next;
	List* first = NULL;
	List* last = NULL;
public:
	void insert(string);
	void displayList();
};

