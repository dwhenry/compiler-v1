#include "catch.hpp"
#include "../src/scan.h"

TEST_CASE("Scaning a source file", "[scan]" ) {
  Scan * scan = new Scan();

  REQUIRE( scan->value() == 9 );
}
