#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Dictionary {
    char *key;
    char *value;
    struct Dictionary *child;
} Dictionary;

static char *duplicate_string(const char *source)
{
    size_t length;
    char *copy;

    if (source == NULL) {
        return NULL;
    }

    length = strlen(source);

    if (length > SIZE_MAX - 1U) {
        return NULL;
    }

    copy = malloc(length + 1U);
    if (copy == NULL) {
        return NULL;
    }

    memcpy(copy, source, length);
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
    const char *const values[],
    size_t count)
{
    Dictionary *root = NULL;
    Dictionary **current = &root;
    size_t index;

    if (count > 0U && (keys == NULL || values == NULL)) {
        return NULL;
    }

    for (index = 0U; index < count; ++index) {
        Dictionary *node;

        if (keys[index] == NULL || values[index] == NULL) {
            free_dictionary(root);
            return NULL;
        }

        node = calloc(1U, sizeof(*node));
        if (node == NULL) {
            free_dictionary(root);
            return NULL;
        }

        node->key = duplicate_string(keys[index]);
        if (node->key == NULL) {
            free(node);
            free_dictionary(root);
            return NULL;
        }

        node->value = duplicate_string(values[index]);
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
        return printf("{}\n") < 0 ? -1 : 0;
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
    const char *const keys[] = {
        "country",
        "state",
        "city"
    };
    const char *const values[] = {
        "USA",
        "California",
        "San Francisco"
    };
    const size_t key_count = sizeof(keys) / sizeof(keys[0]);
    const size_t value_count = sizeof(values) / sizeof(values[0]);
    Dictionary *dictionary;
    int result;

    if (key_count != value_count) {
        fputs("Mismatched key and value counts.\n", stderr);
        return EXIT_FAILURE;
    }

    dictionary = lists_to_nested_dictionary(keys, values, key_count);
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