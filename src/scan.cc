#include "globals.h"
#include "scan.h"

static struct
  {
    int current;
    int preview;
    TokenType::TOKENS token;
  } tokenMap[MAXRESERVED]
  = {
    {'+', '\0', TokenType::PLUS},
    {'-', '\0', TokenType::MINUS},
    {'*', '\0', TokenType::TIMES},
    {'/', '\0', TokenType::DIVIDE},
    {'<', '=', TokenType::LTEQ},
    {'<', '\0', TokenType::LT},
    {'>', '=',TokenType::GTEQ},
    {'>', '\0', TokenType::GT},
    {'=', '=', TokenType::EQ},
    {'=', '\0', TokenType::ASSIGN},
    {'!', '=', TokenType::NOTEQ},
    {';', '\0', TokenType::SEMI},
    {',', '\0', TokenType::COMMA},

    {'(', '\0', TokenType::L_BR},
    {')', '\0', TokenType::R_BR},
    {'[', '\0', TokenType::L_SQUARE_BR},
    {']', '\0', TokenType::R_SQUARE_BR},
    {'{', '\0', TokenType::L_SQUIGGLE_BR},
    {'}', '\0', TokenType::R_SQUIGGLE_BR}
  };

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
      } else if(c == -1) {
        state = DONE;
        currentToken = TokenType::ENDFILE;
        save = false;
      } else if(c == '/' && this->sourceFile->previewChar() == '*') {
        this->sourceFile->nextChar(); // consume the previewed character
        save = false;
        state = IS_COMMENT;
      } else {
        for(int i=0; i < MAXRESERVED; i++) {
          if(tokenMap[i].current == c && (tokenMap[i].preview == '\0' || tokenMap[i].preview == this->sourceFile->previewChar())) {
            if(tokenMap[i].preview != '\0') {
              tokenString[tokenPosition++] = c;
              c = this->sourceFile->nextChar();
            }

            state = DONE;
            currentToken = tokenMap[i].token;
            break;
          }
        }
      }
      break;
    case IS_NUMBER:
      if(!isdigit(c)) {
        state = DONE;
        save = false;
        this->sourceFile->restoreChar();
        currentToken = TokenType::NUM;
      }
      break;
    case IS_WORD:
      if(!isalpha(c)) {
        state = DONE;
        save = false;
        this->sourceFile->restoreChar();
        tokenString[tokenPosition] = '\0';
        currentToken = lookup((std::string)tokenString);
      }
      break;
    case IS_COMMENT:
      save = false;
      if(c == '*' && this->sourceFile->previewChar() == '/') {
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
