#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

typedef struct {
    Tuple tuple;
    int frequency;
} TupleFreq;

TupleFreq* get_tuple_frequencies(const Tuple* input_list, size_t input_length, size_t* out_length);

TupleFreq* get_tuple_frequencies(const Tuple* input_list, size_t input_length, size_t* out_length) {
    if (input_list == NULL || out_length == NULL) {
        return NULL;
    }

    if (input_length == 0) {
        *out_length = 0;
        return NULL;
    }

    TupleFreq* frequencies = (TupleFreq*)malloc(input_length * sizeof(TupleFreq));
    if (frequencies == NULL) {
        *out_length = 0;
        return NULL;
    }

    size_t unique_count = 0;

    for (size_t i = 0; i < input_length; i++) {
        int min_val = input_list[i].a < input_list[i].b ? input_list[i].a : input_list[i].b;
        int max_val = input_list[i].a > input_list[i].b ? input_list[i].a : input_list[i].b;

        int found = 0;
        for (size_t j = 0; j < unique_count; j++) {
            if (frequencies[j].tuple.a == min_val && frequencies[j].tuple.b == max_val) {
                frequencies[j].frequency++;
                found = 1;
                break;
            }
        }

        if (!found) {
            frequencies[unique_count].tuple.a = min_val;
            frequencies[unique_count].tuple.b = max_val;
            frequencies[unique_count].frequency = 1;
            unique_count++;
        }
    }

    TupleFreq* resized_frequencies = (TupleFreq*)realloc(frequencies, unique_count * sizeof(TupleFreq));
    if (resized_frequencies == NULL) {
        *out_length = unique_count;
        return frequencies;
    }

    *out_length = unique_count;
    return resized_frequencies;
}

int main(void) {
    Tuple input[] = {
        {1, 2},
        {3, 4},
        {2, 1},
        {5, 6},
        {4, 3},
        {1, 2},
        {7, 8},
        {8, 7}
    };
    
    /* Possible weaknesses found:
     *  Assignment 'input_length=sizeof(input)/sizeof(input[0])', assigned value is 8
     */
    size_t input_length = sizeof(input) / sizeof(input[0]);
    size_t unique_length = 0;

    TupleFreq* frequencies = get_tuple_frequencies(input, input_length, &unique_length);

    /* Possible weaknesses found:
     *  Condition 'input_length>0' is always true [knownConditionTrueFalse]
     *  Condition 'input_length>0' is always true
     */
    if (frequencies == NULL && input_length > 0) {
        fprintf(stderr, "Memory allocation failed.\n");
        return EXIT_FAILURE;
    }

    for (size_t i = 0; i < unique_length; i++) {
        printf("Tuple (%d, %d) occurs %d time(s).\n", 
               frequencies[i].tuple.a, 
               frequencies[i].tuple.b, 
               frequencies[i].frequency);
    }

    free(frequencies);

    return EXIT_SUCCESS;
}