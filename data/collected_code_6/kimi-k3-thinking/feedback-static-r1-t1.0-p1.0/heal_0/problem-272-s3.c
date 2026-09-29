#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef struct {
    int *data;
    size_t size;
} Tuple;

int extract_rear_elements(const Tuple *tuples, size_t count, int **out_rear, size_t *out_count)
{
    int *rear;
    size_t i;

    if (out_rear == NULL || out_count == NULL) {
        return -1;
    }

    *out_rear = NULL;
    *out_count = 0;

    if (count == 0) {
        return 0;
    }

    if (tuples == NULL) {
        return -1;
    }

    if (count > SIZE_MAX / sizeof(*rear)) {
        return -1;
    }

    rear = malloc(count * sizeof(*rear));
    if (rear == NULL) {
        return -1;
    }

    for (i = 0; i < count; i++) {
        if (tuples[i].data == NULL || tuples[i].size == 0) {
            free(rear);
            return -1;
        }
        rear[i] = tuples[i].data[tuples[i].size - 1];
    }

    *out_rear = rear;
    *out_count = count;
    return 0;
}

int main(void)
{
    int a[] = {1, 2, 3};
    int b[] = {4, 5};
    int c[] = {6, 7, 8, 9};
    Tuple tuples[3];
    int *rear = NULL;
    size_t count = 0;
    size_t i;

    tuples[0].data = a;
    tuples[0].size = sizeof(a) / sizeof(a[0]);
    tuples[1].data = b;
    tuples[1].size = sizeof(b) / sizeof(b[0]);
    tuples[2].data = c;
    tuples[2].size = sizeof(c) / sizeof(c[0]);

    if (extract_rear_elements(tuples, 3, &rear, &count) != 0) {
        fprintf(stderr, "Error: failed to extract rear elements\n");
        return EXIT_FAILURE;
    }

    printf("Rear elements: ");
    for (i = 0; i < count; i++) {
        printf("%d ", rear[i]);
    }
    printf("\n");

    free(rear);
    rear = NULL;

    return EXIT_SUCCESS;
}