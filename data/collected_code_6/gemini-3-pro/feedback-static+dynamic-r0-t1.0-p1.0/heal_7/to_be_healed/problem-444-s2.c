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
 /* Possible weaknesses found:
  *  test case 1 failed: expected '[(3, 2, 1), (4, 9, 2), (1, 2, 3), (8, 2, 1)]', got <no output>
  *  test case 2 failed: expected '[(8, 4), (8, 12), (1, 7), (6, 9)]', got <no output>
  *  test case 0 failed: expected '[(2,), (9,), (2,), (2,)]', got <no output>
  */

TupleList* trim_tuples(const TupleList *input_list, size_t k) {
    if (!input_list || !input_list->tuples) {
        return NULL;
    }

    TupleList *output_list = (TupleList *)malloc(sizeof(TupleList));
    if (!output_list) {
        return NULL;
    }

    output_list->tuples = (Tuple *)malloc(input_list->count * sizeof(Tuple));
    if (!output_list->tuples) {
        free(output_list);
        return NULL;
    }

    size_t filtered_count = 0;
    for (size_t i = 0; i < input_list->count; ++i) {
        size_t original_size = input_list->tuples[i].size;
        if (original_size == k) {
            continue;
        }

        output_list->tuples[filtered_count].size = original_size;
        if (original_size > 0) {
            output_list->tuples[filtered_count].elements = (int *)malloc(original_size * sizeof(int));
            if (!output_list->tuples[filtered_count].elements) {
                for (size_t j = 0; j < filtered_count; ++j) {
                    free(output_list->tuples[j].elements);
                }
                free(output_list->tuples);
                free(output_list);
                return NULL;
            }
            for (size_t j = 0; j < original_size; ++j) {
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

    char *k_str_start = list_end + 1;
    char *k_str_comma = strchr(k_str_start, ',');
    char *k_str = k_str_comma ? k_str_comma + 1 : k_str_start;

    while (*k_str && !isdigit((unsigned char)*k_str) && *k_str != '-') {
        k_str++;
    }
    if (!*k_str) {
        /* Possible weaknesses found:
         *  Variable 'k' is assigned a value that is never used. [unreadVariable]
         */
        size_t k = 0;
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
                p = p_end + 1;
            }
            print_tuple_list(&input_list);
            for (size_t i = 0; i < input_list.count; ++i) {
                free(input_list.tuples[i].elements);
            }
            free(input_list.tuples);
        } else {
            printf("[]\n");
        }
        free(input);
        return 0;
    }

    long k_val = strtol(k_str, NULL, 10);
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
        if (!input_list.tuples) {
            free(input);
            return 1;
        }

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

            if (el_count > 0 && !input_list.tuples[i].elements) {
                input_list.count = i;
                break;
            }

            tmp = p;
            for (size_t j = 0; j < el_count; ++j) {
                while (tmp < p_end && !isdigit((unsigned char)*tmp) && *tmp != '-') tmp++;
                if (tmp < p_end) {
                    long val = strtol(tmp, &tmp, 10);
                    if (val < INT_MIN) val = INT_MIN;
                    else if (val > INT_MAX) val = INT_MAX;
                    input_list.tuples[i].elements[j] = (int)val;
                }
            }
            if (p_end) {
                p = p_end + 1;
            }
        }
    }

    TupleList *trimmed_list = trim_tuples(&input_list, k);
    if (trimmed_list) {
        print_tuple_list(trimmed_list);
        free_tuple_list(trimmed_list);
    } else {
        printf("[]\n");
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