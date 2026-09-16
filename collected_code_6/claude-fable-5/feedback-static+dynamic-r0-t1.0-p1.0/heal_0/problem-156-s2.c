#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

typedef struct {
    char **values;
    size_t count;
} StringTuple;

typedef struct {
    int *values;
    size_t count;
} IntTuple;

int convert_string_to_int(const char *str, int *result)
{
    char *endptr;
    long value;

    if (str == NULL || result == NULL) {
        return -1;
    }

    errno = 0;
    value = strtol(str, &endptr, 10);

    if (errno == ERANGE || value > INT_MAX || value < INT_MIN) {
        return -1;
    }

    if (endptr == str || *endptr != '\0') {
        return -1;
    }

    *result = (int)value;
    return 0;
}

IntTuple *convert_tuple(const StringTuple *input)
{
    IntTuple *output;
    size_t i;

    if (input == NULL || input->values == NULL || input->count == 0) {
        return NULL;
    }

    output = malloc(sizeof(IntTuple));
    if (output == NULL) {
        return NULL;
    }

    output->values = malloc(input->count * sizeof(int));
    if (output->values == NULL) {
        free(output);
        return NULL;
    }

    output->count = input->count;

    for (i = 0; i < input->count; i++) {
        if (convert_string_to_int(input->values[i], &output->values[i]) != 0) {
            free(output->values);
            free(output);
            return NULL;
        }
    }

    return output;
}

void free_int_tuple(IntTuple *tuple)
{
    if (tuple != NULL) {
        free(tuple->values);
        free(tuple);
    }
}

int main(void)
{
    char *strings[] = { "42", "-17", "1000", "0" };
    StringTuple input;
    IntTuple *output;
    size_t i;

    input.values = strings;
    input.count = sizeof(strings) / sizeof(strings[0]);

    output = convert_tuple(&input);
    if (output == NULL) {
        fprintf(stderr, "Conversion failed\n");
        return EXIT_FAILURE;
    }

    printf("(");
    for (i = 0; i < output->count; i++) {
        printf("%d", output->values[i]);
        if (i < output->count - 1) {
            printf(", ");
        }
    }
    printf(")\n");

    free_int_tuple(output);
    return EXIT_SUCCESS;
}