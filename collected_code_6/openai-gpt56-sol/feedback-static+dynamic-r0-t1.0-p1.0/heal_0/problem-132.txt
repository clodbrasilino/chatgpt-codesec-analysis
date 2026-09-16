#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int first;
    int second;
    const char *third;
} Tuple;

static char *tuple_to_string(const Tuple *tuple)
{
    int length;
    char *result;

    if (tuple == NULL || tuple->third == NULL) {
        return NULL;
    }

    length = snprintf(NULL, 0, "(%d, %d, \"%s\")",
                      tuple->first, tuple->second, tuple->third);
    if (length < 0) {
        return NULL;
    }

    result = malloc((size_t)length + 1U);
    if (result == NULL) {
        return NULL;
    }

    if (snprintf(result, (size_t)length + 1U, "(%d, %d, \"%s\")",
                 tuple->first, tuple->second, tuple->third) != length) {
        free(result);
        return NULL;
    }

    return result;
}

int main(void)
{
    const Tuple tuple = {42, 17, "example"};
    char *text = tuple_to_string(&tuple);

    if (text == NULL) {
        fputs("Failed to convert tuple to string.\n", stderr);
        return EXIT_FAILURE;
    }

    if (printf("%s\n", text) < 0) {
        free(text);
        return EXIT_FAILURE;
    }

    free(text);
    return EXIT_SUCCESS;
}