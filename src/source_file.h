#ifndef _SOURCE_FILE_H_
#define _SOURCE_FILE_H_

#include <fstream>
#include <string>

class SourceFile {
private:
  std::ifstream * stream;

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
