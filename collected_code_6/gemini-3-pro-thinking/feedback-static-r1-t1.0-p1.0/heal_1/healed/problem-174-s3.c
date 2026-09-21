#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INITIAL_BUCKETS 16
#define MAX_STR_LEN 4096

typedef struct ValueNode {
    char *value;
    struct ValueNode *next;
} ValueNode;

typedef struct KeyNode {
    char *key;
    ValueNode *values_head;
    ValueNode *values_tail;
    struct KeyNode *next;
} KeyNode;

typedef struct Dictionary {
    KeyNode **buckets;
    size_t num_buckets;
} Dictionary;

typedef struct KeyValuePair {
    const char *key;
    const char *value;
} KeyValuePair;

static char *duplicate_string(const char *src) {
    if (!src) {
        return NULL;
    }
    
    size_t len = 0;
    while (len < MAX_STR_LEN && src[len] != '\0') {
        len++;
    }
    
    char *dst = malloc(len + 1);
    if (dst) {
        size_t i;
        for (i = 0; i < len; i++) {
            dst[i] = src[i];
        }
        dst[len] = '\0';
    }
    return dst;
}

static size_t hash_string(const char *str, size_t num_buckets) {
    size_t hash = 5381;
    int c;
    while ((c = (unsigned char)*str++)) {
        hash = ((hash << 5) + hash) + c;
    }
    return hash % num_buckets;
}

static Dictionary *create_dictionary(size_t num_buckets) {
    if (num_buckets == 0) {
        return NULL;
    }
    Dictionary *dict = malloc(sizeof(Dictionary));
    if (!dict) {
        return NULL;
    }
    dict->buckets = calloc(num_buckets, sizeof(KeyNode *));
    if (!dict->buckets) {
        free(dict);
        return NULL;
    }
    dict->num_buckets = num_buckets;
    return dict;
}

static void free_dictionary(Dictionary *dict) {
    if (!dict) {
        return;
    }
    for (size_t i = 0; i < dict->num_buckets; i++) {
        KeyNode *kn = dict->buckets[i];
        while (kn) {
            KeyNode *next_kn = kn->next;
            ValueNode *vn = kn->values_head;
            while (vn) {
                ValueNode *next_vn = vn->next;
                free(vn->value);
                free(vn);
                vn = next_vn;
            }
            free(kn->key);
            free(kn);
            kn = next_kn;
        }
    }
    free(dict->buckets);
    free(dict);
}

static int insert_pair(Dictionary *dict, const char *key, const char *value) {
    if (!dict || !key || !value) {
        return 0;
    }
    size_t index = hash_string(key, dict->num_buckets);
    KeyNode *kn = dict->buckets[index];
    while (kn) {
        if (strncmp(kn->key, key, MAX_STR_LEN) == 0) {
            break;
        }
        kn = kn->next;
    }

    if (!kn) {
        kn = malloc(sizeof(KeyNode));
        if (!kn) {
            return 0;
        }
        kn->key = duplicate_string(key);
        if (!kn->key) {
            free(kn);
            return 0;
        }
        kn->values_head = NULL;
        kn->values_tail = NULL;
        kn->next = dict->buckets[index];
        dict->buckets[index] = kn;
    }

    ValueNode *vn = malloc(sizeof(ValueNode));
    if (!vn) {
        return 0;
    }
    vn->value = duplicate_string(value);
    if (!vn->value) {
        free(vn);
        return 0;
    }
    vn->next = NULL;

    if (kn->values_tail) {
        kn->values_tail->next = vn;
        kn->values_tail = vn;
    } else {
        kn->values_head = vn;
        kn->values_tail = vn;
    }

    return 1;
}

static Dictionary *group_pairs(const KeyValuePair *pairs, size_t count) {
    if (!pairs || count == 0) {
        return NULL;
    }
    Dictionary *dict = create_dictionary(INITIAL_BUCKETS);
    if (!dict) {
        return NULL;
    }
    for (size_t i = 0; i < count; i++) {
        if (!insert_pair(dict, pairs[i].key, pairs[i].value)) {
            free_dictionary(dict);
            return NULL;
        }
    }
    return dict;
}

static void print_dictionary(const Dictionary *dict) {
    if (!dict) {
        return;
    }
    for (size_t i = 0; i < dict->num_buckets; i++) {
        KeyNode *kn = dict->buckets[i];
        while (kn) {
            printf("%s: [", kn->key);
            ValueNode *vn = kn->values_head;
            while (vn) {
                printf("\"%s\"", vn->value);
                if (vn->next) {
                    printf(", ");
                }
                vn = vn->next;
            }
            printf("]\n");
            kn = kn->next;
        }
    }
}

int main(void) {
    KeyValuePair pairs[] = {
        {"fruit", "apple"},
        {"color", "red"},
        {"fruit", "banana"},
        {"color", "blue"},
        {"animal", "dog"},
        {"fruit", "cherry"}
    };
    size_t count = sizeof(pairs) / sizeof(pairs[0]);

    Dictionary *dict = group_pairs(pairs, count);
    if (dict) {
        print_dictionary(dict);
        free_dictionary(dict);
    } else {
        fprintf(stderr, "Failed to group pairs due to an allocation error.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}