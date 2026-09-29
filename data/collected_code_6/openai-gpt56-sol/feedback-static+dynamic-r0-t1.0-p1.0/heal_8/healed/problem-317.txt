#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *value;
    size_t length;
    size_t count;
} Run;

typedef struct {
    Run *runs;
    size_t size;
} EncodedList;

static int duplicate_string(const char *source, size_t length, char **destination)
{
    char *copy;

    if (destination == NULL) {
        return -1;
    }

    *destination = NULL;

    if (source == NULL || length > SIZE_MAX - 1U) {
        return -1;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return -1;
    }

    if (length != 0U) {
        memcpy(copy, source, length);
    }

    copy[length] = '\0';
    *destination = copy;
    return 0;
}

static void free_encoded_list(EncodedList *encoded)
{
    if (encoded == NULL) {
        return;
    }

    for (size_t i = 0U; i < encoded->size; ++i) {
        free(encoded->runs[i].value);
    }

    free(encoded->runs);
    encoded->runs = NULL;
    encoded->size = 0U;
}

static int modified_run_length_encode(
    const char *const input[],
    const size_t input_lengths[],
    size_t input_size,
    EncodedList *result)
{
    Run *runs = NULL;
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
        size_t length = input_lengths[i];

        if (input[i] == NULL || length > SIZE_MAX - 1U) {
            goto failure;
        }

        while (count < input_size - i) {
            size_t next = i + count;

            if (input[next] == NULL ||
                input_lengths[next] > SIZE_MAX - 1U) {
                goto failure;
            }

            if (input_lengths[next] != length) {
                break;
            }

            if (length != 0U &&
                memcmp(input[i], input[next], length) != 0) {
                break;
            }

            ++count;
        }

        if (duplicate_string(
                input[i], length, &runs[run_count].value) != 0) {
            goto failure;
        }

        runs[run_count].length = length;
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

static int print_quoted_string(const char *value, size_t length)
{
    if (value == NULL || putchar('"') == EOF) {
        return -1;
    }

    for (size_t i = 0U; i < length; ++i) {
        unsigned char ch = (unsigned char)value[i];
        int status;

        switch (ch) {
        case '"':
            status = fputs("\\\"", stdout);
            break;
        case '\\':
            status = fputs("\\\\", stdout);
            break;
        case '\b':
            status = fputs("\\b", stdout);
            break;
        case '\f':
            status = fputs("\\f", stdout);
            break;
        case '\n':
            status = fputs("\\n", stdout);
            break;
        case '\r':
            status = fputs("\\r", stdout);
            break;
        case '\t':
            status = fputs("\\t", stdout);
            break;
        default:
            if (ch < 0x20U || ch >= 0x80U) {
                status = fprintf(stdout, "\\u%04x", (unsigned int)ch);
            } else {
                status = putchar((int)ch);
            }
            break;
        }

        if (status < 0) {
            return -1;
        }
    }

    return putchar('"') == EOF ? -1 : 0;
}

static int print_encoded_list(const EncodedList *encoded)
{
    if (encoded == NULL ||
        (encoded->size != 0U && encoded->runs == NULL)) {
        return -1;
    }

    if (putchar('[') == EOF) {
        return -1;
    }

    for (size_t i = 0U; i < encoded->size; ++i) {
        const Run *run = &encoded->runs[i];

        if (run->value == NULL || run->count == 0U) {
            return -1;
        }

        if (i != 0U && fputs(", ", stdout) == EOF) {
            return -1;
        }

        if (run->count > 1U &&
            fprintf(stdout, "[%zu, ", run->count) < 0) {
            return -1;
        }

        if (print_quoted_string(run->value, run->length) != 0) {
            return -1;
        }

        if (run->count > 1U && putchar(']') == EOF) {
            return -1;
        }
    }

    return puts("]") == EOF ? -1 : 0;
}

int main(void)
{
    static const char *const input[] = {
        "a", "a", "a", "b", "c", "c", "a",
        "a", "d", "e", "e", "e", "e"
    };

    static const size_t input_lengths[] = {
        sizeof("a") - 1U,
        sizeof("a") - 1U,
        sizeof("a") - 1U,
        sizeof("b") - 1U,
        sizeof("c") - 1U,
        sizeof("c") - 1U,
        sizeof("a") - 1U,
        sizeof("a") - 1U,
        sizeof("d") - 1U,
        sizeof("e") - 1U,
        sizeof("e") - 1U,
        sizeof("e") - 1U,
        sizeof("e") - 1U
    };

    const size_t input_count = sizeof(input) / sizeof(input[0]);
    const size_t length_count =
        sizeof(input_lengths) / sizeof(input_lengths[0]);
    EncodedList encoded = {NULL, 0U};
    int status;

    if (input_count != length_count) {
        fputs("Invalid input.\n", stderr);
        return EXIT_FAILURE;
    }

    if (modified_run_length_encode(
            input, input_lengths, input_count, &encoded) != 0) {
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