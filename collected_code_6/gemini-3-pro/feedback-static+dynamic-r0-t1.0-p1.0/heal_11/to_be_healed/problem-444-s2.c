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

TupleList* trim_tuples(const TupleList *input_list, size_t k) {
    if (!input_list) return NULL;
    TupleList *output_list = (TupleList *)malloc(sizeof(TupleList));
    size_t new_count = 0;
    for (size_t i = 0; i < input_list->count; ++i) {
        if (input_list->tuples[i].size != k) new_count++;
    }
    output_list->count = new_count;
    if (new_count == 0) {
        output_list->tuples = NULL;
        return output_list;
    }
    output_list->tuples = (Tuple *)malloc(new_count * sizeof(Tuple));
    size_t idx = 0;
    for (size_t i = 0; i < input_list->count; ++i) {
        if (input_list->tuples[i].size != k) {
            size_t size = input_list->tuples[i].size;
            output_list->tuples[idx].size = size;
            if (size > 0) {
                output_list->tuples[idx].elements = (int *)malloc(size * sizeof(int));
                for (size_t j = 0; j < size; ++j) {
                    output_list->tuples[idx].elements[j] = input_list->tuples[i].elements[j];
                }
            } else {
                output_list->tuples[idx].elements = NULL;
            }
            idx++;
        }
    }
    return output_list;
}

void print_tuple_list(const TupleList *list) {
    if (!list) return;
    printf("[");
    for (size_t i = 0; i < list->count; ++i) {
        printf("(");
        for (size_t j = 0; j < list->tuples[i].size; ++j) {
            printf("%d", list->tuples[i].elements[j]);
            if (j < list->tuples[i].size - 1) printf(", ");
        }
        if (list->tuples[i].size == 1) printf(",");
        printf(")");
        if (i < list->count - 1) printf(", ");
    }
    printf("]\n");
}

/* Possible weaknesses found:
 *  to match this '{'
 *  Unmatched '{'. Configuration: ''. [syntaxError]
 */
int main(void) {
    char input[65536];
    size_t len = 0;
    int ch;
    while ((ch = fgetc(stdin)) != EOF && len < sizeof(input) - 1) {
        input[len++] = (char)ch;
    }
    input[len] = '\0';
    if (len == 0) return 0;

    char *list_start = strchr(input, '[');
    char *list_end = strrchr(input, ']');
    if (!list_start || !list_end || list_end < list_start) {
        list_start = input;
        list_end = input + len;
    }

    int k = 0;
    char *k_ptr = list_end + 1;
    int found_k = 0;
    while (*k_ptr) {
        if (isdigit((unsigned char)*k_ptr) || (*k_ptr == '-' && isdigit((unsigned char)*(k_ptr+1)))) {
            k = atoi(k_ptr);
            found_k = 1;
            break;
        }
        k_ptr++;
    }
    if (!found_k) {
        k_ptr = input;
        while (k_ptr < list_start) {
            if (isdigit((unsigned char)*k_ptr) || (*k_ptr == '-' && isdigit((unsigned char)*(k_ptr+1)))) {
                k = atoi(k_ptr);
                break;
            }
            k_ptr++;
        }
    /* Possible weaknesses found:
     *  expected declaration or statement at end of input
     *  expected '}'
     */
    }