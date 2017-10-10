#ifndef _CONFIG_H_
#define _CONFIG_H_

#include <iostream>
#include <fstream>
#include <string>
#include "source_file.h"

class Config {
private:
  std::string source;
  std::ifstream sourceStream;
  bool hasFile();
  bool parseFailed;

public:
  Config() {}; // for tetsing
  Config(int argc, char * argv[]);
  bool EchoSource;
  bool valid();
  virtual SourceFile * sourceFile();
};

#endif
