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
   newNode->next = NULL; // Inicializar next en NULL

   if (head == NULL)
   {
      return newNode;
   }

   if (element <= head->key)
   {
      newNode->next = head;
      return newNode;
   }

   previous = head;
   actual = head->next;

   while (actual != NULL && element > actual->key)
   {
      previous = actual;
      actual = actual->next;
   }

   newNode->next = actual;
   previous->next = newNode;
   return head;
}

struct node *DeleteElementOfAscendentLinkedList(struct node *head, int element)
{
   struct node *previous, *actual;

   if (head == NULL)
      return NULL;

   if (head->key == element)
   {
      actual = head;
      head = head->next;
      free(actual);
      return head;
   }

   previous = head;
   actual = head->next;

   while (actual != NULL && actual->key <= element)
   {
      if (actual->key == element)
      {
         previous->next = actual->next;
         free(actual);
         return head;
      }
      previous = actual;
      actual = actual->next;
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

int mediana(struct node *head, int size)
{
   struct node *temp = head;

   if (size == 0)
   {
      printf("Empty!\n");
      return -1;
   }

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
   int operationId, operation, v, listSize = 0;
   scanf("%d", &operationId);

   for (int i = 0; i < operationId; i++)
   {
      scanf("%d", &operation);
      if (operation == 1)
      {
         scanf("%d", &v);
         head = InsertElementInAscendentLinkedList(head, v);
         listSize++;
      }
      else if (operation == 2)
      {
         scanf("%d", &v);
         int prevSize = listSize;
         struct node *prevHead = head;
         head = DeleteElementOfAscendentLinkedList(head, v);
         // Solo decrementar si realmente se eliminó un elemento
         if (head != prevHead || (prevHead != NULL && head == NULL))
         {
            listSize--;
         }
      }
      else if (operation == 3)
      {
         int median = mediana(head, listSize);
         if (median != -1)
         {
            printf("%d\n", median);
         }
      }
   }

   return 0;
}