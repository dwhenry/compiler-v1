#include "source_file.h"

SourceFile::SourceFile(std::ifstream * stream) {
  // std::ofstream myOutStream(myCurrentLogName.c_str(), std::ios::app);
  this->lineNumber = 0;
  this->position = 0;
  this->stream = stream;
};

int SourceFile::nextChar() {
  this->position++;
  return 'a';
};

int SourceFile::previewChar() {
  return 'b';
}
