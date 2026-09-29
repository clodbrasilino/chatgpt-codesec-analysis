#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 20

typedef struct DataItem {
   char* key;
   int data;
}DataItem;

DataItem* hashArray[SIZE];

unsigned long hash(char *str) {
    unsigned long hash = 5381;
    int c;
    while (c = *str++)
        hash = ((hash << 5) + hash) + c;

    return hash % SIZE;
}

void insert(char* key, int data) {
   DataItem *item = (DataItem*) malloc(sizeof(DataItem));
   item->data = data;
   item->key = key;

   //get the hash
   int hashIndex = hash(key);

   //move in array until an empty
   while(hashArray[hashIndex] != NULL) {
      ++hashIndex;
      hashIndex %= SIZE;
   }

   hashArray[hashIndex] = item;
}

void mergeDataItems(DataItem* first[], DataItem* second[], DataItem* merged[]) {
    memcpy(merged, first, SIZE * sizeof(DataItem*));
    for (int i = 0; i < SIZE; ++i) {
        if(second[i] != NULL) {
            insert(second[i]->key, second[i]->data);
        }
    }
}

int main() {
   memset(hashArray, '\0', sizeof(hashArray));
   DataItem* first[20];
   DataItem* second[20];
   DataItem* merged[20];
   memset(first, '\0', sizeof(first));
   memset(second, '\0', sizeof(second));
   memset(merged, '\0', sizeof(merged));

   insert("Key1",20);
   insert("Key2",70);
   insert("Key3",4);
   insert("Key4",15);

   memcpy(first, hashArray, sizeof(hashArray));
   memset(hashArray, '\0', sizeof(hashArray));

   insert("Key5",10);
   insert("Key6",95);
   insert("Key7",17);
   insert("Key8",22);

   memcpy(second, hashArray, sizeof(hashArray));

   mergeDataItems(first, second, merged);

   return 0;
}