#include "catch.hpp"
#include "../src/scan.h"
#include "fakes/fake_config.h"

TEST_CASE("Reading tokens from a string", "[scan]" ) {
  char * argv[0];
  char *  fakeFileData[3];
  fakeFileData[1] = (char *)"empty";
  fakeFileData[2] = (char *)"empty";

  FakeConfig * config = new FakeConfig();
  Scan * scan = new Scan(config);
  TokenDetails * tokenDetails;

  SECTION("that contain a single reserverd word") {
    fakeFileData[0] = (char *)"if";

    std::cout << "test 1:\n";
    std::cout << "line 1:" <<  fakeFileData[0] << "\n";
    std::cout << "line 2:" <<  fakeFileData[1] << "\n";
    std::cout << "line 3:" <<  fakeFileData[2] << "\n";

    config->setData( fakeFileData, 1);
    tokenDetails = scan->next();
    REQUIRE( tokenDetails->token == TokenType::IF );
    REQUIRE( tokenDetails->str == "if" );
  }

  SECTION("that contain a single number") {
    fakeFileData[0] = (char *)"1234";
    config->setData( fakeFileData, 1);

    tokenDetails = scan->next();
    REQUIRE( tokenDetails->token == TokenType::NUM );
    REQUIRE( tokenDetails->str == "1234" );
  }

  SECTION("that contain an identifier") {
    fakeFileData[0] = (char *)"hi";
    config->setData( fakeFileData, 1);

    tokenDetails = scan->next();
    REQUIRE( tokenDetails->token == TokenType::ID );
    REQUIRE( tokenDetails->str == "hi" );
  }

  SECTION("it can detect the end of the file") {
    fakeFileData[0] = (char *)"hi";
    config->setData( fakeFileData, 1);

    scan->next();
    tokenDetails = scan->next();
    REQUIRE( tokenDetails->token == TokenType::ENDFILE );
  }

  SECTION("that contain a value assignment") {
    fakeFileData[0] = (char *)"hi = 12";
    config->setData( fakeFileData, 1);

    tokenDetails = scan->next();
    CHECK( tokenDetails->token == TokenType::ID );
    CHECK( tokenDetails->str == "hi" );
    CHECK( tokenDetails->startPosition == 0 );

    tokenDetails = scan->next();
    CHECK( tokenDetails->token == TokenType::ASSIGN );
    CHECK( tokenDetails->str == "=" );
    CHECK( tokenDetails->startPosition == 3 );

    tokenDetails = scan->next();
    CHECK( tokenDetails->token == TokenType::NUM );
    CHECK( tokenDetails->str == "12" );
    CHECK( tokenDetails->startPosition == 5 );
  }

  SECTION("will ignore comments after a token") {
    fakeFileData[0] = (char *)"hi /* comment */";
    config->setData( fakeFileData, 1);

    scan->next();
    tokenDetails = scan->next();
    REQUIRE( tokenDetails->token == TokenType::ENDFILE );
  }

  SECTION("will not eb tricked by stupid comments") {
    fakeFileData[0] = (char *)"/*/ hi */";
    config->setData( fakeFileData, 1);

    tokenDetails = scan->next();
    REQUIRE( tokenDetails->token == TokenType::ENDFILE );
  }

  SECTION("will ignore comments before a token") {
    fakeFileData[0] = (char *)"/* comment */ hi";
    config->setData( fakeFileData, 1);

    tokenDetails = scan->next();
    REQUIRE( tokenDetails->token == TokenType::ID );
    REQUIRE( tokenDetails->str == "hi" );
  }

  SECTION("will ignore multiline comments") {
    fakeFileData[0] = (char *)"/* comment start";
    fakeFileData[1] = (char *)"12345";
    fakeFileData[2] = (char *)"comment end */ 54321";
    config->setData( fakeFileData, 3);

    tokenDetails = scan->next();
    CHECK( tokenDetails->token == TokenType::NUM );
    CHECK( tokenDetails->str == "54321" );
  }
}
