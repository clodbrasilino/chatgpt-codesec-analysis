#include <stdio.h>
#include <stdlib.h>

struct Pair {
    int first;
    int second;
};

static int comparePairs(const void *a, const void *b)
{
    const struct Pair *pa = (const struct Pair *)a;
    const struct Pair *pb = (const struct Pair *)b;

    if (pa->second < pb->second) {
        return -1;
    }
    if (pa->second > pb->second) {
        return 1;
    }
    return 0;
}

int longestChain(struct Pair *pairs, size_t n)
{
    size_t i;
    int count;
    int currentEnd;

    if (pairs == NULL || n == 0U) {
        return 0;
    }

    qsort(pairs, n, sizeof(struct Pair), comparePairs);

    count = 1;
    currentEnd = pairs[0].second;

    for (i = 1U; i < n; i++) {
        if (pairs[i].first > currentEnd) {
            count++;
            currentEnd = pairs[i].second;
        }
    }

    return count;
}

int main(void)
{
    size_t n = 5U;
    struct Pair *pairs;
    int result;

    pairs = (struct Pair *)malloc(n * sizeof(struct Pair));
    if (pairs == NULL) {
        (void)fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    pairs[0].first = 5;
    pairs[0].second = 24;
    pairs[1].first = 15;
    pairs[1].second = 25;
    pairs[2].first = 27;
    pairs[2].second = 40;
    pairs[3].first = 50;
    pairs[3].second = 60;
    pairs[4].first = 1;
    pairs[4].second = 3;

    result = longestChain(pairs, n);

    if (printf("Length of the longest chain is %d\n", result) < 0) {
        free(pairs);
        return EXIT_FAILURE;
    }

    free(pairs);
    pairs = NULL;

    return EXIT_SUCCESS;
}