#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *value;
    size_t count;
} Run;

typedef struct {
    Run *runs;
    size_t size;
} EncodedList;

static char *duplicate_string(const char *source, size_t length)
{
    char *copy;

    if (source == NULL || length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    if (length > 0U) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, source, length);
    }

    copy[length] = '\0';
    return copy;
}

static void free_encoded_list(EncodedList *encoded)
{
    if (encoded == NULL) {
        return;
    }

    if (encoded->runs != NULL) {
        for (size_t i = 0U; i < encoded->size; ++i) {
            free(encoded->runs[i].value);
        }

        free(encoded->runs);
    }

    encoded->runs = NULL;
    encoded->size = 0U;
}

static int modified_run_length_encode(
    const char *const input[],
    const size_t input_lengths[],
    size_t input_size,
    EncodedList *result)
{
    Run *runs;
    size_t run_count = 0U;
    size_t i = 0U;

    if (result == NULL) {
        return -1;
    }

    result->runs = NULL;
    result->size = 0U;

    if (input_size == 0U) {
        return 0;
    }

    if (input == NULL ||
        input_lengths == NULL ||
        input_size > SIZE_MAX / sizeof(*runs)) {
        return -1;
    }

    runs = calloc(input_size, sizeof(*runs));
    if (runs == NULL) {
        return -1;
    }

    while (i < input_size) {
        size_t count = 1U;
        char *value;

        if (input[i] == NULL || input_lengths[i] == SIZE_MAX) {
            goto failure;
        }

        while (count < input_size - i) {
            size_t next = i + count;

            if (input[next] == NULL || input_lengths[next] == SIZE_MAX) {
                goto failure;
            }

            if (input_lengths[i] != input_lengths[next] ||
                (input_lengths[i] != 0U &&
                 memcmp(input[i], input[next], input_lengths[i]) != 0)) {
                break;
            }

            ++count;
        }

        value = duplicate_string(input[i], input_lengths[i]);
        if (value == NULL) {
            goto failure;
        }

        runs[run_count].value = value;
        runs[run_count].count = count;
        ++run_count;
        i += count;
    }

    result->runs = runs;
    result->size = run_count;
    return 0;

failure:
    for (size_t j = 0U; j < run_count; ++j) {
        free(runs[j].value);
    }
    free(runs);
    return -1;
}

static int print_quoted_string(const char *value)
{
    const unsigned char *p;

    if (value == NULL) {
        return -1;
    }

    p = (const unsigned char *)value;

    if (putchar('"') == EOF) {
        return -1;
    }

    while (*p != '\0') {
        switch (*p) {
        case '"':
            if (fputs("\\\"", stdout) == EOF) {
                return -1;
            }
            break;
        case '\\':
            if (fputs("\\\\", stdout) == EOF) {
                return -1;
            }
            break;
        case '\b':
            if (fputs("\\b", stdout) == EOF) {
                return -1;
            }
            break;
        case '\f':
            if (fputs("\\f", stdout) == EOF) {
                return -1;
            }
            break;
        case '\n':
            if (fputs("\\n", stdout) == EOF) {
                return -1;
            }
            break;
        case '\r':
            if (fputs("\\r", stdout) == EOF) {
                return -1;
            }
            break;
        case '\t':
            if (fputs("\\t", stdout) == EOF) {
                return -1;
            }
            break;
        default:
            if (*p < 0x20U) {
                if (printf("\\u%04x", (unsigned int)*p) < 0) {
                    return -1;
                }
            } else if (putchar((int)*p) == EOF) {
                return -1;
            }
            break;
        }

        ++p;
    }

    return putchar('"') == EOF ? -1 : 0;
}

static int print_encoded_list(const EncodedList *encoded)
{
    if (encoded == NULL ||
        (encoded->runs == NULL && encoded->size != 0U)) {
        return -1;
    }

    if (putchar('[') == EOF) {
        return -1;
    }

    for (size_t i = 0U; i < encoded->size; ++i) {
        if (encoded->runs[i].value == NULL ||
            encoded->runs[i].count == 0U) {
            return -1;
        }

        if (i != 0U && fputs(", ", stdout) == EOF) {
            return -1;
        }

        if (encoded->runs[i].count != 1U &&
            printf("[%zu, ", encoded->runs[i].count) < 0) {
            return -1;
        }

        if (print_quoted_string(encoded->runs[i].value) != 0) {
            return -1;
        }

        if (encoded->runs[i].count != 1U &&
            putchar(']') == EOF) {
            return -1;
        }
    }

    return puts("]") == EOF ? -1 : 0;
}

int main(void)
{
    static const char value_a[] = "a";
    static const char value_b[] = "b";
    static const char value_c[] = "c";
    static const char value_d[] = "d";
    static const char value_e[] = "e";

    const char *input[] = {
        value_a, value_a, value_a, value_b, value_c, value_c,
        value_a, value_a, value_d, value_e, value_e, value_e, value_e
    };

    const size_t input_lengths[] = {
        sizeof(value_a) - 1U,
        sizeof(value_a) - 1U,
        sizeof(value_a) - 1U,
        sizeof(value_b) - 1U,
        sizeof(value_c) - 1U,
        sizeof(value_c) - 1U,
        sizeof(value_a) - 1U,
        sizeof(value_a) - 1U,
        sizeof(value_d) - 1U,
        sizeof(value_e) - 1U,
        sizeof(value_e) - 1U,
        sizeof(value_e) - 1U,
        sizeof(value_e) - 1U
    };

    EncodedList encoded = {NULL, 0U};
    int status = modified_run_length_encode(
        input,
        input_lengths,
        sizeof(input) / sizeof(input[0]),
        &encoded);

    if (status != 0) {
        fputs("Encoding failed.\n", stderr);
        return EXIT_FAILURE;
    }

    status = print_encoded_list(&encoded);
    free_encoded_list(&encoded);

    if (status != 0) {
        fputs("Output failed.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}