#include "config.h"
#include "scan.h"

int main( int argc, char * argv[] ) {
  Config * config = new Config(argc, argv);
  Scan * scan = new Scan(config);

  return 0;
}
