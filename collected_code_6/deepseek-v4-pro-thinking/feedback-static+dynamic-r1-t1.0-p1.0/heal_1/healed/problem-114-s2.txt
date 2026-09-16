#include <stddef.h>
#include <stdio.h>

typedef struct {
    int first;
    int second;
    size_t frequency;
} Tuple;

void assign_frequency(Tuple *tuples, size_t count)
{
    size_t i;
    size_t j;

    if (tuples == NULL || count == 0) {
        return;
    }

    for (i = 0; i < count; ++i) {
        size_t freq = 0;
        for (j = 0; j < count; ++j) {
            if (tuples[j].first == tuples[i].first &&
                tuples[j].second == tuples[i].second) {
                ++freq;
            }
        }
        tuples[i].frequency = freq;
    }
}

int main(void)
{
    Tuple tuples[] = {
        {1, 2, 0},
        {3, 4, 0},
        {1, 2, 0},
        {5, 6, 0},
        {3, 4, 0}
    };
    size_t count;
    size_t i;

    count = sizeof(tuples) / sizeof(tuples[0]);
    assign_frequency(tuples, count);

    for (i = 0; i < count; ++i) {
        printf("(%d, %d): %zu\n", tuples[i].first, tuples[i].second, tuples[i].frequency);
    }

    return 0;
}