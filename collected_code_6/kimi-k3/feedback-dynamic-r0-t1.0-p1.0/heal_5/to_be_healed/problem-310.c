#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct {
    char **items;
    size_t count;
    size_t capacity;
} Tuple;

Tuple *tuple_create(void) {
    Tuple *t = malloc(sizeof(Tuple));
    if (t == NULL) {
        return NULL;
    }
    t->capacity = 8;
    t->count = 0;
    t->items = malloc(t->capacity * sizeof(char *));
    if (t->items == NULL) {
        free(t);
        return NULL;
    }
    return t;
}

int tuple_append(Tuple *t, const char *item) {
    if (t == NULL || item == NULL) {
        return -1;
    }
    if (t->count >= t->capacity) {
        size_t new_cap = t->capacity * 2;
        char **new_items = realloc(t->items, new_cap * sizeof(char *));
        if (new_items == NULL) {
            return -1;
        }
        t->items = new_items;
        t->capacity = new_cap;
    }
    t->items[t->count] = malloc(strlen(item) + 1);
    if (t->items[t->count] == NULL) {
        return -1;
    }
    strcpy(t->items[t->count], item);
    t->count++;
    return 0;
}

void tuple_free(Tuple *t) {
    if (t == NULL) {
        return;
    }
    for (size_t i = 0; i < t->count; i++) {
        free(t->items[i]);
    }
    free(t->items);
    free(t);
}
 /* Possible weaknesses found:
  *  test case 2 failed: expected ['1', '5', '.', '1', '0'], got <no output>
  *  test case 1 failed: expected ['i', 't', 'e', 'm', '1'], got <no output>
  *  test case 0 failed: expected ['p', 'y', 't', 'h', 'o', 'n', '3', '.', '0'], got <no output>
  */

Tuple *string_to_tuple(const char *str) {
    if (str == NULL) {
        return NULL;
    }
    
    Tuple *t = tuple_create();
    if (t == NULL) {
        return NULL;
    }
    
    for (size_t i = 0; str[i] != '\0'; i++) {
        char ch[2] = {str[i], '\0'};
        if (tuple_append(t, ch) != 0) {
            tuple_free(t);
            return NULL;
        }
    }
    
    return t;
}

int main(void) {
    const char *inputs[] = {
        "python3.0",
        "item1",
        "1,5.10"
    };
    
    for (size_t i = 0; i < sizeof(inputs) / sizeof(inputs[0]); i++) {
        Tuple *t = string_to_tuple(inputs[i]);
        
        if (t == NULL) {
            fprintf(stderr, "Failed to convert string to tuple\n");
            return EXIT_FAILURE;
        }
        
        printf("(");
        for (size_t j = 0; j < t->count; j++) {
            printf("'%s'", t->items[j]);
            if (j < t->count - 1) {
                printf(", ");
            }
        }
        printf(")\n");
        
        tuple_free(t);
    }
    
    return EXIT_SUCCESS;
}