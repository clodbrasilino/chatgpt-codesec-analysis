#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct DictNode {
    char *key;
    char *value;
    struct DictNode *child;
    struct DictNode *next;
} DictNode;

static char *safe_strdup(const char *str) {
    size_t len;
    char *copy;
    
    if (str == NULL) {
        return NULL;
    }
    
    len = strnlen(str, 4096);
    if (len == 4096 && str[len] != '\0') {
        return NULL;
    }
    
    copy = malloc(len + 1);
    if (copy == NULL) {
        return NULL;
    }
    
    /* Possible weaknesses found:
     * Flawfinder strncpy: Easily used incorrectly; doesn't always \0-terminate or check for invalid pointers [MS-banned] (CWE-120). (risk 1, buffer)
     */
    strncpy(copy, str, len);
    copy[len] = '\0';
    
    return copy;
}

DictNode *create_node(const char *key, const char *value) {
    DictNode *node;
    
    if (key == NULL) {
        return NULL;
    }
    
    node = malloc(sizeof(DictNode));
    if (node == NULL) {
        return NULL;
    }
    
    node->key = safe_strdup(key);
    if (node->key == NULL) {
        free(node);
        return NULL;
    }
    
    if (value != NULL) {
        node->value = safe_strdup(value);
        if (node->value == NULL) {
            free(node->key);
            free(node);
            return NULL;
        }
    } else {
        node->value = NULL;
    }
    
    node->child = NULL;
    node->next = NULL;
    return node;
}

void free_dict(DictNode *dict) {
    DictNode *next;
    
    while (dict != NULL) {
        next = dict->next;
        if (dict->child != NULL) {
            free_dict(dict->child);
        }
        free(dict->key);
        free(dict->value);
        free(dict);
        dict = next;
    }
}

int lists_to_nested_dict(char ***lists, size_t list_count, size_t list_length, DictNode **result) {
    DictNode *root;
    DictNode *current;
    DictNode *child;
    DictNode *prev;
    const char *key;
    const char *value;
    char *new_value;
    size_t i;
    size_t j;
    
    if (lists == NULL || list_count == 0 || list_length == 0 || result == NULL) {
        return -1;
    }
    
    for (i = 0; i < list_count; i++) {
        if (lists[i] == NULL) {
            return -1;
        }
        for (j = 0; j < list_length; j++) {
            if (lists[i][j] == NULL) {
                return -1;
            }
        }
    }
    
    root = create_node("root", NULL);
    if (root == NULL) {
        return -1;
    }
    
    for (i = 0; i < list_length; i++) {
        current = root;
        
        for (j = 0; j < list_count; j++) {
            key = lists[j][i];
            value = (j == list_count - 1) ? lists[j][i] : NULL;
            
            child = current->child;
            prev = NULL;
            
            while (child != NULL && strcmp(child->key, key) != 0) {
                prev = child;
                child = child->next;
            }
            
            if (child == NULL) {
                child = create_node(key, value);
                if (child == NULL) {
                    free_dict(root);
                    return -1;
                }
                
                if (prev == NULL) {
                    current->child = child;
                } else {
                    prev->next = child;
                }
            } else if (value != NULL) {
                new_value = safe_strdup(value);
                if (new_value == NULL) {
                    free_dict(root);
                    return -1;
                }
                free(child->value);
                child->value = new_value;
            }
            
            current = child;
        }
    }
    
    *result = root;
    return 0;
}

void print_dict(DictNode *dict, int depth) {
    int i;
    
    while (dict != NULL) {
        for (i = 0; i < depth; i++) {
            printf("  ");
        }
        printf("%s", dict->key);
        if (dict->value != NULL) {
            printf(": %s", dict->value);
        }
        printf("\n");
        if (dict->child != NULL) {
            print_dict(dict->child, depth + 1);
        }
        dict = dict->next;
    }
}

int main(void) {
    char *names[] = {"Alice", "Bob", "Charlie"};
    char *cities[] = {"NewYork", "London", "Paris"};
    char *jobs[] = {"Engineer", "Doctor", "Artist"};
    
    char **lists[] = {names, cities, jobs};
    size_t list_count = 3;
    size_t list_length = 3;
    
    DictNode *result = NULL;
    
    if (lists_to_nested_dict(lists, list_count, list_length, &result) != 0) {
        fprintf(stderr, "Error: Failed to create nested dictionary\n");
        return EXIT_FAILURE;
    }
    
    printf("Nested Dictionary:\n");
    print_dict(result, 0);
    
    free_dict(result);
    return EXIT_SUCCESS;
}