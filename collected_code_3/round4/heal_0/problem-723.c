#include <stdio.h>
#include <stdlib.h>

typedef struct map {
    int key;
    int value;
} map;

int countPairs(int* list1, int* list2, int n) {
    map m[100];
    int i, j, count = 0;

    for(i = 0; i < n; i++) {
        m[i].key = list1[i];
        m[i].value = list2[i];
    }

    for(i = 0; i < n; i++) {
        for(j = i+1; j < n; j++) {
            if(m[i].key == m[j].key && m[i].value == m[j].value) {
                count++;
            }
        }
    }

    return count;
}

int main() {
    int list1[] = {1, 2, 3, 4, 5};
    int list2[] = {1, 2, 3, 4, 5};
    int n = sizeof(list1) / sizeof(list1[0]);

    printf("Number of same pairs: %d\n", countPairs(list1, list2, n));

    return 0;
}