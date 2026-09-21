#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1048576

int isWoodall(unsigned long long number) {
    unsigned int n;
    unsigned int bits = (unsigned int)(sizeof(number) * CHAR_BIT);

    for (n = 1; n < bits; ++n) {
        unsigned long long power = 1ULL << n;

        if (power > ULLONG_MAX / n) {
            break;
        }

        unsigned long long woodall = n * power - 1;

        if (woodall == number) {
            return 1;
        }

        if (woodall > number) {
            break;
        }
    }

    return 0;
}

char *read_line(void) {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char buffer[MAX_LINE_LENGTH + 2];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[--len] = '\0';
    } else {
        if (len == MAX_LINE_LENGTH + 1) {
            int c;
            /* Possible weaknesses found:
             * Flawfinder getchar: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            while ((c = getchar()) != EOF && c != '\n');
            return NULL;
        }
    }

    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }
    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(result, buffer, len + 1);
    return result;
}

int main(void) {
    unsigned long long number;
    char *endptr;
    char *line = read_line();
    if (line == NULL) {
        return 1;
    }

    errno = 0;
    number = strtoull(line, &endptr, 10);

    if (errno == ERANGE || endptr == line || *endptr != '\0') {
        free(line);
        return 1;
    }

    free(line);

    printf("%s\n", isWoodall(number) ? "Yes" : "No");

    return 0;
}