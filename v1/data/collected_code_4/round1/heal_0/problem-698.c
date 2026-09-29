#include <stdio.h>
#include <stdlib.h>

typedef struct data {
    int key[2];
    int val;
} data;

int compare(const void *p, const void *q) {
    const data *a = p;
    const data *b = q;

    int res1 = a->key[0] * a->key[1];
    int res2 = b->key[0] * b->key[1];

    if (res1 < res2) return -1;
    if (res1 > res2) return 1;
    return 0;
}

void sort_dictionary(data *dict, int length) {
    qsort(dict, length, sizeof(data), compare);
}

int main() {
    int length = 5;
    data dictionary[] = { 
        {{2, 5}, 0},
        {{3, 1}, 1}, 
        {{8, 9}, 2}, 
        {{4, 2}, 3}, 
        {{1, 7}, 4}
    };

    sort_dictionary(dictionary, length);

    for (int i = 0; i < length; i++) {
        printf("Key: [%d, %d], Value: %d\n", dictionary[i].key[0], dictionary[i].key[1], dictionary[i].val);
    }

    return 0;
}