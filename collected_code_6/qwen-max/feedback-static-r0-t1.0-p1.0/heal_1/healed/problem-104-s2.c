#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compare_strings(const void *a, const void *b) {
    return strcmp(*(const char *const *)a, *(const char *const *)b);
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

    list[0] = (char *[]){
        "banana",
        "apple",
        "cherry"
    };
    list[1] = (char *[]){
        "dog",
        "cat"
    };
    list[2] = (char *[]){
        "zebra",
        "tiger",
        "lion",
        "antelope"
    };

    sort_sublists(list, sizes, num_sublists);

    for (int i = 0; i < num_sublists; i++) {
        for (int j = 0; j < sizes[i]; j++) {
            printf("%s ", list[i][j]);
        }
        printf("\n");
    }

    return 0;
}