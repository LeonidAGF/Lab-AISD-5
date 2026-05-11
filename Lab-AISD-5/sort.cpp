#include <stdlib.h>
#include <stdio.h>
#include "sort.hpp"

int dfs(int** graph, int* p, stack* st, int v, int size) {
    if (p[v]>0)
        return 0;
    p[v] = 1;
    int res = 0;
    for (int i = 0; i < size; ++i) {
        if (graph[v][i]) {
            if (p[i] == 1)
                return 1;
            res+=dfs(graph, p, st, i, size);
        }
    }
    p[v] = 2;
    add_el_to_stack(st, v);
    return res;
}

void sort() {
    int n, m, z, t,r = 0;
    stack st = { NULL, 0 };
    
    printf("Enter the number of vertices and the number of edges\n");
    scanf_s("%d %d", &n, &m);

    int** graph = (int**)malloc(sizeof(int*) * n);
    int* p = (int*)malloc(sizeof(int) * n);


    if (graph != NULL && p != NULL) {
        for (int i = 0; i < n; ++i) {
            graph[i] = (int*)malloc(sizeof(int) * n);
            p[i] = 0;
            for (int j = 0; j < n; ++j) {
                if(graph[i]!=NULL)
                    graph[i][j] = 0;
            }
        }
    }


    printf("enter the edges of the graph\n");
    for (int i = 0; i < m; ++i) {
        scanf_s("%d %d", &z, &t);
        if (z > 0 && z <= n && t > 0 && t <= n) {
            graph[z - 1][t - 1] = 1;
        }
    }

    for (int i = 0; i < n; ++i) {
        if (p[i] == 0) {
            r+=dfs(graph, p, &st, i, n);
            if (r > 1) {
                printf("error");
                break;
            }
        }
    }

    if (r == 0) {
        printf("res:\n");
        while (st.head != NULL) {
            node* current = del_el_from_stack(&st);
            if (current != NULL) {
                printf("%d ", current->value + 1);
                free(current);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if(graph != NULL && graph[i]!=NULL)
            free(graph[i]);
    }

    if(graph!=NULL)
        free(graph);
    if(p!=NULL)
        free(p);
}