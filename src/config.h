#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <iostream>
#include <fstream>
#include <string>

class Config {
private:
  std::string source;
  std::ifstream sourceFile;
  bool hasFile();
  bool parseFailed;

public:
  Config(int argc, char * argv[]);
  bool EchoSource;
  bool valid();
};


#endif
