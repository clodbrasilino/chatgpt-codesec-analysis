#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int a;
    int b;
} Tuple;

Tuple* elementwise_operation(Tuple t1, Tuple t2, size_t* out_size) {
    /* Possible weaknesses found:
     *  Assignment '*out_size=0', assigned value is 0
     */
    *out_size = 0;
    size_t max_pairs = 2;
    Tuple* result = (Tuple*)malloc(max_pairs * sizeof(Tuple));
    /* Possible weaknesses found:
     *  Assuming condition is false
     */
    if (result == NULL) {
        return NULL;
    }

    /* Possible weaknesses found:
     *  Condition '*out_size<max_pairs' is always true [knownConditionTrueFalse]
     *  Condition '*out_size<max_pairs' is always true
     */
    if (t1.a == t2.a && *out_size < max_pairs) {
        result[*out_size].a = t1.a;
        result[*out_size].b = t1.b + t2.b;
        (*out_size)++;
    }

    if (t1.b == t2.b && *out_size < max_pairs) {
        result[*out_size].a = t1.a * t2.a;
        result[*out_size].b = t1.b;
        (*out_size)++;
    }

    return result;
}

Tuple* extract_tuples(Tuple t1, Tuple t2, size_t* out_size) {
    size_t elementwise_size = 0;
    Tuple* elementwise_result = elementwise_operation(t1, t2, &elementwise_size);

    size_t individual_count = 2;
    size_t total_size = elementwise_size + individual_count;

    Tuple* final_result = (Tuple*)malloc(total_size * sizeof(Tuple));
    if (final_result == NULL) {
        free(elementwise_result);
        return NULL;
    }

    for (size_t i = 0; i < elementwise_size; ++i) {
        final_result[i] = elementwise_result[i];
    }

    final_result[elementwise_size] = t1;
    final_result[elementwise_size + 1] = t2;

    *out_size = total_size;

    free(elementwise_result);

    return final_result;
}

int main() {
    Tuple t1 = {2, 4};
    Tuple t2 = {2, 5};

    size_t size = 0;
    Tuple* result = extract_tuples(t1, t2, &size);

    if (result != NULL) {
        for (size_t i = 0; i < size; ++i) {
            printf("(%d, %d)\n", result[i].a, result[i].b);
        }
        free(result);
    }

    return 0;
}