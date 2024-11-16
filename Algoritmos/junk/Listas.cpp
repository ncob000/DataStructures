#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node
{
	int key; 
	struct node *next; 
};


struct node *MakeList(int n)
{
	struct node *head = NULL, *newNode; 
	while (n >= 1)
	{
		newNode = (struct node *)malloc(sizeof(struct node));
		newNode->key = n; 
		newNode->next = head; 
		head = newNode; 
		n--; 	
	}
	return head; 
}

void PrintList(struct node *head)
{
	struct node *actualNode = head; 
	while (actualNode != NULL)
	{
		printf("%d -> ", actualNode->key);
		actualNode = actualNode->next;
	}
	printf("NULL\n");
}

struct node *DeleteList(struct node *head)
{
	struct node *actualNode = head; 
	while(actualNode != NULL)
	{
		actualNode = actualNode->next; 
		free(head);
		head = actualNode; 
	}
	/*head = NULL */
	return head; 
}


int main()
{
	struct node *head; 
	int n; 
	scanf("%d", &n);
	head = MakeList(n);
	PrintList(head);
	head = DeleteList(head);
	PrintList(head);
	return 0; 
}


