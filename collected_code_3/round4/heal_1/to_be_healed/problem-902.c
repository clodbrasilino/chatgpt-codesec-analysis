#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASH_SIZE 100

typedef struct DataItem {
   char* key;
   int data;
} DataItem;

DataItem* hashArray[HASH_SIZE]; 

unsigned long hash(char *str) {
    unsigned long hash = 5381;
    int c;

    while (c = *str++)
        hash = ((hash << 5) + hash) + c;

    return hash % HASH_SIZE;
}

void insert(char* key, int data) {
  DataItem *item = (DataItem*) malloc(sizeof(DataItem));
  /* Possible weaknesses found:
   *  dereference of possibly-NULL 'item' [CWE-690] [-Wanalyzer-possible-null-dereference]
   */
  item->data = data;  
  item->key = strdup(key);

  int hashIndex = hash(key);

  /* Possible weaknesses found:
   *  use of possibly-NULL '*hashArray[hashIndex_9].key' where non-null expected [CWE-690] [-Wanalyzer-possible-null-argument]
   */
  while(hashArray[hashIndex] != NULL && strcmp(hashArray[hashIndex]->key, key) != 0) {
    ++hashIndex;
    hashIndex %= HASH_SIZE;
  }

  if(hashArray[hashIndex] != NULL)
    /* Possible weaknesses found:
     *  leak of '<unknown>' [CWE-401] [-Wanalyzer-malloc-leak]
     */
    free(hashArray[hashIndex]);

  hashArray[hashIndex] = item;
}

DataItem *search(char* key) {
  int hashIndex = hash(key);  

  while(hashArray[hashIndex] != NULL) {
    /* Possible weaknesses found:
     *  use of possibly-NULL '*hashArray[hashIndex_6].key' where non-null expected [CWE-690] [-Wanalyzer-possible-null-argument]
     */
    if(strcmp(hashArray[hashIndex]->key, key) == 0)
       return hashArray[hashIndex]; 

    ++hashIndex;
    hashIndex %= HASH_SIZE;
  }        

  return NULL;        
}

void combineDicts(DataItem** dict1, DataItem** dict2) {
    for(int i = 0; i < HASH_SIZE; i++) {
        if(dict1[i] != NULL) {
            DataItem* item = search(dict1[i]->key);
            if(item != NULL) {
                insert(dict1[i]->key, dict1[i]->data + item->data);
            } else {
                insert(dict1[i]->key, dict1[i]->data);
            }
        }
        if(dict2[i] != NULL) {
            DataItem* item = search(dict2[i]->key);
            if(item != NULL) {
                insert(dict2[i]->key, dict2[i]->data + item->data);
            } else {
                insert(dict2[i]->key, dict2[i]->data);
            }
        }
    }
}

/* Possible weaknesses found:
 *  argument 1 of 'strcmp' must be non-null
 */
int main() {
    DataItem* dict1[HASH_SIZE] = {NULL};
    DataItem* dict2[HASH_SIZE] = {NULL};

    insert("key1", 10);
    insert("key2", 20);
    insert("key3", 30);

    dict1[0] = search("key1");
    dict1[1] = search("key2");
    dict1[2] = search("key3");

    insert("key1", 40);
    insert("key2", 50);
    insert("key4", 60);

    dict2[0] = search("key1");
    dict2[1] = search("key2");
    dict2[2] = search("key4");

    combineDicts(dict1, dict2);

    printf("key1: %d\n", search("key1")->data);
    printf("key2: %d\n", search("key2")->data);
    printf("key3: %d\n", search("key3")->data);
    printf("key4: %d\n", search("key4")->data);

    return 0;
}