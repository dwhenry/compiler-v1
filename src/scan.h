#ifndef _SCAN_H_
#define _SCAN_H_

#include "globals.h"
#include "config.h"

#define MAXRESERVED 19

class Scan {
  enum STATES { START, DONE, IS_NUMBER, IS_WORD, IS_COMMENT };

  SourceFile * sourceFile;
  TokenType::TOKENS lookup(std::string tokenString);
  void consumeComment();

public:
  Scan(Config * config);

  TokenDetails * next();
};



#endif
