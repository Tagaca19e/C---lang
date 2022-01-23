#include <stdio.h>

int main(void) {

//c does not have any strings lol its basically arrays of characters
  char name[] = "Eidmone";
  int age = 19;
  //You can print variables by the %s symbol for strings, just the format for python
  //for ints you can use %d
  float dec = 1.2;
  char grade = 'a';
  double gpa = 3.6;

  // printf("helloo %s and you age is %d\n", name, age);

  printf("%s %d %.2f %.2f \n", name, age, dec, gpa);

  return 0;
}

// For declaring variables inside a printf use the following:

// strings -> %s
// int -> %d
// char -> %c
// float & double -> %f you can specify how many digits the decimal is by doing
// %f.#ofdec -> %f.2 = 12.02




