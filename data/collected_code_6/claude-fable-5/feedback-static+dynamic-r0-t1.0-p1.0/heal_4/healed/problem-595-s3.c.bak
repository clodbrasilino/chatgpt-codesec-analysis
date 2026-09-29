#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *min_swaps(const char *s1, const char *s2)
{
    size_t len1;
    size_t len2;
    size_t i;
    long count01;
    long count10;
    char *result;
    int written;

    result = (char *)malloc(32U);
    if (result == NULL) {
        return NULL;
    }

    if (s1 == NULL || s2 == NULL) {
        if (snprintf(result, 32U, "Not Possible") < 0) {
            free(result);
            return NULL;
        }
        return result;
    }

    len1 = strlen(s1);
    len2 = strlen(s2);

    if (len1 != len2) {
        if (snprintf(result, 32U, "Not Possible") < 0) {
            free(result);
            return NULL;
        }
        return result;
    }

    count01 = 0L;
    count10 = 0L;

    for (i = 0U; i < len1; i++) {
        if ((s1[i] != '0' && s1[i] != '1') ||
            (s2[i] != '0' && s2[i] != '1')) {
            if (snprintf(result, 32U, "Not Possible") < 0) {
                free(result);
                return NULL;
            }
            return result;
        }
        if (s1[i] == '0' && s2[i] == '1') {
            count01++;
        } else if (s1[i] == '1' && s2[i] == '0') {
            count10++;
        }
    }

    if (count01 != count10) {
        if (snprintf(result, 32U, "Not Possible") < 0) {
            free(result);
            return NULL;
        }
        return result;
    }

    written = snprintf(result, 32U, "%ld", count01);
    if (written < 0) {
        free(result);
        return NULL;
    }

    return result;
}

int print_result(const char *result)
{
    if (result == NULL) {
        return -1;
    }

    if (strcmp(result, "Not Possible") == 0) {
        if (printf("Not Possible\n") < 0) {
            return -1;
        }
    } else {
        if (printf("Minimum swaps required: %s\n", result) < 0) {
            return -1;
        }
    }

    return 0;
}

int main(void)
{
    const char *a = "1101";
    const char *b = "1011";
    char *result;

    result = min_swaps(a, b);

    if (print_result(result) != 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}