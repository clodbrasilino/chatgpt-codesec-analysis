#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <limits.h>

#define DICT_KEY_MAX 50

typedef struct {
    /* Possible weaknesses found:
     * Flawfinder char: Statically-sized arrays can be improperly restricted, leading to potential overflows or other issues (CWE-119!/CWE-120). Perform bounds checking, use functions that limit length, or ensure that the size is larger than the maximum possible length. (risk 2, buffer)
     */
    char key[DICT_KEY_MAX];
    int value;
} DictItem;

typedef struct {
    DictItem *items;
    size_t size;
    size_t capacity;
} Dictionary;

static int dict_validate_key(const char *key) {
    size_t len;
    
    if (key == NULL) {
        return -1;
    }
    
    len = strnlen(key, DICT_KEY_MAX);
    if (len == 0 || len >= DICT_KEY_MAX) {
        return -1;
    }
    
    return 0;
}

static int dict_check_capacity_growth(size_t current, size_t *new_capacity) {
    if (current == 0) {
        *new_capacity = 1;
        return 0;
    }
    
    if (current > SIZE_MAX / 2) {
        return -1;
    }
    
    *new_capacity = current * 2;
    
    if (*new_capacity > SIZE_MAX / sizeof(DictItem)) {
        return -1;
    }
    
    return 0;
}

int dict_init(Dictionary *dict, size_t initial_capacity) {
    if (dict == NULL || initial_capacity == 0) {
        return -1;
    }
    
    if (initial_capacity > SIZE_MAX / sizeof(DictItem)) {
        return -1;
    }
    
    dict->items = malloc(initial_capacity * sizeof(DictItem));
    if (dict->items == NULL) {
        return -1;
    }
    
    dict->size = 0;
    dict->capacity = initial_capacity;
    return 0;
}

int dict_add(Dictionary *dict, const char *key, int value) {
    size_t new_capacity;
    DictItem *new_items;
    int ret;
    
    if (dict == NULL || dict_validate_key(key) != 0) {
        return -1;
    }
    
    if (dict->size >= dict->capacity) {
        if (dict_check_capacity_growth(dict->capacity, &new_capacity) != 0) {
            return -1;
        }
        
        new_items = realloc(dict->items, new_capacity * sizeof(DictItem));
        if (new_items == NULL) {
            return -1;
        }
        
        dict->items = new_items;
        dict->capacity = new_capacity;
    }
    
    ret = snprintf(dict->items[dict->size].key, 
                   sizeof(dict->items[dict->size].key), 
                   "%s", key);
    
    if (ret < 0 || (size_t)ret >= sizeof(dict->items[dict->size].key)) {
        return -1;
    }
    
    dict->items[dict->size].value = value;
    dict->size++;
    return 0;
}

long dict_sum(const Dictionary *dict) {
    long sum = 0;
    size_t i;
    
    if (dict == NULL) {
        return 0;
    }
    
    for (i = 0; i < dict->size; i++) {
        if (dict->items[i].value > 0 && sum > LONG_MAX - dict->items[i].value) {
            return LONG_MAX;
        }
        if (dict->items[i].value < 0 && sum < LONG_MIN - dict->items[i].value) {
            return LONG_MIN;
        }
        sum += dict->items[i].value;
    }
    
    return sum;
}

void dict_free(Dictionary *dict) {
    if (dict != NULL) {
        free(dict->items);
        dict->items = NULL;
        dict->size = 0;
        dict->capacity = 0;
    }
}

int main(void) {
    Dictionary dict;
    long result;

    if (dict_init(&dict, 4) != 0) {
        fprintf(stderr, "Failed to initialize dictionary\n");
        return EXIT_FAILURE;
    }

    if (dict_add(&dict, "a", 10) != 0 ||
        dict_add(&dict, "b", 20) != 0 ||
        dict_add(&dict, "c", 30) != 0 ||
        dict_add(&dict, "d", 40) != 0 ||
        dict_add(&dict, "e", 50) != 0) {
        fprintf(stderr, "Failed to add items\n");
        dict_free(&dict);
        return EXIT_FAILURE;
    }

    result = dict_sum(&dict);
    printf("Sum of all items: %ld\n", result);

    dict_free(&dict);
    return EXIT_SUCCESS;
}