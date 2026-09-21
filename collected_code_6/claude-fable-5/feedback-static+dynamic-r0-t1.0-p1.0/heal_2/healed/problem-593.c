#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_IP_LEN 64U

char *remove_leading_zeroes(const char *ip)
{
    char *result;
    size_t len;
    size_t i;
    size_t j;

    if (ip == NULL) {
        return NULL;
    }

    len = strnlen(ip, MAX_IP_LEN);
    if (len >= MAX_IP_LEN) {
        return NULL;
    }

    result = malloc(len + 1U);
    if (result == NULL) {
        return NULL;
    }

    i = 0;
    j = 0;
    while (i <= len) {
        size_t start;
        size_t end;
        size_t k;

        start = i;
        while ((i < len) && (ip[i] != '.')) {
            i++;
        }
        end = i;

        k = start;
        while ((end > start) && (k < end - 1U) && (ip[k] == '0')) {
            k++;
        }
        if (start == end) {
            k = start;
        }

        while (k < end) {
            result[j] = ip[k];
            j++;
            k++;
        }

        if (i < len) {
            result[j] = '.';
            j++;
        }
        i++;
    }

    result[j] = '\0';
    return result;
}

int main(void)
{
    const char *tests[] = {
        "192.168.001.010",
        "010.000.000.001",
        "255.255.255.255",
        "001.002.003.004",
        "0.0.0.0"
    };
    size_t count;
    size_t idx;

    count = sizeof(tests) / sizeof(tests[0]);

    for (idx = 0; idx < count; idx++) {
        char *cleaned;

        cleaned = remove_leading_zeroes(tests[idx]);
        if (cleaned == NULL) {
            (void)fprintf(stderr, "Memory allocation failed\n");
            return EXIT_FAILURE;
        }
        if (printf("%s -> %s\n", tests[idx], cleaned) < 0) {
            free(cleaned);
            return EXIT_FAILURE;
        }
        free(cleaned);
    }

    return EXIT_SUCCESS;
}