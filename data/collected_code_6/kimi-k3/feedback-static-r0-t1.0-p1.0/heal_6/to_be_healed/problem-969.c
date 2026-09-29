#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *first;
    char *second;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t size;
    size_t capacity;
} TupleList;

static size_t safe_strlen(const char *s, size_t max_len) {
    size_t len = 0;
    if (s == NULL) {
        return 0;
    }
    while (len < max_len && s[len] != '\0') {
        len++;
    }
    return len;
}

static char *safe_strdup(const char *s, size_t max_len) {
    size_t len;
    char *copy;
    
    if (s == NULL) {
        return NULL;
    }
    
    len = safe_strlen(s, max_len);
    if (len == SIZE_MAX) {
        return NULL;
    }
    
    copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }
    
    if (len > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, s, len);
    }
    copy[len] = '\0';
    return copy;
}

static char *safe_concat3(const char *s1, const char *sep, const char *s2, size_t max_len) {
    size_t len1, len2, len_sep;
    size_t total_len;
    char *result;
    
    if (s1 == NULL || sep == NULL || s2 == NULL) {
        return NULL;
    }
    
    len1 = safe_strlen(s1, max_len);
    len_sep = safe_strlen(sep, max_len);
    len2 = safe_strlen(s2, max_len);
    
    if (len1 > max_len || len_sep > max_len || len2 > max_len) {
        return NULL;
    }
    
    if (len1 > SIZE_MAX - len_sep) {
        return NULL;
    }
    if (len1 + len_sep > SIZE_MAX - len2) {
        return NULL;
    }
    if (len1 + len_sep + len2 > SIZE_MAX - 1) {
        return NULL;
    }
    
    total_len = len1 + len_sep + len2;
    if (total_len >= max_len) {
        return NULL;
    }
    
    result = malloc(total_len + 1);
    if (result == NULL) {
        return NULL;
    }
    
    if (len1 > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result, s1, len1);
    }
    if (len_sep > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + len1, sep, len_sep);
    }
    if (len2 > 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(result + len1 + len_sep, s2, len2);
    }
    result[total_len] = '\0';
    
    return result;
}

int init_list(TupleList *list, size_t capacity) {
    if (list == NULL || capacity == 0) {
        return -1;
    }
    if (capacity > SIZE_MAX / sizeof(Tuple)) {
        return -1;
    }
    list->tuples = malloc(capacity * sizeof(Tuple));
    if (list->tuples == NULL) {
        return -1;
    }
    list->size = 0;
    list->capacity = capacity;
    return 0;
}

int add_tuple(TupleList *list, const char *first, const char *second) {
    char *first_copy;
    char *second_copy;
    
    if (list == NULL || first == NULL || second == NULL) {
        return -1;
    }
    if (list->size >= list->capacity) {
        return -1;
    }
    
    first_copy = safe_strdup(first, 4096);
    if (first_copy == NULL) {
        return -1;
    }
    
    second_copy = safe_strdup(second, 8192);
    if (second_copy == NULL) {
        free(first_copy);
        return -1;
    }
    
    list->tuples[list->size].first = first_copy;
    list->tuples[list->size].second = second_copy;
    list->size++;
    return 0;
}

void free_list(TupleList *list) {
    size_t i;
    if (list == NULL) {
        return;
    }
    for (i = 0; i < list->size; i++) {
        free(list->tuples[i].first);
        free(list->tuples[i].second);
    }
    free(list->tuples);
    list->tuples = NULL;
    list->size = 0;
    list->capacity = 0;
}

TupleList join_similar_tuples(const TupleList *input) {
    TupleList result;
    size_t i, j;
    int *merged;
    int found;

    result.tuples = NULL;
    result.size = 0;
    result.capacity = 0;

    if (input == NULL || input->size == 0) {
        return result;
    }

    if (init_list(&result, input->size) != 0) {
        return result;
    }

    merged = calloc(input->size, sizeof(int));
    if (merged == NULL) {
        free_list(&result);
        return result;
    }

    for (i = 0; i < input->size; i++) {
        if (merged[i]) {
            continue;
        }
        found = 0;
        for (j = i + 1; j < input->size; j++) {
            if (merged[j]) {
                continue;
            }
            if (input->tuples[i].first != NULL && input->tuples[j].first != NULL &&
                strcmp(input->tuples[i].first, input->tuples[j].first) == 0) {
                if (!found) {
                    char *new_second = safe_concat3(input->tuples[i].second, " ", 
                                                     input->tuples[j].second, 8192);
                    if (new_second == NULL) {
                        free(merged);
                        free_list(&result);
                        result.tuples = NULL;
                        return result;
                    }
                    if (add_tuple(&result, input->tuples[i].first, new_second) != 0) {
                        free(new_second);
                        free(merged);
                        free_list(&result);
                        result.tuples = NULL;
                        return result;
                    }
                    free(new_second);
                    found = 1;
                } else {
                    char *new_second = safe_concat3(result.tuples[result.size - 1].second, " ",
                                                     input->tuples[j].second, 8192);
                    if (new_second == NULL) {
                        free(merged);
                        free_list(&result);
                        result.tuples = NULL;
                        return result;
                    }
                    free(result.tuples[result.size - 1].second);
                    result.tuples[result.size - 1].second = new_second;
                }
                merged[j] = 1;
            }
        }
        if (!found) {
            if (add_tuple(&result, input->tuples[i].first, input->tuples[i].second) != 0) {
                free(merged);
                free_list(&result);
                result.tuples = NULL;
                return result;
            }
        }
        merged[i] = 1;
    }

    free(merged);
    return result;
}

int main(void) {
    TupleList input;
    TupleList output;
    size_t i;

    if (init_list(&input, 10) != 0) {
        fprintf(stderr, "Failed to initialize list\n");
        return 1;
    }

    if (add_tuple(&input, "apple", "red") != 0 ||
        add_tuple(&input, "banana", "yellow") != 0 ||
        add_tuple(&input, "apple", "green") != 0 ||
        add_tuple(&input, "cherry", "red") != 0 ||
        add_tuple(&input, "banana", "ripe") != 0 ||
        add_tuple(&input, "apple", "sweet") != 0) {
        fprintf(stderr, "Failed to add tuples\n");
        free_list(&input);
        return 1;
    }

    output = join_similar_tuples(&input);
    if (output.tuples == NULL && input.size > 0) {
        fprintf(stderr, "Failed to join tuples\n");
        free_list(&input);
        return 1;
    }

    printf("Joined tuples:\n");
    for (i = 0; i < output.size; i++) {
        printf("(%s, %s)\n", output.tuples[i].first, output.tuples[i].second);
    }

    free_list(&input);
    free_list(&output);

    return 0;
}