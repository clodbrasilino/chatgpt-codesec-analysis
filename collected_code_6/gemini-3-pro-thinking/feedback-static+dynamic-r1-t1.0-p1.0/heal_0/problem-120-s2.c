#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int first;
    int second;
} Tuple;

int find_max_tuple_product(const Tuple *tuples, size_t count, long long *out_max_product) {
    if (tuples == NULL || out_max_product == NULL || count == 0) {
        return -1;
    }

    long long max_product = (long long)tuples[0].first * (long long)tuples[0].second;

    for (size_t i = 1; i < count; i++) {
        long long current_product = (long long)tuples[i].first * (long long)tuples[i].second;
        if (current_product > max_product) {
            max_product = current_product;
        }
    }

    *out_max_product = max_product;
    
    return 0;
}

int main(void) {
    size_t tuple_count = 5;
    Tuple *tuples = malloc(tuple_count * sizeof(Tuple));
    if (tuples == NULL) {
        return EXIT_FAILURE;
    }

    tuples[0].first = 3;
    tuples[0].second = 5;
    tuples[1].first = -10;
    tuples[1].second = -5;
    tuples[2].first = 7;
    tuples[2].second = 6;
    tuples[3].first = 0;
    tuples[3].second = 100;
    tuples[4].first = -4;
    tuples[4].second = 12;

    long long max_product = 0;
    int status = find_max_tuple_product(tuples, tuple_count, &max_product);

    if (status == 0) {
        printf("%lld\n", max_product);
    }

    free(tuples);
    tuples = NULL;

    return (status == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}