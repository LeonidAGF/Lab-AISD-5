#include <gtest/gtest.h>
#include "sort.hpp"
#include <vector>

using namespace std;

TEST(test_one, test_one)
{
    //тест для stack
    stack st = { NULL, 0 };
    add_el_to_stack(&st, 1);
    add_el_to_stack(&st, 2);
    add_el_to_stack(&st, 3);
    add_el_to_stack(&st, 4);
    add_el_to_stack(&st, 5);

    ASSERT_TRUE(del_el_from_stack(&st)->value == 5);
    ASSERT_TRUE(del_el_from_stack(&st)->value == 4);
    ASSERT_TRUE(st.size == 3);
    ASSERT_TRUE(del_el_from_stack(&st)->value == 3);
    ASSERT_TRUE(del_el_from_stack(&st)->value == 2);
    ASSERT_TRUE(del_el_from_stack(&st)->value == 1);
    ASSERT_TRUE(st.size == 0);
    ASSERT_TRUE(del_el_from_stack(&st) == NULL);
}

TEST(test_two, test_two)
{
    //тест для топологийческой сортиовки
    int r = 0;

    int** graph = (int**)malloc(sizeof(int*) * 4);
    for (int i = 0; i < 4; ++i)
        graph[i] = (int*)calloc(4, sizeof(int));

    int* p = (int*)calloc(4,sizeof(int));

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

    node* n1;
    node* n2;
    node* n3;
    node* n4;

    n1 = del_el_from_stack(&st);
    n2 = del_el_from_stack(&st);
    n3 = del_el_from_stack(&st);
    n4 = del_el_from_stack(&st);

    ASSERT_TRUE(n1->value == 0);
    ASSERT_TRUE(n2->value == 3);
    ASSERT_TRUE(n3->value == 2);
    ASSERT_TRUE(n4->value == 1);
}

TEST(test_three, test_three)
{
    //тест для топологийческой сортиовки с циклом
    int r = 0;

    int** graph = (int**)malloc(sizeof(int*) * 4);
    for (int i = 0; i < 4; ++i)
        graph[i] = (int*)calloc(4, sizeof(int));

    int* p = (int*)calloc(4, sizeof(int));

    graph[0][3] = 1;
    graph[3][1] = 1;
    graph[3][2] = 1;
    graph[2][1] = 1;
    graph[1][0] = 1;

    stack st = { NULL, 0 };

    for (int i = 0; i < 4; ++i) {
        if (p[i] == 0) {
            r += dfs(graph, p, &st, i, 4);
            if (r > 1) {
                printf("error");
                r = 1;
                break;
            }
        }
    }


    ASSERT_TRUE(r == 1);
}


TEST(test_four, test_four)
{
    // большой тест для топологической сортировки
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

    node* arr[15];

    for (int i = 0; i < 15; ++i)
        arr[i] = del_el_from_stack(&st);

    ASSERT_TRUE(arr[0]->value == 1);
    ASSERT_TRUE(arr[1]->value == 4);
    ASSERT_TRUE(arr[2]->value == 7);
    ASSERT_TRUE(arr[3]->value == 0);
    ASSERT_TRUE(arr[4]->value == 3);
    ASSERT_TRUE(arr[5]->value == 6);
    ASSERT_TRUE(arr[6]->value == 9);
    ASSERT_TRUE(arr[7]->value == 11);
    ASSERT_TRUE(arr[8]->value == 13);
    ASSERT_TRUE(arr[9]->value == 2);
    ASSERT_TRUE(arr[10]->value == 5);
    ASSERT_TRUE(arr[11]->value == 8);
    ASSERT_TRUE(arr[12]->value == 10);
    ASSERT_TRUE(arr[13]->value == 12);
    ASSERT_TRUE(arr[14]->value == 14);
}

TEST(test_five, test_five)
{
    // тест с несколькими компанентами связности
    int r = 0;
    int** graph = (int**)malloc(sizeof(int*) * 12);
    int* p = (int*)calloc(12, sizeof(int));

    for (int i = 0; i < 12; ++i)
        graph[i] = (int*)calloc(12, sizeof(int));

    graph[0][1] = 1;
    graph[1][2] = 1;

    graph[3][4] = 1;
    graph[4][5] = 1;

    graph[6][7] = 1;
    graph[7][8] = 1;
    graph[8][9] = 1;

    graph[10][11] = 1;

    stack st = { NULL, 0 };

    for (int i = 0; i < 12; ++i)
        if (p[i] == 0)
            r += dfs(graph, p, &st, i, 12);

    ASSERT_TRUE(r == 0);
}