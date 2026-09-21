#define _GNU_SOURCE
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concat_tuple(const char *elements[], size_t count, const char *delimiter) {
    if ((elements == NULL && count > 0) || (delimiter == NULL && count > 1)) {
        return NULL;
    }

    if (count == 0) {
        char *result = malloc(1);
        if (result != NULL) {
            result[0] = '\0';
        }
        return result;
    }

    const char *safe_delim = (delimiter == NULL) ? "" : delimiter;

    char *buf = NULL;
    size_t size = 0;
    FILE *stream = open_memstream(&buf, &size);
    if (stream == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < count; i++) {
        if (elements[i] == NULL) {
            fclose(stream);
            return NULL;
        }

        if (fputs(elements[i], stream) == EOF) {
            fclose(stream);
            return NULL;
        }

        if (i < count - 1) {
            if (fputs(safe_delim, stream) == EOF) {
                fclose(stream);
                return NULL;
            }
        }
    }

    if (fclose(stream) != 0) {
        return NULL;
    }

    return buf;
}

int main(void) {
    const char *tuple[] = {"apple", "banana", "cherry"};
    char *joined = concat_tuple(tuple, 3, ", ");
    if (joined == NULL) {
        return EXIT_FAILURE;
    }

    printf("%s\n", joined);
    free(joined);

    return EXIT_SUCCESS;
}