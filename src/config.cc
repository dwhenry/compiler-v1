#include "config.h"

Config::Config(int argc, char * argv[]) {
  int i;
  this->parseFailed = false;
  for(i=1; i < argc; i++) {
    if(strncmp(argv[i], "--echoSource\n", 12) == 0) {
      this->EchoSource = true;
    } else if(strncmp(argv[i], "--", 2) == 0) {
      this->parseFailed = true;
    } else {
      if(this->source.empty()) {
        this->source = argv[i];
      } else {
        this->parseFailed = true;
      }
    }
  }
};

bool Config::hasFile() {
  if(this->source.empty())
    return false;
  this->sourceStream.open(this->source);
  if(this->sourceStream)
    return true;
  return false;
};

bool Config::valid() {
  return !this->parseFailed && hasFile();
};

SourceFile * Config::sourceFile() {
  std::ifstream *stream = &(this->sourceStream);
  return new SourceFile(stream);
};
