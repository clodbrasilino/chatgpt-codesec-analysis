#include <errno.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

static int print_first_lucky_numbers(size_t count)
{
    size_t capacity = 0;
    size_t *numbers = NULL;
    size_t length;
    size_t index;

    if (count == 0) {
        return 0;
    }

    if (count > (SIZE_MAX - 1U) / 2U) {
        return -1;
    }

    capacity = count * 2U + 1U;

    for (;;) {
        size_t step_index;

        if (capacity > SIZE_MAX / sizeof(*numbers)) {
            return -1;
        }

        numbers = malloc(capacity * sizeof(*numbers));
        if (numbers == NULL) {
            return -1;
        }

        length = (capacity + 1U) / 2U;
        for (index = 0; index < length; ++index) {
            numbers[index] = index * 2U + 1U;
        }

        step_index = 1U;
        while (step_index < length) {
            size_t step = numbers[step_index];
            size_t read_index;
            size_t write_index = 0U;

            if (step > length) {
                break;
            }

            for (read_index = 0U; read_index < length; ++read_index) {
                if ((read_index + 1U) % step != 0U) {
                    numbers[write_index++] = numbers[read_index];
                }
            }

            length = write_index;
            ++step_index;
        }

        if (length >= count) {
            break;
        }

        free(numbers);
        numbers = NULL;

        if (capacity > (SIZE_MAX - 1U) / 2U) {
            return -1;
        }

        capacity = capacity * 2U + 1U;
    }

    for (index = 0U; index < count; ++index) {
        if (printf("%zu%s", numbers[index], index + 1U == count ? "\n" : " ") < 0) {
            free(numbers);
            return -1;
        }
    }

    free(numbers);
    return 0;
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    unsigned long long value;
    size_t count;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoull(argv[1], &end, 10);

    if (errno == ERANGE || end == argv[1] || *end != '\0' ||
        argv[1][0] == '-' || value > SIZE_MAX) {
        fprintf(stderr, "Invalid value for n\n");
        return EXIT_FAILURE;
    }

    count = (size_t)value;

    if (print_first_lucky_numbers(count) != 0) {
        fprintf(stderr, "Unable to generate or print lucky numbers\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}