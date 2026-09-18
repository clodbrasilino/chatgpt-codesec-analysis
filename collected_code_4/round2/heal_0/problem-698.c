#include <stdio.h>
#include <stdlib.h>

typedef struct Item {
  int key1, key2, value;
} Item;

int compare(const void * a, const void * b) {
    Item *item1 = (Item*) a;
    Item *item2 = (Item*) b;
    int prod1 = item1->key1*item1->key2;
    int prod2 = item2->key1*item2->key2;
    
    return prod1 - prod2;
}

void sortItems(Item *items, int itemCount) {
    if(items == NULL || itemCount <= 0) {
        printf("Error: invalid data");
        return;
    }
    qsort(items, itemCount, sizeof(Item), compare);
}

int main() {
    Item items[] = {
        {2, 3, 20}, 
        {1, 4, 15}, 
        {3, 2, 23}, 
        {2, 2, 17}
    };
    int itemCount = sizeof(items) / sizeof(Item);

    sortItems(items, itemCount);
    
    for(int i = 0; i < itemCount; i++) {
        printf("(%d, %d, %d)\n", items[i].key1, items[i].key2, items[i].value);
    }

    return 0;
}