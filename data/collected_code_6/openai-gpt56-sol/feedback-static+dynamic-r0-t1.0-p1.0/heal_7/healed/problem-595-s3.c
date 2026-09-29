#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <ctype.h>

#define MAX_LENGTH ((size_t)100000)

static int minimum_swaps(const char *source, const char *target,
                         size_t length, size_t *result)
{
    size_t mismatches_01 = 0;
    size_t mismatches_10 = 0;

    if (source == NULL || target == NULL || result == NULL) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        if ((source[i] != '0' && source[i] != '1') ||
            (target[i] != '0' && target[i] != '1')) {
            return -1;
        }

        if (source[i] == '0' && target[i] == '1') {
            ++mismatches_01;
        } else if (source[i] == '1' && target[i] == '0') {
            ++mismatches_10;
        }
    }

    if (mismatches_01 != mismatches_10) {
        return 1;
    }

    *result = mismatches_01;
    return 0;
}

static int read_binary_string(char **output, size_t *length)
{
    char *buffer;
    char line[MAX_LENGTH + 3];
    size_t used = 0;
    int c;

    if (output == NULL || length == NULL) {
        return -1;
    }

    *output = NULL;
    *length = 0;

    do {
        c = fgetc(stdin);
        if (c == EOF) {
            return -1;
        }
    } while (isspace((unsigned char)c));

    if (ungetc(c, stdin) == EOF) {
        return -1;
    }

    if (fgets(line, sizeof(line), stdin) == NULL) {
        return -1;
    }

    while (line[used] != '\0' &&
           !isspace((unsigned char)line[used])) {
        if (line[used] != '0' && line[used] != '1') {
            return -1;
        }
        ++used;
    }

    if (used == 0 || used > MAX_LENGTH) {
        return -1;
    }

    if (line[used] != '\0') {
        for (size_t i = used; line[i] != '\0'; ++i) {
            if (!isspace((unsigned char)line[i])) {
                return -1;
            }
        }
    } else if (used == MAX_LENGTH + 2) {
        return -1;
    } else if (used == MAX_LENGTH + 1) {
        c = fgetc(stdin);
        if (c != EOF && !isspace((unsigned char)c)) {
            while ((c = fgetc(stdin)) != EOF && !isspace((unsigned char)c)) {
            }
            return -1;
        }
        if (c == EOF && ferror(stdin)) {
            return -1;
        }
        return -1;
    } else if (line[used] == '\0' && used > 0 &&
               line[used - 1] != '\n' && !feof(stdin)) {
        c = fgetc(stdin);
        if (c != EOF && !isspace((unsigned char)c)) {
            while ((c = fgetc(stdin)) != EOF && !isspace((unsigned char)c)) {
            }
            return -1;
        }
        if (c == EOF && ferror(stdin)) {
            return -1;
        }
    }

    buffer = malloc(used + 1);
    if (buffer == NULL) {
        return -1;
    }

    for (size_t i = 0; i < used; ++i) {
        buffer[i] = line[i];
    }
    buffer[used] = '\0';

    *output = buffer;
    *length = used;
    return 0;
}

static int only_trailing_whitespace(void)
{
    char buffer[4096];

    while (fgets(buffer, sizeof(buffer), stdin) != NULL) {
        for (size_t i = 0; buffer[i] != '\0'; ++i) {
            if (!isspace((unsigned char)buffer[i])) {
                return 0;
            }
        }
    }

    return ferror(stdin) ? -1 : 1;
}

int main(void)
{
    char *source = NULL;
    char *target = NULL;
    size_t source_length = 0;
    size_t target_length = 0;
    size_t swaps = 0;
    int status;
    int trailing_status;

    if (read_binary_string(&source, &source_length) != 0 ||
        read_binary_string(&target, &target_length) != 0) {
        free(source);
        free(target);
        fputs("Failed to read two binary strings.\n", stderr);
        return EXIT_FAILURE;
    }

    trailing_status = only_trailing_whitespace();
    if (trailing_status <= 0) {
        free(source);
        free(target);
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (source_length != target_length) {
        free(source);
        free(target);
        puts("-1");
        return EXIT_SUCCESS;
    }

    status = minimum_swaps(source, target, source_length, &swaps);

    free(source);
    free(target);

    if (status < 0) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (status > 0) {
        puts("-1");
    } else {
        printf("%zu\n", swaps);
    }

    return EXIT_SUCCESS;
}