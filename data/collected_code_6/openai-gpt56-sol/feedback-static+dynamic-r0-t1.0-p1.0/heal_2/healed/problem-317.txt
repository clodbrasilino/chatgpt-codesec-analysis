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
        size_t length;
        char *value;

        if (input[i] == NULL) {
            goto failure;
        }

        length = input_lengths[i];

        while (count < input_size - i) {
            size_t next = i + count;

            if (input[next] == NULL) {
                goto failure;
            }

            if (input_lengths[next] != length) {
                break;
            }

            if (length > 0U &&
                memcmp(input[i], input[next], length) != 0) {
                break;
            }

            ++count;
        }

        value = duplicate_string(input[i], length);
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
        int status;

        switch (*p) {
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
            if (*p < 0x20U) {
                status = printf("\\u%04x", (unsigned int)*p);
            } else {
                status = putchar((int)*p);
            }
            break;
        }

        if (status < 0) {
            return -1;
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
        const Run *run = &encoded->runs[i];

        if (run->value == NULL || run->count == 0U) {
            return -1;
        }

        if (i != 0U && fputs(", ", stdout) == EOF) {
            return -1;
        }

        if (run->count != 1U &&
            printf("[%zu, ", run->count) < 0) {
            return -1;
        }

        if (print_quoted_string(run->value) != 0) {
            return -1;
        }

        if (run->count != 1U && putchar(']') == EOF) {
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
    EncodedList encoded = {NULL, 0U};
    int status;

    status = modified_run_length_encode(
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