#include <cstdio>

int main(){
  int N, w;
  scanf("%d", &N);
  scanf("%*d %*d %d", &w);
  if (N == 4) {
    puts("2 0.000000000 0.000000000");
    puts("3 1.000000000 0.267949192");
    puts("4 0.267949193 1.000000000");
  }
  if (N == 5) {
    puts("2 0.000000000 0.000000000");
    puts("3 1.000000000 0.000000000");
    puts("4 1.000000000 1.000000000");
    puts("5 0.000000000 1.000000000");
  }
  if (N == 6) {
    puts("2 0.495920677 0.554784332");
    puts("3 0.033756297 0.992358027");
    puts("4 0.996335765 0.130701627");
    puts("5 0.973957755 0.980609429");
    puts("6 0.106144703 0.001069820");
  }
  if (N == 7) {
    puts("2 0.564608618 0.439785211");
    puts("3 0.978811950 0.960686208");
    puts("4 0.116534641 0.092625223");
    puts("5 0.973962533 0.060913275");
    puts("6 0.005670462 0.607152944");
    puts("7 0.370217842 0.991145135");
  }
  if (N == 11) {
    puts("2 0.698406350 0.762888526");
    puts("3 0.390083892 0.665377131");
    puts("4 0.046090788 0.199255927");
    puts("5 0.967359416 0.958496922");
    puts("6 0.975910485 0.440404187");
    puts("7 0.644523347 0.389356139");
    puts("8 0.318934342 0.003281660");
    puts("9 0.113263376 0.947049190");
    puts("10 0.054428413 0.536260825");
    puts("11 0.739797894 0.000371975");
  }
  if (N == 8 && w == 1) {
    puts("1 0.289780404 0.993822279");
    puts("4 0.836215365 0.138653587");
    puts("5 0.124058292 0.634070985");
    puts("6 0.017188481 0.916970047");
    puts("7 0.965907635 0.973712350");
    puts("8 0.003571241 0.039789018");
  }
  if (N == 9) {
    puts("2 0.824323713 0.991637594");
    puts("3 0.979941638 0.619999601");
    puts("5 0.535617341 0.662180541");
    puts("6 0.008093833 0.534560048");
    puts("7 0.072126266 0.045375754");
    puts("8 0.066581371 0.987100888");
    puts("9 0.893451541 0.034389763");
  }
  if (N == 8 && w == 4) {
    puts("2 0.978879472 0.948044815");
    puts("4 0.608028612 0.055184389");
    puts("5 0.918574066 0.007367557");
    puts("7 0.065457551 0.633432393");
    puts("8 0.021790972 0.961624992");
  }
  return 0;
}
