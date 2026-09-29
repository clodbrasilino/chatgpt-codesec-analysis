#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#define MAX_TUPLE_SIZE 100
#define MAX_STRING_LENGTH 50

typedef struct {
    int *values;
    size_t size;
} IntTuple;

typedef struct {
    char **values;
    size_t size;
} StringTuple;

static size_t safe_strlen(const char *str, size_t max_len) {
    size_t len = 0;
    if (str == NULL) {
        return 0;
    }
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

IntTuple convert_string_tuple_to_int_tuple(const StringTuple *input) {
    IntTuple result;
    result.values = NULL;
    result.size = 0;

    if (input == NULL || input->values == NULL || input->size == 0) {
        return result;
    }

    result.values = (int *)malloc(input->size * sizeof(int));
    if (result.values == NULL) {
        return result;
    }

    result.size = input->size;
    for (size_t i = 0; i < input->size; i++) {
        if (input->values[i] == NULL) {
            free(result.values);
            result.values = NULL;
            result.size = 0;
            return result;
        }
        
        char *endptr = NULL;
        errno = 0;
        long value = strtol(input->values[i], &endptr, 10);
        
        if (errno == ERANGE || value > INT_MAX || value < INT_MIN) {
            free(result.values);
            result.values = NULL;
            result.size = 0;
            return result;
        }
        
        if (endptr == input->values[i] || *endptr != '\0') {
            free(result.values);
            result.values = NULL;
            result.size = 0;
            return result;
        }
        
        result.values[i] = (int)value;
    }
    return result;
}

void free_string_tuple(StringTuple *tuple) {
    if (tuple == NULL) return;
    if (tuple->values != NULL) {
        for (size_t i = 0; i < tuple->size; i++) {
            free(tuple->values[i]);
        }
        free(tuple->values);
    }
    tuple->values = NULL;
    tuple->size = 0;
}

void free_int_tuple(IntTuple *tuple) {
    if (tuple == NULL) return;
    free(tuple->values);
    tuple->values = NULL;
    tuple->size = 0;
}

int main(void) {
    const size_t test_size = 5;
    const char *test_strings[] = {"10", "20", "30", "40", "50"};

    StringTuple str_tuple;
    str_tuple.size = test_size;
    str_tuple.values = (char **)malloc(test_size * sizeof(char *));
    if (str_tuple.values == NULL) {
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < test_size; i++) {
        size_t len = safe_strlen(test_strings[i], MAX_STRING_LENGTH);
        size_t copy_len = len < MAX_STRING_LENGTH ? len : MAX_STRING_LENGTH - 1;
        
        str_tuple.values[i] = (char *)malloc((copy_len + 1) * sizeof(char));
        if (str_tuple.values[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(str_tuple.values[j]);
            }
            free(str_tuple.values);
            str_tuple.values = NULL;
            return EXIT_FAILURE;
        }
        
        if (copy_len > 0) {
            /* Possible weaknesses found:
             * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
             */
            memcpy(str_tuple.values[i], test_strings[i], copy_len);
        }
        str_tuple.values[i][copy_len] = '\0';
    }

    IntTuple int_tuple = convert_string_tuple_to_int_tuple(&str_tuple);
    if (int_tuple.values == NULL) {
        free_string_tuple(&str_tuple);
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < int_tuple.size; i++) {
        printf("%d ", int_tuple.values[i]);
    }
    printf("\n");

    free_string_tuple(&str_tuple);
    free_int_tuple(&int_tuple);

    return EXIT_SUCCESS;
}