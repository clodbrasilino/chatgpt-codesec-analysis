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

    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    size_t len = strlen(input);
    if (len == 0) {
        *out_len = 0;
        return NULL;
    }

    RleNode* result = malloc(len * sizeof(RleNode));
    if (!result) {
        *out_len = 0;
        return NULL;
    }

    size_t result_idx = 0;
    size_t i = 0;

    while (i < len) {
        char current = input[i];
        int count = 1;
        
        while (i + 1 < len && input[i + 1] == current) {
            count++;
            i++;
        }
        
        result[result_idx].count = count;
        result[result_idx].value = current;
        result_idx++;
        i++;
    }

    *out_len = result_idx;
    
    RleNode* shrunk = realloc(result, result_idx * sizeof(RleNode));
    return shrunk ? shrunk : result;
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
    /* Possible weaknesses found:
     * Flawfinder strlen: Does not handle strings that are not \0-terminated; if given one it may perform an over-read (it could cause a crash if unprotected) (CWE-126). (risk 1, buffer)
     */
    } else if (rle_len == 0 && text && strlen(text) > 0) {
        fprintf(stderr, "Memory allocation failed\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}