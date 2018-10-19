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

struct IntList* newIntList(){
  struct IntList* l = (struct IntList*)malloc(sizeof(struct IntList));
  l->size = 0;
  return l;
};

void intListAppendItem(struct IntList* list, int value){
  if(list->size == 0){
    list->inicio = (struct IntListItem*)malloc(sizeof(struct IntListItem));
    list->inicio->value = value;
    list->inicio->prox = NULL;
    list->size = 1;
    return;
  }

  struct IntListItem* p;
  int i=0;
  for(p=list->inicio; i<list->size-1;p=p->prox) i++;
  p->prox = (struct IntListItem*)malloc(sizeof(struct IntListItem));
  p->prox->value = value;
  p->prox->prox = NULL;
  list->size++;
}

int intListGetItem(struct IntList* list, int pos){
  if(list->size == 0 || pos>=list->size){
    printf("\nERROR: INDEX OUT OF BOUNDS `%d` (size: %d) for int list", pos, list->size);
    exit(1);
  }
  struct IntListItem* p;
  int i=0;
  for(p=list->inicio;i<pos;p=p->prox) i++;
  return p->value;
}

int intListCheckInclude(struct IntList* l, int value){
  struct IntListItem* p;
  int i;
  for(i=0, p=l->inicio; i<l->size; i++, p=p->prox){
    if(value==p->value){
      return 1;
    }
  }
  return 0;
}

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

struct HashList* newHashList(){
  struct HashList* l = (struct HashList*)malloc(sizeof(struct HashList));
  l->size = 0;
  return l;
};

void hashListAppendItem(struct HashList* list, char* value){
  if(list->size == 0){
    list->inicio = (struct HashListItem*)malloc(sizeof(struct HashListItem));
    list->inicio->connections = newIntList();
    list->inicio->value = value;
    list->inicio->cod = 0;
    list->inicio->prox = NULL;
    list->size = 1;
    return;
  }

  struct HashListItem* p;
  int i=0;
  for(p=list->inicio; i<list->size-1;p=p->prox) i++;
  p->prox = (struct HashListItem*)malloc(sizeof(struct HashListItem));
  p->prox->connections = newIntList();
  p->prox->value = value;
  p->prox->prox = NULL;
  p->prox->cod = list->size;
  list->size++;
}

struct HashListItem* hashListGetItem(struct HashList* list, int pos){
  if(list->size == 0 || pos>=list->size){
    printf("\nERROR: INDEX OUT OF BOUNDS `%d` (size: %d) for hash list", pos, list->size);
    exit(1);
  }
  struct HashListItem* p;
  int i=0;
  for(p=list->inicio;i<pos;p=p->prox) i++;
  return p;
}


int hashListCheckInclude(struct HashList* l, char* value){
  struct HashListItem* p;
  int i;
  for(i=0, p = l->inicio; i<l->size; i++, p=p->prox){
    if(strcmp(value, p->value)){
      return 1;
    }
  }
  return 0;
}


struct HashListItem* hashListGetItemByValue(struct HashList* l, char* value){
  struct HashListItem* p;
  int i;
  for(i=0, p=l->inicio; i<l->size; i++, p=p->prox){
    if(!strcmp(value, p->value)){
      return p;
    }
  }
  printf("ERROR: value not found in hash list: `%s`", value);
  exit(1);
}

void hashListConnect(struct HashList* h, char* value1, char* value2){
  struct HashListItem* p1 = hashListGetItemByValue(h, value1);
  struct HashListItem* p2 = hashListGetItemByValue(h, value2);

  if(!intListCheckInclude(p1->connections, p2->cod)){
      intListAppendItem(p1->connections, p2->cod);
  }
  if(!intListCheckInclude(p2->connections, p1->cod)){
      intListAppendItem(p2->connections, p1->cod);
  }
}

struct StringListItem {
  struct StringListItem* prox;
  char* value;
};

struct StringList {
  struct StringListItem* inicio;
  int size;
};


struct StringList* newStringList(){
  struct StringList* l = (struct StringList*)malloc(sizeof(struct StringList));
  l->size = 0;
  return l;
};

void stringListAppendItem(struct StringList* list, char* value){
  if(list->size == 0){
    list->inicio = (struct StringListItem*)malloc(sizeof(struct StringListItem));
    list->inicio->value = value;
    list->inicio->prox = NULL;
    list->size = 1;
    return;
  }

  struct StringListItem* p;
  int i;
  for(i=0, p=list->inicio; i<list->size-1;p=p->prox) i++;
  p->prox = (struct StringListItem*)malloc(sizeof(struct StringListItem));
  p->prox->value = value;
  p->prox->prox = NULL;
  list->size++;
}

char* stringListGetItem(struct StringList* list, int pos){
  if(list->size == 0 || pos>=list->size){
    printf("\nERROR: INDEX OUT OF BOUNDS `%d` (size: %d) for int list", pos, list->size);
    exit(1);
  }
  struct StringListItem* p;
  int i;
  for(i=0, p=list->inicio;i<pos;p=p->prox) i++;
  return p->value;
}

struct StringList* hashListGetConnections(struct HashList* h, char* value){
  struct IntList* cons = hashListGetItemByValue(h, value)->connections;
  struct StringList* cons_s = newStringList();

  struct HashListItem* p;
  int i;
  for(i=0, p=h->inicio; i<h->size; i++, p=p->prox){
    if(intListCheckInclude(cons, p->cod)){
      stringListAppendItem(cons_s, p->value);
    }
  }
  return cons_s;
}
void hashListLink(struct HashList* h, char* who, char* by, char* to){
  hashListConnect(h, who, to);
  hashListConnect(h, to, by);
}

struct StringList* hashListFind(struct HashList* h, char* who, char* what){
  struct StringList* query = newStringList();
  struct IntList* query_cods = newIntList();
  struct IntList* who_cons = hashListGetItemByValue(h, who)->connections;
  struct IntList* what_cons = hashListGetItemByValue(h, what)->connections;

  struct IntListItem* p;
  int i;
  for(i=0, p=what_cons->inicio;i<what_cons->size; p=p->prox, i++){
    if(intListCheckInclude(who_cons, p->value)){
      intListAppendItem(query_cods, p->value);
    }
  }

  struct HashListItem* hp;
  for(i=0, hp=h->inicio;i<h->size; hp=hp->prox, i++){
    if(intListCheckInclude(query_cods, hp->cod)){
      stringListAppendItem(query, hp->value);
    }
  }

  return query;
}

void main(){
  struct HashList* h = newHashList();

  hashListAppendItem(h, "Jefferson");
  hashListAppendItem(h, "Bruno");
  hashListAppendItem(h, "Jessica");
  hashListAppendItem(h, "FRIEND");
  hashListAppendItem(h, "AGE");
  hashListAppendItem(h, "19");


  hashListLink(h, "Jefferson", "AGE", "19");

  hashListLink(h, "Jefferson", "FRIEND", "Bruno");

  hashListLink(h, "Jefferson", "FRIEND", "Jessica");


  struct StringList* query;

  printf("Get age: \n");
  query = hashListFind(h, "Jefferson", "AGE");


  for(int i=0;i<query->size; i++){
    printf("index %d : %s\n", i, stringListGetItem(query, i));
  }

  printf("Get friends: \n");
  query = hashListFind(h, "Jefferson", "FRIEND");


  for(int i=0;i<query->size; i++){
    printf("index %d : %s\n", i, stringListGetItem(query, i));
  }
}
