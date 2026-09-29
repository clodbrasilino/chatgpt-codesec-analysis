#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_lowercase(unsigned char character)
{
    return character >= (unsigned char)'a' && character <= (unsigned char)'z';
}

static void free_split(char **parts, size_t count)
{
    size_t i;

    if (parts == NULL) {
        return;
    }

    for (i = 0; i < count; ++i) {
        free(parts[i]);
    }

    free(parts);
}

static char **split_at_lowercase(const char *string, size_t *part_count)
{
    char **parts;
    size_t count = 0;
    size_t index = 0;
    size_t part_index = 0;
    int inside_part = 0;

    if (string == NULL || part_count == NULL) {
        return NULL;
    }

    *part_count = 0;

    while (string[index] != '\0') {
        if (is_lowercase((unsigned char)string[index])) {
            inside_part = 0;
        } else if (!inside_part) {
            ++count;
            inside_part = 1;
        }
        ++index;
    }

    if (count == 0) {
        parts = malloc(sizeof(*parts));
        return parts;
    }

    if (count > (size_t)-1 / sizeof(*parts)) {
        return NULL;
    }

    parts = calloc(count, sizeof(*parts));
    if (parts == NULL) {
        return NULL;
    }

    index = 0;

    while (string[index] != '\0') {
        size_t start;
        size_t length;

        while (string[index] != '\0' &&
               is_lowercase((unsigned char)string[index])) {
            ++index;
        }

        if (string[index] == '\0') {
            break;
        }

        start = index;

        while (string[index] != '\0' &&
               !is_lowercase((unsigned char)string[index])) {
            ++index;
        }

        length = index - start;
        parts[part_index] = malloc(length + 1);

        if (parts[part_index] == NULL) {
            free_split(parts, part_index);
            return NULL;
        }

        memcpy(parts[part_index], string + start, length);
        parts[part_index][length] = '\0';
        ++part_index;
    }

    *part_count = count;
    return parts;
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *argv[])
{
    char **parts;
    size_t count;
    size_t i;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <string>\n", argv[0]);
        return EXIT_FAILURE;
    }

    parts = split_at_lowercase(argv[1], &count);
    if (parts == NULL) {
        fputs("Unable to split the string.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0; i < count; ++i) {
        if (puts(parts[i]) == EOF) {
            free_split(parts, count);
            fputs("Output error.\n", stderr);
            return EXIT_FAILURE;
        }
    }

    free_split(parts, count);
    return EXIT_SUCCESS;
}