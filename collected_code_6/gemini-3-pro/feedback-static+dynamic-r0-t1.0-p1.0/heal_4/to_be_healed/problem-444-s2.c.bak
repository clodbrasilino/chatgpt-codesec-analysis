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
  *  test case 2 failed: expected '[(8, 4), (8, 12), (1, 7), (6, 9)]', got <no output>
  *  test case 1 failed: expected '[(3, 2, 1), (4, 9, 2), (1, 2, 3), (8, 2, 1)]', got <no output>
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
 /* Possible weaknesses found:
  * Fuzzing found a crash (signal 6) on input id:000000,sig:06,src:000000,time:6470,execs:630,op:havoc,rep:14; likely memory-safety defect
  */

int main(void) {
    char input[8192];
    if (!fgets(input, sizeof(input), stdin)) {
        return 0;
    }

    char *list_start = strchr(input, '[');
    char *list_end = strrchr(input, ']');
    if (!list_start || !list_end || list_end < list_start) return 1;

    char *k_str = strrchr(input, ',');
    if (!k_str) return 1;
    while (!isdigit((unsigned char)*k_str) && k_str > list_end) {
        k_str++;
    }
    size_t k = (size_t)atoi(k_str);

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
            p++;
            char *p_end = strchr(p, ')');

            size_t el_count = 0;
            char *tmp = p;
            while (tmp < p_end) {
                if (isdigit((unsigned char)*tmp) || (*tmp == '-' && isdigit((unsigned char)*(tmp + 1)))) {
                    el_count++;
                    while (isdigit((unsigned char)*tmp) || *tmp == '-') tmp++;
                } else {
                    tmp++;
                }
            }
            
            input_list.tuples[i].size = el_count;
            input_list.tuples[i].elements = el_count > 0 ? (int *)malloc(el_count * sizeof(int)) : NULL;

            tmp = p;
            for (size_t j = 0; j < el_count; ++j) {
                while (!isdigit((unsigned char)*tmp) && *tmp != '-') tmp++;
                input_list.tuples[i].elements[j] = atoi(tmp);
                while (isdigit((unsigned char)*tmp) || *tmp == '-') tmp++;
            }
            /* Possible weaknesses found:
             * UBSan: applying non-zero offset 1 to null pointer (AFL crash: id:000001,sig:06,src:000000,time:15389,execs:1387,op:havoc,rep:7)
             */
            p = p_end + 1;
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