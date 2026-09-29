#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_strings(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

void sort_sublists(char ***list, const int *sizes, int num_sublists) {
    for (int i = 0; i < num_sublists; i++) {
        if (sizes[i] > 1) {
            qsort(list[i], sizes[i], sizeof(char *), compare_strings);
        }
    }
}

int main() {
    int num_sublists = 3;
    const int sizes[] = {3, 2, 4};

    char **list[3];

    list[0] = malloc(3 * sizeof(char *));
    list[0][0] = "banana";
    list[0][1] = "apple";
    list[0][2] = "cherry";

    list[1] = malloc(2 * sizeof(char *));
    list[1][0] = "dog";
    list[1][1] = "cat";

    list[2] = malloc(4 * sizeof(char *));
    list[2][0] = "zebra";
    list[2][1] = "tiger";
    list[2][2] = "lion";
    list[2][3] = "antelope";

    sort_sublists(list, sizes, num_sublists);

    for (int i = 0; i < num_sublists; i++) {
        for (int j = 0; j < sizes[i]; j++) {
            printf("%s ", list[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < num_sublists; i++) {
        free(list[i]);
    }

    return 0;
}