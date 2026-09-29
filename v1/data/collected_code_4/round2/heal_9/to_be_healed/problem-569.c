#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sortSublist(char ***list, int row, int col) {
    int i, j, k;
    char *temp;
    for (i = 0; i < row; i++) {
        for (j = 0; j < col - 1; j++) {
            for (k = j + 1; k < col; k++) {
                if (strcmp(list[i][j], list[i][k]) > 0) {
                    temp = list[i][j];
                    list[i][j] = list[i][k];
                    list[i][k] = temp;
                }
            }
        }
    }
}

void freeMemory(char*** list, int row, int col) {
    int i, j;
    for (i = 0; i < row; i++) {
        for(j = 0; j < col; j++) {
            free(list[i][j]);
        }
        free(list[i]);
    }
    free(list);
}

int main() {
    int i, j;
    int row = 3;
    int col = 4;
    char ***list;

    list = malloc(row * sizeof(char**));
    if (!list) return 1;

    for (i = 0; i < row; i++) {
        list[i] = malloc(col * sizeof(char*));
        if (!list[i]) {
            for (int k = i - 1; k >= 0; k--) {
                /* Possible weaknesses found:
                 *  leak of '<unknown>' [CWE-401] [-Wanalyzer-malloc-leak]
                 */
                free(list[k]);
            }
            free(list);
            return 1;
        }

        for (j = 0; j < col; j++) {
            list[i][j] = malloc(50 * sizeof(char));
            if (!list[i][j]) {
                for (int k = j - 1; k >= 0; k--) {
                    free(list[i][k]);
                }
                free(list[i]);
                for (int k = i - 1; k >= 0; k--) {
                    for(int l = col - 1; l >= 0; l--) {
                        free(list[k][l]);
                    }
                    free(list[k]);
                }
                free(list);
                return 1;
            }
        }
    }

    strcpy(list[0][0], "bbb");
    strcpy(list[0][1], "aaa");
    strcpy(list[0][2], "ddd");
    strcpy(list[0][3], "ccc");

    strcpy(list[1][0], "zzz");
    strcpy(list[1][1], "xxx");
    strcpy(list[1][2], "ggg");
    strcpy(list[1][3], "ttt");

    strcpy(list[2][0], "rrr");
    strcpy(list[2][1], "mmm");
    strcpy(list[2][2], "qqq");
    strcpy(list[2][3], "ppp");

    sortSublist(list, row, col);

    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            printf("%s ", list[i][j]);
        }
        printf("\n");
    }

    freeMemory(list, row, col);

    return 0;
}