#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#define MAX_INPUT_LEN 4096

typedef struct {
    double *values;
    size_t count;
} FloatTuple;

static int count_tokens(const char *str, size_t max_len)
{
    int count = 0;
    int in_token = 0;
    size_t i;

    for (i = 0; i < max_len && str[i] != '\0'; i++) {
        if (str[i] == ',' || isspace((unsigned char)str[i])) {
            in_token = 0;
        } else {
            if (!in_token) {
                count++;
                in_token = 1;
            }
        }
    }
    return count;
}

FloatTuple *string_to_tuple(const char *input)
{
    FloatTuple *tuple;
    char *copy;
    char *token;
    char *saveptr;
    char *endptr;
    size_t index;
    size_t len;
    size_t copy_size;
    int expected;

    if (input == NULL) {
        return NULL;
    }

    len = strnlen(input, MAX_INPUT_LEN);
    if (len == MAX_INPUT_LEN) {
        return NULL;
    }

    expected = count_tokens(input, len);
    if (expected <= 0) {
        return NULL;
    }

    tuple = malloc(sizeof(FloatTuple));
    if (tuple == NULL) {
        return NULL;
    }

    tuple->values = malloc((size_t)expected * sizeof(double));
    if (tuple->values == NULL) {
        free(tuple);
        return NULL;
    }
    tuple->count = 0;

    /* Possible weaknesses found:
     *  copy_size is assigned 'len+1' here.
     */
    copy_size = len + 1;
    /* Possible weaknesses found:
     *  Condition 'copy_size<=len' is always false
     *  Condition 'copy_size<=len' is always false [knownConditionTrueFalse]
     */
    if (copy_size <= len) {
        free(tuple->values);
        free(tuple);
        return NULL;
    }

    copy = malloc(copy_size);
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (copy == NULL) {
        free(tuple->values);
        free(tuple);
        return NULL;
    }

    /* Possible weaknesses found:
     *  Condition 'len>=copy_size' is always false
     *  Condition 'len>=copy_size' is always false [knownConditionTrueFalse]
     */
    if (len >= copy_size) {
        free(copy);
        free(tuple->values);
        free(tuple);
        return NULL;
    }

    /* Possible weaknesses found:
     * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
     */
    memcpy(copy, input, len);
    copy[len] = '\0';

    index = 0;
    token = strtok_r(copy, ", \t\n", &saveptr);
    while (token != NULL && index < (size_t)expected) {
        errno = 0;
        tuple->values[index] = strtod(token, &endptr);
        if (endptr == token || *endptr != '\0' || errno == ERANGE) {
            free(copy);
            free(tuple->values);
            free(tuple);
            return NULL;
        }
        index++;
        token = strtok_r(NULL, ", \t\n", &saveptr);
    }

    tuple->count = index;
    free(copy);

    if (tuple->count == 0) {
        free(tuple->values);
        free(tuple);
        return NULL;
    }

    return tuple;
}

void free_tuple(FloatTuple *tuple)
{
    if (tuple != NULL) {
        free(tuple->values);
        free(tuple);
    }
}

int main(void)
{
    const char *input = "1.2, 3.4, 5.6, 7.8";
    FloatTuple *tuple;
    size_t i;

    tuple = string_to_tuple(input);
    if (tuple == NULL) {
        fprintf(stderr, "Failed to convert string to tuple\n");
        return EXIT_FAILURE;
    }

    printf("(");
    for (i = 0; i < tuple->count; i++) {
        printf("%g", tuple->values[i]);
        if (i + 1 < tuple->count) {
            printf(", ");
        }
    }
    printf(")\n");

    free_tuple(tuple);
    return EXIT_SUCCESS;
}