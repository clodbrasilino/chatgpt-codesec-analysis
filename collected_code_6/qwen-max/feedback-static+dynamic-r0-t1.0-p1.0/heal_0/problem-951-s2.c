#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int max(int a, int b) {
    return a > b ? a : b;
}

Tuple* findMaxPairs(Tuple *list1, Tuple *list2, int length, int *resultLength) {
    *resultLength = length;
    Tuple *result = (Tuple *)malloc(length * sizeof(Tuple));
    if (result == NULL) {
        *resultLength = 0;
        return NULL;
    }
    for (int i = 0; i < length; i++) {
        result[i].first = max(list1[i].first, list2[i].first);
        result[i].second = max(list1[i].second, list2[i].second);
    }
    return result;
}

int main() {
    Tuple list1[] = {{1, 2}, {3, 4}, {5, 6}};
    Tuple list2[] = {{2, 1}, {4, 3}, {6, 5}};
    int len = 3;
    int resLen;
    Tuple *result = findMaxPairs(list1, list2, len, &resLen);
    if (result != NULL) {
        for (int i = 0; i < resLen; i++) {
            printf("(%d, %d)\n", result[i].first, result[i].second);
        }
        free(result);
    }
    return 0;
}