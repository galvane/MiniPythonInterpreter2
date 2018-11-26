//
// Created by osboxes on 11/21/18.
//

#include "scope.h"

#ifndef ORDONEZ_HW4_NODE_H
#define ORDONEZ_HW4_NODE_H

/* Node of a doubly linked list */
struct Node {
    Scope *data;
    struct Node* next;
    struct Node* prev;
    Node(Scope *data);
    static void appendToDLL(struct Node ** head, Scope *newData);
};

#endif //ORDONEZ_HW4_NODE_H