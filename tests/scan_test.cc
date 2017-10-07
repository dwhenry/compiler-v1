#include "catch.hpp"
#include "../src/scan.h"

TEST_CASE("Reading tokens from a string", "[scan]" ) {
  Scan * scan = new Scan();

  SECTION("that contain a single reserverd word") {
    REQUIRE( scan->next() == Tokens::ID );
  }
}
