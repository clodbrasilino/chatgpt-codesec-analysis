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

    size_t allocation_size;

    if (__builtin_add_overflow(length, (size_t)1, &allocation_size)) {
        errno = EOVERFLOW;
        return NULL;
    }

    char *copy = malloc(allocation_size);
    if (copy == NULL) {
        return NULL;
    }

    if (length > 0) {
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

    size_t new_capacity = 16;

    if (*capacity != 0) {
        if (__builtin_mul_overflow(*capacity, (size_t)2, &new_capacity)) {
            errno = EOVERFLOW;
            return -1;
        }
    }

    size_t allocation_size;

    if (__builtin_mul_overflow(new_capacity, sizeof(**words),
                               &allocation_size)) {
        errno = EOVERFLOW;
        return -1;
    }

    WordCount *resized = realloc(*words, allocation_size);
    if (resized == NULL) {
        return -1;
    }

    *words = resized;
    *capacity = new_capacity;
    return 0;
}

static int grow_buffer(char **buffer, size_t *capacity, size_t required)
{
    if (buffer == NULL || capacity == NULL || required == 0) {
        errno = EINVAL;
        return -1;
    }

    if (*capacity >= required) {
        return 0;
    }

    size_t new_capacity = *capacity == 0 ? 4096 : *capacity;

    while (new_capacity < required) {
        size_t doubled;

        if (__builtin_mul_overflow(new_capacity, (size_t)2, &doubled)) {
            new_capacity = required;
            break;
        }

        new_capacity = doubled;
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

static int add_word(WordCount **words, size_t *count, size_t *capacity,
                    const char *word, size_t length)
{
    if (words == NULL || count == NULL || capacity == NULL ||
        word == NULL || length == 0 || *count > *capacity) {
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

    char *copy = duplicate_string(word, length);
    if (copy == NULL) {
        return -1;
    }

    (*words)[*count].word = copy;
    (*words)[*count].count = 1;
    ++*count;
    return 0;
}

static int process_input_block(const unsigned char *input, size_t input_size,
                               WordCount **words, size_t *count,
                               size_t *word_array_capacity,
                               char **word_buffer, size_t *word_length,
                               size_t *word_capacity)
{
    if (input == NULL || words == NULL || count == NULL ||
        word_array_capacity == NULL || word_buffer == NULL ||
        word_length == NULL || word_capacity == NULL) {
        errno = EINVAL;
        return -1;
    }

    for (size_t i = 0; i < input_size; ++i) {
        unsigned char byte = input[i];

        if (isalnum(byte) != 0 || byte == (unsigned char)'\'') {
            size_t required;

            if (__builtin_add_overflow(*word_length, (size_t)1, &required)) {
                errno = EOVERFLOW;
                return -1;
            }

            if (grow_buffer(word_buffer, word_capacity, required) != 0) {
                return -1;
            }

            (*word_buffer)[*word_length] = (char)tolower(byte);
            ++*word_length;
        } else if (*word_length != 0) {
            if (add_word(words, count, word_array_capacity,
                         *word_buffer, *word_length) != 0) {
                return -1;
            }

            *word_length = 0;
        }
    }

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
    size_t word_array_capacity = 0;
    char *word_buffer = NULL;
    size_t word_length = 0;
    size_t word_capacity = 0;
    unsigned char *input = malloc(8192);

    if (input == NULL) {
        return -1;
    }

    for (;;) {
        size_t bytes_read = fread(input, 1, 8192, stream);

        if (process_input_block(input, bytes_read, &words, &count,
                                &word_array_capacity, &word_buffer,
                                &word_length, &word_capacity) != 0) {
            goto failure;
        }

        if (bytes_read < 8192) {
            if (ferror(stream)) {
                if (errno == 0) {
                    errno = EIO;
                }
                goto failure;
            }

            if (feof(stream)) {
                break;
            }

            errno = EIO;
            goto failure;
        }
    }

    if (word_length != 0 &&
        add_word(&words, &count, &word_array_capacity,
                 word_buffer, word_length) != 0) {
        goto failure;
    }

    free(input);
    free(word_buffer);
    *result = words;
    *result_count = count;
    return 0;

failure:
    {
        int saved_errno = errno != 0 ? errno : EIO;
        free(input);
        free(word_buffer);
        free_word_counts(words, count);
        errno = saved_errno;
    }

    return -1;
}

static size_t count_common_words(WordCount *words, size_t count)
{
    if (words == NULL || count == 0) {
        return 0;
    }

    qsort(words, count, sizeof(*words), compare_words);

    size_t unique_count = 0;

    for (size_t i = 0; i < count;) {
        size_t next = i + 1;

        while (next < count &&
               strcmp(words[i].word, words[next].word) == 0) {
            ++next;
        }

        char *representative = words[i].word;

        for (size_t j = i + 1; j < next; ++j) {
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
        errno = EINVAL;
        return -1;
    }

    char *end = NULL;
    errno = 0;
    unsigned long long value = strtoull(text, &end, 10);

    if (errno == ERANGE || end == text || *end != '\0' || value == 0 ||
        value > (unsigned long long)SIZE_MAX) {
        errno = EINVAL;
        return -1;
    }

    *limit = (size_t)value;
    return 0;
}

static int set_close_on_exec(int fd)
{
    int flags = fcntl(fd, F_GETFD);

    if (flags < 0) {
        return -1;
    }

    if ((flags & FD_CLOEXEC) == 0 &&
        fcntl(fd, F_SETFD, flags | FD_CLOEXEC) < 0) {
        return -1;
    }

    return 0;
}

static int open_directory_fd(const char *path)
{
    if (path == NULL || path[0] == '\0') {
        errno = EINVAL;
        return -1;
    }

    int flags = O_RDONLY;

#ifdef O_DIRECTORY
    flags |= O_DIRECTORY;
#endif
#ifdef O_CLOEXEC
    flags |= O_CLOEXEC;
#endif
#ifdef O_NOFOLLOW
    flags |= O_NOFOLLOW;
#endif

    int fd = open(path, flags);
    if (fd < 0) {
        return -1;
    }

    if (set_close_on_exec(fd) != 0) {
        int saved_errno = errno;
        close(fd);
        errno = saved_errno;
        return -1;
    }

    struct stat status;

    if (fstat(fd, &status) != 0) {
        int saved_errno = errno;
        close(fd);
        errno = saved_errno;
        return -1;
    }

    if (!S_ISDIR(status.st_mode)) {
        close(fd);
        errno = ENOTDIR;
        return -1;
    }

#ifndef O_NOFOLLOW
    struct stat path_status;

    if (lstat(path, &path_status) != 0) {
        int saved_errno = errno;
        close(fd);
        errno = saved_errno;
        return -1;
    }

    if (S_ISLNK(path_status.st_mode) ||
        path_status.st_dev != status.st_dev ||
        path_status.st_ino != status.st_ino) {
        close(fd);
        errno = ELOOP;
        return -1;
    }
#endif

    return fd;
}

static int open_regular_file_at(int directory_fd, const char *name)
{
    if (name == NULL || name[0] == '\0' || strchr(name, '/') != NULL) {
        errno = EINVAL;
        return -1;
    }

    int flags = O_RDONLY;

#ifdef O_CLOEXEC
    flags |= O_CLOEXEC;
#endif
#ifdef O_NOFOLLOW
    flags |= O_NOFOLLOW;
#endif
#ifdef O_NONBLOCK
    flags |= O_NONBLOCK;
#endif

    int fd = openat(directory_fd, name, flags);
    if (fd < 0) {
        return -1;
    }

    struct stat status;

    if (fstat(fd, &status) != 0) {
        int saved_errno = errno;
        close(fd);
        errno = saved_errno;
        return -1;
    }

    if (!S_ISREG(status.st_mode)) {
        close(fd);
        errno = EINVAL;
        return -1;
    }

#ifndef O_NOFOLLOW
    struct stat path_status;

    if (fstatat(directory_fd, name, &path_status, AT_SYMLINK_NOFOLLOW) != 0) {
        int saved_errno = errno;
        close(fd);
        errno = saved_errno;
        return -1;
    }

    if (S_ISLNK(path_status.st_mode) ||
        path_status.st_dev != status.st_dev ||
        path_status.st_ino != status.st_ino) {
        close(fd);
        errno = ELOOP;
        return -1;
    }
#endif

#ifdef O_NONBLOCK
    int descriptor_flags = fcntl(fd, F_GETFL);

    if (descriptor_flags < 0 ||
        fcntl(fd, F_SETFL, descriptor_flags & ~O_NONBLOCK) < 0) {
        int saved_errno = errno;
        close(fd);
        errno = saved_errno;
        return -1;
    }
#endif

    if (set_close_on_exec(fd) != 0) {
        int saved_errno = errno;
        close(fd);
        errno = saved_errno;
        return -1;
    }

    return fd;
}

static FILE *open_dictionary(const char *path)
{
    if (path == NULL || path[0] == '\0') {
        errno = EINVAL;
        return NULL;
    }

    const char *slash = strrchr(path, '/');
    const char *name = path;
    int directory_fd = AT_FDCWD;

    if (slash != NULL) {
        if (slash[1] == '\0') {
            errno = EINVAL;
            return NULL;
        }

        name = slash + 1;
        size_t directory_length = (size_t)(slash - path);
        char *directory;

        if (directory_length == 0) {
            directory = duplicate_string("/", 1);
        } else {
            directory = duplicate_string(path, directory_length);
        }

        if (directory == NULL) {
            return NULL;
        }

        directory_fd = open_directory_fd(directory);
        free(directory);

        if (directory_fd < 0) {
            return NULL;
        }
    }

    int fd = open_regular_file_at(directory_fd, name);
    int saved_errno = errno;

    if (directory_fd != AT_FDCWD) {
        close(directory_fd);
    }

    if (fd < 0) {
        errno = saved_errno;
        return NULL;
    }

    FILE *stream = fdopen(fd, "rb");

    if (stream == NULL) {
        saved_errno = errno;
        close(fd);
        errno = saved_errno;
        return NULL;
    }

    return stream;
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

    errno = 0;
    FILE *stream = open_dictionary(argv[1]);

    if (stream == NULL) {
        int saved_errno = errno != 0 ? errno : EIO;
        fprintf(stderr, "Unable to open %s: %s\n",
                argv[1], strerror(saved_errno));
        return EXIT_FAILURE;
    }

    WordCount *words = NULL;
    size_t count = 0;

    errno = 0;
    int read_status = read_dictionary(stream, &words, &count);
    int read_error = errno != 0 ? errno : EIO;

    errno = 0;
    int close_status = fclose(stream);
    int close_error = errno != 0 ? errno : EIO;

    if (read_status != 0) {
        fprintf(stderr, "Unable to read dictionary: %s\n",
                strerror(read_error));
        free_word_counts(words, count);
        return EXIT_FAILURE;
    }

    if (close_status != 0) {
        fprintf(stderr, "Unable to close dictionary: %s\n",
                strerror(close_error));
        free_word_counts(words, count);
        return EXIT_FAILURE;
    }

    size_t unique_count = count_common_words(words, count);
    size_t output_count = unique_count < limit ? unique_count : limit;

    for (size_t i = 0; i < output_count; ++i) {
        errno = 0;

        if (printf("%s %zu\n", words[i].word, words[i].count) < 0) {
            int saved_errno = errno != 0 ? errno : EIO;
            fprintf(stderr, "Unable to write output: %s\n",
                    strerror(saved_errno));
            free_word_counts(words, unique_count);
            return EXIT_FAILURE;
        }
    }

    errno = 0;

    if (fflush(stdout) == EOF) {
        int saved_errno = errno != 0 ? errno : EIO;
        fprintf(stderr, "Unable to write output: %s\n",
                strerror(saved_errno));
        free_word_counts(words, unique_count);
        return EXIT_FAILURE;
    }

    free_word_counts(words, unique_count);
    return EXIT_SUCCESS;
}