#include <regex.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int grow_buffer(char **buffer, size_t *capacity, size_t required)
{
    size_t new_capacity;
    char *temporary;

    if (buffer == NULL || capacity == NULL) {
        return -1;
    }

    if (required <= *capacity) {
        return 0;
    }

    new_capacity = *capacity;
    if (new_capacity == 0U) {
        new_capacity = 1U;
    }

    while (new_capacity < required) {
        if (new_capacity > SIZE_MAX / 2U) {
            new_capacity = required;
            break;
        }
        new_capacity *= 2U;
    }

    temporary = realloc(*buffer, new_capacity);
    if (temporary == NULL) {
        return -1;
    }

    *buffer = temporary;
    *capacity = new_capacity;
    return 0;
}

static char *camel_to_snake(const char *input)
{
    static const char pattern[] = "([[:lower:][:digit:]])([[:upper:]])";
    regex_t regex;
    regmatch_t matches[3];
    char *current;
    size_t capacity;
    size_t search_offset;
    int regex_status;

    if (input == NULL) {
        return NULL;
    }

    if (strlen(input) == SIZE_MAX) {
        return NULL;
    }

    capacity = strlen(input) + 1U;
    current = malloc(capacity);
    if (current == NULL) {
        return NULL;
    }

    memcpy(current, input, capacity);

    regex_status = regcomp(&regex, pattern, REG_EXTENDED);
    if (regex_status != 0) {
        free(current);
        return NULL;
    }

    search_offset = 0U;

    for (;;) {
        size_t length;
        size_t first_end;
        size_t second_start;
        size_t required;
        size_t tail_size;

        length = strlen(current);
        if (search_offset > length) {
            break;
        }

        regex_status = regexec(&regex, current + search_offset, 3U, matches, 0);
        if (regex_status == REG_NOMATCH) {
            break;
        }

        if (regex_status != 0 ||
            matches[1].rm_eo < 0 ||
            matches[2].rm_so < 0) {
            regfree(&regex);
            free(current);
            return NULL;
        }

        if ((size_t)matches[1].rm_eo > SIZE_MAX - search_offset ||
            (size_t)matches[2].rm_so > SIZE_MAX - search_offset) {
            regfree(&regex);
            free(current);
            return NULL;
        }

        first_end = search_offset + (size_t)matches[1].rm_eo;
        second_start = search_offset + (size_t)matches[2].rm_so;

        if (first_end > second_start ||
            second_start > length ||
            length > SIZE_MAX - 2U) {
            regfree(&regex);
            free(current);
            return NULL;
        }

        required = length + 2U;

        if (grow_buffer(&current, &capacity, required) != 0) {
            regfree(&regex);
            free(current);
            return NULL;
        }

        tail_size = length - second_start + 1U;
        memmove(current + first_end + 1U,
                current + second_start,
                tail_size);
        current[first_end] = '_';
        search_offset = first_end + 2U;
    }

    regfree(&regex);
    return current;
}

int main(int argc, char *const argv[])
{
    char *result;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <camelCaseString>\n", argv[0]);
        return EXIT_FAILURE;
    }

    result = camel_to_snake(argv[1]);
    if (result == NULL) {
        fputs("Conversion failed\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", result) < 0) {
        free(result);
        return EXIT_FAILURE;
    }

    free(result);
    return EXIT_SUCCESS;
}