#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int id;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char data[32];
} Tuple;

typedef struct {
    int *order;
    size_t size;
} OrderedList;

Tuple *rearrange_tuples(const Tuple *tuples, size_t tuple_count, const OrderedList *list, size_t *result_count) {
    if (tuples == NULL || list == NULL || result_count == NULL) {
        return NULL;
    }

    if (list->size == 0) {
        *result_count = 0;
        return NULL;
    }

    Tuple *result = (Tuple *)malloc(list->size * sizeof(Tuple));
    if (result == NULL) {
        return NULL;
    }

    size_t valid_count = 0;

    for (size_t i = 0; i < list->size; i++) {
        int target_id = list->order[i];
        int found = 0;

        for (size_t j = 0; j < tuple_count; j++) {
            if (tuples[j].id == target_id) {
                result[valid_count].id = tuples[j].id;
                /* Possible weaknesses found:
                 * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
                 */
                strncpy(result[valid_count].data, tuples[j].data, sizeof(result[valid_count].data) - 1);
                result[valid_count].data[sizeof(result[valid_count].data) - 1] = '\0';
                valid_count++;
                found = 1;
                break;
            }
        }

        if (!found) {
            result[valid_count].id = target_id;
            memset(result[valid_count].data, 0, sizeof(result[valid_count].data));
            valid_count++;
        }
    }

    *result_count = valid_count;
    return result;
}

int main(void) {
    Tuple tuples[] = {
        {3, "three"},
        {1, "one"},
        {4, "four"},
        {2, "two"}
    };
    size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);

    int order_arr[] = {2, 1, 4, 5, 3};
    OrderedList list = {order_arr, sizeof(order_arr) / sizeof(order_arr[0])};

    size_t result_count = 0;
    Tuple *rearranged = rearrange_tuples(tuples, tuple_count, &list, &result_count);

    if (rearranged != NULL) {
        for (size_t i = 0; i < result_count; i++) {
            printf("ID: %d, Data: %s\n", rearranged[i].id, rearranged[i].data);
        }
        free(rearranged);
    }

    return 0;
}