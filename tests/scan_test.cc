#include "catch.hpp"
#include "fakeit.hpp"
#include "../src/scan.h"

TEST_CASE("Reading tokens from a string", "[scan]" ) {
  char * argv[0];
  fakeit::Mock<Config> mockConfig;
  fakeit::Mock<SourceFile> mockFile;
  fakeit::When(Method(mockFile, nextChar)).Return("a");
  SourceFile * sourceFile = &mockFile.get() ;
  fakeit::When(Method(mockConfig, sourceFile)).Return(sourceFile);

  Scan * scan = new Scan(&mockConfig.get());

  SECTION("that contain a single reserverd word") {
    REQUIRE( scan->next() == Tokens::ID );
  }
}
