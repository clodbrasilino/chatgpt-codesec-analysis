#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int count;
    char value;
} RLEToken;

typedef struct {
    RLEToken *tokens;
    size_t length;
} RLEList;

RLEList *rle_encode(const char *input) {
    if (input == NULL) {
        return NULL;
    }

    size_t input_len = strlen(input);
    if (input_len == 0) {
        RLEList *empty = (RLEList *)malloc(sizeof(RLEList));
        if (empty == NULL) {
            return NULL;
        }
        empty->tokens = NULL;
        empty->length = 0;
        return empty;
    }

    RLEToken *tokens = (RLEToken *)malloc(input_len * sizeof(RLEToken));
    if (tokens == NULL) {
        return NULL;
    }

    size_t token_count = 0;
    size_t i = 0;

    while (i < input_len) {
        char current = input[i];
        int count = 1;
        while (i + count < input_len && input[i + count] == current) {
            count++;
        }
        tokens[token_count].count = count;
        tokens[token_count].value = current;
        token_count++;
        i += count;
    }

    RLEToken *resized = (RLEToken *)realloc(tokens, token_count * sizeof(RLEToken));
    if (resized == NULL && token_count > 0) {
        free(tokens);
        return NULL;
    }

    RLEList *result = (RLEList *)malloc(sizeof(RLEList));
    if (result == NULL) {
        free(resized != NULL ? resized : tokens);
        return NULL;
    }

    result->tokens = resized != NULL ? resized : tokens;
    result->length = token_count;
    return result;
}

void rle_free(RLEList *list) {
    if (list == NULL) {
        return;
    }
    free(list->tokens);
    free(list);
}

void rle_print(const RLEList *list) {
    if (list == NULL) {
        printf("NULL\n");
        return;
    }
    for (size_t i = 0; i < list->length; i++) {
        printf("(%d,%c) ", list->tokens[i].count, list->tokens[i].value);
    }
    printf("\n");
}

int main(void) {
    const char *test1 = "aaabbbcccaaa";
    const char *test2 = "";
    const char *test3 = "a";
    const char *test4 = "abcd";
    const char *test5 = NULL;

    RLEList *rle1 = rle_encode(test1);
    RLEList *rle2 = rle_encode(test2);
    RLEList *rle3 = rle_encode(test3);
    RLEList *rle4 = rle_encode(test4);
    RLEList *rle5 = rle_encode(test5);

    printf("Test 1: ");
    rle_print(rle1);
    printf("Test 2: ");
    rle_print(rle2);
    printf("Test 3: ");
    rle_print(rle3);
    printf("Test 4: ");
    rle_print(rle4);
    printf("Test 5: ");
    rle_print(rle5);

    rle_free(rle1);
    rle_free(rle2);
    rle_free(rle3);
    rle_free(rle4);
    rle_free(rle5);

    return 0;
}