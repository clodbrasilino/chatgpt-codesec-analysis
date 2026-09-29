#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_leading_zeroes_ip(const char *ip) {
    if (ip == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(ip);
    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }

    size_t ri = 0;
    size_t i = 0;

    while (i < len) {
        size_t octet_start = i;
        while (i < len && ip[i] != '.') {
            i++;
        }
        size_t octet_end = i;

        size_t j = octet_start;
        while (j < octet_end && ip[j] == '0') {
            j++;
        }

        if (j >= octet_end) {
            result[ri++] = '0';
        } else {
            while (j < octet_end) {
                result[ri++] = ip[j++];
            }
        }

        if (i < len && ip[i] == '.') {
            result[ri++] = '.';
            i++;
        }
    }

    result[ri] = '\0';
    return result;
}

int main(void) {
    const char *test_cases[] = {
        "192.168.001.010",
        "010.000.001.000",
        "0.0.0.0",
        "001.002.003.004",
        "255.255.255.255",
        ""
    };

    size_t num_tests = sizeof(test_cases) / sizeof(test_cases[0]);

    for (size_t t = 0; t < num_tests; t++) {
        char *result = remove_leading_zeroes_ip(test_cases[t]);
        if (result != NULL) {
            printf("Input:  \"%s\"\n", test_cases[t]);
            printf("Output: \"%s\"\n\n", result);
            free(result);
        }
    }

    /* Possible weaknesses found:
     *  Variable 'null_result' can be declared as pointer to const [constVariablePointer]
     *  Calling function 'remove_leading_zeroes_ip' returns 0
     *  Assignment 'null_result=remove_leading_zeroes_ip(NULL)', assigned value is 0
     */
    char *null_result = remove_leading_zeroes_ip(NULL);
    /* Possible weaknesses found:
     *  Condition 'null_result==NULL' is always true [knownConditionTrueFalse]
     *  Condition 'null_result==NULL' is always true
     */
    if (null_result == NULL) {
        printf("NULL input handled correctly.\n");
    }

    return 0;
}