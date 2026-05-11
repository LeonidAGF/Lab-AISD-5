#include <stdlib.h>
#include <stdio.h>
#include "sort.hpp"

int dfs(int** graph, int* p, stack* st, int v, int size) {
    if (p[v] > 0)
        return p[v] == 1;
    p[v] = 1;
    for (int i = 0; i < size; ++i) {
        if (graph[v][i]) {
            if (dfs(graph, p, st, i, size))
                return 1;
        }
    }
    p[v] = 2;
    add_el_to_stack(st, v);
    return 0;
}

char* getline(FILE* stream) {
    if (stream != NULL) {
        int len = 0;
        int size = 100;
        int c;
        char* buffer = (char*)malloc(size * sizeof(char));

        if (buffer == NULL)
            return NULL;

        c = fgetc(stream);
        while (c != EOF && c != '\n') {
            buffer[len++] = c;
            if (len >= size) {
                size *= 2;
                char* temp = (char*)realloc(buffer, size);
                if (temp == NULL) {
                    free(buffer);
                    return NULL;
                }
                buffer = temp;
            }
            c = fgetc(stream);
        }
        if (len == 0) {
            free(buffer);
            return NULL;
        }
        buffer[len] = '\0';
        return buffer;
    }
    return NULL;
}

void sort() {
    int n, m, z, t,r = 0;
    stack st = { NULL, 0 };
    int** graph = NULL;
    int* p = NULL;

    int input_com, output_com;
    double input_value;

    FILE* stream = stdout;


    printf("choose mode: from file - 1, from console - 2\n");
    scanf_s("%d", &input_com);
    printf("choose mode to write answers: to console - 1, to file - 2\n");
    scanf_s("%d", &output_com);

    if (output_com == 2)
        if (fopen_s(&stream, "res.txt", "w") != 0)
            return;

    if (input_com == 1) {
        int buff_size;
        printf("length of file name:\n");
        scanf_s("%d ", &buff_size);
        char* name = (char*)malloc(sizeof(char) * buff_size);
        printf("file name:\n");
        fgets(name, buff_size, stdin);


        FILE* file = NULL;
        fopen_s(&file, name, "r");
        if (file != NULL) {
            int line_count = 0,mn = 1,num = 0,pos = 0,r1,r2;
            char* line;
            while ((line = getline(file)) != NULL) {
                while (line[pos] != ' ' && line[pos] != '\0') {
                    num = num * 10 + (line[pos++] - '0');
                    mn *= 10;
                }
                pos++;
                mn = 1;
                r1 = num;
                num = 0;
                while (line[pos] != ' ' && line[pos] != '\0') {
                    num = num * 10 + (line[pos++] - '0');
                    mn *= 10;
                }
                r2 = num;
                num = 0;
                if (line_count++==0) {
                    n = r1;
                    m = r2;
                    graph = (int**)malloc(sizeof(int*) * n);
                    p = (int*)calloc(n, sizeof(int));
                    if (graph != NULL && p != NULL)
                        for (int i = 0; i < n; ++i)
                            graph[i] = (int*)calloc(n, sizeof(int));
                }
                else {
                    if (r1 > 0 && r1 <= n && r2 > 0 && r2 <= n)
                        graph[r1 - 1][r2 - 1] = 1;
                    else
                        return;
                }
                free(line);
                pos = 0;
            }

        }
        fclose(file);
    }
    else {
        fprintf(stream, "Enter the number of vertices and the number of edges\n");
        scanf_s("%d %d", &n, &m);

        graph = (int**)malloc(sizeof(int*) * n);
        p = (int*)calloc(n,sizeof(int));


        if (graph != NULL && p != NULL)
            for (int i = 0; i < n; ++i)
                graph[i] = (int*)calloc(n,sizeof(int));


        fprintf(stream, "enter the edges of the graph\n");
        for (int i = 0; i < m; ++i) {
            scanf_s("%d %d", &z, &t);
            if (z > 0 && z <= n && t > 0 && t <= n)
                graph[z - 1][t - 1] = 1;
            else
                return;
        }
    }

    for (int i = 0; i < n; ++i) {
        if (p[i] == 0) {
            r += dfs(graph, p, &st, i, n);
            if (r > 1) {
                fprintf(stream, "error");
                printf("error");
                break;
            }
        }
    }

    if (r == 0) {
        fprintf(stream, "res:\n");
        while (st.head != NULL) {
            node* current = del_el_from_stack(&st);
            if (current != NULL) {
                fprintf(stream, "%d ", current->value + 1);
                free(current);
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        if (graph != NULL && graph[i] != NULL)
            free(graph[i]);
    }

    if (graph != NULL)
        free(graph);
    if (p != NULL)
        free(p);

    if (output_com == 2)
        fclose(stream);
}