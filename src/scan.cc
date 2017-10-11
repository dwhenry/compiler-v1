#include "globals.h"
#include "scan.h"

TokenDetails * Scan::next() {
  int state = START;
  char tokenString[MAX_TOKEN_LENGTH];
  int c;
  int tokenPosition = 0;
  bool save;
  TokenType::TOKENS currentToken;
  int startLine = this->sourceFile->lineNumber;
  int startPosition = this->sourceFile->position;

  while (state != DONE) {
    save = true;
    c = this->sourceFile->nextChar();
    switch (state) {
    case START:
      if(isdigit(c)) {
        state = IS_NUMBER;
      } else if (isalpha(c)) {
        state = IS_WORD;
      } else if ((c == ' ') || (c == '\t') || (c == '\n')) {
        startPosition = this->sourceFile->position;
        save = false;
      } else {
        switch(c) {
        case -1:
          state = DONE;
          currentToken = TokenType::ENDFILE;
          save = false;
          break;
        case '/':
          if(this->sourceFile->previewChar() == '*') {
            this->sourceFile->nextChar(); // consume the previewed character
            save = false;
            state = IS_COMMENT;
            std::cout << "Comment: ";
          } else {
            state = DONE;
            currentToken = TokenType::DIVIDE;
          }
          break;
        case '=':
          state = DONE;

          currentToken = TokenType::ASSIGN;
          break;
        }
        // other characters
        // PLUS,MINUS,TIMES,DIVIDE,LT,LTEQ,GT,GTEQ,EQ,NOTEQ,ASSIGN,SEMI,COMMA,
      }
      break;
    case IS_NUMBER:
      if(!isdigit(c)) {
        state = DONE;
        save = false;
        // this->sourceFile->restoreChar();
        currentToken = TokenType::NUM;
      }
      break;
    case IS_WORD:
      if(!isalpha(c)) {
        state = DONE;
        save = false;
        //this->sourceFile->restoreChar();
        tokenString[tokenPosition] = '\0';
        currentToken = lookup((std::string)tokenString);
      }
      break;
    case IS_COMMENT:
      save = false;
      std::cout << (char)c;
      if(c == '*' && this->sourceFile->previewChar() == '/') {
        std::cout << "\n";
        this->sourceFile->nextChar(); // consume the previewed character
        state = START;
      };
    }
    if(save) {
      tokenString[tokenPosition++] = c;
    }
  }
  tokenString[tokenPosition] = '\0';

  TokenDetails * token = new TokenDetails();
  token->token = currentToken;
  token->str = tokenString;
  token->lineNumber = startLine;
  token->startPosition = startPosition;
  return token;
};

TokenType::TOKENS Scan::lookup(std::string tokenString) {
  if(tokenString == "if") {
    return TokenType::IF;
//    IF,ELSE,INT,RETURN,VOID,WHILE,
  } else {
    return TokenType::ID;
  }
}




Scan::Scan(Config * config) {
  this->sourceFile = config->sourceFile();
};
