#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

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

    output_list->count = input_list->count;
    output_list->tuples = (Tuple *)malloc(output_list->count * sizeof(Tuple));
    if (!output_list->tuples) {
        free(output_list);
        return NULL;
    }

    for (size_t i = 0; i < input_list->count; ++i) {
        size_t original_size = input_list->tuples[i].size;
        size_t new_size = (original_size > k) ? (original_size - k) : 0;

        output_list->tuples[i].size = new_size;
        
        if (new_size > 0) {
            output_list->tuples[i].elements = (int *)malloc(new_size * sizeof(int));
            if (!output_list->tuples[i].elements) {
                for (size_t j = 0; j < i; ++j) {
                    free(output_list->tuples[j].elements);
                }
                free(output_list->tuples);
                free(output_list);
                return NULL;
            }
            for (size_t j = 0; j < new_size; ++j) {
                output_list->tuples[i].elements[j] = input_list->tuples[i].elements[j];
            }
        } else {
            output_list->tuples[i].elements = NULL;
        }
    }

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
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char input[8192];
    if (!fgets(input, sizeof(input), stdin)) {
        return 0;
    }

    char *list_start = strchr(input, '[');
    char *list_end = strrchr(input, ']');
    if (!list_start || !list_end || list_end < list_start) return 1;

    char *k_str_start = list_end + 1;
    char *k_str_comma = strchr(k_str_start, ',');
    char *k_str = k_str_comma ? k_str_comma + 1 : k_str_start;

    while (*k_str && !isdigit((unsigned char)*k_str) && *k_str != '-') {
        k_str++;
    }
    if (!*k_str) {
        return 1;
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
        if (!input_list.tuples) return 1;

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
                    /* Possible weaknesses found:
                     * Flawfinder atoi: Unless checked, the resulting number can exceed the expected range (CWE-190). If source untrusted, check both minimum and maximum, even if the input had no minus sign (large numbers can roll over into negative number; consider saving to an unsigned value if that is intended). (risk 2, integer)
                     */
                    input_list.tuples[i].elements[j] = atoi(tmp);
                    while (tmp < p_end && (isdigit((unsigned char)*tmp) || *tmp == '-')) tmp++;
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
    }
    
    if (input_list.tuples) {
        for (size_t i = 0; i < input_list.count; ++i) {
            free(input_list.tuples[i].elements);
        }
        free(input_list.tuples);
    }
    
    return 0;
}