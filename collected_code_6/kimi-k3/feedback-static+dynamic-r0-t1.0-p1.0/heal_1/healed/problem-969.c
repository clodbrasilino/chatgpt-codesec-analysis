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

int init_list(TupleList *list, size_t capacity) {
    if (list == NULL || capacity == 0) {
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
    size_t first_len;
    size_t second_len;
    
    if (list == NULL || first == NULL || second == NULL) {
        return -1;
    }
    if (list->size >= list->capacity) {
        return -1;
    }
    
    first_len = strnlen(first, SIZE_MAX);
    if (first_len == SIZE_MAX) {
        return -1;
    }
    
    list->tuples[list->size].first = malloc(first_len + 1);
    if (list->tuples[list->size].first == NULL) {
        return -1;
    }
    snprintf(list->tuples[list->size].first, first_len + 1, "%s", first);
    
    second_len = strnlen(second, SIZE_MAX);
    if (second_len == SIZE_MAX) {
        free(list->tuples[list->size].first);
        return -1;
    }
    
    list->tuples[list->size].second = malloc(second_len + 1);
    if (list->tuples[list->size].second == NULL) {
        free(list->tuples[list->size].first);
        return -1;
    }
    snprintf(list->tuples[list->size].second, second_len + 1, "%s", second);
    
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
            if (strcmp(input->tuples[i].first, input->tuples[j].first) == 0) {
                if (!found) {
                    size_t len2 = strnlen(input->tuples[i].second, SIZE_MAX);
                    size_t len3 = strnlen(input->tuples[j].second, SIZE_MAX);
                    char *new_second;
                    
                    if (len2 == SIZE_MAX || len3 == SIZE_MAX) {
                        free(merged);
                        free_list(&result);
                        result.tuples = NULL;
                        return result;
                    }
                    
                    new_second = malloc(len2 + len3 + 2);
                    if (new_second == NULL) {
                        free(merged);
                        free_list(&result);
                        result.tuples = NULL;
                        return result;
                    }
                    
                    snprintf(new_second, len2 + len3 + 2, "%s %s", 
                             input->tuples[i].second, input->tuples[j].second);
                    
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
                    size_t old_len = strnlen(result.tuples[result.size - 1].second, SIZE_MAX);
                    size_t add_len = strnlen(input->tuples[j].second, SIZE_MAX);
                    char *new_second;
                    
                    if (old_len == SIZE_MAX || add_len == SIZE_MAX) {
                        free(merged);
                        free_list(&result);
                        result.tuples = NULL;
                        return result;
                    }
                    
                    new_second = malloc(old_len + add_len + 2);
                    if (new_second == NULL) {
                        free(merged);
                        free_list(&result);
                        result.tuples = NULL;
                        return result;
                    }
                    
                    snprintf(new_second, old_len + add_len + 2, "%s %s",
                             result.tuples[result.size - 1].second, 
                             input->tuples[j].second);
                    
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