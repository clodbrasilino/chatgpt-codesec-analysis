#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['MSAMIS ', 'IS BEST ', 'BEST FOR ', 'FOR ALL ', 'ALL SKD'], got <no output>
  *  test case 1 failed: expected ['RES IS ', 'IS BEST ', 'BEST FOR ', 'FOR ALL ', 'ALL QESR'], got <no output>
  *  test case 0 failed: expected ['DSP IS ', 'IS BEST ', 'BEST FOR ', 'FOR ALL ', 'ALL UTS'], got ["
  */

char *concat_adjacent_elements(char *tuple[], int size) {
    if (tuple == NULL || size <= 0) {
        return NULL;
    }

    int total_length = 0;
    for (int i = 0; i < size; i++) {
        if (tuple[i] == NULL) {
            return NULL;
        }
        total_length += strlen(tuple[i]);
    }

    char *result = (char *)malloc((total_length + 1) * sizeof(char));
    if (result == NULL) {
        return NULL;
    }

    int pos = 0;
    for (int i = 0; i < size; i++) {
        int len = strlen(tuple[i]);
        strcpy(result + pos, tuple[i]);
        pos += len;
    }
    result[pos] = '\0';

    return result;
}

int main(void) {
    char *tuple1[] = {"MSAMIS ", "IS BEST ", "BEST FOR ", "FOR ALL ", "ALL SKD"};
    int size1 = sizeof(tuple1) / sizeof(tuple1[0]);
    
    char *result1 = concat_adjacent_elements(tuple1, size1);
    if (result1 != NULL) {
        printf("%s\n", result1);
        free(result1);
    }

    char *tuple2[] = {"RES IS ", "IS BEST ", "BEST FOR ", "FOR ALL ", "ALL QESR"};
    int size2 = sizeof(tuple2) / sizeof(tuple2[0]);
    
    char *result2 = concat_adjacent_elements(tuple2, size2);
    if (result2 != NULL) {
        printf("%s\n", result2);
        free(result2);
    }

    char *tuple3[] = {"DSP IS ", "IS BEST ", "BEST FOR ", "FOR ALL ", "ALL UTS"};
    int size3 = sizeof(tuple3) / sizeof(tuple3[0]);
    
    char *result3 = concat_adjacent_elements(tuple3, size3);
    if (result3 != NULL) {
        printf("%s\n", result3);
        free(result3);
    }

    return 0;
}