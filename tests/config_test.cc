#include "catch.hpp"
#include "../src/config.h"

TEST_CASE("Parsing config variables", "[scan]" ) {
  char * argv[5];
  argv[0] = (char *)"method";

  SECTION("when no file is specified") {
    Config * config = new Config(1, argv);

    REQUIRE_FALSE( config->valid() );
  }

  SECTION("when a valid file is specified") {
    argv[1] = (char *)"app_test";
    Config * config = new Config(2, argv);

    REQUIRE( config->valid() );
  }

  SECTION("when invalid file is specified") {
    argv[1] = (char *)"invalid_file";
    Config * config = new Config(2, argv);

    REQUIRE_FALSE( config->valid() );
  }

  SECTION("when multiple filenames are specified") {
    argv[1] = (char *)"app_test";
    argv[2] = (char *)"second_app_test";
    Config * config = new Config(3, argv);

    REQUIRE_FALSE( config->valid() );
  }

  SECTION("can pass in echoSource flags") {
    argv[1] = (char *)"app_test";
    argv[2] = (char *)"--echoSource\n";
    Config * config = new Config(3, argv);

    REQUIRE( config->valid() );
    REQUIRE( config->EchoSource );
  }

  SECTION("invalid when invalid flag is passed in") {
    argv[1] = (char *)"app_test";
    argv[2] = (char *)"--invalidFlag";
    Config * config = new Config(3, argv);

    REQUIRE_FALSE( config->valid() );
  }
}
