//
// Created by samir on 4/27/23.
//

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>
#include "LinkedList.h"

DLLNode *newNode(DLLNode *node, char *data) {
    assert(data != NULL);

    char *p = calloc(strlen(data), sizeof(char));
    assert(p != NULL);

    strcpy(p, data);

    DLLNode *createdNode = (DLLNode *) malloc(sizeof(DLLNode));
    assert(createdNode != NULL);

    createdNode->data = p; // Pointer to the calloc we made earlier.
    createdNode->next = NULL;
    if (node != NULL) { // There was a previous node!
        createdNode->prev = node;
        node->next = createdNode;
    }

    return createdNode;
}

void delNode(DLLNode *node) {
    assert(node != NULL);

    // This node is in the middle of the chain
    if (node->next && node->prev) {
        // Set the previous node's next pointer to *this* node's next pointer
        node->prev->next = node->next;
    } else if (node->next && !node->prev) { // This node is the first node in the list
        node->next->prev = NULL;
    } else if (!node->next && node->prev) { // This node is the *last* node in the list
        node->prev->next = NULL;
    } // Else, this is the only node that exists. We can just delete the node, which deletes the chain.

    // Free the node's data, since it's a malloc'd character string
    free(node->data);
    // Then free this node's malloc.
    free(node);
}

void editNode(DLLNode *node, char *newData) {
    assert(node != NULL);
    assert(newData != NULL);

    char *newP = reallocarray(node->data, strlen(newData), sizeof(char));
    assert(newP != NULL);

    node->data = newP;
}

DLLNode *getHead(DLLNode *node) {
    assert(node != NULL);

    DLLNode *headNode = node->prev;
    if(headNode == NULL) return node;

    while (headNode->prev != NULL) {
        headNode = headNode->prev;
    }
    return headNode;
}

void printList(DLLNode *node) {
    assert(node != NULL);

    DLLNode *nextNode = node->next;
    while(nextNode->next != NULL) {
        printf(" %s ", nextNode->data);
    }
}