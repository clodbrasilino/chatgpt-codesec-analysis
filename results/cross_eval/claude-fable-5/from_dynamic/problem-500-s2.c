#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *concatenate_list(const char *const *list, size_t count)
{
    size_t total = 0;
    size_t i;
    char *result = NULL;
    char *pos = NULL;

    if (list == NULL) {
        return NULL;
    }

    for (i = 0; i < count; i++) {
        size_t len;

        if (list[i] == NULL) {
            return NULL;
        }
        len = strlen(list[i]);
        if (total > SIZE_MAX - len - 1) {
            return NULL;
        }
        total += len;
    }

    result = malloc(total + 1);
    if (result == NULL) {
        return NULL;
    }

    pos = result;
    for (i = 0; i < count; i++) {
        size_t len = strlen(list[i]);
        memcpy(pos, list[i], len);
        pos += len;
    }
    *pos = '\0';

    return result;
}

int main(void)
{
    const char *const list[] = { "Hello", ", ", "world", "!" };
    size_t count = sizeof(list) / sizeof(list[0]);
    char *joined = concatenate_list(list, count);

    if (joined == NULL) {
        fprintf(stderr, "Concatenation failed\n");
        return EXIT_FAILURE;
    }

    if (printf("%s\n", joined) < 0) {
        free(joined);
        return EXIT_FAILURE;
    }

    free(joined);
    return EXIT_SUCCESS;
}