#include <stdio.h>
#include <stdlib.h>

typedef struct List {
    int *data;
    size_t size;
} List;

int countMatchingPairs(List list1, List list2, List list3) {
    int count = 0;
    for (size_t i = 0; i < list1.size && i < list2.size && i < list3.size; ++i) {
        if (list1.data[i] == list2.data[i] && list2.data[i] == list3.data[i]) {
            count++;
        }
    }
    return count;
}

int main() {
    List list1 = { .data = (int[]){1, 2, 3, 4, 5}, .size = 5 };
    List list2 = { .data = (int[]){1, 2, 6, 4, 7}, .size = 5 };
    List list3 = { .data = (int[]){1, 2, 9, 4, 10}, .size = 5 };

    int result = countMatchingPairs(list1, list2, list3);
    printf("Number of matching pairs: %d\n", result);

    return 0;
}