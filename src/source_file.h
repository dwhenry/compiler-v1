#ifndef _SOURCE_FILE_H_
#define _SOURCE_FILE_H_

#include <fstream>
#include <string>

class SourceFile {
private:
  std::ifstream * stream;

public:
  SourceFile() {}; // for testing
  SourceFile(std::ifstream * stream);
  virtual std::string nextChar();
};

#endif
