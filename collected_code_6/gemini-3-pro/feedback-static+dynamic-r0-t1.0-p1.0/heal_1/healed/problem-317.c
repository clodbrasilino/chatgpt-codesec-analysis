#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    int count;
    char value;
} RleNode;

RleNode* modified_rle(const char* input, size_t* out_len) {
    if (!input || !out_len) {
        return NULL;
    }

    if (input[0] == '\0') {
        *out_len = 0;
        return NULL;
    }

    size_t capacity = 16;
    RleNode* result = malloc(capacity * sizeof(RleNode));
    if (!result) {
        *out_len = 0;
        return NULL;
    }

    size_t result_idx = 0;
    size_t i = 0;

    while (input[i] != '\0') {
        char current = input[i];
        int count = 1;

        while (input[i + 1] == current) {
            count++;
            i++;
        }

        if (result_idx >= capacity) {
            capacity *= 2;
            RleNode* temp = realloc(result, capacity * sizeof(RleNode));
            if (!temp) {
                free(result);
                *out_len = 0;
                return NULL;
            }
            result = temp;
        }

        result[result_idx].count = count;
        result[result_idx].value = current;
        result_idx++;
        i++;
    }

    *out_len = result_idx;

    if (result_idx > 0) {
        RleNode* shrunk = realloc(result, result_idx * sizeof(RleNode));
        return shrunk ? shrunk : result;
    } else {
        free(result);
        return NULL;
    }
}

int main(void) {
    const char* text = "aaaabccaadeeee";
    size_t rle_len = 0;

    RleNode* encoded = modified_rle(text, &rle_len);

    if (encoded) {
        for (size_t i = 0; i < rle_len; i++) {
            if (encoded[i].count == 1) {
                printf("%c\n", encoded[i].value);
            } else {
                printf("(%d, %c)\n", encoded[i].count, encoded[i].value);
            }
        }
        free(encoded);
    } else if (rle_len == 0 && text && text[0] != '\0') {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}