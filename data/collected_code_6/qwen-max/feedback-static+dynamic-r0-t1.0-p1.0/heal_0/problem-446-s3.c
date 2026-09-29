#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *elements;
    size_t count;
} List;

typedef struct {
    int *elements;
    size_t count;
} Tuple;

int countOccurrences(List list, Tuple tuple) {
    int count = 0;
    for (size_t i = 0; i < list.count; ++i) {
        for (size_t j = 0; j < tuple.count; ++j) {
            if (list.elements[i] == tuple.elements[j]) {
                ++count;
                break;
            }
        }
    }
    return count;
}

int main() {
    int listData[] = {1, 2, 3, 4, 5};
    int tupleData[] = {3, 4, 1, 6, 7, 1};

    List list = {listData, sizeof(listData) / sizeof(listData[0])};
    Tuple tuple = {tupleData, sizeof(tupleData) / sizeof(tupleData[0])};

    int occurrences = countOccurrences(list, tuple);
    printf("Number of occurrences: %d\n", occurrences);

    return 0;
}