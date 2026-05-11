#include <benchmark/benchmark.h>
#include <gtest/gtest.h>
#include "sort.hpp"
#include <fstream>

int main(int argc, char** argv) {

    //tests
    testing::InitGoogleTest(&argc, argv);
    RUN_ALL_TESTS();

    //benchmark
    benchmark::Initialize(&argc, argv);
    std::ofstream out("result.txt");
    benchmark::ConsoleReporter reporter;
    reporter.SetOutputStream(&out);
    benchmark::RunSpecifiedBenchmarks(&reporter);

    //cli
    sort();
    return 0;
}