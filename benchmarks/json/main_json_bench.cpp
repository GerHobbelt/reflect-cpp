#include <benchmark/benchmark.h>


#if defined(BUILD_MONOLITHIC)
#define main reflectcpp_benchmark_json_main
#endif
extern "C" int main(int argc, const char** argv);

BENCHMARK_MAIN();
