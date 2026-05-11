#pragma once
typedef struct node {
    node* next;
    int value;
} node;

typedef struct stack {
    node* head;
    int size;
} stack;

void add_el_to_stack(stack* st, int value);

node* del_el_from_stack(stack* st);