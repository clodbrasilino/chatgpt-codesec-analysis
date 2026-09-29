#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static char *duplicate_string(const char *source)
{
    size_t length;
    char *copy;

    if (source == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    length = strlen(source) + 1U;
    copy = malloc(length);
    if (copy == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, source, length);
    return copy;
}

size_t remove_words_containing(char **words, size_t count, const char *substring)
{
    size_t read_index;
    size_t write_index;

    if (words == NULL || substring == NULL || substring[0] == '\0') {
        return 0U;
    }

    write_index = 0U;
    for (read_index = 0U; read_index < count; read_index++) {
        if (words[read_index] == NULL) {
            continue;
        }
        if (strstr(words[read_index], substring) != NULL) {
            free(words[read_index]);
            words[read_index] = NULL;
        } else {
            words[write_index] = words[read_index];
            if (write_index != read_index) {
                words[read_index] = NULL;
            }
            write_index++;
        }
    }

    return write_index;
}

void free_word_list(char **words, size_t count)
{
    size_t index;

    if (words == NULL) {
        return;
    }

    for (index = 0U; index < count; index++) {
        free(words[index]);
        words[index] = NULL;
    }

    free(words);
}

int main(void)
{
    const char *initial_words[] = {
        "apple", "banana", "grape", "kiwi", "orange", "mango", "peach"
    };
    const size_t count = sizeof(initial_words) / sizeof(initial_words[0]);
    size_t new_count;
    size_t index;
    char **words;

    words = calloc(count, sizeof(*words));
    if (words == NULL) {
        fprintf(stderr, "Failed to allocate word list\n");
        return EXIT_FAILURE;
    }

    for (index = 0U; index < count; index++) {
        words[index] = duplicate_string(initial_words[index]);
        if (words[index] == NULL) {
            fprintf(stderr, "Failed to allocate word\n");
            free_word_list(words, count);
            return EXIT_FAILURE;
        }
    }

    printf("Before removal:\n");
    for (index = 0U; index < count; index++) {
        printf("%s\n", words[index]);
    }

    new_count = remove_words_containing(words, count, "an");

    printf("\nAfter removing words containing \"an\":\n");
    for (index = 0U; index < new_count; index++) {
        printf("%s\n", words[index]);
    }

    new_count = remove_words_containing(words, new_count, "g");

    printf("\nAfter removing words containing 'g':\n");
    for (index = 0U; index < new_count; index++) {
        printf("%s\n", words[index]);
    }

    free_word_list(words, count);

    return EXIT_SUCCESS;
}