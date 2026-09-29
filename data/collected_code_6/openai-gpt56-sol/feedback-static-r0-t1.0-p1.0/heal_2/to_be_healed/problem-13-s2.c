#include <ctype.h>
#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *word;
    size_t count;
} WordCount;

static void free_word_counts(WordCount *words, size_t count)
{
    if (words == NULL) {
        return;
    }

    for (size_t i = 0; i < count; ++i) {
        free(words[i].word);
    }

    free(words);
}

static char *duplicate_string(const char *text, size_t length)
{
    if (text == NULL || length == SIZE_MAX) {
        return NULL;
    }

    char *copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    if (length > 0U) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, text, length);
    }
    copy[length] = '\0';

    return copy;
}

static int compare_words(const void *left, const void *right)
{
    const WordCount *a = left;
    const WordCount *b = right;

    return strcmp(a->word, b->word);
}

static int compare_counts(const void *left, const void *right)
{
    const WordCount *a = left;
    const WordCount *b = right;

    if (a->count < b->count) {
        return 1;
    }

    if (a->count > b->count) {
        return -1;
    }

    return strcmp(a->word, b->word);
}

static int grow_word_array(WordCount **words, size_t *capacity)
{
    size_t new_capacity;

    if (*capacity == 0U) {
        new_capacity = 16U;
    } else {
        if (*capacity > SIZE_MAX / 2U) {
            return -1;
        }
        new_capacity = *capacity * 2U;
    }

    if (new_capacity > SIZE_MAX / sizeof(**words)) {
        return -1;
    }

    WordCount *resized = realloc(*words, new_capacity * sizeof(**words));
    if (resized == NULL) {
        return -1;
    }

    *words = resized;
    *capacity = new_capacity;
    return 0;
}

static int add_word(WordCount **words, size_t *count, size_t *capacity,
                    const char *word, size_t length)
{
    if (words == NULL || count == NULL || capacity == NULL ||
        word == NULL || *count > *capacity) {
        return -1;
    }

    if (*count == *capacity && grow_word_array(words, capacity) != 0) {
        return -1;
    }

    char *copy = duplicate_string(word, length);
    if (copy == NULL) {
        return -1;
    }

    (*words)[*count].word = copy;
    (*words)[*count].count = 1U;
    ++*count;

    return 0;
}

static int grow_buffer(char **buffer, size_t *capacity, size_t required)
{
    if (buffer == NULL || capacity == NULL) {
        return -1;
    }

    size_t new_capacity = *capacity == 0U ? 64U : *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2U) {
            return -1;
        }
        new_capacity *= 2U;
    }

    char *resized = realloc(*buffer, new_capacity);
    if (resized == NULL) {
        return -1;
    }

    *buffer = resized;
    *capacity = new_capacity;
    return 0;
}

static int read_dictionary(FILE *stream, WordCount **result,
                           size_t *result_count)
{
    if (stream == NULL || result == NULL || result_count == NULL) {
        return -1;
    }

    *result = NULL;
    *result_count = 0U;

    WordCount *words = NULL;
    size_t count = 0U;
    size_t capacity = 0U;
    char *buffer = NULL;
    size_t length = 0U;
    size_t buffer_capacity = 0U;
    int character;

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((character = fgetc(stream)) != EOF) {
        unsigned char byte = (unsigned char)character;

        if (isalnum(byte) != 0 || character == '\'') {
            if (length == SIZE_MAX ||
                grow_buffer(&buffer, &buffer_capacity, length + 1U) != 0) {
                free(buffer);
                free_word_counts(words, count);
                return -1;
            }

            buffer[length++] = (char)tolower(byte);
        } else if (length > 0U) {
            if (add_word(&words, &count, &capacity, buffer, length) != 0) {
                free(buffer);
                free_word_counts(words, count);
                return -1;
            }

            length = 0U;
        }
    }

    if (ferror(stream) != 0) {
        free(buffer);
        free_word_counts(words, count);
        return -1;
    }

    if (length > 0U &&
        add_word(&words, &count, &capacity, buffer, length) != 0) {
        free(buffer);
        free_word_counts(words, count);
        return -1;
    }

    free(buffer);
    *result = words;
    *result_count = count;

    return 0;
}

static size_t count_common_words(WordCount *words, size_t count)
{
    if (words == NULL || count == 0U) {
        return 0U;
    }

    qsort(words, count, sizeof(*words), compare_words);

    size_t unique_count = 0U;

    for (size_t i = 0U; i < count;) {
        size_t next = i + 1U;

        while (next < count &&
               strcmp(words[i].word, words[next].word) == 0) {
            ++next;
        }

        char *representative = words[i].word;

        for (size_t j = i + 1U; j < next; ++j) {
            free(words[j].word);
            words[j].word = NULL;
        }

        words[unique_count].word = representative;
        words[unique_count].count = next - i;

        if (unique_count != i) {
            words[i].word = NULL;
        }

        ++unique_count;
        i = next;
    }

    qsort(words, unique_count, sizeof(*words), compare_counts);
    return unique_count;
}

static int parse_limit(const char *text, size_t *limit)
{
    if (text == NULL || limit == NULL || text[0] == '\0' ||
        !isdigit((unsigned char)text[0])) {
        return -1;
    }

    char *end = NULL;
    errno = 0;
    unsigned long long value = strtoull(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' || value == 0ULL ||
        value > (unsigned long long)SIZE_MAX) {
        return -1;
    }

    *limit = (size_t)value;
    return 0;
}

int main(int argc, char **argv)
{
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: %s <dictionary-file> [limit]\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t limit = 10U;

    if (argc == 3 && parse_limit(argv[2], &limit) != 0) {
        fprintf(stderr, "Invalid limit: %s\n", argv[2]);
        return EXIT_FAILURE;
    }

    /* Possible weaknesses found:
     * Flawfinder fopen: Check when opening files - can an attacker redirect it (via symlinks), force the opening of special file type (e.g., device files), move things around to create a race condition, control its ancestors, or change its contents? (CWE-362). (risk 2, misc)
     */
    FILE *stream = fopen(argv[1], "rb");
    if (stream == NULL) {
        fprintf(stderr, "Unable to open %s: %s\n", argv[1],
                strerror(errno));
        return EXIT_FAILURE;
    }

    WordCount *words = NULL;
    size_t count = 0U;
    int read_status = read_dictionary(stream, &words, &count);
    int saved_read_errno = errno;
    int close_status = fclose(stream);
    int saved_close_errno = errno;

    if (read_status != 0) {
        errno = saved_read_errno;
        fprintf(stderr, "Unable to read dictionary: %s\n", strerror(errno));
        free_word_counts(words, count);
        return EXIT_FAILURE;
    }

    if (close_status != 0) {
        errno = saved_close_errno;
        fprintf(stderr, "Unable to close dictionary: %s\n", strerror(errno));
        free_word_counts(words, count);
        return EXIT_FAILURE;
    }

    size_t unique_count = count_common_words(words, count);
    size_t output_count = unique_count < limit ? unique_count : limit;

    for (size_t i = 0U; i < output_count; ++i) {
        if (printf("%s %zu\n", words[i].word, words[i].count) < 0) {
            fprintf(stderr, "Unable to write output\n");
            free_word_counts(words, unique_count);
            return EXIT_FAILURE;
        }
    }

    if (fflush(stdout) == EOF) {
        fprintf(stderr, "Unable to write output\n");
        free_word_counts(words, unique_count);
        return EXIT_FAILURE;
    }

    free_word_counts(words, unique_count);
    return EXIT_SUCCESS;
}