#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DICTIONARY_SIZE 5U

static bool dictionary_contains(const char *const dictionary[],
                                size_t dictionary_size,
                                const char *key)
{
    if (dictionary == NULL || key == NULL) {
        return false;
    }

    for (size_t i = 0U; i < dictionary_size; ++i) {
        if (dictionary[i] != NULL && strcmp(dictionary[i], key) == 0) {
            return true;
        }
    }

    return false;
}

int main(void)
{
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    static const char *const dictionary[DICTIONARY_SIZE] = {
        "apple",
        "carrot",
        "blue",
        "dog",
        "table"
    };

    char *key = NULL;
    size_t capacity = 0U;
    ssize_t length = getline(&key, &capacity, stdin);

    if (length < 0) {
        if (ferror(stdin)) {
            fputs("Failed to read input.\n", stderr);
        } else {
            fputs("No input provided.\n", stderr);
        }
        free(key);
        return EXIT_FAILURE;
    }

    while (length > 0 && (key[length - 1] == '\n' || key[length - 1] == '\r')) {
        key[--length] = '\0';
    }

    if (length == 0) {
        fputs("Key must not be empty.\n", stderr);
        free(key);
        return EXIT_FAILURE;
    }

    puts(dictionary_contains(dictionary, DICTIONARY_SIZE, key)
             ? "Key is present."
             : "Key is not present.");

    free(key);
    return EXIT_SUCCESS;
}