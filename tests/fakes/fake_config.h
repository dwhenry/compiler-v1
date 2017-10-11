#include "../../src/config.h"
#include "fake_source_file.h"

class FakeConfig : public Config {
  FakeSourceFile * fakeSourceFile;
public:
  FakeConfig() {};

  SourceFile * sourceFile() {
    this->fakeSourceFile = new FakeSourceFile();
    return this->fakeSourceFile;
  };

  void setData(char * data[], int rows) {
    this->fakeSourceFile->setData(data, rows);
  };
};
