#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Dictionary {
    char *key;
    struct Dictionary *children;
    size_t child_count;
} Dictionary;

static char *duplicate_string(const char *source, size_t length)
{
    char *copy;

    if (source == NULL || length == SIZE_MAX) {
        return NULL;
    }

    copy = malloc(length + 1);
    if (copy == NULL) {
        return NULL;
    }

    if (length != 0) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(copy, source, length);
    }

    copy[length] = '\0';
    return copy;
}

static void free_dictionary(Dictionary *dictionary)
{
    size_t i;

    if (dictionary == NULL) {
        return;
    }

    for (i = 0; i < dictionary->child_count; ++i) {
        free_dictionary(&dictionary->children[i]);
    }

    free(dictionary->children);
    free(dictionary->key);

    dictionary->children = NULL;
    dictionary->key = NULL;
    dictionary->child_count = 0;
}

static int initialize_dictionary(
    Dictionary *dictionary,
    const char *key,
    size_t key_length)
{
    char *key_copy;

    if (dictionary == NULL || key == NULL) {
        return -1;
    }

    key_copy = duplicate_string(key, key_length);
    if (key_copy == NULL) {
        return -1;
    }

    dictionary->key = key_copy;
    dictionary->children = NULL;
    dictionary->child_count = 0;
    return 0;
}

static Dictionary *find_child(
    Dictionary *parent,
    const char *key,
    size_t key_length)
{
    size_t i;

    if (parent == NULL || key == NULL || key_length == SIZE_MAX) {
        return NULL;
    }

    for (i = 0; i < parent->child_count; ++i) {
        const char *child_key = parent->children[i].key;

        if (child_key != NULL &&
            strncmp(child_key, key, key_length) == 0 &&
            child_key[key_length] == '\0') {
            return &parent->children[i];
        }
    }

    return NULL;
}

static Dictionary *add_child(
    Dictionary *parent,
    const char *key,
    size_t key_length)
{
    Dictionary *resized;
    Dictionary *child;
    char *key_copy;
    size_t new_count;

    if (parent == NULL || key == NULL ||
        key_length == SIZE_MAX ||
        parent->child_count == SIZE_MAX) {
        return NULL;
    }

    key_copy = duplicate_string(key, key_length);
    if (key_copy == NULL) {
        return NULL;
    }

    new_count = parent->child_count + 1;
    if (new_count > SIZE_MAX / sizeof(*parent->children)) {
        free(key_copy);
        return NULL;
    }

    resized = realloc(
        parent->children,
        new_count * sizeof(*parent->children));
    if (resized == NULL) {
        free(key_copy);
        return NULL;
    }

    parent->children = resized;
    child = &parent->children[parent->child_count];
    child->key = key_copy;
    child->children = NULL;
    child->child_count = 0;
    parent->child_count = new_count;

    return child;
}

static int lists_to_nested_dictionary(
    const char *const *const *lists,
    const size_t *const *key_lengths,
    const size_t *list_lengths,
    size_t list_count,
    Dictionary *root)
{
    static const char root_key[] = "root";
    size_t i;
    size_t j;

    if (lists == NULL || key_lengths == NULL ||
        list_lengths == NULL || root == NULL) {
        return -1;
    }

    root->key = NULL;
    root->children = NULL;
    root->child_count = 0;

    if (initialize_dictionary(root, root_key, sizeof(root_key) - 1) != 0) {
        return -1;
    }

    for (i = 0; i < list_count; ++i) {
        Dictionary *current = root;

        if (list_lengths[i] != 0 &&
            (lists[i] == NULL || key_lengths[i] == NULL)) {
            free_dictionary(root);
            return -1;
        }

        for (j = 0; j < list_lengths[i]; ++j) {
            Dictionary *next;

            if (lists[i][j] == NULL || key_lengths[i][j] == SIZE_MAX) {
                free_dictionary(root);
                return -1;
            }

            next = find_child(current, lists[i][j], key_lengths[i][j]);
            if (next == NULL) {
                next = add_child(current, lists[i][j], key_lengths[i][j]);
                if (next == NULL) {
                    free_dictionary(root);
                    return -1;
                }
            }

            current = next;
        }
    }

    return 0;
}

static int print_escaped_string(const char *text)
{
    const unsigned char *position;

    if (text == NULL || putchar('"') == EOF) {
        return -1;
    }

    position = (const unsigned char *)text;

    while (*position != '\0') {
        switch (*position) {
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
            if (*position < 0x20U) {
                if (fprintf(
                        stdout,
                        "\\u%04x",
                        (unsigned int)*position) < 0) {
                    return -1;
                }
            } else if (putchar((int)*position) == EOF) {
                return -1;
            }
            break;
        }

        ++position;
    }

    return putchar('"') == EOF ? -1 : 0;
}

static int print_dictionary(const Dictionary *dictionary)
{
    size_t i;

    if (dictionary == NULL || putchar('{') == EOF) {
        return -1;
    }

    for (i = 0; i < dictionary->child_count; ++i) {
        if (i != 0 && fputs(", ", stdout) == EOF) {
            return -1;
        }

        if (print_escaped_string(dictionary->children[i].key) != 0 ||
            fputs(": ", stdout) == EOF ||
            print_dictionary(&dictionary->children[i]) != 0) {
            return -1;
        }
    }

    return putchar('}') == EOF ? -1 : 0;
}

int main(void)
{
    static const char users[] = "users";
    static const char alice[] = "alice";
    static const char bob[] = "bob";
    static const char email[] = "email";
    static const char address[] = "address";
    static const char settings[] = "settings";
    static const char theme[] = "theme";

    const char *list1[] = {users, alice, email};
    const char *list2[] = {users, alice, address};
    const char *list3[] = {users, bob, email};
    const char *list4[] = {settings, theme};

    const size_t key_lengths1[] = {
        sizeof(users) - 1,
        sizeof(alice) - 1,
        sizeof(email) - 1
    };
    const size_t key_lengths2[] = {
        sizeof(users) - 1,
        sizeof(alice) - 1,
        sizeof(address) - 1
    };
    const size_t key_lengths3[] = {
        sizeof(users) - 1,
        sizeof(bob) - 1,
        sizeof(email) - 1
    };
    const size_t key_lengths4[] = {
        sizeof(settings) - 1,
        sizeof(theme) - 1
    };

    const char *const *lists[] = {
        list1,
        list2,
        list3,
        list4
    };
    const size_t *key_lengths[] = {
        key_lengths1,
        key_lengths2,
        key_lengths3,
        key_lengths4
    };
    const size_t list_lengths[] = {
        sizeof(list1) / sizeof(list1[0]),
        sizeof(list2) / sizeof(list2[0]),
        sizeof(list3) / sizeof(list3[0]),
        sizeof(list4) / sizeof(list4[0])
    };

    Dictionary root = {0};
    int result;

    result = lists_to_nested_dictionary(
        lists,
        key_lengths,
        list_lengths,
        sizeof(lists) / sizeof(lists[0]),
        &root);

    if (result != 0) {
        fputs("Failed to create dictionary.\n", stderr);
        return EXIT_FAILURE;
    }

    if (print_dictionary(&root) != 0 || putchar('\n') == EOF) {
        free_dictionary(&root);
        fputs("Failed to print dictionary.\n", stderr);
        return EXIT_FAILURE;
    }

    free_dictionary(&root);
    return EXIT_SUCCESS;
}