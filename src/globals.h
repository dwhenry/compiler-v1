#ifndef _GLOBALS_H_
#define _GLOBALS_H_

#include <string>

namespace TokenType {
  enum TOKENS {
    /* book-keeping tokens */
    ENDFILE, //ERROR,
    /* reserved words */
    IF, ELSE, INT, RETURN, VOID, WHILE,
    /* multicharacter tokens */
    ID,NUM,
    /* special symbols */
    PLUS,MINUS,TIMES,DIVIDE,LT,LTEQ,GT,GTEQ,EQ,NOTEQ,ASSIGN,SEMI,COMMA,
    /* brackets */
    L_BR,R_BR,L_SQUARE_BR,R_SQUARE_BR,L_SQUIGGLE_BR,R_SQUIGGLE_BR
  };
}

typedef struct tokenDetails {
  TokenType::TOKENS token;
  std::string str;
  int lineNumber;
  int startPosition;
} TokenDetails;


#define MAX_TOKEN_LENGTH 40

#endif
