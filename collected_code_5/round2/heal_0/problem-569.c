#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sortSublist(char ***list, int row, int col) {
    int i, j, k;
    char temp[50];
    for (i = 0; i < row; i++) {
        for (j = 0; j < col - 1; j++) {
            for (k = j + 1; k < col; k++) {
                if (strcmp(list[i][j], list[i][k]) > 0) {
                    strcpy(temp, list[i][j]);
                    strcpy(list[i][j], list[i][k]);
                    strcpy(list[i][k], temp);
                }
            }
        }
    }
}

int main() {
    int i, j;
    int row = 3;
    int col = 4;
    char ***list = malloc(row * sizeof(char **));

    for (i = 0; i < row; i++) {
        list[i] = malloc(col * sizeof(char *));
        for (j = 0; j < col; j++) {
            list[i][j] = malloc(50 * sizeof(char));
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

    for (i = 0; i < row; i++) {
        for (j = 0; j < col; j++) {
            free(list[i][j]);
        }
        free(list[i]);
    }
    free(list);

    return 0;
}