#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STR_LEN 4096

typedef enum {
    TYPE_STRING,
    TYPE_DICT
} ValueType;

typedef struct DictNode {
    char *key;
    ValueType type;
    union {
        char *string_val;
        struct DictNode *dict_val;
    } value;
    struct DictNode *next;
} DictNode;

char *duplicate_string(const char *src);
int insert_nested(DictNode **root, char **keys, size_t num_keys, const char *value);
void print_dict(DictNode *node, int indent);
void free_dict(DictNode *node);

char *duplicate_string(const char *src) {
    if (!src) {
        return NULL;
    }
    
    size_t len = 0;
    /* Possible weaknesses found:
     *  Array index 'len' is used before limits check. [arrayIndexThenCheck]
     */
    while (src[len] != '\0' && len < MAX_STR_LEN - 1) {
        len++;
    }
    
    char *dst = malloc(len + 1);
    if (dst) {
        /* Possible weaknesses found:
         * Flawfinder memcpy: Does not check for buffer overflows when copying to destination (CWE-120). Make sure destination can always hold the source data. (risk 2, buffer)
         */
        memcpy(dst, src, len);
        dst[len] = '\0';
    }
    return dst;
}

int insert_nested(DictNode **root, char **keys, size_t num_keys, const char *value) {
    if (!root || !keys || num_keys == 0 || !value) {
        return -1;
    }

    DictNode **current = root;
    for (size_t i = 0; i < num_keys; i++) {
        if (!keys[i]) {
            return -1;
        }

        DictNode *node = *current;
        while (node != NULL) {
            if (strcmp(node->key, keys[i]) == 0) {
                break;
            }
            node = node->next;
        }

        if (node == NULL) {
            node = malloc(sizeof(DictNode));
            if (!node) {
                return -1;
            }

            node->key = duplicate_string(keys[i]);
            if (!node->key) {
                free(node);
                return -1;
            }

            node->type = (i == num_keys - 1) ? TYPE_STRING : TYPE_DICT;
            if (node->type == TYPE_STRING) {
                node->value.string_val = duplicate_string(value);
                if (!node->value.string_val) {
                    free(node->key);
                    free(node);
                    return -1;
                }
            } else {
                node->value.dict_val = NULL;
            }

            node->next = *current;
            *current = node;
        } else {
            if (i == num_keys - 1) {
                if (node->type != TYPE_STRING) {
                    return -1;
                }
                char *new_str = duplicate_string(value);
                if (!new_str) {
                    return -1;
                }
                free(node->value.string_val);
                node->value.string_val = new_str;
            }
        }

        if (i < num_keys - 1) {
            if (node->type != TYPE_DICT) {
                return -1;
            }
            current = &(node->value.dict_val);
        }
    }
    return 0;
}

void print_dict(DictNode *node, int indent) {
    while (node) {
        for (int i = 0; i < indent; i++) {
            printf("  ");
        }
        printf("\"%s\": ", node->key);
        if (node->type == TYPE_STRING) {
            printf("\"%s\"\n", node->value.string_val);
        } else {
            printf("{\n");
            print_dict(node->value.dict_val, indent + 1);
            for (int i = 0; i < indent; i++) {
                printf("  ");
            }
            printf("}\n");
        }
        node = node->next;
    }
}

void free_dict(DictNode *node) {
    while (node) {
        DictNode *next = node->next;
        free(node->key);
        if (node->type == TYPE_STRING) {
            free(node->value.string_val);
        } else {
            free_dict(node->value.dict_val);
        }
        free(node);
        node = next;
    }
}

int main(void) {
    DictNode *root = NULL;

    char *list1[] = {"user", "profile", "name"};
    char *list2[] = {"user", "profile", "age"};
    char *list3[] = {"settings", "theme"};
    char *list4[] = {"settings", "notifications", "email"};

    int err1 = insert_nested(&root, list1, 3, "John Doe");
    int err2 = insert_nested(&root, list2, 3, "30");
    int err3 = insert_nested(&root, list3, 2, "Dark");
    int err4 = insert_nested(&root, list4, 3, "Enabled");

    if (err1 == 0 && err2 == 0 && err3 == 0 && err4 == 0) {
        printf("{\n");
        print_dict(root, 1);
        printf("}\n");
    } else {
        fprintf(stderr, "Dictionary allocation failed.\n");
    }

    free_dict(root);

    return (err1 == 0 && err2 == 0 && err3 == 0 && err4 == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}