#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Dictionary {
    char *key;
    char *value;
    struct Dictionary *child;
} Dictionary;

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

static void free_dictionary(Dictionary *dictionary)
{
    while (dictionary != NULL) {
        Dictionary *next = dictionary->child;

        free(dictionary->key);
        free(dictionary->value);
        free(dictionary);
        dictionary = next;
    }
}

static Dictionary *lists_to_nested_dictionary(
    const char *const keys[],
    const size_t key_lengths[],
    const char *const values[],
    const size_t value_lengths[],
    size_t count)
{
    Dictionary *root = NULL;
    Dictionary **current = &root;
    size_t index;

    if (count > 0U &&
        (keys == NULL || key_lengths == NULL ||
         values == NULL || value_lengths == NULL)) {
        return NULL;
    }

    for (index = 0U; index < count; ++index) {
        Dictionary *node;

        if (keys[index] == NULL || values[index] == NULL ||
            key_lengths[index] == SIZE_MAX ||
            value_lengths[index] == SIZE_MAX) {
            free_dictionary(root);
            return NULL;
        }

        node = calloc(1U, sizeof(*node));
        if (node == NULL) {
            free_dictionary(root);
            return NULL;
        }

        node->key = duplicate_string(keys[index], key_lengths[index]);
        if (node->key == NULL) {
            free(node);
            free_dictionary(root);
            return NULL;
        }

        node->value = duplicate_string(values[index], value_lengths[index]);
        if (node->value == NULL) {
            free(node->key);
            free(node);
            free_dictionary(root);
            return NULL;
        }

        *current = node;
        current = &node->child;
    }

    return root;
}

static int print_nested_dictionary(const Dictionary *dictionary)
{
    size_t depth = 0U;
    size_t index;

    if (dictionary == NULL) {
        return fputs("{}\n", stdout) == EOF ? -1 : 0;
    }

    while (dictionary != NULL) {
        for (index = 0U; index < depth; ++index) {
            if (fputs("  ", stdout) == EOF) {
                return -1;
            }
        }

        if (printf("{\"%s\": \"%s\"", dictionary->key,
                   dictionary->value) < 0) {
            return -1;
        }

        if (dictionary->child != NULL && fputs(",\n", stdout) == EOF) {
            return -1;
        }

        dictionary = dictionary->child;

        if (depth == SIZE_MAX) {
            return -1;
        }
        ++depth;
    }

    while (depth > 0U) {
        --depth;

        if (fputc('}', stdout) == EOF) {
            return -1;
        }

        if (depth > 0U) {
            if (fputc('\n', stdout) == EOF) {
                return -1;
            }

            for (index = 0U; index < depth; ++index) {
                if (fputs("  ", stdout) == EOF) {
                    return -1;
                }
            }
        }
    }

    return fputc('\n', stdout) == EOF ? -1 : 0;
}

int main(void)
{
    static const char key_country[] = "country";
    static const char key_state[] = "state";
    static const char key_city[] = "city";
    static const char value_country[] = "USA";
    static const char value_state[] = "California";
    static const char value_city[] = "San Francisco";

    const char *const keys[] = {
        key_country,
        key_state,
        key_city
    };
    const size_t key_lengths[] = {
        sizeof(key_country) - 1U,
        sizeof(key_state) - 1U,
        sizeof(key_city) - 1U
    };
    const char *const values[] = {
        value_country,
        value_state,
        value_city
    };
    const size_t value_lengths[] = {
        sizeof(value_country) - 1U,
        sizeof(value_state) - 1U,
        sizeof(value_city) - 1U
    };
    const size_t key_count = sizeof(keys) / sizeof(keys[0]);
    const size_t key_length_count =
        sizeof(key_lengths) / sizeof(key_lengths[0]);
    const size_t value_count = sizeof(values) / sizeof(values[0]);
    const size_t value_length_count =
        sizeof(value_lengths) / sizeof(value_lengths[0]);
    Dictionary *dictionary;
    int result;

    if (key_count != value_count ||
        key_count != key_length_count ||
        value_count != value_length_count) {
        fputs("Mismatched input counts.\n", stderr);
        return EXIT_FAILURE;
    }

    dictionary = lists_to_nested_dictionary(
        keys, key_lengths, values, value_lengths, key_count);
    if (dictionary == NULL) {
        fputs("Failed to create nested dictionary.\n", stderr);
        return EXIT_FAILURE;
    }

    result = print_nested_dictionary(dictionary);
    free_dictionary(dictionary);

    if (result != 0) {
        fputs("Failed to print nested dictionary.\n", stderr);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}