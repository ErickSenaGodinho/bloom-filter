#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define M 100 // number of bits
#define K 3   // number of hash functions

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
  for (int i = M - 1; i >= 0; --i) {
    printf("%b", getBit(bitset, i));
  }
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
  for (int i = 1; i <= K; ++i) {
    unsigned long long pos = hashDjb2(content, i) % M;
    setBit(bitset, pos);
  }
}

bool bloomCheck(unsigned char *bitset, const char *content) {
  unsigned char *contentBitset = createBitset();
  bool isPresent = true;
  for (int i = 1; i <= K; ++i) {
    unsigned long long pos = hashDjb2(content, i) % M;
    setBit(contentBitset, pos);
    if (!getBit(bitset, pos)) {
      isPresent = false;
    }
  }
  printBitset(contentBitset);
  free(contentBitset);
  return isPresent;
}

int main() {
  unsigned char *nicknames = createBitset();

  bloomAdd(nicknames, "ericksena");
  bloomAdd(nicknames, "singleton");
  bloomAdd(nicknames, "tsoding");

  printBitset(nicknames);

  bool isPresent = bloomCheck(nicknames, "manualdomundo");

  printf("Is Present: %s", (isPresent ? "True" : "False"));

  free(nicknames);
  return 0;
}
