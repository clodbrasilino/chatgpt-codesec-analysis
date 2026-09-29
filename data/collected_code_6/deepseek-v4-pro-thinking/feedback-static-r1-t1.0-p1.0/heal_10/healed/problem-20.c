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
    char buffer[MAX_LINE_LENGTH + 2];
    if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
        return NULL;
    }

    size_t len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n') {
        buffer[--len] = '\0';
    } else {
        if (len == MAX_LINE_LENGTH + 1) {
            int c;
            while ((c = getchar()) != EOF && c != '\n');
            return NULL;
        }
    }

    char *result = malloc(len + 1);
    if (result == NULL) {
        return NULL;
    }
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