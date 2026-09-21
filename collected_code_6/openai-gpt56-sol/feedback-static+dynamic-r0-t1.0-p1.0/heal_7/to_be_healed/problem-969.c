#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *initial;
    char **elements;
    size_t count;
} Tuple;

static char *duplicate_string(const char *source, size_t max_length)
{
    const char *terminator;
    size_t length;
    char *copy;

    if (source == NULL) {
        return NULL;
    }

    terminator = memchr(source, '\0', max_length);
    if (terminator == NULL) {
        return NULL;
    }

    length = (size_t)(terminator - source);
    if (length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    if (length > 0U) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, source, length);
    }
    copy[length] = '\0';

    return copy;
}

static void free_tuple(Tuple *tuple)
{
    size_t i;

    if (tuple == NULL) {
        return;
    }

    free(tuple->initial);

    for (i = 0U; i < tuple->count; ++i) {
        free(tuple->elements[i]);
    }

    free(tuple->elements);
    tuple->initial = NULL;
    tuple->elements = NULL;
    tuple->count = 0U;
}

static void free_tuples(Tuple *tuples, size_t count)
{
    size_t i;

    if (tuples == NULL) {
        return;
    }

    for (i = 0U; i < count; ++i) {
        free_tuple(&tuples[i]);
    }

    free(tuples);
}

static int append_element(Tuple *tuple, const char *element,
                          size_t element_max_length)
{
    char **resized;
    char *copy;
    size_t new_count;

    if (tuple == NULL || element == NULL || element_max_length == 0U) {
        return 0;
    }

    if (tuple->count >= SIZE_MAX / sizeof(*tuple->elements)) {
        return 0;
    }

    copy = duplicate_string(element, element_max_length);
    if (copy == NULL) {
        return 0;
    }

    new_count = tuple->count + 1U;
    resized = realloc(tuple->elements,
                      new_count * sizeof(*tuple->elements));
    if (resized == NULL) {
        free(copy);
        return 0;
    }

    tuple->elements = resized;
    tuple->elements[tuple->count] = copy;
    tuple->count = new_count;

    return 1;
}

static int add_tuple(Tuple **tuples, size_t *count, const char *initial,
                     size_t initial_max_length)
{
    Tuple *resized;
    char *initial_copy;
    size_t new_count;

    if (tuples == NULL || count == NULL || initial == NULL ||
        initial_max_length == 0U) {
        return 0;
    }

    if (*count >= SIZE_MAX / sizeof(**tuples)) {
        return 0;
    }

    initial_copy = duplicate_string(initial, initial_max_length);
    if (initial_copy == NULL) {
        return 0;
    }

    new_count = *count + 1U;
    resized = realloc(*tuples, new_count * sizeof(**tuples));
    if (resized == NULL) {
        free(initial_copy);
        return 0;
    }

    *tuples = resized;
    (*tuples)[*count].initial = initial_copy;
    (*tuples)[*count].elements = NULL;
    (*tuples)[*count].count = 0U;
    *count = new_count;

    return 1;
}

static int bounded_strings_equal(const char *left, size_t left_max_length,
                                 const char *right)
{
    const char *left_terminator;
    size_t left_length;
    size_t right_length;

    if (left == NULL || right == NULL || left_max_length == 0U) {
        return 0;
    }

    left_terminator = memchr(left, '\0', left_max_length);
    if (left_terminator == NULL) {
        return 0;
    }

    left_length = (size_t)(left_terminator - left);
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    right_length = strlen(right);

    return left_length == right_length &&
           memcmp(left, right, left_length) == 0;
}

static int join_tuples(const Tuple *input, size_t input_count,
                       size_t string_max_length,
                       Tuple **output, size_t *output_count)
{
    size_t i;

    if (output == NULL || output_count == NULL ||
        string_max_length == 0U ||
        (input == NULL && input_count != 0U)) {
        return 0;
    }

    *output = NULL;
    *output_count = 0U;

    for (i = 0U; i < input_count; ++i) {
        size_t destination;
        size_t j;

        if (input[i].initial == NULL ||
            (input[i].elements == NULL && input[i].count != 0U) ||
            memchr(input[i].initial, '\0', string_max_length) == NULL) {
            goto failure;
        }

        for (destination = 0U;
             destination < *output_count;
             ++destination) {
            if (bounded_strings_equal(input[i].initial, string_max_length,
                                      (*output)[destination].initial)) {
                break;
            }
        }

        if (destination == *output_count) {
            if (!add_tuple(output, output_count, input[i].initial,
                           string_max_length)) {
                goto failure;
            }
        }

        for (j = 0U; j < input[i].count; ++j) {
            if (input[i].elements[j] == NULL ||
                !append_element(&(*output)[destination],
                                input[i].elements[j],
                                string_max_length)) {
                goto failure;
            }
        }
    }

    return 1;

failure:
    free_tuples(*output, *output_count);
    *output = NULL;
    *output_count = 0U;
    return 0;
}

int main(void)
{
    char *first_elements[] = {"1", "2"};
    char *second_elements[] = {"3"};
    char *third_elements[] = {"4", "5"};
    char *fourth_elements[] = {"6"};
    Tuple input[] = {
        {"A", first_elements, 2U},
        {"B", second_elements, 1U},
        {"A", third_elements, 2U},
        {"C", fourth_elements, 1U}
    };
    Tuple *joined = NULL;
    size_t joined_count = 0U;
    size_t i;

    if (!join_tuples(input, sizeof(input) / sizeof(input[0]), 64U,
                     &joined, &joined_count)) {
        fputs("Failed to join tuples.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < joined_count; ++i) {
        size_t j;

        if (printf("(%s", joined[i].initial) < 0) {
            free_tuples(joined, joined_count);
            return EXIT_FAILURE;
        }

        for (j = 0U; j < joined[i].count; ++j) {
            if (printf(", %s", joined[i].elements[j]) < 0) {
                free_tuples(joined, joined_count);
                return EXIT_FAILURE;
            }
        }

        if (puts(")") == EOF) {
            free_tuples(joined, joined_count);
            return EXIT_FAILURE;
        }
    }

    free_tuples(joined, joined_count);
    return EXIT_SUCCESS;
}