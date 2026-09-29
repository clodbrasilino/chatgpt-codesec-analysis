#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int count;
    char character;
} RLE_Element;

RLE_Element* encode_modified_rle(const char* input, size_t len, int* out_size) {
    if (!input || !out_size) {
        return NULL;
    }

    if (len == 0) {
        *out_size = 0;
        return NULL;
    }

    RLE_Element* result = malloc(len * sizeof(RLE_Element));
    if (!result) {
        return NULL;
    }

    int count = 1;
    int index = 0;

    for (size_t i = 1; i <= len; i++) {
        if (i < len && input[i] == input[i - 1]) {
            count++;
        } else {
            result[index].count = count;
            result[index].character = input[i - 1];
            index++;
            count = 1;
        }
    }

    *out_size = index;

    if (index == 0) {
        free(result);
        return NULL;
    }
    
    RLE_Element* shrunk_result = realloc(result, index * sizeof(RLE_Element));
    if (!shrunk_result) {
        return result;
    }

    return shrunk_result;
}

int main(void) {
    const char test_str[] = "aaaabccaadeeee";
    int out_size = 0;
    size_t len = sizeof(test_str) - 1;

    RLE_Element* encoded = encode_modified_rle(test_str, len, &out_size);

    if (encoded) {
        for (int i = 0; i < out_size; i++) {
            if (encoded[i].count == 1) {
                printf("%c\n", encoded[i].character);
            } else {
                printf("(%d, %c)\n", encoded[i].count, encoded[i].character);
            }
        }
        free(encoded);
    }

    return 0;
}