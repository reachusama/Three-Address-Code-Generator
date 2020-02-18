#include "List.h"
void List::insert(string value)
{
	List* node = new List();
	node->type = value;
	node->next = NULL;
	if (last == NULL)
	{
		first = last = node;
	}
	else
	{
		last->next = node;
		last = node;
	}
}
void List::displayList()
{
	List* temp = new List();
	temp = first;
	while (temp != NULL)
	{
		cout << "Type : " << temp->type << endl;
		temp = temp->next;
	}
}