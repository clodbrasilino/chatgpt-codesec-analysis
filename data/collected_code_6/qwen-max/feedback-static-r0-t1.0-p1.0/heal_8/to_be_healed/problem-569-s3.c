#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_strings(const void *a, const void *b) {
    return strcmp(*(char **)a, *(char **)b);
}

void sort_sublist(char **list, int size) {
    qsort(list, size, sizeof(char *), compare_strings);
}

int main() {
    char *strings1[] = {"banana", "apple", "orange", NULL};
    char *strings2[] = {"grape", "kiwi", "cherry", "avocado", NULL};
    char *strings3[] = {"pear", NULL, "mango", NULL};

    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char **lists[3] = { strings1, strings2, strings3 };
    const int sizes[] = {3, 4, 2};

    for (int i = 0; i < 3; i++) {
        if (sizes[i] > 0) {
            sort_sublist(lists[i], sizes[i]);
        }
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