#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct KeyValuePair {
    char *key;
    char *value;
};

struct ValueNode {
    char *value;
    struct ValueNode *next;
};

struct MapNode {
    char *key;
    struct ValueNode *values;
    struct MapNode *next;
};

struct Map {
    struct MapNode **buckets;
    size_t num_buckets;
};

char *duplicate_string(const char *s) {
    if (!s) {
        return NULL;
    }
    size_t max_len = 8192;
    size_t len = 0;
    while (len < max_len && s[len] != '\0') {
        len++;
    }
    char *dup = malloc(len + 1);
    if (dup) {
        for (size_t i = 0; i < len; i++) {
            dup[i] = s[i];
        }
        dup[len] = '\0';
    }
    return dup;
}

size_t hash_function(const char *str, size_t num_buckets) {
    size_t hash = 5381;
    int c;
    while ((c = *str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % num_buckets;
}

struct Map* create_map(size_t num_buckets) {
    if (num_buckets == 0) {
        return NULL;
    }
    struct Map *map = malloc(sizeof(struct Map));
    if (!map) {
        return NULL;
    }
    map->buckets = calloc(num_buckets, sizeof(struct MapNode*));
    if (!map->buckets) {
        free(map);
        return NULL;
    }
    map->num_buckets = num_buckets;
    return map;
}

struct ValueNode* create_value_node(const char *value) {
    struct ValueNode *node = malloc(sizeof(struct ValueNode));
    if (!node) {
        return NULL;
    }
    node->value = duplicate_string(value);
    if (!node->value) {
        free(node);
        return NULL;
    }
    node->next = NULL;
    return node;
}

void free_map(struct Map *map) {
    if (!map) {
        return;
    }
    for (size_t i = 0; i < map->num_buckets; i++) {
        struct MapNode *m_node = map->buckets[i];
        while (m_node) {
            struct MapNode *next_m = m_node->next;
            struct ValueNode *v_node = m_node->values;
            while (v_node) {
                struct ValueNode *next_v = v_node->next;
                free(v_node->value);
                free(v_node);
                v_node = next_v;
            }
            free(m_node->key);
            free(m_node);
            m_node = next_m;
        }
    }
    free(map->buckets);
    free(map);
}

int insert_map(struct Map *map, const char *key, const char *value) {
    if (!map || !key || !value) {
        return -1;
    }
    size_t index = hash_function(key, map->num_buckets);
    struct MapNode *current = map->buckets[index];
    
    while (current) {
        if (strcmp(current->key, key) == 0) {
            struct ValueNode *v_node = create_value_node(value);
            if (!v_node) {
                return -1;
            }
            if (!current->values) {
                current->values = v_node;
            } else {
                struct ValueNode *tail = current->values;
                while (tail->next) {
                    tail = tail->next;
                }
                tail->next = v_node;
            }
            return 0;
        }
        current = current->next;
    }
    
    struct MapNode *m_node = malloc(sizeof(struct MapNode));
    if (!m_node) {
        return -1;
    }
    m_node->key = duplicate_string(key);
    if (!m_node->key) {
        free(m_node);
        return -1;
    }
    m_node->values = create_value_node(value);
    if (!m_node->values) {
        free(m_node->key);
        free(m_node);
        return -1;
    }
    m_node->next = map->buckets[index];
    map->buckets[index] = m_node;
    
    return 0;
}

struct Map* group_pairs(struct KeyValuePair *pairs, size_t count, size_t num_buckets) {
    if (!pairs || count == 0 || num_buckets == 0) {
        return NULL;
    }
    struct Map *map = create_map(num_buckets);
    if (!map) {
        return NULL;
    }
    for (size_t i = 0; i < count; i++) {
        if (insert_map(map, pairs[i].key, pairs[i].value) != 0) {
            free_map(map);
            return NULL;
        }
    }
    return map;
}

void print_map(struct Map *map) {
    if (!map) {
        return;
    }
    for (size_t i = 0; i < map->num_buckets; i++) {
        struct MapNode *m_node = map->buckets[i];
        while (m_node) {
            printf("%s: [", m_node->key);
            struct ValueNode *v_node = m_node->values;
            while (v_node) {
                printf("%s%s", v_node->value, v_node->next ? ", " : "");
                v_node = v_node->next;
            }
            printf("]\n");
            m_node = m_node->next;
        }
    }
}

int main(void) {
    struct KeyValuePair pairs[] = {
        {"category_a", "item_1"},
        {"category_b", "item_2"},
        {"category_a", "item_3"},
        {"category_c", "item_4"},
        {"category_b", "item_5"},
        {"category_a", "item_6"}
    };
    
    size_t count = sizeof(pairs) / sizeof(pairs[0]);
    size_t bucket_count = 16;
    
    struct Map *grouped_map = group_pairs(pairs, count, bucket_count);
    if (!grouped_map) {
        fprintf(stderr, "Failed to group key-value pairs.\n");
        return EXIT_FAILURE;
    }
    
    print_map(grouped_map);
    free_map(grouped_map);
    
    return EXIT_SUCCESS;
}