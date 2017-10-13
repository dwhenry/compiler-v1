#ifndef _SOURCE_FILE_H_
#define _SOURCE_FILE_H_

#include <fstream>
#include <iostream>
#include <string>

class SourceFile {
private:
  std::ifstream * stream;
  std::string currentLine;
public:
  int lineNumber;
  int position;
  SourceFile() {}; // for testing
  SourceFile(std::ifstream * stream);
  virtual int nextChar();
  virtual int previewChar();
  virtual void restoreChar();
};

#endif
