#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int x;
    int y;
} Tuple;

static int lambda_cmp(const void *a, const void *b) {
    const Tuple *t1 = (const Tuple *)a;
    const Tuple *t2 = (const Tuple *)b;
    
    if (t1->x != t2->x) {
        return (t1->x > t2->x) - (t1->x < t2->x);
    }
    return (t1->y > t2->y) - (t1->y < t2->y);
}

void sort_tuples(Tuple *array, size_t size) {
    if (array == NULL || size == 0) {
        return;
    }
    qsort(array, size, sizeof(Tuple), lambda_cmp);
}

int main(void) {
    Tuple tuples[] = {
        {5, 2},
        {1, 9},
        {3, 4},
        {1, 2},
        {3, 1}
    };
    
    size_t size = sizeof(tuples) / sizeof(tuples[0]);

    sort_tuples(tuples, size);

    for (size_t i = 0; i < size; i++) {
        if (printf("(%d, %d)\n", tuples[i].x, tuples[i].y) < 0) {
            return EXIT_FAILURE;
        }
    }

    return EXIT_SUCCESS;
}