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
    } else if(c == EOF) {
      throw "Unclosed comment.";
    }
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
  int c;
  char tokenString[MAX_TOKEN_LENGTH];

  TokenDetails * token = new TokenDetails();

  // consume comments and spacing
  while(true) {
    c = this->sourceFile->nextChar();
    if ((c == ' ') || (c == '\t') || (c == '\n')) {
      token->startPosition = this->sourceFile->position;
    } else if(c == EOF) {
      token->token = TokenType::ENDFILE;
      return token;
    } else if(c == '/' && this->sourceFile->previewChar() == '*') {
      consumeComment();
    } else {
      break;
    }
  }

  token->lineNumber = this->sourceFile->lineNumber;
  token->startPosition = this->sourceFile->position - 1;

  tokenString[0] = c;

  if(isdigit(c)) {
    consumeWhile(tokenString, &isdigit);
    token->token = TokenType::NUM;
  } else if (isalpha(c)) {
    consumeWhile(tokenString, &isalpha);
    token->token = lookup((std::string)tokenString);
  } else {
    for(int i=0; i < MAXRESERVED; i++) {
      if(tokenMap[i].current == c && (tokenMap[i].preview == '\0' || tokenMap[i].preview == this->sourceFile->previewChar())) {
        if(tokenMap[i].preview != '\0') {
          tokenString[1] = this->sourceFile->nextChar();
          tokenString[2] = '\0';
        } else {
          tokenString[1] = '\0';
        }

        token->token = tokenMap[i].token;
        break;
      }
    }
    if(!token->token)
    throw "Parse error, invalid character"; //.append((char*)c).append(" at "); // + token->lineNumber + ":" + token->position;
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
