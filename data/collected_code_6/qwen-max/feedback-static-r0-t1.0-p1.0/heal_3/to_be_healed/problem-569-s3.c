#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_strings(const void *a, const void *b) {
    return strcmp(*(char **)a, *(char **)b);
}

void sort_sublist(char ***list, int size) {
    for (int i = 0; i < size; i++) {
        if (list[i]) {
            qsort(list[i], size, sizeof(char *), compare_strings);
        }
    }
}

int main() {
    char *strings1[] = {"banana", "apple", "orange"};
    char *strings2[] = {"grape", "kiwi", "cherry", "avocado"};
    char *strings3[] = {"pear", NULL, "mango"};

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char *lists[3][5] = { {strings1[0], strings1[1], strings1[2], NULL, NULL},
                          {strings2[0], strings2[1], strings2[2], strings2[3], NULL},
                          {strings3[0], strings3[1], strings3[2], NULL, NULL} };
    const int sizes[] = {3, 4, 3};

    for (int i = 0; i < 3; i++) {
        sort_sublist((char ***)lists + i, sizes[i]);
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < sizes[i]; j++) {
            if (lists[i][j]) {
                printf("%s ", lists[i][j]);
            }
        }
        printf("\n");
    }

    return 0;
}