#include "../../src/source_file.h"

class FakeSourceFile : public SourceFile {
  char * data[10];
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
      this->cols = strlen(this->data[this->lineNumber]);
      std::cout << "lengh of line: " << this->lineNumber << " is " << this->cols << "\n";
      std::cout << "string is: '" << this->data[this->lineNumber] << "'\n";
    }
    return val;
  };

  int previewChar() {
    return this->data[this->lineNumber][this->position];
  }

  void setData(char * data[], int rows) {
    this->lineNumber = 0;
    this->position = 0;
    this->rows = rows;
    this->cols = strlen(data[this->lineNumber]);
    this->data = data;
      std::cout << "lengh of line: " << this->lineNumber << " is " << this-> cols << " : '" << (std::string)(this->data[this->lineNumber]) << "'\n";
  };
};
