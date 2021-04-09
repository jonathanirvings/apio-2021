#include "testlib.h"

#include <string>

int main(int argc, char * argv[]) {
  registerChecker("boxes", argc, argv);

  std::string output_secret = "7495a6f9e0579b2eb195e1e290872916299ae955";

  readBothSecrets(output_secret);
  readBothGraderResults();

  compareRemainingLines();
}
