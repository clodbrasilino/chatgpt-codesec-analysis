#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concat_adjacent(const char *s1, const char *s2) {
    int length = strlen(s1) + strlen(s2) + 1;
    char *result = (char *)malloc(length * sizeof(char));
    if (result == NULL) {
        return NULL;
    }
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

void free_tuples(char **tuples, int n) {
    for (int i = 0; i < n; i++) {
        if (tuples[i] != NULL) {
            free(tuples[i]);
        }
    }
    free(tuples);
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['MSAMIS ', 'IS BEST ', 'BEST FOR ', 'FOR ALL ', 'ALL SKD'], got <no output>
  *  test case 0 failed: expected ['DSP IS ', 'IS BEST ', 'BEST FOR ', 'FOR ALL ', 'ALL UTS'], got <no output>
  *  test case 1 failed: expected ['RES IS ', 'IS BEST ', 'BEST FOR ', 'FOR ALL ', 'ALL QESR'], got <no output>
  */

char **concatenate_adjacent_elements(char **tuples, int n, int *new_n) {
    if (n < 2) {
        *new_n = n;
        return tuples;
    }

    *new_n = n - 1;
    char **result = (char **)malloc((*new_n) * sizeof(char *));
    if (result == NULL) {
        return NULL;
    }

    for (int i = 0; i < *new_n; i++) {
        result[i] = concat_adjacent(tuples[i], tuples[i + 1]);
        if (result[i] == NULL) {
            free_tuples(result, i);
            return NULL;
        }
    }

    free_tuples(tuples, n);
    return result;
}

int main() {
    char *tuples[] = {"RES IS ", "IS BEST ", "BEST FOR ", "FOR ALL ", "ALL QESR"};
    int n = 5;
    int new_n;

    char **new_tuples = concatenate_adjacent_elements(tuples, n, &new_n);

    if (new_tuples != NULL) {
        for (int i = 0; i < new_n; i++) {
            printf("%s\n", new_tuples[i]);
            free(new_tuples[i]);
        }
        free(new_tuples);
    } else {
        printf("Error: Memory allocation failed.\n");
    }

    return 0;
}