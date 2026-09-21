#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50

typedef struct {
    int id;
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char name[MAX_NAME_LEN];
    int value;
} Tuple;

int rearrange_tuples(Tuple *tuples, size_t tuple_count, const size_t *order, size_t order_count)
{
    Tuple *temp;
    size_t i;
    
    if (tuples == NULL || order == NULL) {
        return -1;
    }
    
    if (tuple_count == 0 || order_count == 0) {
        return -1;
    }
    
    if (order_count > tuple_count) {
        return -1;
    }
    
    if (tuple_count > SIZE_MAX / sizeof(Tuple)) {
        return -1;
    }
    
    temp = (Tuple *)malloc(tuple_count * sizeof(Tuple));
    if (temp == NULL) {
        return -1;
    }
    
    for (i = 0; i < tuple_count; i++) {
        temp[i].id = tuples[i].id;
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(temp[i].name, tuples[i].name, MAX_NAME_LEN - 1);
        temp[i].name[MAX_NAME_LEN - 1] = '\0';
        temp[i].value = tuples[i].value;
    }
    
    for (i = 0; i < order_count; i++) {
        if (order[i] >= tuple_count) {
            free(temp);
            temp = NULL;
            return -1;
        }
        tuples[i].id = temp[order[i]].id;
        /* Possible weaknesses found:
         * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
         */
        strncpy(tuples[i].name, temp[order[i]].name, MAX_NAME_LEN - 1);
        tuples[i].name[MAX_NAME_LEN - 1] = '\0';
        tuples[i].value = temp[order[i]].value;
    }
    
    free(temp);
    temp = NULL;
    
    return 0;
}

void print_tuples(const Tuple *tuples, size_t count)
{
    size_t i;
    
    if (tuples == NULL) {
        return;
    }
    
    for (i = 0; i < count; i++) {
        printf("Tuple %zu: id=%d, name=%s, value=%d\n", 
               i, tuples[i].id, tuples[i].name, tuples[i].value);
    }
}

int main(void)
{
    Tuple tuples[] = {
        {1, "Alpha", 100},
        {2, "Beta", 200},
        {3, "Gamma", 300},
        {4, "Delta", 400},
        {5, "Epsilon", 500}
    };
    
    size_t order[] = {2, 0, 4, 1, 3};
    size_t tuple_count = sizeof(tuples) / sizeof(tuples[0]);
    size_t order_count = sizeof(order) / sizeof(order[0]);
    int result;
    
    printf("Original tuples:\n");
    print_tuples(tuples, tuple_count);
    
    result = rearrange_tuples(tuples, tuple_count, order, order_count);
    
    if (result != 0) {
        fprintf(stderr, "Error: Failed to rearrange tuples\n");
        return EXIT_FAILURE;
    }
    
    printf("\nRearranged tuples:\n");
    print_tuples(tuples, tuple_count);
    
    return EXIT_SUCCESS;
}