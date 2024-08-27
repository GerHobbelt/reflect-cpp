//
// main() for monolithic build of the gumbo_parser tests
//

#include "gtest/gtest.h"

#include "gtest/gtest-spi.h"
//#include "src/gtest-internal-inl.h"

#include <iostream>
#include <sstream>

using namespace std;

using ::testing::InitGoogleTest;
using ::testing::TestEventListeners;
using ::testing::TestWithParam;
using ::testing::UnitTest;
using ::testing::Test;
using ::testing::Values;



class ExpectNFailuresListener : public testing::EmptyTestEventListener {
public:
	ExpectNFailuresListener(int n) :
		expected_failure_count(n), expected_failure_remain(0)
	{}

	testing::TestPartResult OnTestPartResult(const testing::TestPartResult& result) override {
		testing::TestPartResult r = result;

		if (r.type() != testing::TestPartResult::kSuccess && expected_failure_remain > 0)
		{
			expected_failure_remain--;
			r.change_type(testing::TestPartResult::kSuccess);
		}
		return r;
	}

	void OnTestIterationStart(const testing::UnitTest& unit_test, int iteration) override {
		expected_failure_remain = expected_failure_count;
	}

	void OnTestIterationEnd(const testing::UnitTest& unit_test, int iteration) override {
		if (expected_failure_remain != 0 && expected_failure_count != 0)
		{
			ostringstream os;
			os << "Expected " << expected_failure_count << " failures, but observed " << (expected_failure_count - expected_failure_remain) << " failures instead.";

			// ZERO the expected count: this way all errors show up in the next test round (if any)
			expected_failure_count = 0;

			throw std::runtime_error(os.str());
		}
	}

private:
	int expected_failure_count;
	int expected_failure_remain;
};

int main(int argc, const char** argv)
{
	int rv = 0;
#if 0
	bool also_run_disabled_tests_ = false;
  bool break_on_failure_ = false;
  bool catch_exceptions_ = false;
  std::string color_;
  std::string death_test_style_;
  bool death_test_use_fork_ = false;
  bool fail_fast_ = false;
  std::string filter_;
  std::string internal_run_death_test_;
  bool list_tests_ = false;
  std::string output_;
  bool brief_ = false;
  bool print_time_ = false;
  bool print_utf8_ = false;
  int32_t random_seed_ = 42;
  int32_t repeat_ = 1;
  bool recreate_environments_when_repeating_ = false;
  bool shuffle_ = false;
  int32_t stack_trace_depth_ = 5;
  std::string stream_result_to_;
  bool throw_on_failure_ = false;
#endif

	InitGoogleTest(&argc, argv);
#if 0
	GTEST_FLAG_SET(death_test_style, "threadsafe");
	// class GTestFlagSaver -->
  GTEST_FLAG_SET(also_run_disabled_tests, also_run_disabled_tests_);
  GTEST_FLAG_SET(break_on_failure, break_on_failure_);
  GTEST_FLAG_SET(catch_exceptions, catch_exceptions_);
  GTEST_FLAG_SET(color, color_);
  GTEST_FLAG_SET(death_test_style, death_test_style_);
  //GTEST_FLAG_SET(death_test_use_fork, death_test_use_fork_);
  GTEST_FLAG_SET(filter, filter_);
  GTEST_FLAG_SET(fail_fast, fail_fast_);
  GTEST_FLAG_SET(internal_run_death_test, internal_run_death_test_);
  GTEST_FLAG_SET(list_tests, list_tests_);
  GTEST_FLAG_SET(output, output_);
  GTEST_FLAG_SET(brief, brief_);
  GTEST_FLAG_SET(print_time, print_time_);
  GTEST_FLAG_SET(print_utf8, print_utf8_);
  GTEST_FLAG_SET(random_seed, random_seed_);
  GTEST_FLAG_SET(repeat, repeat_);
  GTEST_FLAG_SET(recreate_environments_when_repeating, recreate_environments_when_repeating_);
  GTEST_FLAG_SET(shuffle, shuffle_);
  GTEST_FLAG_SET(stack_trace_depth, stack_trace_depth_);
  GTEST_FLAG_SET(stream_result_to, stream_result_to_);
  GTEST_FLAG_SET(throw_on_failure, throw_on_failure_);
#endif

	TestEventListeners& listeners = UnitTest::GetInstance()->listeners();
	listeners.Append(new ExpectNFailuresListener(0));

	rv = RUN_ALL_TESTS();

	return rv;
}
