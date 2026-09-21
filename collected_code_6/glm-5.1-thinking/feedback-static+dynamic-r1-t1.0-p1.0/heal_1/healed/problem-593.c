#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *remove_leading_zeroes_ip(const char *ip) {
    if (ip == NULL) {
        return NULL;
    }

    size_t len = 0;
    while (len < 256 && ip[len] != '\0') {
        len++;
    }

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

    const char *null_result = remove_leading_zeroes_ip(NULL);
    printf("NULL input handled correctly: %s\n", null_result == NULL ? "yes" : "no");

    return 0;
}