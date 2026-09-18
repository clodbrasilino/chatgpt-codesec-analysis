#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DictNode {
    char *key;
    struct DictNode *child;
    char *value;
    struct DictNode *next;
} DictNode;

char *duplicate_string(const char *src) {
    if (!src) {
        return NULL;
    }
    size_t len = strlen(src) + 1;
    char *dst = malloc(len);
    if (dst) {
        memcpy(dst, src, len);
    }
    return dst;
}

void free_dict(DictNode *node) {
    while (node) {
        DictNode *next = node->next;
        if (node->key) {
            free(node->key);
        }
        if (node->value) {
            free(node->value);
        }
        if (node->child) {
            free_dict(node->child);
        }
        free(node);
        node = next;
    }
}

int insert_path(DictNode **root, char **list, size_t len) {
    if (!root || !list || len < 2) {
        return -1;
    }

    char *key = list[0];
    DictNode *curr = *root;
    DictNode *prev = NULL;

    while (curr) {
        if (strcmp(curr->key, key) == 0) {
            break;
        }
        prev = curr;
        curr = curr->next;
    }

    if (!curr) {
        curr = calloc(1, sizeof(DictNode));
        if (!curr) {
            return -1;
        }
        curr->key = duplicate_string(key);
        if (!curr->key) {
            free(curr);
            return -1;
        }
        if (prev) {
            prev->next = curr;
        } else {
            *root = curr;
        }
    }

    if (len == 2) {
        if (curr->value) {
            free(curr->value);
        }
        curr->value = duplicate_string(list[1]);
        if (!curr->value) {
            return -1;
        }
    } else {
        if (insert_path(&(curr->child), list + 1, len - 1) != 0) {
            return -1;
        }
    }

    return 0;
}

/* Possible weaknesses found:
 *  Parameter 'lengths' can be declared as pointer to const [constParameterPointer]
 */
DictNode *lists_to_dict(char ***lists, size_t *lengths, size_t num_lists) {
    if (!lists || !lengths || num_lists == 0) {
        return NULL;
    }

    DictNode *root = NULL;

    for (size_t i = 0; i < num_lists; i++) {
        if (insert_path(&root, lists[i], lengths[i]) != 0) {
            free_dict(root);
            return NULL;
        }
    }

    return root;
}

void print_dict(DictNode *node, int indent) {
    while (node) {
        for (int i = 0; i < indent; i++) {
            printf("  ");
        }
        printf("%s: ", node->key);
        if (node->value) {
            printf("%s\n", node->value);
        } else if (node->child) {
            printf("\n");
            print_dict(node->child, indent + 1);
        }
        node = node->next;
    }
}

int main(void) {
    char *list1[] = {"root", "config", "port", "8080"};
    char *list2[] = {"root", "config", "host", "localhost"};
    char *list3[] = {"root", "users", "admin", "yes"};
    char *list4[] = {"status", "active"};

    char **lists[] = {list1, list2, list3, list4};
    size_t lengths[] = {4, 4, 4, 2};
    size_t num_lists = 4;

    DictNode *dictionary = lists_to_dict(lists, lengths, num_lists);

    if (dictionary) {
        print_dict(dictionary, 0);
        free_dict(dictionary);
    } else {
        fprintf(stderr, "Failed to create dictionary.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}