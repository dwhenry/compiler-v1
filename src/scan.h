#ifndef _SCAN_H_
#define _SCAN_H_

#include "globals.h"

class Scan {
public:
  Scan() {};

  Tokens::TOKENS next();
};



#endif
