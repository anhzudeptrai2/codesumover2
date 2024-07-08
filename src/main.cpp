#include <iostream>
#include <cstdlib>
#include <time.h>

using namespace std;
// Khai bao va cap bo nho danh sach lien ket don
typedef struct Node
{
    int data
        strut Node *next;
} Node;
// Gan gia tri
Node *createNode(int data)
{
    Node *createNode = (Node *)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}
// Duyet danh sach
void printList(Node *head)
{
    Node *temp = head;
    while (temp != NULL)
    {
        printf("%d -> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}
// Duyet danh sach tim kiem
find(head, val)
tmp = head 
index = 1
while (tmp != NULL && tmp -> data != val )
tmp = tmp -> next 
index ++ 
if (tmp == NULL) return -1
else return index
