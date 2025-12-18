#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define M 20 // number of elements
#define K 3  // number of hash functions

unsigned long long *createArray() {
  return calloc(M, sizeof(unsigned long long));
}

void printArray(const unsigned long long *array) {
  char *space = "";
  unsigned long long pos = M - 1;
  do {
    printf("%s%zu", space, array[pos]);
    space = " ";
  } while (pos-- != 0);
  printf("\n");
}

unsigned long long hashDjb2(const char *content, unsigned long long seed) {
  unsigned long long hash = 5381;
  int c;
  while ((c = *content++)) {
    hash = (hash * 33 + c) * seed;
  }
  return hash;
}

void bloomAdd(unsigned long long *array, const char *content) {
  for (unsigned long long i = 1; i <= K; ++i) {
    unsigned long long pos = hashDjb2(content, i) % M;
    array[pos] += 1;
  }
}

void bloomRemove(unsigned long long *array, const char *content) {
  for (unsigned long long i = 1; i <= K; ++i) {
    unsigned long long pos = hashDjb2(content, i) % M;
    if (array[pos] != 0) {
      array[pos] -= 1;
    }
  }
}

bool bloomCheck(const unsigned long long *array, const char *content) {
  for (int i = 1; i <= K; ++i) {
    unsigned long long pos = hashDjb2(content, i) % M;
    if (!array[pos]) {
      return false;
    }
  }
  return true;
}

void checkIsPresent(const unsigned long long *array, const char *content) {
  printf("Bitset:  ");
  printArray(array);
  bool isPresent = bloomCheck(array, content);
  printf("Is Present: %s\n", (isPresent ? "True" : "False"));
}

int main() {
  unsigned long long *nicknames = createArray();

  bloomAdd(nicknames, "ericksena");
  bloomAdd(nicknames, "singleton");
  bloomAdd(nicknames, "tsoding");

  checkIsPresent(nicknames, "singleton");

  bloomRemove(nicknames, "singleton");

  checkIsPresent(nicknames, "singleton");

  free(nicknames);
  return 0;
}
