#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <errno.h>
#include <limits.h>

typedef struct {
    int *values;
    size_t length;
} Tuple;

static int parse_integer(const char *str, size_t str_len, size_t *index) {
    while (*index < str_len && isspace((unsigned char)str[*index])) {
        (*index)++;
    }
    
    if (*index >= str_len || str[*index] == '\0') {
        return 0;
    }
    
    char *endptr;
    errno = 0;
    long val = strtol(str + *index, &endptr, 10);
    
    if (endptr == str + *index) {
        return 0;
    }
    
    if (errno == ERANGE || val > INT_MAX || val < INT_MIN) {
        return 0;
    }
    
    *index = endptr - str;
    
    while (*index < str_len && isspace((unsigned char)str[*index])) {
        (*index)++;
    }
    
    if (*index < str_len && str[*index] == ',') {
        (*index)++;
    }
    
    return (int)val;
}

static size_t count_integers(const char *str, size_t str_len) {
    size_t count = 0;
    size_t i = 0;
    int in_number = 0;
    
    while (i < str_len) {
        if (isdigit((unsigned char)str[i]) || str[i] == '-') {
            if (!in_number) {
                count++;
                in_number = 1;
            }
        } else if (str[i] == ',' || isspace((unsigned char)str[i])) {
            in_number = 0;
        }
        i++;
    }
    
    return count;
}

static Tuple string_to_tuple(const char *str, size_t str_len) {
    Tuple result = {NULL, 0};
    
    if (str == NULL || str_len == 0) {
        return result;
    }
    
    size_t count = count_integers(str, str_len);
    if (count == 0) {
        return result;
    }
    
    result.values = malloc(count * sizeof(int));
    if (result.values == NULL) {
        return result;
    }
    
    size_t index = 0;
    for (size_t i = 0; i < count; i++) {
        if (index >= str_len) {
            free(result.values);
            result.values = NULL;
            result.length = 0;
            return result;
        }
        result.values[i] = parse_integer(str, str_len, &index);
        result.length++;
    }
    
    return result;
}

static void free_tuple(Tuple *tuple) {
    if (tuple != NULL && tuple->values != NULL) {
        free(tuple->values);
        tuple->values = NULL;
        tuple->length = 0;
    }
}

int main(void) {
    const char *input = "10, 20, 30, 40, 50";
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t input_len = strlen(input);
    Tuple result = string_to_tuple(input, input_len);
    
    if (result.values == NULL) {
        fprintf(stderr, "Failed to parse tuple\n");
        return EXIT_FAILURE;
    }
    
    printf("Tuple: (");
    for (size_t i = 0; i < result.length; i++) {
        if (i > 0) {
            printf(", ");
        }
        printf("%d", result.values[i]);
    }
    printf(")\n");
    
    free_tuple(&result);
    return EXIT_SUCCESS;
}