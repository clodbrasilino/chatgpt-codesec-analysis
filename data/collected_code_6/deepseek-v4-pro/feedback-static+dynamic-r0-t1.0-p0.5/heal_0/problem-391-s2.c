#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node {
    char *key;
    void *value;
    int is_dict;
    struct Node *next;
} Node;

typedef struct Dict {
    Node *head;
} Dict;

Dict *create_dict(void) {
    Dict *d = (Dict *)malloc(sizeof(Dict));
    if (!d) return NULL;
    d->head = NULL;
    return d;
}

void dict_set(Dict *d, const char *key, void *value, int is_dict) {
    if (!d || !key) return;
    Node *n = (Node *)malloc(sizeof(Node));
    if (!n) return;
    n->key = strdup(key);
    if (!n->key) {
        free(n);
        return;
    }
    n->value = value;
    n->is_dict = is_dict;
    n->next = d->head;
    d->head = n;
}

void *dict_get(Dict *d, const char *key) {
    if (!d || !key) return NULL;
    Node *cur = d->head;
    while (cur) {
        if (strcmp(cur->key, key) == 0) return cur->value;
        cur = cur->next;
    }
    return NULL;
}

int dict_has_key(Dict *d, const char *key) {
    if (!d || !key) return 0;
    Node *cur = d->head;
    while (cur) {
        if (strcmp(cur->key, key) == 0) return 1;
        cur = cur->next;
    }
    return 0;
}

void free_dict(Dict *d) {
    if (!d) return;
    Node *cur = d->head;
    while (cur) {
        Node *tmp = cur;
        cur = cur->next;
        free(tmp->key);
        if (tmp->is_dict) {
            free_dict((Dict *)tmp->value);
        } else {
            free(tmp->value);
        }
        free(tmp);
    }
    free(d);
}

Dict *lists_to_nested_dict(char ***keys, int *list_lengths, int num_lists) {
    if (!keys || !list_lengths || num_lists <= 0) return NULL;

    Dict *root = create_dict();
    if (!root) return NULL;

    for (int i = 0; i < num_lists; i++) {
        if (!keys[i] || list_lengths[i] <= 0) continue;

        Dict *current = root;
        for (int j = 0; j < list_lengths[i]; j++) {
            const char *key = keys[i][j];
            if (!key) continue;

            if (j == list_lengths[i] - 1) {
                if (!dict_has_key(current, key)) {
                    char *val = strdup("");
                    if (val) {
                        dict_set(current, key, val, 0);
                    }
                }
            } else {
                if (!dict_has_key(current, key)) {
                    Dict *new_dict = create_dict();
                    if (!new_dict) continue;
                    dict_set(current, key, new_dict, 1);
                }
                void *val = dict_get(current, key);
                if (val && ((Node *)val)->is_dict) {
                    current = (Dict *)val;
                } else {
                    break;
                }
            }
        }
    }

    return root;
}

void print_dict(Dict *d, int indent) {
    if (!d) return;
    Node *cur = d->head;
    while (cur) {
        for (int i = 0; i < indent; i++) printf("  ");
        printf("%s: ", cur->key);
        if (cur->is_dict) {
            printf("{\n");
            print_dict((Dict *)cur->value, indent + 1);
            for (int i = 0; i < indent; i++) printf("  ");
            printf("}\n");
        } else {
            printf("\"%s\"\n", (char *)cur->value);
        }
        cur = cur->next;
    }
}

int main(void) {
    char *list1[] = {"a", "b", "c"};
    char *list2[] = {"a", "b", "d"};
    char *list3[] = {"x", "y"};
    char *list4[] = {"a", "z"};

    char **keys[] = {list1, list2, list3, list4};
    int lengths[] = {3, 3, 2, 2};

    Dict *result = lists_to_nested_dict(keys, lengths, 4);
    if (result) {
        print_dict(result, 0);
        free_dict(result);
    }

    return 0;
}