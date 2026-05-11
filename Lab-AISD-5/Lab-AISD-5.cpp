#include <benchmark/benchmark.h>
#include <gtest/gtest.h>
#include "sort.hpp"

int main(int argc, char** argv) {

    //tests
    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();

    //benchmark
    benchmark::Initialize(&argc, argv);
    benchmark::RunSpecifiedBenchmarks();

    //cli
    sort();
    return 0;
}