#include <stdio.h>

typedef struct {
    int* list;
    int size;
} Tuple;

int countLists(Tuple* tuples, int size) {
    int count = 0;
    for(int i = 0; i < size; i++) {
        if(tuples[i].list != NULL) {
            count++;
        }
    }
    return count;
}

int main() {
    int list1[] = {1, 2, 3};
    int list2[] = {4, 5, 6, 7, 8};
    int list3[] = {9, 10};

    Tuple tuples[3] = {
        {list1, sizeof(list1)/sizeof(int)},
        {list2, sizeof(list2)/sizeof(int)},
        {list3, sizeof(list3)/sizeof(int)}
    };

    printf("Number of lists in tuple: %d\n", countLists(tuples, 3));

    return 0;
}