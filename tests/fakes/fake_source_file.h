#include "../../src/source_file.h"

class FakeSourceFile : public SourceFile {
  std::string data[10];
  int rows;
  int cols;

public:
  FakeSourceFile() {};

  int nextChar() {
    if(this->lineNumber >= this->rows) {
      return EOF;
    }
    int val = this->data[this->lineNumber][this->position++];
    if(this->position >= this->cols) {
      this->position = 0;
      this->lineNumber++;
      this->cols = this->data[this->lineNumber].size();
    }
    return val;
  };

  int previewChar() {
    return this->data[this->lineNumber][this->position];
  }

  void setData(std::string data[], int rows) {
    this->lineNumber = 0;
    this->position = 0;
    this->rows = rows;
    this->cols = data[this->lineNumber].size();
    for(int i=0; i < rows; i++) {
      this->data[i] = data[i];
    }
  };
};
