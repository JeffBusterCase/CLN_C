#include "../cln.h"

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
