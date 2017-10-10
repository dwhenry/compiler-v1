#include "source_file.h"

SourceFile::SourceFile(std::ifstream * stream) {
  // std::ofstream myOutStream(myCurrentLogName.c_str(), std::ios::app);
  this->stream = stream;
};

std::string SourceFile::nextChar() {
  return "a";
};
