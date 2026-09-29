#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected ['RES IS ', 'IS BEST ', 'BEST FOR ', 'FOR ALL ', 'ALL QESR'], got <no output>
  *  test case 2 failed: expected ['MSAMIS ', 'IS BEST ', 'BEST FOR ', 'FOR ALL ', 'ALL SKD'], got <no output>
  *  test case 0 failed: expected ['DSP IS ', 'IS BEST ', 'BEST FOR ', 'FOR ALL ', 'ALL UTS'], got <no output>
  */

char* concat_adjacent_elements(const char* const* tuple, int size) {
    if (tuple == NULL || size <= 0) {
        return NULL;
    }

    size_t total_length = 0;
    size_t* lengths = (size_t*)malloc((size_t)size * sizeof(size_t));
    if (lengths == NULL) {
        return NULL;
    }

    for (int i = 0; i < size; i++) {
        if (tuple[i] == NULL) {
            free(lengths);
            return NULL;
        }
        size_t len = strnlen(tuple[i], total_length + size * 256);
        lengths[i] = len;
        total_length += len;
    }

    char* result = (char*)malloc(total_length + 1);
    if (result == NULL) {
        free(lengths);
        return NULL;
    }

    size_t pos = 0;
    for (int i = 0; i < size; i++) {
        if (pos + lengths[i] > total_length) {
            free(lengths);
            free(result);
            return NULL;
        }
        if (lengths[i] > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(result + pos, tuple[i], lengths[i]);
            result[pos + lengths[i]] = '\0';
        }
        pos += lengths[i];
    }
    result[pos] = '\0';

    free(lengths);
    return result;
}

int main(void) {
    const char* tuple1[] = {"DSP IS ", "IS BEST ", "BEST FOR ", "FOR ALL ", "ALL UTS"};
    int size1 = sizeof(tuple1) / sizeof(tuple1[0]);

    char* result1 = concat_adjacent_elements(tuple1, size1);
    if (result1 != NULL) {
        printf("%s\n", result1);
        free(result1);
    }

    const char* tuple2[] = {"RES IS ", "IS BEST ", "BEST FOR ", "FOR ALL ", "ALL QESR"};
    int size2 = sizeof(tuple2) / sizeof(tuple2[0]);

    char* result2 = concat_adjacent_elements(tuple2, size2);
    if (result2 != NULL) {
        printf("%s\n", result2);
        free(result2);
    }

    const char* tuple3[] = {"MSAMIS ", "IS BEST ", "BEST FOR ", "FOR ALL ", "ALL SKD"};
    int size3 = sizeof(tuple3) / sizeof(tuple3[0]);

    char* result3 = concat_adjacent_elements(tuple3, size3);
    if (result3 != NULL) {
        printf("%s\n", result3);
        free(result3);
    }

    return 0;
}