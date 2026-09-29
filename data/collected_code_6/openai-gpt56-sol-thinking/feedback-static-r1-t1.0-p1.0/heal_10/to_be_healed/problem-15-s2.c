#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int is_lowercase(char character)
{
    return character >= 'a' && character <= 'z';
}

static size_t string_length(const char *string)
{
    size_t length = 0;

    while (string[length] != '\0') {
        ++length;
    }

    return length;
}

char **split_at_lowercase(const char *input, size_t input_length,
                          size_t *part_count)
{
    char **parts;
    size_t count = 0;
    size_t index = 0;
    size_t part_index = 0;

    if (input == NULL || part_count == NULL) {
        errno = EINVAL;
        return NULL;
    }

    *part_count = 0;

    while (index < input_length) {
        while (index < input_length && is_lowercase(input[index])) {
            ++index;
        }

        if (index == input_length) {
            break;
        }

        if (count == SIZE_MAX) {
            errno = EOVERFLOW;
            return NULL;
        }

        ++count;

        while (index < input_length && !is_lowercase(input[index])) {
            ++index;
        }
    }

    if (count == SIZE_MAX ||
        count + 1 > SIZE_MAX / sizeof(*parts)) {
        errno = EOVERFLOW;
        return NULL;
    }

    parts = calloc(count + 1, sizeof(*parts));
    if (parts == NULL) {
        errno = ENOMEM;
        return NULL;
    }

    index = 0;

    while (index < input_length) {
        size_t start;
        size_t length;
        size_t copy_index;

        while (index < input_length && is_lowercase(input[index])) {
            ++index;
        }

        if (index == input_length) {
            break;
        }

        start = index;

        while (index < input_length && !is_lowercase(input[index])) {
            ++index;
        }

        length = index - start;

        if (part_index >= count || length == SIZE_MAX) {
            errno = EOVERFLOW;
            goto failure;
        }

        parts[part_index] = malloc(length + 1);
        if (parts[part_index] == NULL) {
            errno = ENOMEM;
            goto failure;
        }

        for (copy_index = 0; copy_index < length; ++copy_index) {
            parts[part_index][copy_index] = input[start + copy_index];
        }

        parts[part_index][length] = '\0';
        ++part_index;
    }

    parts[part_index] = NULL;
    *part_count = part_index;

    return parts;

failure:
    {
        int saved_errno = errno;

        while (part_index > 0) {
            free(parts[--part_index]);
        }

        free(parts);
        errno = saved_errno;
    }

    return NULL;
}

void free_split_parts(char **parts, size_t part_count)
{
    size_t index;

    if (parts == NULL) {
        return;
    }

    for (index = 0; index < part_count; ++index) {
        free(parts[index]);
    }

    free(parts);
}

static int run(const char *input)
{
    char **parts;
    size_t part_count;
    size_t index;
    int status = EXIT_SUCCESS;

    if (input == NULL) {
        errno = EINVAL;
        perror("split_at_lowercase");
        return EXIT_FAILURE;
    }

    parts = split_at_lowercase(input, string_length(input), &part_count);
    if (parts == NULL) {
        perror("split_at_lowercase");
        return EXIT_FAILURE;
    }

    for (index = 0; index < part_count; ++index) {
        if (puts(parts[index]) == EOF) {
            status = EXIT_FAILURE;
            break;
        }
    }

    if (fflush(stdout) == EOF) {
        status = EXIT_FAILURE;
    }

    free_split_parts(parts, part_count);

    return status;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    if (argc != 2) {
        fputs("Usage: split_lowercase <string>\n", stderr);
        return EXIT_FAILURE;
    }

    return run(argv[1]);
}