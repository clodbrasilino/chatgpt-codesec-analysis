#define _POSIX_C_SOURCE 200809L

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

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
    static const char *const dictionary[] = {
        "apple",
        "carrot",
        "blue",
        "dog",
        "table"
    };

    const size_t dictionary_size = sizeof(dictionary) / sizeof(dictionary[0]);
    char *key = NULL;
    size_t capacity = 0U;
    ssize_t length = getline(&key, &capacity, stdin);

    if (length < 0) {
        fputs(ferror(stdin) ? "Failed to read input.\n"
                           : "No input provided.\n",
              stderr);
        free(key);
        return EXIT_FAILURE;
    }

    while (length > 0 &&
           (key[(size_t)length - 1U] == '\n' ||
            key[(size_t)length - 1U] == '\r')) {
        key[--length] = '\0';
    }

    if (length == 0) {
        fputs("Key must not be empty.\n", stderr);
        free(key);
        return EXIT_FAILURE;
    }

    puts(dictionary_contains(dictionary, dictionary_size, key)
             ? "Key is present."
             : "Key is not present.");

    free(key);
    return EXIT_SUCCESS;
}