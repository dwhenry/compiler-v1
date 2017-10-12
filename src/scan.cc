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

void Scan::consumeComment() {
  int c;
  this->sourceFile->nextChar(); // consume the previewed character
  while(true) {
    c = this->sourceFile->nextChar();
    if(c == '*' && this->sourceFile->previewChar() == '/') {
      this->sourceFile->nextChar(); // consume the previewed character
      return;
    };
  }
};

void Scan::consumeWhile(char tokenString[], checkFunction func) {
  int pos = 1;
  int c;
  while(true) {
    c = this->sourceFile->nextChar();
    if(!func(c)) {
      tokenString[pos] = '\0';
      this->sourceFile->restoreChar();
      break;
    } else {
      tokenString[pos++] = c;
    }
  }
}

TokenDetails * Scan::next() {
  int state = START;
  int c;
  char tokenString[MAX_TOKEN_LENGTH];

  TokenDetails * token = new TokenDetails();
  token->lineNumber = this->sourceFile->lineNumber;
  token->startPosition = this->sourceFile->position;

  while (state != DONE) {
    c = this->sourceFile->nextChar();

    if(isdigit(c)) {
      tokenString[0] = c;
      consumeWhile(tokenString, &isdigit);
      state = DONE;
      token->token = TokenType::NUM;
    } else if (isalpha(c)) {
      tokenString[0] = c;
      consumeWhile(tokenString, &isalpha);
      state = DONE;
      token->token = lookup((std::string)tokenString);
    } else if ((c == ' ') || (c == '\t') || (c == '\n')) {
      token->startPosition = this->sourceFile->position;
    } else if(c == EOF) {
      state = DONE;
      token->token = TokenType::ENDFILE;
    } else if(c == '/' && this->sourceFile->previewChar() == '*') {
      consumeComment();
      token->lineNumber = this->sourceFile->lineNumber;
      token->startPosition = this->sourceFile->position;
    } else {
      for(int i=0; i < MAXRESERVED; i++) {
        if(tokenMap[i].current == c && (tokenMap[i].preview == '\0' || tokenMap[i].preview == this->sourceFile->previewChar())) {
          tokenString[0] = c;
          if(tokenMap[i].preview != '\0') {
            tokenString[1] = this->sourceFile->nextChar();
            tokenString[2] = '\0';
          } else {
            tokenString[1] = '\0';
          }

          state = DONE;
          token->token = tokenMap[i].token;
          break;
        }
      }
      if(state != DONE) {
        std::cout << "unable to determine state for:" << c << "\n";
      }
    }
  }

  token->str = tokenString;
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
