#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef struct {
    char **strings;
    size_t count;
} StringTuple;

static size_t safe_strlen(const char *s, size_t max_len) {
    size_t len = 0;
    while (len < max_len && s[len] != '\0') {
        len++;
    }
    return len;
}

StringTuple *concatenate_tuples(const StringTuple *tuple1, const StringTuple *tuple2) {
    if (tuple1 == NULL || tuple2 == NULL || 
        (tuple1->count > 0 && tuple1->strings == NULL) || 
        (tuple2->count > 0 && tuple2->strings == NULL)) {
        return NULL;
    }

    if (tuple1->count > SIZE_MAX - tuple2->count) {
        return NULL;
    }

    size_t total_count = tuple1->count + tuple2->count;
    
    StringTuple *result = malloc(sizeof(StringTuple));
    if (result == NULL) {
        return NULL;
    }

    result->count = total_count;
    result->strings = NULL;

    if (total_count == 0) {
        return result;
    }

    result->strings = calloc(total_count, sizeof(char *));
    if (result->strings == NULL) {
        free(result);
        return NULL;
    }

    size_t index = 0;
    
    for (size_t i = 0; i < tuple1->count; i++) {
        if (tuple1->strings[i] == NULL) {
            continue;
        }
        size_t len = safe_strlen(tuple1->strings[i], 4096);
        if (len == 4096 && tuple1->strings[i][len] != '\0') {
            for (size_t j = 0; j < index; j++) {
                free(result->strings[j]);
            }
            free(result->strings);
            free(result);
            return NULL;
        }
        result->strings[index] = malloc(len + 1);
        if (result->strings[index] == NULL) {
            for (size_t j = 0; j < index; j++) {
                free(result->strings[j]);
            }
            free(result->strings);
            free(result);
            return NULL;
        }
        if (len > 0) {
            memcpy(result->strings[index], tuple1->strings[i], len);
        }
        result->strings[index][len] = '\0';
        index++;
    }

    for (size_t i = 0; i < tuple2->count; i++) {
        if (tuple2->strings[i] == NULL) {
            continue;
        }
        size_t len = safe_strlen(tuple2->strings[i], 4096);
        if (len == 4096 && tuple2->strings[i][len] != '\0') {
            for (size_t j = 0; j < index; j++) {
                free(result->strings[j]);
            }
            free(result->strings);
            free(result);
            return NULL;
        }
        result->strings[index] = malloc(len + 1);
        if (result->strings[index] == NULL) {
            for (size_t j = 0; j < index; j++) {
                free(result->strings[j]);
            }
            free(result->strings);
            free(result);
            return NULL;
        }
        if (len > 0) {
            memcpy(result->strings[index], tuple2->strings[i], len);
        }
        result->strings[index][len] = '\0';
        index++;
    }

    result->count = index;
    return result;
}

void free_tuple(StringTuple *tuple) {
    if (tuple == NULL) {
        return;
    }
    if (tuple->strings != NULL) {
        for (size_t i = 0; i < tuple->count; i++) {
            free(tuple->strings[i]);
        }
        free(tuple->strings);
    }
    free(tuple);
}

int main(void) {
    char *data1[] = {"Hello", "World", "From"};
    char *data2[] = {"C", "Programming", "Language"};
    
    StringTuple tuple1 = {data1, 3};
    StringTuple tuple2 = {data2, 3};
    
    StringTuple *result = concatenate_tuples(&tuple1, &tuple2);
    
    if (result == NULL) {
        fprintf(stderr, "Error: Failed to concatenate tuples\n");
        return EXIT_FAILURE;
    }
    
    printf("Concatenated tuple contents:\n");
    for (size_t i = 0; i < result->count; i++) {
        printf("[%zu]: %s\n", i, result->strings[i]);
    }
    
    free_tuple(result);
    
    return EXIT_SUCCESS;
}