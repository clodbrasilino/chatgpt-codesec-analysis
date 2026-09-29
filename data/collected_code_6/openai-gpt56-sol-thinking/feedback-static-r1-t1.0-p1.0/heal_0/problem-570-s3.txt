#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int remove_words_containing(const char **words, size_t *count, const char *pattern)
{
    size_t read_index;
    size_t write_index = 0;

    if (count == NULL || pattern == NULL || pattern[0] == '\0') {
        return -1;
    }

    if (*count > 0 && words == NULL) {
        return -1;
    }

    for (read_index = 0; read_index < *count; ++read_index) {
        if (words[read_index] == NULL) {
            return -1;
        }
    }

    for (read_index = 0; read_index < *count; ++read_index) {
        if (strstr(words[read_index], pattern) == NULL) {
            words[write_index++] = words[read_index];
        }
    }

    for (read_index = write_index; read_index < *count; ++read_index) {
        words[read_index] = NULL;
    }

    *count = write_index;
    return 0;
}

int main(void)
{
    const char *words[] = {
        "apple",
        "banana",
        "cherry",
        "grape",
        "orange",
        "pear"
    };
    const char *pattern = "an";
    size_t count = sizeof(words) / sizeof(words[0]);
    size_t index;

    if (remove_words_containing(words, &count, pattern) != 0) {
        fputs("Failed to remove words.\n", stderr);
        return EXIT_FAILURE;
    }

    for (index = 0; index < count; ++index) {
        puts(words[index]);
    }

    return EXIT_SUCCESS;
}