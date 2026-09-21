#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Dictionary {
    char *key;
    size_t key_length;
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

    if (length > 0) {
        memcpy(copy, source, length);
    }

    copy[length] = '\0';
    return copy;
}

static void free_dictionary(Dictionary *dictionary)
{
    if (dictionary == NULL) {
        return;
    }

    for (size_t i = 0; i < dictionary->child_count; ++i) {
        free_dictionary(&dictionary->children[i]);
    }

    free(dictionary->children);
    free(dictionary->key);

    dictionary->key = NULL;
    dictionary->key_length = 0;
    dictionary->children = NULL;
    dictionary->child_count = 0;
}

static int initialize_dictionary(Dictionary *dictionary,
                                 const char *key,
                                 size_t key_length)
{
    char *key_copy;

    if (dictionary == NULL || key == NULL || key_length == SIZE_MAX) {
        return -1;
    }

    key_copy = duplicate_string(key, key_length);
    if (key_copy == NULL) {
        return -1;
    }

    dictionary->key = key_copy;
    dictionary->key_length = key_length;
    dictionary->children = NULL;
    dictionary->child_count = 0;

    return 0;
}

static Dictionary *find_child(Dictionary *parent,
                              const char *key,
                              size_t key_length)
{
    if (parent == NULL || key == NULL ||
        (parent->child_count > 0 && parent->children == NULL)) {
        return NULL;
    }

    for (size_t i = 0; i < parent->child_count; ++i) {
        Dictionary *child = &parent->children[i];

        if (child->key != NULL &&
            child->key_length == key_length &&
            (key_length == 0 ||
             memcmp(child->key, key, key_length) == 0)) {
            return child;
        }
    }

    return NULL;
}

static Dictionary *add_child(Dictionary *parent,
                             const char *key,
                             size_t key_length)
{
    Dictionary child = {0};
    Dictionary *resized;
    size_t new_count;

    if (parent == NULL || key == NULL || key_length == SIZE_MAX ||
        (parent->child_count > 0 && parent->children == NULL) ||
        parent->child_count == SIZE_MAX ||
        parent->child_count >= SIZE_MAX / sizeof(*parent->children)) {
        return NULL;
    }

    if (initialize_dictionary(&child, key, key_length) != 0) {
        return NULL;
    }

    new_count = parent->child_count + 1;

    resized = realloc(parent->children,
                      new_count * sizeof(*parent->children));
    if (resized == NULL) {
        free_dictionary(&child);
        return NULL;
    }

    parent->children = resized;
    parent->children[parent->child_count] = child;
    parent->child_count = new_count;

    return &parent->children[new_count - 1];
}

static int lists_to_nested_dictionary(const char *const *const *lists,
                                      const size_t *const *key_lengths,
                                      const size_t *lengths,
                                      size_t list_count,
                                      Dictionary *root)
{
    if (lists == NULL || key_lengths == NULL ||
        lengths == NULL || root == NULL) {
        return -1;
    }

    *root = (Dictionary){0};

    if (initialize_dictionary(root, "root", sizeof("root") - 1) != 0) {
        return -1;
    }

    for (size_t i = 0; i < list_count; ++i) {
        Dictionary *current = root;

        if (lengths[i] > 0 &&
            (lists[i] == NULL || key_lengths[i] == NULL)) {
            free_dictionary(root);
            return -1;
        }

        for (size_t j = 0; j < lengths[i]; ++j) {
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

static int print_escaped_string(const char *text, size_t length)
{
    if (text == NULL || putchar('"') == EOF) {
        return -1;
    }

    for (size_t i = 0; i < length; ++i) {
        unsigned char ch = (unsigned char)text[i];

        switch (ch) {
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
            if (ch < 0x20U) {
                if (fprintf(stdout, "\\u%04x", (unsigned int)ch) < 0) {
                    return -1;
                }
            } else if (putchar((int)ch) == EOF) {
                return -1;
            }
            break;
        }
    }

    return putchar('"') == EOF ? -1 : 0;
}

static int print_dictionary(const Dictionary *dictionary)
{
    if (dictionary == NULL ||
        (dictionary->child_count > 0 && dictionary->children == NULL) ||
        putchar('{') == EOF) {
        return -1;
    }

    for (size_t i = 0; i < dictionary->child_count; ++i) {
        const Dictionary *child = &dictionary->children[i];

        if ((i > 0 && fputs(", ", stdout) == EOF) ||
            child->key == NULL ||
            print_escaped_string(child->key, child->key_length) != 0 ||
            fputs(": ", stdout) == EOF ||
            print_dictionary(child) != 0) {
            return -1;
        }
    }

    return putchar('}') == EOF ? -1 : 0;
}

int main(void)
{
    const char *list1[] = {"users", "alice", "email"};
    const char *list2[] = {"users", "alice", "address"};
    const char *list3[] = {"users", "bob", "email"};
    const char *list4[] = {"settings", "theme"};

    const size_t list1_lengths[] = {
        sizeof("users") - 1,
        sizeof("alice") - 1,
        sizeof("email") - 1
    };
    const size_t list2_lengths[] = {
        sizeof("users") - 1,
        sizeof("alice") - 1,
        sizeof("address") - 1
    };
    const size_t list3_lengths[] = {
        sizeof("users") - 1,
        sizeof("bob") - 1,
        sizeof("email") - 1
    };
    const size_t list4_lengths[] = {
        sizeof("settings") - 1,
        sizeof("theme") - 1
    };

    const char *const *lists[] = {
        list1,
        list2,
        list3,
        list4
    };
    const size_t *key_lengths[] = {
        list1_lengths,
        list2_lengths,
        list3_lengths,
        list4_lengths
    };
    const size_t lengths[] = {
        sizeof(list1) / sizeof(list1[0]),
        sizeof(list2) / sizeof(list2[0]),
        sizeof(list3) / sizeof(list3[0]),
        sizeof(list4) / sizeof(list4[0])
    };

    Dictionary root = {0};

    if (lists_to_nested_dictionary(
            lists,
            key_lengths,
            lengths,
            sizeof(lists) / sizeof(lists[0]),
            &root) != 0) {
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