#include "stack.h"
#include <stdlib.h>

void add_el_to_stack(stack* st, int value) {
    node* el = (node*)malloc(sizeof(node));
    if (el != NULL) {
        el->value = value;
        el->next = st->head;
        st->head = el;
        st->size++;
    }
}

node* del_el_from_stack(stack* st) {
    node* el = st->head;
    if (st->head != NULL) {
        st->head = st->head->next;
        st->size--;
    }
    return el;
}