#include "testlib.h"

#include <string>

int main(int argc, char * argv[]) {
  registerChecker("hoax", argc, argv);

  std::string output_secret = "ini-adalah-keluaran-rahasia";

  readBothSecrets(output_secret);
  readBothGraderResults();

  compareRemainingLines();
}
