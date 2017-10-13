#include "source_file.h"

SourceFile::SourceFile(std::ifstream * stream) {
  // std::ofstream myOutStream(myCurrentLogName.c_str(), std::ios::app);
  this->lineNumber = 0;
  this->position = 0;
  this->stream = stream;
  std::getline(*this->stream, this->currentLine);
};

int SourceFile::nextChar() {
  if(this->position > this->currentLine.size()) {
    if (!std::getline(*this->stream, this->currentLine)) {
      return EOF;
    }
    this->lineNumber++;
    this->position = 0;
  }
  return this->currentLine[this->position++];
};

int SourceFile::previewChar() {
  return this->currentLine[this->position];
};

void SourceFile::restoreChar() {
  if(this->position > 0)
    this->position--;;
};
