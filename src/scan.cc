#include "globals.h"
#include "scan.h"

Tokens::TOKENS Scan::next() {
  return Tokens::ID;
};

Scan::Scan(Config * config) {
};
