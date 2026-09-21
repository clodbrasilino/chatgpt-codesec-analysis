#define _POSIX_C_SOURCE 200809L

#include <ctype.h>
#include <errno.h>
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

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
    if (text == NULL) {
        errno = EINVAL;
        return NULL;
    }

    if (length > SIZE_MAX - 1) {
        errno = EOVERFLOW;
        return NULL;
    }

    size_t allocation_size = length + 1;
    char *copy = malloc(allocation_size);

    if (copy == NULL) {
        return NULL;
    }

    if (length != 0) {
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
    if (words == NULL || capacity == NULL) {
        errno = EINVAL;
        return -1;
    }

    size_t new_capacity;

    if (*capacity == 0) {
        new_capacity = 16;
    } else {
        if (*capacity > SIZE_MAX / 2) {
            errno = EOVERFLOW;
            return -1;
        }

        new_capacity = *capacity * 2;
    }

    if (new_capacity > SIZE_MAX / sizeof **words) {
        errno = EOVERFLOW;
        return -1;
    }

    WordCount *resized = realloc(*words, new_capacity * sizeof **words);

    if (resized == NULL) {
        return -1;
    }

    *words = resized;
    *capacity = new_capacity;
    return 0;
}

static int add_word(WordCount **words, size_t *count, size_t *capacity,
                    const char *word, size_t word_length)
{
    if (words == NULL || count == NULL || capacity == NULL || word == NULL ||
        *count > *capacity) {
        errno = EINVAL;
        return -1;
    }

    if (*count == SIZE_MAX) {
        errno = EOVERFLOW;
        return -1;
    }

    if (*count == *capacity && grow_word_array(words, capacity) != 0) {
        return -1;
    }

    char *copy = duplicate_string(word, word_length);

    if (copy == NULL) {
        return -1;
    }

    (*words)[*count].word = copy;
    (*words)[*count].count = 1;
    ++*count;
    return 0;
}

static int grow_buffer(char **buffer, size_t *capacity, size_t required)
{
    if (buffer == NULL || capacity == NULL) {
        errno = EINVAL;
        return -1;
    }

    if (required <= *capacity) {
        return 0;
    }

    size_t new_capacity = *capacity == 0 ? 64 : *capacity;

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = required;
            break;
        }

        new_capacity *= 2;
    }

    if (new_capacity < required) {
        errno = EOVERFLOW;
        return -1;
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
        errno = EINVAL;
        return -1;
    }

    *result = NULL;
    *result_count = 0;

    WordCount *words = NULL;
    size_t count = 0;
    size_t words_capacity = 0;
    char *buffer = NULL;
    size_t length = 0;
    size_t buffer_capacity = 0;

    for (;;) {
        int character = fgetc(stream);

        if (character == EOF) {
            if (ferror(stream)) {
                goto failure;
            }

            break;
        }

        unsigned char byte = (unsigned char)character;

        if (isalnum(byte) != 0 || byte == (unsigned char)'\'') {
            if (length == SIZE_MAX) {
                errno = EOVERFLOW;
                goto failure;
            }

            size_t required = length + 1;

            if (grow_buffer(&buffer, &buffer_capacity, required) != 0) {
                goto failure;
            }

            buffer[length] = (char)tolower(byte);
            ++length;
        } else if (length != 0) {
            if (add_word(&words, &count, &words_capacity, buffer, length) != 0) {
                goto failure;
            }

            length = 0;
        }
    }

    if (length != 0 &&
        add_word(&words, &count, &words_capacity, buffer, length) != 0) {
        goto failure;
    }

    free(buffer);
    *result = words;
    *result_count = count;
    return 0;

failure:
    {
        int saved_errno = errno;

        free(buffer);
        free_word_counts(words, count);
        errno = saved_errno != 0 ? saved_errno : EIO;
    }

    return -1;
}

static size_t count_common_words(WordCount *words, size_t count)
{
    if (words == NULL || count == 0) {
        return 0;
    }

    qsort(words, count, sizeof *words, compare_words);

    size_t unique_count = 0;

    for (size_t i = 0; i < count;) {
        size_t next = i + 1;

        while (next < count &&
               strcmp(words[i].word, words[next].word) == 0) {
            ++next;
        }

        words[unique_count].word = words[i].word;
        words[unique_count].count = next - i;

        for (size_t j = i + 1; j < next; ++j) {
            free(words[j].word);
            words[j].word = NULL;
        }

        ++unique_count;
        i = next;
    }

    qsort(words, unique_count, sizeof *words, compare_counts);
    return unique_count;
}

static int parse_limit(const char *text, size_t *limit)
{
    if (text == NULL || limit == NULL || text[0] == '\0' ||
        text[0] == '-' || isspace((unsigned char)text[0]) != 0) {
        errno = EINVAL;
        return -1;
    }

    errno = 0;
    char *end = NULL;
    unsigned long long value = strtoull(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' || value == 0 ||
        value > (unsigned long long)SIZE_MAX) {
        errno = EINVAL;
        return -1;
    }

    *limit = (size_t)value;
    return 0;
}

static int open_regular_file(const char *path, FILE **stream)
{
    if (path == NULL || stream == NULL || path[0] == '\0') {
        errno = EINVAL;
        return -1;
    }

    *stream = NULL;

    int flags = O_RDONLY | O_CLOEXEC;

#ifdef O_NOFOLLOW
    flags |= O_NOFOLLOW;
#endif

#ifdef O_NONBLOCK
    flags |= O_NONBLOCK;
#endif

    int descriptor = open(path, flags);

    if (descriptor < 0) {
        return -1;
    }

    struct stat status;

    if (fstat(descriptor, &status) != 0) {
        int saved_errno = errno;
        (void)close(descriptor);
        errno = saved_errno;
        return -1;
    }

    if (!S_ISREG(status.st_mode)) {
        (void)close(descriptor);
        errno = EINVAL;
        return -1;
    }

#ifdef O_NONBLOCK
    int descriptor_flags = fcntl(descriptor, F_GETFL);

    if (descriptor_flags < 0 ||
        fcntl(descriptor, F_SETFL, descriptor_flags & ~O_NONBLOCK) < 0) {
        int saved_errno = errno;
        (void)close(descriptor);
        errno = saved_errno;
        return -1;
    }
#endif

    FILE *file = fdopen(descriptor, "rb");

    if (file == NULL) {
        int saved_errno = errno;
        (void)close(descriptor);
        errno = saved_errno;
        return -1;
    }

    *stream = file;
    return 0;
}

int main(int argc, char **argv)
{
    if (argc < 2 || argc > 3) {
        fprintf(stderr, "Usage: %s <dictionary-file> [limit]\n", argv[0]);
        return EXIT_FAILURE;
    }

    size_t limit = 10;

    if (argc == 3 && parse_limit(argv[2], &limit) != 0) {
        fprintf(stderr, "Invalid limit: %s\n", argv[2]);
        return EXIT_FAILURE;
    }

    FILE *stream = NULL;

    if (open_regular_file(argv[1], &stream) != 0) {
        int saved_errno = errno;

        fprintf(stderr, "Unable to open %s: %s\n",
                argv[1], strerror(saved_errno));
        return EXIT_FAILURE;
    }

    WordCount *words = NULL;
    size_t count = 0;

    errno = 0;
    int read_status = read_dictionary(stream, &words, &count);
    int read_error = errno;

    errno = 0;
    int close_status = fclose(stream);
    int close_error = errno;

    if (read_status != 0) {
        fprintf(stderr, "Unable to read dictionary: %s\n",
                strerror(read_error != 0 ? read_error : EIO));
        free_word_counts(words, count);
        return EXIT_FAILURE;
    }

    if (close_status != 0) {
        fprintf(stderr, "Unable to close dictionary: %s\n",
                strerror(close_error != 0 ? close_error : EIO));
        free_word_counts(words, count);
        return EXIT_FAILURE;
    }

    size_t unique_count = count_common_words(words, count);
    size_t output_count = unique_count < limit ? unique_count : limit;

    for (size_t i = 0; i < output_count; ++i) {
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