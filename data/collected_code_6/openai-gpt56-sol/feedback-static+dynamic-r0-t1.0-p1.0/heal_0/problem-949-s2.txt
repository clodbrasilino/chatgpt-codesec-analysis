#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

typedef struct {
    long long first;
    long long second;
} Tuple;

static size_t digit_count(long long value)
{
    unsigned long long magnitude;

    if (value < 0) {
        magnitude = 0ULL - (unsigned long long)value;
    } else {
        magnitude = (unsigned long long)value;
    }

    size_t count = 1U;
    while (magnitude >= 10ULL) {
        magnitude /= 10ULL;
        ++count;
    }

    return count;
}

static size_t tuple_digit_count(const Tuple *tuple)
{
    return digit_count(tuple->first) + digit_count(tuple->second);
}

static int compare_tuples(const void *left, const void *right)
{
    const Tuple *a = left;
    const Tuple *b = right;
    const size_t a_digits = tuple_digit_count(a);
    const size_t b_digits = tuple_digit_count(b);

    if (a_digits < b_digits) {
        return -1;
    }
    if (a_digits > b_digits) {
        return 1;
    }
    if (a->first < b->first) {
        return -1;
    }
    if (a->first > b->first) {
        return 1;
    }
    if (a->second < b->second) {
        return -1;
    }
    if (a->second > b->second) {
        return 1;
    }

    return 0;
}

static int sort_tuples_by_total_digits(Tuple *tuples, size_t count)
{
    if (tuples == NULL && count != 0U) {
        return -1;
    }

    if (count > 1U) {
        qsort(tuples, count, sizeof(*tuples), compare_tuples);
    }

    return 0;
}

int main(void)
{
    size_t count;

    if (scanf("%zu", &count) != 1) {
        fputs("Invalid tuple count\n", stderr);
        return EXIT_FAILURE;
    }

    if (count > SIZE_MAX / sizeof(Tuple)) {
        fputs("Tuple count is too large\n", stderr);
        return EXIT_FAILURE;
    }

    Tuple *tuples = count == 0U ? NULL : malloc(count * sizeof(*tuples));
    if (count != 0U && tuples == NULL) {
        perror("malloc");
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (scanf("%lld %lld", &tuples[i].first, &tuples[i].second) != 2) {
            fputs("Invalid tuple input\n", stderr);
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    if (sort_tuples_by_total_digits(tuples, count) != 0) {
        fputs("Unable to sort tuples\n", stderr);
        free(tuples);
        return EXIT_FAILURE;
    }

    for (size_t i = 0U; i < count; ++i) {
        if (printf("(%lld, %lld)\n", tuples[i].first, tuples[i].second) < 0) {
            fputs("Output error\n", stderr);
            free(tuples);
            return EXIT_FAILURE;
        }
    }

    free(tuples);

    if (fflush(stdout) == EOF) {
        fputs("Output error\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}