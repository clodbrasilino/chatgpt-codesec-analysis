#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

static int print_first_lucky_numbers(size_t count)
{
    unsigned char *numbers = NULL;
    unsigned char *filtered = NULL;
    size_t capacity;
    size_t length;
    size_t filter_index;

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
        size_t i;

        numbers = malloc(capacity);
        filtered = malloc(capacity);
        if (numbers == NULL || filtered == NULL) {
            free(numbers);
            free(filtered);
            return EXIT_FAILURE;
        }

        length = (capacity + 1U) / 2U;
        for (i = 0U; i < length; ++i) {
            numbers[i] = 1U;
        }

        filter_index = 1U;
        for (;;) {
            size_t lucky;
            size_t position;
            size_t output_length = 0U;

            position = 0U;
            lucky = 0U;
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

            for (i = 0U; i < length; ++i) {
                numbers[i] = 0U;
            }

            output_length = 0U;
            position = 0U;
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

                if (printf("%zu%s", value, i + 1U == count ? "\n" : " ") < 0) {
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
        numbers = NULL;
        filtered = NULL;

        if (capacity > SIZE_MAX / 2U) {
            return EXIT_FAILURE;
        }
        capacity *= 2U;
    }
}

int main(int argc, char *argv[])
{
    char *end = NULL;
    uintmax_t value;

    if (argc != 2) {
        fprintf(stderr, "Usage: %s n\n", argv[0]);
        return EXIT_FAILURE;
    }

    errno = 0;
    value = strtoumax(argv[1], &end, 10);
    if (errno != 0 || end == argv[1] || *end != '\0' || value > SIZE_MAX) {
        fprintf(stderr, "Invalid value for n\n");
        return EXIT_FAILURE;
    }

    return print_first_lucky_numbers((size_t)value);
}