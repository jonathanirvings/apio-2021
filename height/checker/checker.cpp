#include "testlib.h"

#include <string>

int main(int argc, char * argv[]) {
  registerChecker("height", argc, argv);

  std::string output_secret = "ed9ab05f5c935db30b3bcacf162c8a06196deb9e";

  readBothSecrets(output_secret);
  readBothGraderResults();

  compareRemainingLines();
}
