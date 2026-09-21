#ifndef _POSIX_C_SOURCE
#define _POSIX_C_SOURCE 200809L
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

typedef struct {
    int *elements;
    size_t size;
} Tuple;

typedef struct {
    Tuple *tuples;
    size_t count;
} TupleList;

TupleList* trim_tuples(const TupleList *input_list, size_t k) {
    if (!input_list || !input_list->tuples) {
        return NULL;
    }

    TupleList *output_list = (TupleList *)malloc(sizeof(TupleList));
    if (!output_list) return NULL;

    output_list->tuples = (Tuple *)malloc(input_list->count * sizeof(Tuple));
    if (!output_list->tuples && input_list->count > 0) {
        free(output_list);
        return NULL;
    }

    size_t filtered_count = 0;
    for (size_t i = 0; i < input_list->count; ++i) {
        size_t original_size = input_list->tuples[i].size;
        size_t new_size = (original_size > k) ? (original_size - k) : 0;

        output_list->tuples[filtered_count].size = new_size;
        if (new_size > 0) {
            output_list->tuples[filtered_count].elements = (int *)malloc(new_size * sizeof(int));
            if (!output_list->tuples[filtered_count].elements) {
                for (size_t j = 0; j < filtered_count; ++j) {
                    free(output_list->tuples[j].elements);
                }
                free(output_list->tuples);
                free(output_list);
                return NULL;
            }
            for (size_t j = 0; j < new_size; ++j) {
                output_list->tuples[filtered_count].elements[j] = input_list->tuples[i].elements[j];
            }
        } else {
            output_list->tuples[filtered_count].elements = NULL;
        }
        filtered_count++;
    }
    output_list->count = filtered_count;
    return output_list;
}

void free_tuple_list(TupleList *list) {
    if (!list) return;
    if (list->tuples) {
        for (size_t i = 0; i < list->count; ++i) {
            free(list->tuples[i].elements);
        }
        free(list->tuples);
    }
    free(list);
}

void print_tuple_list(const TupleList *list) {
    if (!list) return;
    printf("[");
    for (size_t i = 0; i < list->count; ++i) {
        printf("(");
        for (size_t j = 0; j < list->tuples[i].size; ++j) {
            printf("%d", list->tuples[i].elements[j]);
            if (j < list->tuples[i].size - 1) {
                printf(", ");
            }
        }
        if (list->tuples[i].size == 1) {
            printf(",");
        }
        printf(")");
        if (i < list->count - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void) {
    char *input = NULL;
    size_t len = 0;
    ssize_t read = getline(&input, &len, stdin);
    if (read == -1) {
        free(input);
        return 0;
    }
    
    char *list_start = strchr(input, '[');
    char *list_end = strrchr(input, ']');
    if (!list_start || !list_end || list_end < list_start) {
        free(input);
        return 1;
    }
    
    long k_val = 0;
    char *k_str_start = list_end + 1;
    char *k_str_comma = strchr(k_str_start, ',');
    char *k_str = k_str_comma ? k_str_comma + 1 : k_str_start;
    
    while (*k_str && !isdigit((unsigned char)*k_str) && *k_str != '-') {
        k_str++;
    }
    
    if (*k_str) {
        k_val = strtol(k_str, NULL, 10);
    } else {
        char *extra_input = NULL;
        size_t extra_len = 0;
        if (getline(&extra_input, &extra_len, stdin) != -1) {
            char *tmp = extra_input;
            while (*tmp && !isdigit((unsigned char)*tmp) && *tmp != '-') tmp++;
            if (*tmp) k_val = strtol(tmp, NULL, 10);
        }
        free(extra_input);
    }
    
    if (k_val < 0) k_val = 0;
    size_t k = (size_t)k_val;

    TupleList input_list;
    input_list.count = 0;
    input_list.tuples = NULL;

    char *p = list_start;
    while (p < list_end) {
        p = strchr(p, '(');
        if (!p || p > list_end) break;
        input_list.count++;
        p++;
    }

    if (input_list.count > 0) {
        input_list.tuples = (Tuple *)malloc(input_list.count * sizeof(Tuple));
        p = list_start;
        for (size_t i = 0; i < input_list.count; ++i) {
            p = strchr(p, '(');
            if (!p) break;
            p++;
            char *p_end = strchr(p, ')');
            if (!p_end || p_end > list_end) p_end = list_end;

            size_t el_count = 0;
            char *tmp = p;
            while (tmp < p_end) {
                if (isdigit((unsigned char)*tmp) || (*tmp == '-' && isdigit((unsigned char)*(tmp + 1)))) {
                    el_count++;
                    while (tmp < p_end && (isdigit((unsigned char)*tmp) || *tmp == '-')) tmp++;
                } else {
                    tmp++;
                }
            }
            
            input_list.tuples[i].size = el_count;
            input_list.tuples[i].elements = el_count > 0 ? (int *)malloc(el_count * sizeof(int)) : NULL;

            tmp = p;
            for (size_t j = 0; j < el_count; ++j) {
                while (tmp < p_end && !isdigit((unsigned char)*tmp) && *tmp != '-') tmp++;
                if (tmp < p_end) {
                    input_list.tuples[i].elements[j] = (int)strtol(tmp, &tmp, 10);
                }
            }
        }
    }

    TupleList *output_list = trim_tuples(&input_list, k);
    if (output_list) {
        print_tuple_list(output_list);
        free_tuple_list(output_list);
    }

    if (input_list.tuples) {
        for (size_t i = 0; i < input_list.count; ++i) {
            free(input_list.tuples[i].elements);
        }
        free(input_list.tuples);
    }
    free(input);
    return 0;
}