#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

void sort_sublists(char *list[][10], int num_lists, const int sublist_sizes[]) {
    for (int i = 0; i < num_lists; ++i) {
        qsort(list[i], sublist_sizes[i], sizeof(char *), compare);
    }
}

int main() {
    char *list1[] = {"banana", "apple", "cherry"};
    char *list2[] = {"dog", "cat", "elephant", "bird"};
    char *list3[] = {"red", "blue", "green", "yellow"};

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char *list[3][10] = {0};

    /* Possible weaknesses found:
     *  outer condition: i<3
     */
    for (int i = 0; i < 3; i++) {
        /* Possible weaknesses found:
         *  Identical inner 'if' condition is always true. [identicalInnerCondition]
         *  identical inner condition: i<3
         */
        if (i < 3) list[0][i] = list1[i];
    }

    /* Possible weaknesses found:
     *  Assuming that condition 'i<4' is not redundant
     */
    for (int i = 0; i < 4; i++) {
        /* Possible weaknesses found:
         *  Condition 'i<10' is always true
         *  Condition 'i<10' is always true [knownConditionTrueFalse]
         */
        if (i < 10) list[1][i] = list2[i];
    }

    /* Possible weaknesses found:
     *  Assuming that condition 'i<4' is not redundant
     */
    for (int i = 0; i < 4; i++) {
        /* Possible weaknesses found:
         *  Condition 'i<10' is always true
         *  Condition 'i<10' is always true [knownConditionTrueFalse]
         */
        if (i < 10) list[2][i] = list3[i];
    }

    const int sublist_sizes[] = {3, 4, 4};
    int num_lists = 3;

    sort_sublists(list, num_lists, sublist_sizes);

    for (int i = 0; i < num_lists; ++i) {
        for (int j = 0; j < sublist_sizes[i]; ++j) {
            printf("%s ", list[i][j]);
        }
        printf("\n");
    }

    return 0;
}