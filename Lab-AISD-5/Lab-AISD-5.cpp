#include <stdlib.h>
#include <stdio.h>

typedef struct node {
    node* next;
    int value;
} node;

typedef struct stack {
    node* head;
    int size;
} stack;

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

void dfs(int** graph, int* p, stack* st, int v, int size) {
    if (p[v] > 0)
        return;
    p[v] = 1;
    for (int i = 0; i < size; ++i) {
        if (graph[v][i]) {
            dfs(graph, p, st, i, size);
        }
    }
    p[v] = 2;
    add_el_to_stack(st, v);
}

int main() {
    int n, m, z, t;
    stack st = { NULL, 0 };
    int** graph = (int**)malloc(sizeof(int*) * n);
    int* p = (int*)malloc(sizeof(int) * n);

    scanf_s("%d %d", &n, &m);

    for (int i = 0; i < n; ++i) {
        graph[i] = (int*)malloc(sizeof(int) * n);
        p[i] = 0;
        for (int j = 0; j < n; ++j) {
            graph[i][j] = 0;
        }
    }

    printf("...:\n");
    for (int i = 0; i < m; ++i) {
        scanf_s("%d %d", &z, &t);
        if (z > 0 && z <= n && t > 0 && t <= n) {
            graph[z - 1][t - 1] = 1;
        }
    }

    for (int i = 0; i < n; ++i) {
        if (p[i] == 0) {
            dfs(graph, p, &st, i, n);
        }
    }

    printf("res:\n");
    while (st.head != NULL) {
        node* current = del_el_from_stack(&st);
        if (current != NULL) {
            printf("%d ", current->value + 1);
            free(current);
        }
    }

    for (int i = 0; i < n; ++i) {
        free(graph[i]);
    }

    free(graph);
    free(p);

    return 0;
}