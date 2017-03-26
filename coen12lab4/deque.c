#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "deque.h"

struct node
{
    int data;
    struct node *next;
    struct node *prev;
};

struct deque
{
    int count;
    struct node *head;
};

DEQUE *createDeque(void)
{

    DEQUE *dp;
    dp = malloc(sizeof(struct deque));
    assert(dp!=NULL);
    dp->count=0;
    dp->head=malloc(sizeof(struct node));
    assert(dp->head !=NULL);
    dp->head->next=dp->head;
    dp->head->prev=dp->head;
    
    return dp;
}

void destroyDeque(DEQUE *dp)
{
    struct node *dummy, *next;
    
    assert(dp!=NULL);
    dummy= dp->head;
    
    do{
        next = dummy->next;
        free(dummy);
        dummy=next;
    }while (dummy != dp->head);
    
    free(dp);
}

int numItems(DEQUE *dp)
{
    assert(dp!=NULL);
    return dp->count;
}

void addFirst(DEQUE *dp, int x)
{

    assert(dp!=NULL);
    struct node *temp;
    struct node *dummy;
    dummy=dp->head;
    temp = malloc(sizeof(struct node));
    temp->data=x;
    temp->prev=dummy;
    temp->next=dummy->next;
    dummy->next->prev=temp;
    dummy->next=temp;
    dp->count++;
 
}

void addLast(DEQUE *dp, int x)
{

    assert(dp!=NULL);
    struct node *temp;
    struct node *dummy;
    dummy=dp->head;
    temp = malloc(sizeof(struct node));
    temp->data=x;
    temp->next=dummy;
    temp->prev=dummy->prev;
    dummy->prev->next=temp;
    dummy->prev=temp;
    dp->count++;

}

int removeFirst(DEQUE *dp)
{
    int x;
    assert(dp!=NULL);
    struct node *temp;
    struct node *dummy;
    dummy=dp->head;
    temp=dummy->next;
    dummy->next=dummy->next->next;
    dummy->next->next->prev=dummy;
    dp->count--;
    x=temp->data;
    free(temp);
    
    return x;
    
}

int removeLast(DEQUE *dp)
{
    int x;

    assert(dp!=NULL);
    struct node *temp;
    struct node *dummy;
    dummy=dp->head;
    temp=dummy->prev;
    dummy->prev->prev->next=dummy;
    dummy->prev=dummy->prev->prev;
    dp->count--;
    x =temp->data;
    free(temp);
    
    return x;
}

int getFirst(DEQUE *dp)
{

    assert(dp!=NULL);
    struct node *dummy;
    dummy=dp->head;
    
    return dummy->next->data;
}

int getLast(DEQUE *dp)
{

    assert(dp!=NULL);
    struct node *dummy;
    dummy=dp->head;
    return dummy->prev->data;
}








