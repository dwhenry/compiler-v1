#ifndef _SCAN_H_
#define _SCAN_H_

#include "globals.h"
#include "config.h"

#define TOKENS_MAPS 19
#define RESERVED_MAPS 6

typedef int (*checkFunction)(int);

class Scan {
  enum STATES { START, DONE, IS_NUMBER, IS_WORD, IS_COMMENT };

  SourceFile * sourceFile;
  TokenType::TOKENS lookup(std::string tokenString);
  void consumeComment();
  bool consumeIgnorables();
  void consumeWhile(char tokenString[], checkFunction func);

public:
  Scan(Config * config);
  TokenDetails * next();
};



#endif
