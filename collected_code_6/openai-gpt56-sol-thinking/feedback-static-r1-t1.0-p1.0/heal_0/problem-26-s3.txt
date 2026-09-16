#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>

typedef struct {
    const int *elements;
    size_t length;
} Tuple;

bool tuple_list_has_all_k_elements(const Tuple *tuples, size_t tuple_count, int k)
{
    size_t i;
    size_t j;

    if (tuples == NULL || tuple_count == 0U) {
        return false;
    }

    for (i = 0U; i < tuple_count; ++i) {
        if (tuples[i].elements == NULL || tuples[i].length == 0U) {
            return false;
        }

        for (j = 0U; j < tuples[i].length; ++j) {
            if (tuples[i].elements[j] != k) {
                return false;
            }
        }
    }

    return true;
}

int main(void)
{
    const int first[] = {4, 4};
    const int second[] = {4, 4, 4};
    const int third[] = {4, 4};

    const Tuple tuples[] = {
        {first, sizeof(first) / sizeof(first[0])},
        {second, sizeof(second) / sizeof(second[0])},
        {third, sizeof(third) / sizeof(third[0])}
    };

    const size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    const int k = 4;

    printf("%s\n",
           tuple_list_has_all_k_elements(tuples, tuple_count, k)
               ? "true"
               : "false");

    return 0;
}