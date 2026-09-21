#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdint.h>

typedef struct {
    char **items;
    size_t count;
    size_t capacity;
} Tuple;

static size_t safe_strlen(const char *str, size_t maxlen) {
    if (str == NULL) {
        return 0;
    }
    size_t len = 0;
    while (len < maxlen && str[len] != '\0') {
        len++;
    }
    return len;
}

static void free_tuple_internal(Tuple *tuple) {
    if (tuple == NULL) {
        return;
    }
    for (size_t i = 0; i < tuple->count; i++) {
        free(tuple->items[i]);
    }
    free(tuple->items);
    tuple->items = NULL;
    tuple->count = 0;
    tuple->capacity = 0;
}

void string_to_tuple(const char *str, Tuple *tuple) {
    tuple->items = NULL;
    tuple->count = 0;
    tuple->capacity = 0;
    
    if (str == NULL) {
        return;
    }
    
    size_t len = safe_strlen(str, SIZE_MAX);
    if (len == 0 || len >= SIZE_MAX) {
        return;
    }
    
    if (len >= SIZE_MAX) {
        return;
    }
    
    char *copy = malloc(len + 1);
    if (copy == NULL) {
        return;
    }
    
    if (len + 1 <= len) {
        free(copy);
        return;
    }
    
    memcpy(copy, str, len);
    copy[len] = '\0';
    
    size_t capacity = 8;
    tuple->items = malloc(capacity * sizeof(char *));
    if (tuple->items == NULL) {
        free(copy);
        return;
    }
    tuple->capacity = capacity;
    
    char *start = copy;
    char *p = copy;
    int in_quotes = 0;
    char *write_ptr = copy;
    
    while (*p) {
        if (*p == '"') {
            in_quotes = !in_quotes;
            p++;
        } else if (*p == ',' && !in_quotes) {
            *write_ptr = '\0';
            
            while (isspace((unsigned char)*start)) start++;
            
            size_t remaining_start = write_ptr - start;
            if (remaining_start > len) {
                remaining_start = len;
            }
            size_t token_len = safe_strlen(start, remaining_start + 1);
            char *end = start + token_len;
            while (end > start) {
                end--;
                if (isspace((unsigned char)*end)) {
                    *end = '\0';
                } else {
                    break;
                }
            }
            
            size_t final_len = safe_strlen(start, remaining_start + 1);
            if (final_len > 0) {
                if (tuple->count >= tuple->capacity) {
                    size_t new_capacity = tuple->capacity * 2;
                    if (new_capacity < tuple->capacity || new_capacity > SIZE_MAX / sizeof(char *)) {
                        free(copy);
                        free_tuple_internal(tuple);
                        return;
                    }
                    char **new_items = realloc(tuple->items, new_capacity * sizeof(char *));
                    if (new_items == NULL) {
                        free(copy);
                        free_tuple_internal(tuple);
                        return;
                    }
                    tuple->items = new_items;
                    tuple->capacity = new_capacity;
                }
                
                tuple->items[tuple->count] = malloc(final_len + 1);
                if (tuple->items[tuple->count] == NULL) {
                    free(copy);
                    free_tuple_internal(tuple);
                    return;
                }
                memcpy(tuple->items[tuple->count], start, final_len);
                tuple->items[tuple->count][final_len] = '\0';
                tuple->count++;
            }
            
            start = p + 1;
            write_ptr = start;
            p++;
        } else {
            *write_ptr = *p;
            write_ptr++;
            p++;
        }
    }
    
    *write_ptr = '\0';
    
    while (isspace((unsigned char)*start)) start++;
    
    size_t remaining_start = write_ptr - start;
    if (remaining_start > len) {
        remaining_start = len;
    }
    size_t token_len = safe_strlen(start, remaining_start + 1);
    char *end = start + token_len;
    while (end > start) {
        end--;
        if (isspace((unsigned char)*end)) {
            *end = '\0';
        } else {
            break;
        }
    }
    
    size_t final_len = safe_strlen(start, remaining_start + 1);
    if (final_len > 0) {
        if (tuple->count >= tuple->capacity) {
            size_t new_capacity = tuple->capacity * 2;
            if (new_capacity < tuple->capacity || new_capacity > SIZE_MAX / sizeof(char *)) {
                free(copy);
                free_tuple_internal(tuple);
                return;
            }
            char **new_items = realloc(tuple->items, new_capacity * sizeof(char *));
            if (new_items == NULL) {
                free(copy);
                free_tuple_internal(tuple);
                return;
            }
            tuple->items = new_items;
            tuple->capacity = new_capacity;
        }
        
        tuple->items[tuple->count] = malloc(final_len + 1);
        if (tuple->items[tuple->count] == NULL) {
            free(copy);
            free_tuple_internal(tuple);
            return;
        }
        memcpy(tuple->items[tuple->count], start, final_len);
        tuple->items[tuple->count][final_len] = '\0';
        tuple->count++;
    }
    
    free(copy);
}

void free_tuple(Tuple *tuple) {
    free_tuple_internal(tuple);
}

int main(void) {
    const char *test1 = "hello, world, foo, bar";
    const char *test2 = "\"hello, world\", foo, bar";
    const char *test3 = "  spaced  ,  items  ";
    const char *test4 = "";
    const char *test5 = "single";
    
    Tuple t1;
    string_to_tuple(test1, &t1);
    printf("Test 1: %zu items\n", t1.count);
    for (size_t i = 0; i < t1.count; i++) {
        printf("  [%zu]: %s\n", i, t1.items[i]);
    }
    free_tuple(&t1);
    
    Tuple t2;
    string_to_tuple(test2, &t2);
    printf("Test 2: %zu items\n", t2.count);
    for (size_t i = 0; i < t2.count; i++) {
        printf("  [%zu]: %s\n", i, t2.items[i]);
    }
    free_tuple(&t2);
    
    Tuple t3;
    string_to_tuple(test3, &t3);
    printf("Test 3: %zu items\n", t3.count);
    for (size_t i = 0; i < t3.count; i++) {
        printf("  [%zu]: %s\n", i, t3.items[i]);
    }
    free_tuple(&t3);
    
    Tuple t4;
    string_to_tuple(test4, &t4);
    printf("Test 4: %zu items\n", t4.count);
    free_tuple(&t4);
    
    Tuple t5;
    string_to_tuple(test5, &t5);
    printf("Test 5: %zu items\n", t5.count);
    for (size_t i = 0; i < t5.count; i++) {
        printf("  [%zu]: %s\n", i, t5.items[i]);
    }
    free_tuple(&t5);
    
    return 0;
}