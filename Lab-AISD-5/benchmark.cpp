#include <benchmark/benchmark.h>
#include "sort.hpp"

int bench1() {
    int r = 0;
    int** graph = (int**)malloc(sizeof(int*) * 15);
    int* p = (int*)calloc(15, sizeof(int));

    for (int i = 0; i < 15; ++i)
        graph[i] = (int*)calloc(15, sizeof(int));


    graph[0][2] = 1;
    graph[0][3] = 1;
    graph[1][3] = 1;
    graph[1][4] = 1;
    graph[2][5] = 1;
    graph[3][5] = 1;
    graph[3][6] = 1;
    graph[4][6] = 1;
    graph[4][7] = 1;
    graph[5][8] = 1;
    graph[6][8] = 1;
    graph[6][9] = 1;
    graph[7][9] = 1;
    graph[8][10] = 1;
    graph[9][10] = 1;
    graph[9][11] = 1;
    graph[10][12] = 1;
    graph[11][12] = 1;
    graph[11][13] = 1;
    graph[12][14] = 1;
    graph[13][14] = 1;

    stack st = { NULL, 0 };

    for (int i = 0; i < 15; ++i) {
        if (p[i] == 0) {
            r += dfs(graph, p, &st, i, 15);
            if (r == 1) {
                printf("error");
                break;
            }
        }
    }
    return r;
}

void benchmark1 (benchmark::State& state) {
    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(bench1());
    }
}

BENCHMARK(benchmark1);

int bench2() {
    int r = 0;

    int** graph = (int**)malloc(sizeof(int*) * 4);
    for (int i = 0; i < 4; ++i)
        graph[i] = (int*)calloc(4, sizeof(int));

    int* p = (int*)calloc(4, sizeof(int));

    graph[0][3] = 1;
    graph[3][1] = 1;
    graph[3][2] = 1;
    graph[2][1] = 1;

    stack st = { NULL, 0 };

    for (int i = 0; i < 4; ++i) {
        if (p[i] == 0) {
            r += dfs(graph, p, &st, i, 4);
            if (r == 1) {
                printf("error");
                break;
            }
        }
    }
    return r;
}

void benchmark2(benchmark::State& state) {
    while (state.KeepRunning()) {
        benchmark::DoNotOptimize(bench2());
    }
}

BENCHMARK(benchmark2);