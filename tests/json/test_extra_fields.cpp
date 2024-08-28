//#define _ALLOW_ITERATOR_DEBUG_LEVEL_MISMATCH 1
//#define _HAS_ITERATOR_DEBUGGING 0

#include <iostream>
#include <rfl.hpp>
#include <rfl/json.hpp>
#include <source_location>
#include <string>
#include <vector>

#include "write_and_read.hpp"

namespace test_extra_fields {

struct Person {
  rfl::Rename<"firstName", std::string> first_name;
  rfl::Rename<"lastName", std::string> last_name = "Simpson";
  rfl::ExtraFields<rfl::Generic> extra_fields;
};

TEST(json, test_extra_fields) {
  auto homer = Person{.first_name = "Homer"};

  homer.extra_fields["age"] = 45;
  homer.extra_fields["email"] = "homer@simpson.com";
  homer.extra_fields["town"] = "Springfield";

	// hacky fix for MSVC2022 in debug build crashing internally in std::vector iterator validation code upon calling the destructor for `homer`.
#if !defined(_ITERATOR_DEBUG_LEVEL) || _ITERATOR_DEBUG_LEVEL != 2 || 1
  write_and_read(
      homer,
      R"({"firstName":"Homer","lastName":"Simpson","age":45,"email":"homer@simpson.com","town":"Springfield"})");
#endif
}
}  // namespace test_extra_fields
