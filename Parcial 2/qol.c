#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

struct node
{
   int key;
   struct node *next;
};

struct node *InsertElementInAscendentLinkedList(struct node *head, int element)
{
   struct node *newNode, *previous, *actual;
   newNode = (struct node *)malloc(sizeof(struct node));
   newNode->key = element;
   if (head == NULL)
   {
      newNode->next = NULL;
      head = newNode;
   }
   else
   {
      if (element <= head->key)
      {
         newNode->next = head;
         head = newNode;
      }
      else
      {
         previous = head;
         actual = head->next;
         while (actual != NULL)
         {
            if (element > actual->key)
            {
               previous = actual;
               actual = actual->next;
            }
            else
               break;
         }
         newNode->next = actual;
         previous->next = newNode;
      }
   }
   return head;
}
struct node *DeleteElementOfAscendentLinkedList(struct node *head, int element)
{
   struct node *previous, *actual;
   if (head == NULL)
      return NULL;
   else
   {
      if (element == head->key)
      {
         actual = head;
         head = head->next;
         free(actual);
      }
      else
      {
         previous = head;
         actual = head->next;
         while (actual != NULL)
         {
            if (element > actual->key)
            {
               previous = actual;
               actual = actual->next;
            }
            else if (element == actual->key)
            {
               previous->next = actual->next;
               free(actual);
               break;
            }
            else
               break;
         }
      }
   }
   return head;
}

int ListSize(struct node *head)
{
   int count = 0;
   struct node *actual = head;
   while (actual != NULL)
   {
      count++;
      actual = actual->next;
   }
   return count;
}

int mediana(struct node *head)
{
   struct node *temp = head;
   int size = ListSize(head);
   int mid = size / 2;

   if (size % 2 == 0)
   {
      for (int i = 0; i < mid - 1; i++)
      {
         temp = temp->next;
      }
      int left = temp->key;
      int right = temp->next->key;
      return (left + right) / 2;
   }
   else
   {
      for (int i = 0; i < mid; i++)
      {
         temp = temp->next;
      }
      return temp->key;
   }
}

int main()
{
   struct node *head = NULL;
   int operationId, operation, i, v;
   scanf("%d", &operationId);
   for (i = 1; i <= operationId; i++)
   {
      scanf("%d", &operation);
      if (operation == 1)
      {
         scanf("%d", &v);
         head = InsertElementInAscendentLinkedList(head, v);
      }
      else if (operation == 2)
      {
         scanf("%d", &v);
         if (head != NULL)
         {
            head = DeleteElementOfAscendentLinkedList(head, v);
         }
      }
      else if (operation == 3)
      {
         if (head == NULL)
            printf("Empty!\n");
         else
            printf("%d\n", mediana(head));
      }
   }
   return 0;
}