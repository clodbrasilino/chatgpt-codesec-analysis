#include <errno.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

enum { MAX_INPUT_LENGTH = 1048576 };

static int compare_digits_descending(const void *left, const void *right)
{
    const unsigned char a = *(const unsigned char *)left;
    const unsigned char b = *(const unsigned char *)right;

    return (a < b) - (a > b);
}

static char *largest_number_from_digits(const char *digits, size_t length)
{
    char *result;

    if (digits == NULL || length == 0 || length == SIZE_MAX) {
        errno = EINVAL;
        return NULL;
    }

    result = malloc(length + 1);
    if (result == NULL) {
        return NULL;
    }

    for (size_t i = 0; i < length; ++i) {
        if (digits[i] < '0' || digits[i] > '9') {
            free(result);
            errno = EINVAL;
            return NULL;
        }

        result[i] = digits[i];
    }

    result[length] = '\0';
    qsort(result, length, sizeof(result[0]), compare_digits_descending);

    return result;
}

static int read_digits(FILE *stream, char **digits, size_t *length)
{
    char *buffer = NULL;
    size_t capacity = 0;
    size_t used = 0;
    int ch;

    if (stream == NULL || digits == NULL || length == NULL) {
        errno = EINVAL;
        return -1;
    }

    /* Possible weaknesses found:
     * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
     */
    while ((ch = fgetc(stream)) != EOF) {
        if (ch == '\n') {
            break;
        }

        if (ch == '\r') {
            /* Possible weaknesses found:
             * Flawfinder fgetc: Check buffer boundaries if used in a loop including recursive loops (CWE-120, CWE-20). (risk 1, buffer)
             */
            ch = fgetc(stream);
            if (ch != '\n' && ch != EOF && ungetc(ch, stream) == EOF) {
                free(buffer);
                errno = EIO;
                return -1;
            }
            break;
        }

        if (ch < '0' || ch > '9') {
            free(buffer);
            errno = EINVAL;
            return -1;
        }

        if (used == MAX_INPUT_LENGTH) {
            free(buffer);
            errno = EOVERFLOW;
            return -1;
        }

        if (used == capacity) {
            size_t new_capacity;
            char *resized;

            if (capacity == 0) {
                new_capacity = 64;
            } else if (capacity > MAX_INPUT_LENGTH / 2) {
                new_capacity = MAX_INPUT_LENGTH;
            } else {
                new_capacity = capacity * 2;
            }

            if (new_capacity <= used) {
                free(buffer);
                errno = EOVERFLOW;
                return -1;
            }

            resized = realloc(buffer, new_capacity);
            if (resized == NULL) {
                free(buffer);
                return -1;
            }

            buffer = resized;
            capacity = new_capacity;
        }

        buffer[used++] = (char)ch;
    }

    if (ferror(stream)) {
        free(buffer);
        errno = EIO;
        return -1;
    }

    if (used == 0) {
        free(buffer);
        errno = EINVAL;
        return -1;
    }

    *digits = buffer;
    *length = used;
    return 0;
}

int main(void)
{
    char *input = NULL;
    char *largest = NULL;
    size_t length = 0;
    int status = EXIT_FAILURE;

    errno = 0;
    if (read_digits(stdin, &input, &length) != 0) {
        if (errno == EINVAL) {
            fputs("Input must contain one or more decimal digits.\n", stderr);
        } else if (errno == EOVERFLOW) {
            fputs("Input is too long.\n", stderr);
        } else if (errno == ENOMEM) {
            fputs("Unable to allocate memory.\n", stderr);
        } else {
            fputs("Failed to read input.\n", stderr);
        }
        goto cleanup;
    }

    errno = 0;
    largest = largest_number_from_digits(input, length);
    if (largest == NULL) {
        if (errno == EINVAL) {
            fputs("Input must contain one or more decimal digits.\n", stderr);
        } else {
            fputs("Unable to allocate memory.\n", stderr);
        }
        goto cleanup;
    }

    if (puts(largest) == EOF) {
        fputs("Failed to write output.\n", stderr);
        goto cleanup;
    }

    status = EXIT_SUCCESS;

cleanup:
    free(largest);
    free(input);
    return status;
}