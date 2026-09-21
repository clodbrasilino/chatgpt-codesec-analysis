#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Dictionary {
    char *key;
    char *value;
    struct Dictionary *children;
    size_t child_count;
} Dictionary;

static char *duplicate_string(const char *source, size_t max_length)
{
    const char *terminator;
    size_t length;
    char *copy;

    if (source == NULL || max_length == 0U) {
        return NULL;
    }

    terminator = memchr(source, '\0', max_length);
    if (terminator == NULL) {
        return NULL;
    }

    length = (size_t)(terminator - source);

    if (length > SIZE_MAX - 1U) {
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

static void free_dictionary(Dictionary *entries, size_t count)
{
    size_t i;

    if (entries == NULL) {
        return;
    }

    for (i = 0U; i < count; ++i) {
        free(entries[i].key);
        free(entries[i].value);
        free_dictionary(entries[i].children, entries[i].child_count);
    }

    free(entries);
}

static Dictionary *lists_to_nested_dictionary(
    const char *const *keys,
    const char *const *values,
    size_t list_count,
    size_t list_length,
    size_t max_string_length)
{
    Dictionary *root;
    Dictionary *node;
    size_t depth;

    if (keys == NULL || list_count == 0U || list_length == 0U ||
        max_string_length == 0U) {
        return NULL;
    }

    if (list_count > SIZE_MAX / list_length ||
        list_count > SIZE_MAX / sizeof(Dictionary)) {
        return NULL;
    }

    root = calloc(1U, sizeof(*root));
    if (root == NULL) {
        return NULL;
    }

    node = root;

    for (depth = 0U; depth < list_length; ++depth) {
        size_t column;

        node->children = calloc(list_count, sizeof(*node->children));
        if (node->children == NULL) {
            free_dictionary(root, 1U);
            return NULL;
        }

        node->child_count = list_count;

        for (column = 0U; column < list_count; ++column) {
            size_t offset = column * list_length + depth;
            Dictionary *entry = &node->children[column];

            if (keys[offset] == NULL) {
                free_dictionary(root, 1U);
                return NULL;
            }

            entry->key = duplicate_string(keys[offset], max_string_length);
            if (entry->key == NULL) {
                free_dictionary(root, 1U);
                return NULL;
            }

            if (depth == list_length - 1U &&
                values != NULL &&
                values[column] != NULL) {
                entry->value = duplicate_string(
                    values[column], max_string_length);

                if (entry->value == NULL) {
                    free_dictionary(root, 1U);
                    return NULL;
                }
            }
        }

        node = &node->children[0];
    }

    return root;
}

static int print_json_string(const char *text)
{
    const unsigned char *current;

    if (text == NULL || putchar('"') == EOF) {
        return -1;
    }

    for (current = (const unsigned char *)text;
         *current != '\0';
         ++current) {
        switch (*current) {
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
                if (*current < 0x20U) {
                    if (fprintf(stdout, "\\u%04x",
                                (unsigned int)*current) < 0) {
                        return -1;
                    }
                } else if (putchar((int)*current) == EOF) {
                    return -1;
                }
                break;
        }
    }

    return putchar('"') == EOF ? -1 : 0;
}

static int print_dictionary(const Dictionary *dictionary)
{
    size_t i;

    if (dictionary == NULL ||
        (dictionary->child_count != 0U &&
         dictionary->children == NULL) ||
        putchar('{') == EOF) {
        return -1;
    }

    for (i = 0U; i < dictionary->child_count; ++i) {
        const Dictionary *entry = &dictionary->children[i];

        if (entry->key == NULL) {
            return -1;
        }

        if (i != 0U && putchar(',') == EOF) {
            return -1;
        }

        if (print_json_string(entry->key) != 0 ||
            putchar(':') == EOF) {
            return -1;
        }

        if (entry->child_count != 0U) {
            if (entry->children == NULL ||
                print_dictionary(entry) != 0) {
                return -1;
            }
        } else if (entry->value != NULL) {
            if (print_json_string(entry->value) != 0) {
                return -1;
            }
        } else if (fputs("null", stdout) == EOF) {
            return -1;
        }
    }

    return putchar('}') == EOF ? -1 : 0;
}

int main(void)
{
    static const char *const keys[] = {
        "users", "alice",
        "users", "bob",
        "services", "database"
    };
    static const char *const values[] = {
        "administrator",
        "developer",
        "online"
    };
    Dictionary *dictionary;
    int status = EXIT_SUCCESS;

    dictionary = lists_to_nested_dictionary(
        keys, values, 3U, 2U, 256U);

    if (dictionary == NULL) {
        fputs("Failed to create dictionary\n", stderr);
        return EXIT_FAILURE;
    }

    if (print_dictionary(dictionary) != 0 ||
        putchar('\n') == EOF) {
        fputs("Failed to print dictionary\n", stderr);
        status = EXIT_FAILURE;
    }

    free_dictionary(dictionary, 1U);

    if (fflush(stdout) == EOF) {
        status = EXIT_FAILURE;
    }

    return status;
}