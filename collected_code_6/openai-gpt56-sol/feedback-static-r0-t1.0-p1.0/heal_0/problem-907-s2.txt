#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int generate_lucky_numbers(size_t count, unsigned long long **result)
{
    unsigned long long *numbers = NULL;
    size_t capacity;
    size_t length;
    size_t sieve_index;

    if (result == NULL || count == 0U) {
        return EINVAL;
    }

    if (count > (SIZE_MAX / sizeof(*numbers))) {
        return EOVERFLOW;
    }

    capacity = count;
    for (;;) {
        unsigned long long candidate;
        size_t i;

        if (capacity > (SIZE_MAX / sizeof(*numbers))) {
            return EOVERFLOW;
        }

        numbers = malloc(capacity * sizeof(*numbers));
        if (numbers == NULL) {
            return ENOMEM;
        }

        for (i = 0U; i < capacity; ++i) {
            if (i > ((ULLONG_MAX - 1ULL) / 2ULL)) {
                free(numbers);
                return EOVERFLOW;
            }
            candidate = (2ULL * (unsigned long long)i) + 1ULL;
            numbers[i] = candidate;
        }

        length = capacity;
        sieve_index = 1U;

        while (sieve_index < length) {
            unsigned long long step_value = numbers[sieve_index];
            size_t step;
            size_t read_index;
            size_t write_index;

            if (step_value > (unsigned long long)SIZE_MAX) {
                break;
            }

            step = (size_t)step_value;
            if (step > length) {
                break;
            }

            write_index = 0U;
            for (read_index = 0U; read_index < length; ++read_index) {
                if (((read_index + 1U) % step) != 0U) {
                    numbers[write_index++] = numbers[read_index];
                }
            }

            length = write_index;
            ++sieve_index;
        }

        if (length >= count) {
            *result = numbers;
            return 0;
        }

        free(numbers);
        numbers = NULL;

        if (capacity > (SIZE_MAX / 2U)) {
            return EOVERFLOW;
        }
        capacity *= 2U;
    }
}

static int print_lucky_numbers(size_t count)
{
    unsigned long long *numbers = NULL;
    size_t i;
    int status;

    status = generate_lucky_numbers(count, &numbers);
    if (status != 0) {
        return status;
    }

    for (i = 0U; i < count; ++i) {
        if (printf("%s%llu", i == 0U ? "" : " ", numbers[i]) < 0) {
            free(numbers);
            return EIO;
        }
    }

    if (putchar('\n') == EOF) {
        free(numbers);
        return EIO;
    }

    free(numbers);
    return 0;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    unsigned long long parsed;
    size_t count;
    int status;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    parsed = strtoull(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' || parsed == 0ULL ||
        parsed > (unsigned long long)SIZE_MAX) {
        fputs("Invalid value for n\n", stderr);
        return EXIT_FAILURE;
    }

    count = (size_t)parsed;
    status = print_lucky_numbers(count);
    if (status != 0) {
        errno = status;
        perror("Unable to print lucky numbers");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}