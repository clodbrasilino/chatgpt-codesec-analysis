#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>
 /* Possible weaknesses found:
  *  test case 1 failed: expected 'Not Possible', got -1
  */

int min_swaps(const char *str1, const char *str2) {
    size_t i = 0;
    int mismatch_1_to_0 = 0;
    int mismatch_0_to_1 = 0;

    if (str1 == NULL || str2 == NULL) {
        return -1;
    }

    while (str1[i] != '\0' && str2[i] != '\0') {
        if ((str1[i] != '0' && str1[i] != '1') || (str2[i] != '0' && str2[i] != '1')) {
            return -1;
        }

        if (str1[i] != str2[i]) {
            if (str1[i] == '1') {
                mismatch_1_to_0++;
            } else {
                mismatch_0_to_1++;
            }
        }
        i++;
    }

    if (str1[i] != '\0' || str2[i] != '\0') {
        return -1;
    }

    if (mismatch_1_to_0 != mismatch_0_to_1) {
        return -1;
    }

    return mismatch_1_to_0;
}

char* read_word(void) {
    size_t cap = 1024;
    size_t len = 0;
    char *str = malloc(cap);
    int c;

    if (!str) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((c = fgetc(stdin)) != EOF && isspace(c)) {
    }

    if (c == EOF) {
        free(str);
        return NULL;
    }

    do {
        if (len + 1 >= cap) {
            cap *= 2;
            char *tmp = realloc(str, cap);
            if (!tmp) {
                free(str);
                return NULL;
            }
            str = tmp;
        }
        str[len++] = (char)c;
    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    } while ((c = fgetc(stdin)) != EOF && !isspace(c));

    str[len] = '\0';
    return str;
}

int main(void) {
    char *str1 = read_word();
    char *str2 = read_word();

    if (str1 && str2) {
        int result = min_swaps(str1, str2);

        if (result != -1) {
            printf("%d\n", result);
        } else {
            printf("Not Possible\n");
        }
    } else {
        printf("Not Possible\n");
    }

    free(str1);
    free(str2);

    return 0;
}