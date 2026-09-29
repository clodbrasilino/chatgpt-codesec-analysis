#include <errno.h>
#include <inttypes.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int print_first_lucky_numbers(size_t count)
{
    size_t capacity;

    if (count == 0U) {
        putchar('\n');
        return ferror(stdout) ? EXIT_FAILURE : EXIT_SUCCESS;
    }

    if (count > SIZE_MAX / 8U) {
        return EXIT_FAILURE;
    }

    capacity = count * 8U;
    if (capacity < 64U) {
        capacity = 64U;
    }

    for (;;) {
        unsigned char *numbers = malloc(capacity);
        unsigned char *filtered = malloc(capacity);
        size_t length;
        size_t filter_index = 1U;
        size_t i;

        if (numbers == NULL || filtered == NULL) {
            free(numbers);
            free(filtered);
            return EXIT_FAILURE;
        }

        length = (capacity + 1U) / 2U;

        for (i = 0U; i < length; ++i) {
            numbers[i] = 1U;
        }

        for (;;) {
            size_t lucky = 0U;
            size_t position = 0U;
            size_t output_length = 0U;

            for (i = 0U; i < length; ++i) {
                if (numbers[i] != 0U) {
                    if (position == filter_index) {
                        lucky = (i * 2U) + 1U;
                        break;
                    }
                    ++position;
                }
            }

            if (lucky == 0U || lucky > length) {
                break;
            }

            position = 0U;
            for (i = 0U; i < length; ++i) {
                if (numbers[i] != 0U) {
                    ++position;
                    if (position % lucky != 0U) {
                        filtered[output_length++] = 1U;
                    }
                } else {
                    filtered[output_length++] = 0U;
                }
            }

            output_length = 0U;
            for (i = 0U; i < length; ++i) {
                if (filtered[i] != 0U) {
                    numbers[output_length++] = 1U;
                }
            }

            length = output_length;
            ++filter_index;

            if (filter_index >= count) {
                break;
            }
        }

        if (length >= count) {
            for (i = 0U; i < count; ++i) {
                size_t value = (i * 2U) + 1U;

                if (printf("%zu%s", value,
                           i + 1U == count ? "\n" : " ") < 0) {
                    free(numbers);
                    free(filtered);
                    return EXIT_FAILURE;
                }
            }

            free(numbers);
            free(filtered);
            return ferror(stdout) ? EXIT_FAILURE : EXIT_SUCCESS;
        }

        free(numbers);
        free(filtered);

        if (capacity > SIZE_MAX / 2U) {
            return EXIT_FAILURE;
        }

        capacity *= 2U;
    }
}

/* Possible weaknesses found:
 *  Parameter 'argv' can be declared as const array [constParameter]
 */
int main(int argc, char *const argv[])
{
    char *end = NULL;
    uintmax_t value;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(argv[1], &end, 10);

    if (errno != 0 || end == argv[1] || *end != '\0' ||
        value > (uintmax_t)SIZE_MAX) {
        fprintf(stderr, "Invalid value for n\n");
        return EXIT_FAILURE;
    }

    return print_first_lucky_numbers((size_t)value);
}