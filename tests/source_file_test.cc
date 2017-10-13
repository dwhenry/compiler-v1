#include "catch.hpp"
#include "../src/scan.h"
#include "fakes/fake_config.h"

TEST_CASE("Reading characters from a file", "[scan]" ) {
  std::string filename = "tests/fixtures/test_data.c";
  std::ifstream stream;
  stream.open(filename);

  // std::string tmpStream;
  // std::getline(stream, tmpStream);
  // std::cout << "look at me '" << tmpStream << "' here\n";
  SourceFile *sourceFile = new SourceFile(&(stream));

  SECTION("getting characters") {
    CHECK( sourceFile->nextChar() == '1' );
    CHECK( sourceFile->nextChar() == '2' );
    CHECK( sourceFile->nextChar() == '\0' );
    CHECK( sourceFile->nextChar() == 'a' );
    CHECK( sourceFile->nextChar() == 'b' );
    CHECK( sourceFile->nextChar() == 'c' );
    CHECK( sourceFile->nextChar() == '\0' );
    CHECK( sourceFile->nextChar() == '\0' );
    CHECK( sourceFile->nextChar() == 'i' );
    CHECK( sourceFile->nextChar() == 'd' );
    CHECK( sourceFile->nextChar() == '\0' );
    CHECK( sourceFile->nextChar() == EOF );
  }

  SECTION("previewing characters") {
    CHECK( sourceFile->previewChar() == '1' );
    sourceFile->nextChar();
    CHECK( sourceFile->previewChar() == '2' );
    sourceFile->nextChar();
    CHECK( sourceFile->previewChar() == '\0' );
    sourceFile->nextChar();
    CHECK( sourceFile->previewChar() == '\0' ); // can't preview the next line.
    sourceFile->nextChar();
    CHECK( sourceFile->previewChar() == 'b' );
  }

  SECTION("reverting characters") {
    sourceFile->nextChar();
    CHECK( sourceFile->previewChar() == '2' );
    sourceFile->restoreChar();
    CHECK( sourceFile->previewChar() == '1' );
  }

  SECTION("can't revert past the start of a line") {
    sourceFile->nextChar(); // => 1
    sourceFile->nextChar(); // => 2
    sourceFile->nextChar(); // => \0
    sourceFile->nextChar(); // => a
    CHECK( sourceFile->previewChar() == 'b' );
    sourceFile->restoreChar();
    CHECK( sourceFile->previewChar() == 'a' );
    sourceFile->restoreChar();
    CHECK( sourceFile->previewChar() == 'a' );  }
}

