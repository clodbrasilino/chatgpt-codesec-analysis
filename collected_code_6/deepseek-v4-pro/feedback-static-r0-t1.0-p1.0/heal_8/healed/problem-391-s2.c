#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DictNode {
    char *key;
    struct DictNode *value;
    struct DictNode *next;
} DictNode;

typedef struct {
    DictNode *head;
} Dict;

DictNode *create_node(const char *key, size_t key_len) {
    if (key == NULL) {
        return NULL;
    }
    
    if (key_len >= 1024) {
        return NULL;
    }
    
    DictNode *node = (DictNode *)malloc(sizeof(DictNode));
    if (node == NULL) {
        return NULL;
    }
    
    node->key = (char *)malloc(key_len + 1);
    if (node->key == NULL) {
        free(node);
        return NULL;
    }
    
    if (key_len > 0) {
        memcpy(node->key, key, key_len);
    }
    node->key[key_len] = '\0';
    node->value = NULL;
    node->next = NULL;
    return node;
}

DictNode *create_node_from_string(const char *str) {
    if (str == NULL) {
        return NULL;
    }
    size_t len = strlen(str);
    if (len >= 1024) {
        return NULL;
    }
    return create_node(str, len);
}

DictNode *find_key(DictNode *head, const char *key) {
    DictNode *current = head;
    while (current != NULL) {
        if (current->key != NULL && key != NULL && strcmp(current->key, key) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void free_dict(DictNode *node) {
    while (node != NULL) {
        DictNode *next = node->next;
        free(node->key);
        if (node->value != NULL) {
            free_dict(node->value);
        }
        free(node);
        node = next;
    }
}

static size_t safe_strlen(const char *str, size_t max_len) {
    if (str == NULL) {
        return 0;
    }
    size_t len = 0;
    while (len < max_len && str[len] != '\0') {
        len++;
    }
    return len;
}

Dict *convert_lists_to_dict(char ***lists, int num_lists, const int *list_lengths) {
    if (lists == NULL || list_lengths == NULL || num_lists <= 0) {
        return NULL;
    }
    
    Dict *dict = (Dict *)malloc(sizeof(Dict));
    if (dict == NULL) {
        return NULL;
    }
    dict->head = NULL;

    for (int i = 0; i < num_lists; i++) {
        if (list_lengths[i] <= 0 || lists[i] == NULL) {
            free_dict(dict->head);
            free(dict);
            return NULL;
        }
        
        DictNode **current_level = &(dict->head);
        for (int j = 0; j < list_lengths[i] - 1; j++) {
            if (lists[i][j] == NULL) {
                free_dict(dict->head);
                free(dict);
                return NULL;
            }
            
            size_t key_len = safe_strlen(lists[i][j], 1023);
            if (key_len == 0 && lists[i][j][0] != '\0') {
                free_dict(dict->head);
                free(dict);
                return NULL;
            }
            
            DictNode *existing = find_key(*current_level, lists[i][j]);
            if (existing == NULL) {
                existing = create_node(lists[i][j], key_len);
                if (existing == NULL) {
                    free_dict(dict->head);
                    free(dict);
                    return NULL;
                }
                existing->next = *current_level;
                *current_level = existing;
            }
            if (existing->value == NULL) {
                existing->value = (DictNode *)calloc(1, sizeof(DictNode));
                if (existing->value == NULL) {
                    free_dict(dict->head);
                    free(dict);
                    return NULL;
                }
            }
            current_level = &(existing->value);
        }
        
        if (lists[i][list_lengths[i] - 1] == NULL) {
            free_dict(dict->head);
            free(dict);
            return NULL;
        }
        
        size_t leaf_key_len = safe_strlen(lists[i][list_lengths[i] - 1], 1023);
        DictNode *leaf = find_key(*current_level, lists[i][list_lengths[i] - 1]);
        if (leaf == NULL) {
            leaf = create_node(lists[i][list_lengths[i] - 1], leaf_key_len);
            if (leaf == NULL) {
                free_dict(dict->head);
                free(dict);
                return NULL;
            }
            leaf->next = *current_level;
            *current_level = leaf;
        }
    }

    return dict;
}

void print_dict_level(DictNode *node, int level) {
    while (node != NULL) {
        for (int i = 0; i < level; i++) {
            printf("  ");
        }
        printf("%s\n", node->key ? node->key : "(null)");
        if (node->value != NULL) {
            print_dict_level(node->value, level + 1);
        }
        node = node->next;
    }
}

void print_dict(Dict *dict) {
    if (dict == NULL || dict->head == NULL) {
        printf("Empty dictionary\n");
        return;
    }
    print_dict_level(dict->head, 0);
}

int main() {
    char *list1[] = {"a", "b", "c"};
    char *list2[] = {"a", "b", "d"};
    char *list3[] = {"x", "y"};
    char *list4[] = {"a", "e"};

    char **lists[] = {list1, list2, list3, list4};
    const int lengths[] = {3, 3, 2, 2};

    Dict *result = convert_lists_to_dict(lists, 4, lengths);

    if (result != NULL) {
        printf("Dictionary created successfully\n");
        print_dict(result);
        free_dict(result->head);
        free(result);
    } else {
        printf("Failed to create dictionary\n");
    }

    return 0;
}