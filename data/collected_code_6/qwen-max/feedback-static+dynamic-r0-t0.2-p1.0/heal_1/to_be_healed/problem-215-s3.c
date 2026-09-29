#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'encoded' can be declared as pointer to const [constParameterPointer]
 */
int* decode_rle(int* encoded, int encodedSize, int* returnSize) {
    *returnSize = 0;
    for (int i = 0; i < encodedSize; i += 2) {
        *returnSize += encoded[i];
    }
    int* decoded = (int*)malloc(*returnSize * sizeof(int));
    if (decoded == NULL) {
        *returnSize = 0;
        return NULL;
    }
    int index = 0;
    for (int i = 0; i < encodedSize; i += 2) {
        for (int j = 0; j < encoded[i]; ++j) {
            decoded[index++] = encoded[i + 1];
        }
    }
    return decoded;
}

int main() {
    int encoded[] = {2, 3, 3, 5, 1, 7};
    int encodedSize = 6;
    int returnSize;
    int* decoded = decode_rle(encoded, encodedSize, &returnSize);
    if (decoded != NULL) {
        for (int i = 0; i < returnSize; ++i) {
            printf("%d ", decoded[i]);
        }
        free(decoded);
    }
    return 0;
}