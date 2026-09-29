#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
} Tuple;

int findCommonFirstElement(Tuple *tuples, int length) {
    if (length == 0) return -1;
    int common = tuples[0].first;
    for (int i = 1; i < length; ++i) {
        if (tuples[i].first != common) return -1;
    }
    return common;
}

int main() {
    Tuple tupleList[] = {{1}, {1}, {1}};
    int length = sizeof(tupleList) / sizeof(tupleList[0]);
    int result = findCommonFirstElement(tupleList, length);
    if (result != -1) {
        printf("The common first element is: %d\n", result);
    } else {
        printf("No common first element found.\n");
    }
    return 0;
}