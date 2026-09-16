#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int remove_words_containing(char **words, size_t *count, const char *target)
{
    size_t read_index;
    size_t write_index = 0;
    size_t original_count;

    if (words == NULL || count == NULL || target == NULL || target[0] == '\0') {
        return -1;
    }

    original_count = *count;

    for (read_index = 0; read_index < original_count; ++read_index) {
        if (words[read_index] == NULL) {
            return -1;
        }
    }

    for (read_index = 0; read_index < original_count; ++read_index) {
        if (strstr(words[read_index], target) == NULL) {
            words[write_index++] = words[read_index];
        }
    }

    for (read_index = write_index; read_index < original_count; ++read_index) {
        words[read_index] = NULL;
    }

    *count = write_index;
    return 0;
}

int main(int argc, char *argv[])
{
    char **words;
    const char *target;
    size_t count;
    size_t index;

    if (argc < 3) {
        fprintf(stderr, "Usage: %s <character-or-string> <word> [word ...]\n", argv[0]);
        return EXIT_FAILURE;
    }

    target = argv[1];
    words = &argv[2];
    count = (size_t)(argc - 2);

    if (remove_words_containing(words, &count, target) != 0) {
        fprintf(stderr, "Failed to remove words\n");
        return EXIT_FAILURE;
    }

    for (index = 0; index < count; ++index) {
        puts(words[index]);
    }

    return EXIT_SUCCESS;
}