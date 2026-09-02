#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sort_sublist(char ***sublist, int size) {
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - 1 - i; j++) {
            if (strcmp((*sublist)[j], (*sublist)[j + 1]) > 0) {
                char *temp = (*sublist)[j];
                (*sublist)[j] = (*sublist)[j + 1];
                (*sublist)[j + 1] = temp;
            }
        }
    }
}

void sort_list_of_lists(char ****list, int num_sublists, const int *sizes) {
    for (int i = 0; i < num_sublists; i++) {
        sort_sublist(&(*list)[i], sizes[i]);
    }
}

int main() {
    int num_sublists = 3;
    const int sizes[] = {3, 2, 4};

    char ***list = (char ***)malloc(num_sublists * sizeof(char **));
    list[0] = (char **)malloc(3 * sizeof(char *));
    list[0][0] = "dog";
    list[0][1] = "cat";
    list[0][2] = "elephant";

    list[1] = (char **)malloc(2 * sizeof(char *));
    list[1][0] = "apple";
    list[1][1] = "banana";

    list[2] = (char **)malloc(4 * sizeof(char *));
    list[2][0] = "red";
    list[2][1] = "blue";
    list[2][2] = "green";
    list[2][3] = "yellow";

    sort_list_of_lists(&list, num_sublists, sizes);

    for (int i = 0; i < num_sublists; i++) {
        for (int j = 0; j < sizes[i]; j++) {
            printf("%s ", list[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < num_sublists; i++) {
        free(list[i]);
    }
    free(list);

    return 0;
}