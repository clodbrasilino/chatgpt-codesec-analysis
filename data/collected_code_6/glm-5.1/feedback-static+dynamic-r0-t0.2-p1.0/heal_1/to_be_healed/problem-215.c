#include <stdio.h>
#include <stdlib.h>

/* Possible weaknesses found:
 *  Parameter 'encoded' can be declared as pointer to const [constParameterPointer]
 */
int* decode(int* encoded, int encodedSize, int* returnSize) {
    if (encoded == NULL || returnSize == NULL || encodedSize < 0) {
        if (returnSize != NULL) {
            *returnSize = 0;
        }
        return NULL;
    }

    int totalElements = 0;
    for (int i = 0; i < encodedSize; i += 2) {
        if (encoded[i] < 0) {
            *returnSize = 0;
            return NULL;
        }
        totalElements += encoded[i];
    }

    if (totalElements == 0) {
        *returnSize = 0;
        return NULL;
    }

    int* decoded = (int*)malloc(totalElements * sizeof(int));
    if (decoded == NULL) {
        *returnSize = 0;
        return NULL;
    }

    int index = 0;
    for (int i = 0; i < encodedSize; i += 2) {
        int count = encoded[i];
        int value = encoded[i + 1];
        for (int j = 0; j < count; j++) {
            decoded[index++] = value;
        }
    }

    *returnSize = totalElements;
    return decoded;
}

int main() {
    int encoded[] = {3, 1, 2, 4, 1, 5};
    int encodedSize = sizeof(encoded) / sizeof(encoded[0]);
    int returnSize = 0;

    int* decoded = decode(encoded, encodedSize, &returnSize);

    if (decoded != NULL) {
        for (int i = 0; i < returnSize; i++) {
            printf("%d ", decoded[i]);
        }
        printf("\n");
        free(decoded);
    }

    return 0;
}