#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
    int rear;
} Tuple;

int extract_rear(const Tuple *records, size_t count, int **result)
{
    int *output = NULL;
    size_t i;

    if (records == NULL || result == NULL || count == 0U) {
        return -1;
    }

    output = malloc(count * sizeof(*output));
    if (output == NULL) {
        return -1;
    }

    for (i = 0U; i < count; i++) {
        output[i] = records[i].rear;
    }

    *result = output;
    return 0;
}

int main(void)
{
    Tuple records[] = {
        {1, 2, 21},
        {3, 4, 20},
        {5, 6, 19}
    };
    size_t count = sizeof(records) / sizeof(records[0]);
    int *rears = NULL;
    size_t i;

    if (extract_rear(records, count, &rears) != 0) {
        fprintf(stderr, "Extraction failed\n");
        return EXIT_FAILURE;
    }

    printf("Rear elements: ");
    for (i = 0U; i < count; i++) {
        printf("%d ", rears[i]);
    }
    printf("\n");

    free(rears);
    rears = NULL;

    return EXIT_SUCCESS;
}