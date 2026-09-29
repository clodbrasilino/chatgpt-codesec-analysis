#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_strings(const void *a, const void *b) {
    return strcmp(*(const char * const *)a, *(const char * const *)b);
}

/* Possible weaknesses found:
 *  expected 'char * const* const*' but argument is of type 'char * (*)[5]'
 */
void sort_sublists(char * const * const *list, const int *sizes, int num_sublists) {
    for (int i = 0; i < num_sublists; i++) {
        if (sizes[i] > 1) {
            qsort(list[i], sizes[i], sizeof(char *), compare_strings);
        }
    }
}

int main() {
    int num_sublists = 3;
    const int sizes[] = {3, 2, 4};
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char *list[3][5];

    list[0][0] = "banana";
    list[0][1] = "apple";
    list[0][2] = "cherry";

    list[1][0] = "dog";
    list[1][1] = "cat";

    list[2][0] = "zebra";
    list[2][1] = "tiger";
    list[2][2] = "lion";
    list[2][3] = "antelope";

    /* Possible weaknesses found:
     *  passing argument 1 of 'sort_sublists' from incompatible pointer type [-Wincompatible-pointer-types]
     */
    sort_sublists(list, sizes, num_sublists);

    for (int i = 0; i < num_sublists; i++) {
        for (int j = 0; j < sizes[i]; j++) {
            printf("%s ", list[i][j]);
        }
        printf("\n");
    }

    return 0;
}