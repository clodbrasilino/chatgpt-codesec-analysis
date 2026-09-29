#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sort_sublists(char ****list_of_lists, const int *sublist_sizes, int num_sublists) {
    if (!list_of_lists || !(*list_of_lists) || !sublist_sizes || num_sublists <= 0) {
        return;
    }

    for (int i = 0; i < num_sublists; i++) {
        if (!(*list_of_lists)[i] || sublist_sizes[i] <= 0) {
            continue;
        }

        for (int j = 0; j < sublist_sizes[i] - 1; j++) {
            for (int k = j + 1; k < sublist_sizes[i]; k++) {
                if ((*list_of_lists)[i][j] && (*list_of_lists)[i][k]) {
                    if (strcmp((*list_of_lists)[i][j], (*list_of_lists)[i][k]) > 0) {
                        char *temp = (*list_of_lists)[i][j];
                        (*list_of_lists)[i][j] = (*list_of_lists)[i][k];
                        (*list_of_lists)[i][k] = temp;
                    }
                }
            }
        }
    }
}

int main(void) {
    int num_sublists = 2;
    int sublist_sizes[] = {3, 2};

    char ***list_of_lists = (char ***)calloc((size_t)num_sublists, sizeof(char **));
    if (!list_of_lists) {
        return 1;
    }

    for (int i = 0; i < num_sublists; i++) {
        if (sublist_sizes[i] > 0) {
            list_of_lists[i] = (char **)calloc((size_t)sublist_sizes[i], sizeof(char *));
            if (!list_of_lists[i]) {
                for (int j = 0; j < i; j++) {
                    free(list_of_lists[j]);
                }
                free(list_of_lists);
                return 1;
            }
        }
    }

    list_of_lists[0][0] = strdup("zebra");
    list_of_lists[0][1] = strdup("apple");
    list_of_lists[0][2] = strdup("mango");

    list_of_lists[1][0] = strdup("yellow");
    list_of_lists[1][1] = strdup("blue");

    for (int i = 0; i < num_sublists; i++) {
        for (int j = 0; j < sublist_sizes[i]; j++) {
            if (!list_of_lists[i][j]) {
                for (int k = 0; k <= i; k++) {
                    int limit = (k == i) ? j : sublist_sizes[k];
                    for (int l = 0; l < limit; l++) {
                        free(list_of_lists[k][l]);
                    }
                    free(list_of_lists[k]);
                }
                free(list_of_lists);
                return 1;
            }
        }
    }

    sort_sublists(&list_of_lists, sublist_sizes, num_sublists);

    for (int i = 0; i < num_sublists; i++) {
        for (int j = 0; j < sublist_sizes[i]; j++) {
            if (list_of_lists[i][j]) {
                printf("%s ", list_of_lists[i][j]);
                free(list_of_lists[i][j]);
            }
        }
        printf("\n");
        free(list_of_lists[i]);
    }
    free(list_of_lists);

    return 0;
}