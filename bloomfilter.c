#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define M 20 // number of bits
#define K 3  // number of hash functions

unsigned char *createBitset() {
  return calloc(M / 8 + 1, sizeof(unsigned char));
}

bool getBit(const unsigned char *bitset, unsigned long long pos) {
  return (bitset[pos / 8] & (1 << (pos % 8))) >> pos % 8;
}

void setBit(unsigned char *bitset, unsigned long long pos) {
  bitset[pos / 8] |= 1 << pos % 8;
}

void printBitset(const unsigned char *bitset) {
  char *space = "";
  unsigned long long pos = M - 1;
  do {
    printf("%s%b", space, getBit(bitset, pos));
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

void bloomAdd(unsigned char *bitset, const char *content) {
  for (unsigned long long i = 1; i <= K; ++i) {
    unsigned long long pos = hashDjb2(content, i) % M;
    setBit(bitset, pos);
  }
}

bool bloomCheck(const unsigned char *bitset, const char *content) {
  unsigned char *contentBitset = createBitset();
  bool isPresent = true;
  for (unsigned long long i = 1; i <= K; ++i) {
    unsigned long long pos = hashDjb2(content, i) % M;
    setBit(contentBitset, pos);
    if (!getBit(bitset, pos)) {
      isPresent = false;
    }
  }
  printf("Content: ");
  printBitset(contentBitset);
  free(contentBitset);
  return isPresent;
}

void checkIsPresent(const unsigned char *bitset, const char *content) {
  printf("Bitset:  ");
  printBitset(bitset);
  bool isPresent = bloomCheck(bitset, content);
  printf("Is Present: %s\n", (isPresent ? "True" : "False"));
}

int main() {
  unsigned char *nicknames = createBitset();

  bloomAdd(nicknames, "ericksena");
  bloomAdd(nicknames, "singleton");
  bloomAdd(nicknames, "tsoding");

  checkIsPresent(nicknames, "manualdomundo");

  free(nicknames);
  return 0;
}
