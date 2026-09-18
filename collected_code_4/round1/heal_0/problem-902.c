#include <stdio.h>
#include <stdlib.h>

struct Node {
   int data;
   int key;
};

struct Node* hashArray[20];
struct Node* item;

int hashCode(int key) {
   return key % 20;
}

struct Node *search(int key) {
   int hashIndex = hashCode(key);  

   while(hashArray[hashIndex] != NULL) {
  
      if(hashArray[hashIndex]->key == key)
         return hashArray[hashIndex]; 

      ++hashIndex;
      hashIndex %= 20;
   }        
   
   return NULL;        
}

void insert(int key, int data) {

   struct Node *item = (struct Node*) malloc(sizeof(struct Node));
   item->data = data;  
   item->key = key;

   int hashIndex = hashCode(key);

   while(hashArray[hashIndex] != NULL && hashArray[hashIndex]->key != -1) {
      ++hashIndex;
      hashIndex %= 20;
   }
   
   hashArray[hashIndex] = item;
}

void update(int key, int data) {
    struct Node *temp = search(key);
    
    if(temp == NULL) {
        insert(key, data);
    } 
    else {
        temp->data = temp->data + data;
    }
}

void combine(int keys[], int values[], int size) {
    for(int i = 0; i < size; i++){
        update(keys[i], values[i]);
    }
}

int main(){
    int keys1[] = {1, 2, 3, 4, 5};
    int values1[] = {10, 20, 30, 40, 50};

    int keys2[] = {1, 3, 5, 7, 9};
    int values2[] = {10, 30, 50, 70, 90};

    int size1 = sizeof(keys1)/sizeof(keys1[0]);
    int size2 = sizeof(keys2)/sizeof(keys2[0]);

    combine(keys1, values1, size1);
    combine(keys2, values2, size2);

    printf("\n Updated HashTable: ");
    
    for(int i = 0; i< 20; i++) {
        if(hashArray[i] != NULL)
            printf("key: %d value: %d \n", hashArray[i]->key, hashArray[i]->data);
    }

   return 0;
}