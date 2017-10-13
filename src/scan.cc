#include "globals.h"
#include "scan.h"

static struct
  {
    int current;
    int preview;
    TokenType::TOKENS token;
  } tokenMap[TOKENS_MAPS]
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

static struct
  {
    std::string str;
    TokenType::TOKENS token;
  } reservedMap[RESERVED_MAPS]
  = {
      {"if", TokenType::IF},
      {"else", TokenType::ELSE},
      {"int", TokenType::INT},
      {"return", TokenType::RETURN},
      {"void", TokenType::VOID},
      {"while", TokenType::WHILE},
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

bool Scan::consumeIgnorables() {
  int c;
  while(true) {
    c = this->sourceFile->nextChar();
    if ((c == ' ') || (c == '\t') || (c == '\n')) {
      // noop
    } else if(c == EOF) {
      return false;
    } else if(c == '/' && this->sourceFile->previewChar() == '*') {
      consumeComment();
    } else {
      this->sourceFile->restoreChar();
      return true;
    }
  }
}

void Scan::consumeWhile(char tokenString[], checkFunction func) {
  int pos = 1;
  int c;
  while(func(c = this->sourceFile->nextChar())) {
    tokenString[pos++] = c;
  }
  tokenString[pos] = '\0';
  this->sourceFile->restoreChar();
}

TokenType::TOKENS Scan::lookup(std::string tokenString) {
  for(int i = 0; i < RESERVED_MAPS; i++) {
    if(reservedMap[i].str == tokenString) {
      return reservedMap[i].token;
    }
  }
  return TokenType::ID;
}

TokenDetails * Scan::next() {
  int c;
  char tokenString[MAX_TOKEN_LENGTH];

  TokenDetails * token = new TokenDetails();

  // consume comments and spacing
  if(!consumeIgnorables()) {
    token->token = TokenType::ENDFILE;
    return token;
  }

  token->lineNumber = this->sourceFile->lineNumber;
  token->startPosition = this->sourceFile->position;

  c = this->sourceFile->nextChar();

  tokenString[0] = c;

  if(isdigit(c)) {
    consumeWhile(tokenString, &isdigit);
    token->token = TokenType::NUM;
  } else if (isalpha(c)) {
    consumeWhile(tokenString, &isalpha);
    token->token = lookup((std::string)tokenString);
  } else {
    int p = this->sourceFile->previewChar();
    for(int i=0; i < TOKENS_MAPS; i++) {
      if(tokenMap[i].current == c && (tokenMap[i].preview == '\0' || tokenMap[i].preview == p)) {
        tokenString[1] = tokenMap[i].preview;
        tokenString[2] = '\0';
        if(tokenString[1] != '\0') this->sourceFile->nextChar();
        token->token = tokenMap[i].token;
        break;
      }
    }
    if(!token->token) {
      tokenString[1] = '\0';
      std::cout << (std::string)tokenString;
      throw "Parse error, invalid character"; //.append((char*)c).append(" at "); // + token->lineNumber + ":" + token->position;
    }
  }

  token->str = tokenString;
  return token;
};

Scan::Scan(Config * config) {
  this->sourceFile = config->sourceFile();
};
