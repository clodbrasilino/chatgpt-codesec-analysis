#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int print_first_lucky_numbers(size_t count)
{
    size_t capacity;
    size_t *numbers;

    if (count == 0U) {
        return putchar('\n') == EOF ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    capacity = count < 64U ? 64U : count;

    for (;;) {
        size_t length;
        size_t lucky_index;

        if (capacity > SIZE_MAX / sizeof(*numbers) ||
            capacity > (SIZE_MAX - 1U) / 2U) {
            return EXIT_FAILURE;
        }

        numbers = malloc(capacity * sizeof(*numbers));
        if (numbers == NULL) {
            return EXIT_FAILURE;
        }

        for (length = 0U; length < capacity; ++length) {
            numbers[length] = 2U * length + 1U;
        }

        lucky_index = 1U;

        while (lucky_index < length) {
            const size_t lucky = numbers[lucky_index];
            size_t read_index;
            size_t write_index = 0U;

            if (lucky > length) {
                break;
            }

            for (read_index = 0U; read_index < length; ++read_index) {
                if ((read_index + 1U) % lucky != 0U) {
                    numbers[write_index++] = numbers[read_index];
                }
            }

            length = write_index;
            ++lucky_index;
        }

        if (length >= count) {
            size_t i;

            for (i = 0U; i < count; ++i) {
                if (printf("%zu%c", numbers[i],
                           i + 1U == count ? '\n' : ' ') < 0) {
                    free(numbers);
                    return EXIT_FAILURE;
                }
            }

            free(numbers);
            return ferror(stdout) ? EXIT_FAILURE : EXIT_SUCCESS;
        }

        free(numbers);

        if (capacity > SIZE_MAX / 2U) {
            return EXIT_FAILURE;
        }

        capacity *= 2U;
    }
}

int main(int argc, char *const argv[])
{
    char *end;
    uintmax_t value;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    end = NULL;
    value = strtoumax(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' ||
        argv[1][0] == '-' || value > (uintmax_t)SIZE_MAX) {
        fprintf(stderr, "Invalid value for n\n");
        return EXIT_FAILURE;
    }

    return print_first_lucky_numbers((size_t)value);
}