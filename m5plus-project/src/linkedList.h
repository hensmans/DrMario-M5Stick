#include "rectFunctions.h"

//took some inspiration of here and reimplemented it https://codeforwin.org/2015/09/c-program-to-create-and-traverse-singly-linked-list.html

void insertInList(Rect* rec1, Rect* rec2, Playfield* field){
    Pill* newPill = (Pill*)malloc(sizeof(Pill));
    struct node* head = (struct node*)malloc(sizeof(struct node));
    
    newPill->recL = rec1; // Link data field with data
    newPill->recR = rec2;
    newPill->dir = UP;
    head->pill = newPill;
    head->next = NULL; // Link address field to NULL

    // Terminate if memory not allocated
    if(!(field->linkedListOfPills==NULL)){
        head->next = field->linkedListOfPills;
    }
    field->linkedListOfPills = head;
}
void traverseList(Playfield* field){
    struct node* head = field->linkedListOfPills;

    // Return if list is empty 
    if(head == NULL){
        return;
    }
    
    struct node* temp = head;
    while(temp != NULL){
      //write here what u want to do
        temp = temp->next;                 // Move to next node
    }
}

void freeLinkedList(Playfield* field){
  struct node* head = field->linkedListOfPills;

    // Return if list is empty 
    if(head == NULL){
        return;
    }
    struct node* temp = head;
    while(temp != NULL){
      //write here what u want to do
        head = temp;                 // Move to next node
        temp = head->next;
        free(head->pill); //free pill struct
        free(head); //free head struct
    }
}
