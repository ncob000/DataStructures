#include <stdlib.h>
#include <stdio.h>

struct node
{
    int key;
    struct node *next;
};

struct node *insertInCircularLinkedList(struct node *tail, int element)
{
    struct node *newNode = (struct node *)malloc(sizeof(struct node));
    newNode->key = element;

    if (tail == NULL)
    { 
        newNode->next = newNode;
        tail = newNode;
    }
    else
    { // Lista con elementos
        newNode->next = tail->next;
        tail->next = newNode;
        tail = newNode;
    }
    return tail;
}

struct node *deleteFirstNodeInCircularLinkedList(struct node *tail)
{
    if (tail == NULL)
        return NULL;

    struct node *firstNode = tail->next;

    if (tail == tail->next)
    { // Un solo nodo
        free(tail);
        return NULL;
    }
    else
    {
        tail->next = firstNode->next; // Saltar el primer nodo
        free(firstNode);              // Liberar el nodo
        return tail;
    }
}

static int m = 1;
int eenymeeny(int n)
{
    struct node *tail = NULL;

    for (int i = 1; i <= n; i++)
        tail = insertInCircularLinkedList(tail, i);

    while (tail->next != tail)
    {
        tail = deleteFirstNodeInCircularLinkedList(tail);
        for (int i = 0; i < m; i++)
            tail = tail->next;
    }

    if (tail->key == 2)
        return m + 1;
    else
    {
        m++;
        return eenymeeny(n);
    }
}

int main()
{
    int n;

    while (scanf("%d", &n))
    {
        if (n == 0)
            return 0;
        else
        {
            m = 1; /* reiniciar m cada nuevo caso*/
            printf("%d\n", eenymeeny(n));
        }
    return 0;
}
