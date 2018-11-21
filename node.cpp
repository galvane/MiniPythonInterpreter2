//
// Created by osboxes on 11/21/18.
//

#include "node.h"

Node::Node(Scope *data){
    this->data = data;
    this->next = NULL;
    this->prev = NULL;
}

// DOUBLY LINKED LIST INSERTION:
void Node::appendToDLL(struct Node ** head, Scope *newData) {
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));

    struct Node* last = *head;

    newNode->data = newData;

    newNode->next = NULL;

    if (*head == NULL)
    {
        newNode->prev = NULL;
        *head = newNode;
        return;
    }

    while (last->next != NULL)
        last = last->next;

    last->next = newNode;

    newNode->prev = last;

    return;
}


