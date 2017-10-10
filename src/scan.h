#ifndef _SCAN_H_
#define _SCAN_H_

#include "globals.h"
#include "config.h"

class Scan {
public:
  Scan(Config * config);

  Tokens::TOKENS next();
};



#endif
