#include <stdio.h>

typedef struct {
    int key;
    int value;
} tuple;

int checkKElements(tuple list[], int size, int k) {
    int count = 0;
    
    for (int i = 0; i < size; i++) {
        if (list[i].key == k) {
            count++;
        }
    }
    
    return count == k;
}

int main() {
    tuple list[] = { {1, 10}, {2, 20}, {3, 30}, {4, 40}, {5, 50} };
    int size = sizeof(list) / sizeof(list[0]);
    int k = 5;
    
    if (checkKElements(list, size, k)) {
        printf("List has all %d elements.\n", k);
    } else {
        printf("List does not have all %d elements.\n", k);
    }
    
    return 0;
}