#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct ValueNode {
    int value;
    struct ValueNode* next;
};

struct DictNode {
    char* key;
    struct ValueNode* values_head;
    struct ValueNode* values_tail;
    struct DictNode* next;
};

struct Dictionary {
    struct DictNode** buckets;
    size_t num_buckets;
};

struct KeyValuePair {
    const char* key;
    int value;
};

static char* duplicate_string(const char* src) {
    if (!src) {
        return NULL;
    }
    
    size_t len = 0;
    size_t max_len = 4096;
    while (src[len] != '\0' && len < max_len) {
        len++;
    }
    
    char* dest = malloc(len + 1);
    if (dest) {
        for (size_t i = 0; i < len; i++) {
            dest[i] = src[i];
        }
        dest[len] = '\0';
    }
    return dest;
}

static size_t hash_string(const char* str, size_t num_buckets) {
    size_t hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + (size_t)c;
    }
    return hash % num_buckets;
}

static struct Dictionary* create_dictionary(size_t num_buckets) {
    if (num_buckets == 0) {
        return NULL;
    }

    struct Dictionary* dict = malloc(sizeof(struct Dictionary));
    if (!dict) {
        return NULL;
    }

    dict->buckets = calloc(num_buckets, sizeof(struct DictNode*));
    if (!dict->buckets) {
        free(dict);
        return NULL;
    }

    dict->num_buckets = num_buckets;
    return dict;
}

static void free_dictionary(struct Dictionary* dict) {
    if (!dict) {
        return;
    }

    for (size_t i = 0; i < dict->num_buckets; ++i) {
        struct DictNode* current_dict_node = dict->buckets[i];
        while (current_dict_node) {
            struct DictNode* next_dict_node = current_dict_node->next;
            
            struct ValueNode* current_value_node = current_dict_node->values_head;
            while (current_value_node) {
                struct ValueNode* next_value_node = current_value_node->next;
                free(current_value_node);
                current_value_node = next_value_node;
            }
            
            free(current_dict_node->key);
            free(current_dict_node);
            current_dict_node = next_dict_node;
        }
    }
    free(dict->buckets);
    free(dict);
}

static int insert_dictionary(struct Dictionary* dict, const char* key, int value) {
    if (!dict || !key) {
        return 0;
    }

    size_t index = hash_string(key, dict->num_buckets);
    struct DictNode* node = dict->buckets[index];

    while (node) {
        if (strcmp(node->key, key) == 0) {
            break;
        }
        node = node->next;
    }

    if (!node) {
        node = malloc(sizeof(struct DictNode));
        if (!node) {
            return 0;
        }
        
        node->key = duplicate_string(key);
        if (!node->key) {
            free(node);
            return 0;
        }
        
        node->values_head = NULL;
        node->values_tail = NULL;
        node->next = dict->buckets[index];
        dict->buckets[index] = node;
    }

    struct ValueNode* val_node = malloc(sizeof(struct ValueNode));
    if (!val_node) {
        return 0;
    }

    val_node->value = value;
    val_node->next = NULL;

    if (!node->values_head) {
        node->values_head = val_node;
        node->values_tail = val_node;
    } else {
        node->values_tail->next = val_node;
        node->values_tail = val_node;
    }

    return 1;
}

static struct Dictionary* group_pairs(const struct KeyValuePair* pairs, size_t num_pairs) {
    if (!pairs && num_pairs > 0) {
        return NULL;
    }

    size_t num_buckets = (num_pairs > 0) ? num_pairs : 1;
    struct Dictionary* dict = create_dictionary(num_buckets);
    if (!dict) {
        return NULL;
    }

    for (size_t i = 0; i < num_pairs; ++i) {
        if (!insert_dictionary(dict, pairs[i].key, pairs[i].value)) {
            free_dictionary(dict);
            return NULL;
        }
    }

    return dict;
}

static void print_dictionary(const struct Dictionary* dict) {
    if (!dict) {
        return;
    }

    for (size_t i = 0; i < dict->num_buckets; ++i) {
        struct DictNode* node = dict->buckets[i];
        while (node) {
            printf("%s: [", node->key);
            struct ValueNode* val_node = node->values_head;
            while (val_node) {
                printf("%d", val_node->value);
                if (val_node->next) {
                    printf(", ");
                }
                val_node = val_node->next;
            }
            printf("]\n");
            node = node->next;
        }
    }
}

int main(void) {
    struct KeyValuePair pairs[] = {
        {"apple", 1},
        {"banana", 2},
        {"apple", 3},
        {"orange", 4},
        {"banana", 5},
        {"banana", 6}
    };
    
    size_t num_pairs = sizeof(pairs) / sizeof(pairs[0]);
    struct Dictionary* dict = group_pairs(pairs, num_pairs);
    
    if (dict) {
        print_dictionary(dict);
        free_dictionary(dict);
        return EXIT_SUCCESS;
    }

    return EXIT_FAILURE;
}