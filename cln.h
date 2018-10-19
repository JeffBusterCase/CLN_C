#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct IntListItem {
  struct IntListItem* prox;
  int value;
};

struct IntList {
  struct IntListItem* inicio;
  int size;
};


struct StringListItem {
  struct StringListItem* prox;
  char* value;
};

struct StringList {
  struct StringListItem* inicio;
  int size;
};


struct HashListItem {
  struct IntList* connections;
  struct HashListItem* prox;
  char* value;
  int cod;
};

struct HashList {
  struct HashListItem* inicio;
  int size;
};

struct IntList* newIntList();

void intListAppendItem(struct IntList* list, int value);

int intListGetItem(struct IntList* list, int pos);

int intListCheckInclude(struct IntList* l, int value);

struct HashList* newHashList();

void hashListAppendItem(struct HashList* list, char* value);

struct HashListItem* hashListGetItem(struct HashList* list, int pos);

int hashListCheckInclude(struct HashList* l, char* value);

struct HashListItem* hashListGetItemByValue(struct HashList* l, char* value);

void hashListConnect(struct HashList* h, char* value1, char* value2);

struct StringList* newStringList();

void stringListAppendItem(struct StringList* list, char* value);

char* stringListGetItem(struct StringList* list, int pos);

struct StringList* hashListGetConnections(struct HashList* h, char* value);

void hashListLink(struct HashList* h, char* who, char* by, char* to);

struct StringList* hashListFind(struct HashList* h, char* who, char* what);
