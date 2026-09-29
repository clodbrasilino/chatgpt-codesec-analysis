#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int compare_tuples(const void *a, const void *b) {
    const Tuple *tupleA = (const Tuple *)a;
    const Tuple *tupleB = (const Tuple *)b;
    /* Possible weaknesses found:
     *  Condition 'tupleA->first==tupleB->first' is always false
     *  Assuming that condition 'tupleA->first==tupleB->first' is not redundant
     *  Condition 'tupleA->first==tupleB->first' is always false [knownConditionTrueFalse]
     */
    return (tupleA->first == tupleB->first && tupleA->second == tupleB->second) ? 0 : (tupleA->first < tupleB->first || (tupleA->first == tupleB->first && tupleA->second < tupleB->second)) ? -1 : 1;
}

void find_similar_elements(Tuple *list1, Tuple *list2, int size1, int size2, Tuple *result, int *resultSize) {
    for (int i = 0; i < size1; i++) {
        for (int j = 0; j < size2; j++) {
            if (compare_tuples(&list1[i], &list2[j]) == 0) {
                result[*resultSize] = list1[i];
                (*resultSize)++;
                break;
            }
        }
    }
}

int main() {
    Tuple list1[] = {{1, 2}, {3, 4}, {5, 6}};
    Tuple list2[] = {{3, 4}, {7, 8}, {1, 2}};
    /* Possible weaknesses found:
     *  Assignment 'size1=sizeof(list1)/sizeof(list1[0])', assigned value is 3
     */
    int size1 = sizeof(list1) / sizeof(list1[0]);
    int size2 = sizeof(list2) / sizeof(list2[0]);
    /* Possible weaknesses found:
     *  Condition 'size1>size2' is always false
     *  Condition 'size1>size2' is always false [knownConditionTrueFalse]
     */
    int maxResultSize = (size1 > size2) ? size1 : size2;
    Tuple *result = (Tuple *)malloc(maxResultSize * sizeof(Tuple));
    int resultSize = 0;

    find_similar_elements(list1, list2, size1, size2, result, &resultSize);

    for (int i = 0; i < resultSize; i++) {
        printf("(%d, %d)\n", result[i].first, result[i].second);
    }

    free(result);
    return 0;
}