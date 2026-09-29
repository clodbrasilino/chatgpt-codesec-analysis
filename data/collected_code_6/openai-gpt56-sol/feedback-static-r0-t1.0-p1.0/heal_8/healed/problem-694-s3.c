#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    const char *value;
    size_t length;
} DictionaryEntry;

typedef struct {
    char *value;
    size_t length;
} UniqueValue;

static char *duplicate_string(const char *source, size_t length)
{
    char *copy;

    if (source == NULL || length > SIZE_MAX - 1U) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    if (length != 0U) {
        memcpy(copy, source, length);
    }

    copy[length] = '\0';
    return copy;
}

static void free_values(UniqueValue *values, size_t count)
{
    size_t i;

    if (values == NULL) {
        return;
    }

    for (i = 0U; i < count; ++i) {
        free(values[i].value);
    }

    free(values);
}

static int extract_unique_values(const DictionaryEntry *dictionary,
                                 size_t dictionary_size,
                                 UniqueValue **unique_values,
                                 size_t *unique_count)
{
    UniqueValue *result;
    size_t count;
    size_t i;

    if (unique_values == NULL || unique_count == NULL) {
        return -1;
    }

    *unique_values = NULL;
    *unique_count = 0U;

    if (dictionary_size == 0U) {
        return 0;
    }

    if (dictionary == NULL ||
        dictionary_size > SIZE_MAX / sizeof(UniqueValue)) {
        return -1;
    }

    result = calloc(dictionary_size, sizeof(UniqueValue));
    if (result == NULL) {
        return -1;
    }

    count = 0U;

    for (i = 0U; i < dictionary_size; ++i) {
        size_t j;
        int found;

        if (dictionary[i].value == NULL ||
            dictionary[i].length > SIZE_MAX - 1U) {
            free_values(result, count);
            return -1;
        }

        found = 0;

        for (j = 0U; j < count; ++j) {
            if (dictionary[i].length == result[j].length &&
                (dictionary[i].length == 0U ||
                 memcmp(dictionary[i].value,
                        result[j].value,
                        dictionary[i].length) == 0)) {
                found = 1;
                break;
            }
        }

        if (found == 0) {
            char *copy;

            copy = duplicate_string(dictionary[i].value,
                                    dictionary[i].length);
            if (copy == NULL) {
                free_values(result, count);
                return -1;
            }

            result[count].value = copy;
            result[count].length = dictionary[i].length;
            ++count;
        }
    }

    *unique_values = result;
    *unique_count = count;
    return 0;
}

static int write_value(FILE *stream, const char *value, size_t length)
{
    size_t written;

    if (stream == NULL || (value == NULL && length != 0U)) {
        return -1;
    }

    written = 0U;

    while (written < length) {
        size_t amount;

        amount = fwrite(value + written, 1U, length - written, stream);
        if (amount == 0U) {
            return -1;
        }

        written += amount;
    }

    return fputc('\n', stream) == EOF ? -1 : 0;
}

int main(void)
{
    static const char apple[] = "apple";
    static const char banana[] = "banana";
    static const char orange[] = "orange";
    const DictionaryEntry dictionary[] = {
        {apple, sizeof apple - 1U},
        {banana, sizeof banana - 1U},
        {apple, sizeof apple - 1U},
        {orange, sizeof orange - 1U},
        {banana, sizeof banana - 1U}
    };
    const size_t dictionary_size =
        sizeof dictionary / sizeof dictionary[0];
    UniqueValue *unique_values;
    size_t unique_count;
    size_t i;
    int status;

    unique_values = NULL;
    unique_count = 0U;
    status = EXIT_SUCCESS;

    if (extract_unique_values(dictionary,
                              dictionary_size,
                              &unique_values,
                              &unique_count) != 0) {
        fputs("Failed to extract unique values.\n", stderr);
        return EXIT_FAILURE;
    }

    for (i = 0U; i < unique_count; ++i) {
        if (write_value(stdout,
                        unique_values[i].value,
                        unique_values[i].length) != 0) {
            status = EXIT_FAILURE;
            break;
        }
    }

    if (fflush(stdout) == EOF) {
        status = EXIT_FAILURE;
    }

    free_values(unique_values, unique_count);
    return status;
}