#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int count;
    char value;
} RLEPair;

typedef struct {
    RLEPair *pairs;
    size_t length;
    size_t capacity;
} RLEList;

void rle_init(RLEList *list) {
    list->pairs = NULL;
    list->length = 0;
    list->capacity = 0;
}

void rle_free(RLEList *list) {
    free(list->pairs);
    list->pairs = NULL;
    list->length = 0;
    list->capacity = 0;
}

int rle_append(RLEList *list, int count, char value) {
    if (list->length == list->capacity) {
        size_t new_capacity = list->capacity == 0 ? 16 : list->capacity * 2;
        RLEPair *new_pairs = realloc(list->pairs, new_capacity * sizeof(RLEPair));
        if (new_pairs == NULL) {
            return 0;
        }
        list->pairs = new_pairs;
        list->capacity = new_capacity;
    }
    list->pairs[list->length].count = count;
    list->pairs[list->length].value = value;
    list->length++;
    return 1;
}

RLEList rle_encode(const char *input) {
    RLEList result;
    rle_init(&result);
    
    if (input == NULL || *input == '\0') {
        return result;
    }
    
    size_t len = strlen(input);
    size_t i = 0;
    
    while (i < len) {
        char current = input[i];
        size_t j = i + 1;
        while (j < len && input[j] == current) {
            j++;
        }
        
        int count = (int)(j - i);
        
        if (count > 1) {
            if (!rle_append(&result, count, current)) {
                rle_free(&result);
                return result;
            }
        } else {
            size_t start = i;
            while (j < len && input[j] != input[j-1]) {
                j++;
            }
            if (j < len && input[j] == input[j-1]) {
                j--;
            }
            
            size_t single_count = j - start;
            if (single_count > 0) {
                if (!rle_append(&result, -(int)single_count, 0)) {
                    rle_free(&result);
                    return result;
                }
                for (size_t k = start; k < start + single_count; k++) {
                    if (!rle_append(&result, 0, input[k])) {
                        rle_free(&result);
                        return result;
                    }
                }
                i = start + single_count;
            } else {
                if (!rle_append(&result, 1, current)) {
                    rle_free(&result);
                    return result;
                }
                i++;
            }
        }
        
        if (count > 1) {
            i = j;
        }
    }
    
    return result;
}

void rle_print(const RLEList *list) {
    printf("[");
    for (size_t i = 0; i < list->length; i++) {
        if (list->pairs[i].count < 0) {
            printf("(%d,)", list->pairs[i].count);
        } else if (list->pairs[i].count == 0) {
            printf("'%c'", list->pairs[i].value);
        } else {
            printf("(%d,'%c')", list->pairs[i].count, list->pairs[i].value);
        }
        if (i < list->length - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main(void) {
    const char *test1 = "aaaabccaadeeee";
    const char *test2 = "abc";
    const char *test3 = "a";
    const char *test4 = "";
    const char *test5 = "aaabbb";
    const char *test6 = "abbbcc";
    
    RLEList result1 = rle_encode(test1);
    RLEList result2 = rle_encode(test2);
    RLEList result3 = rle_encode(test3);
    RLEList result4 = rle_encode(test4);
    RLEList result5 = rle_encode(test5);
    RLEList result6 = rle_encode(test6);
    
    printf("Input: %s\n", test1);
    rle_print(&result1);
    
    printf("Input: %s\n", test2);
    rle_print(&result2);
    
    printf("Input: %s\n", test3);
    rle_print(&result3);
    
    printf("Input: %s\n", test4);
    rle_print(&result4);
    
    printf("Input: %s\n", test5);
    rle_print(&result5);
    
    printf("Input: %s\n", test6);
    rle_print(&result6);
    
    rle_free(&result1);
    rle_free(&result2);
    rle_free(&result3);
    rle_free(&result4);
    rle_free(&result5);
    rle_free(&result6);
    
    return 0;
}