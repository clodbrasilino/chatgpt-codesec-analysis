#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *initial;
    char **elements;
    size_t count;
} Tuple;

static char *duplicate_string(const char *source)
{
    size_t length;
    char *copy;

    if (source == NULL) {
        return NULL;
    }

    length = strlen(source);

    if (length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, source, length + 1U);
    return copy;
}

static void free_tuple(Tuple *tuple)
{
    if (tuple == NULL) {
        return;
    }

    free(tuple->initial);
    tuple->initial = NULL;

    if (tuple->elements != NULL) {
        for (size_t i = 0U; i < tuple->count; ++i) {
            free(tuple->elements[i]);
        }
    }

    free(tuple->elements);
    tuple->elements = NULL;
    tuple->count = 0U;
}

static void free_tuples(Tuple *tuples, size_t count)
{
    if (tuples == NULL) {
        return;
    }

    for (size_t i = 0U; i < count; ++i) {
        free_tuple(&tuples[i]);
    }

    free(tuples);
}

static int append_element(Tuple *tuple, const char *element)
{
    char **resized;
    char *copy;
    size_t new_count;

    if (tuple == NULL || element == NULL) {
        return 0;
    }

    if (tuple->count >= SIZE_MAX / sizeof(*tuple->elements)) {
        return 0;
    }

    copy = duplicate_string(element);
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

static int add_tuple(Tuple **tuples, size_t *count, const char *initial)
{
    Tuple *resized;
    char *initial_copy;
    size_t new_count;

    if (tuples == NULL || count == NULL || initial == NULL) {
        return 0;
    }

    if (*count >= SIZE_MAX / sizeof(**tuples)) {
        return 0;
    }

    initial_copy = duplicate_string(initial);
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

static int join_tuples(const Tuple *input, size_t input_count,
                       Tuple **output, size_t *output_count)
{
    if (output == NULL || output_count == NULL ||
        (input == NULL && input_count != 0U)) {
        return 0;
    }

    *output = NULL;
    *output_count = 0U;

    for (size_t i = 0U; i < input_count; ++i) {
        size_t destination;

        if (input[i].initial == NULL ||
            (input[i].elements == NULL && input[i].count != 0U)) {
            goto failure;
        }

        for (destination = 0U;
             destination < *output_count;
             ++destination) {
            if (strcmp((*output)[destination].initial,
                       input[i].initial) == 0) {
                break;
            }
        }

        if (destination == *output_count) {
            if (!add_tuple(output, output_count, input[i].initial)) {
                goto failure;
            }
        }

        for (size_t j = 0U; j < input[i].count; ++j) {
            if (input[i].elements[j] == NULL ||
                !append_element(&(*output)[destination],
                                input[i].elements[j])) {
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
    const size_t input_count = sizeof(input) / sizeof(input[0]);
    int status = EXIT_SUCCESS;

    if (!join_tuples(input, input_count, &joined, &joined_count)) {
        fputs("Failed to join tuples.\n", stderr);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < joined_count; ++i) {
        if (printf("(%s", joined[i].initial) < 0) {
            status = EXIT_FAILURE;
            break;
        }

        for (size_t j = 0U; j < joined[i].count; ++j) {
            if (printf(", %s", joined[i].elements[j]) < 0) {
                status = EXIT_FAILURE;
                break;
            }
        }

        if (status != EXIT_SUCCESS || puts(")") == EOF) {
            status = EXIT_FAILURE;
            break;
        }
    }

    free_tuples(joined, joined_count);
    return status;
}