#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int count;
    int value;
} RLEPair;

typedef struct {
    RLEPair *data;
    size_t length;
    size_t capacity;
} RLEList;

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 */
RLEList* rle_encode(int *list, size_t list_len) {
    RLEList *rle = malloc(sizeof(RLEList));
    if (!rle) return NULL;

    rle->capacity = list_len > 0 ? list_len : 1;
    rle->data = malloc(rle->capacity * sizeof(RLEPair));
    if (!rle->data) {
        free(rle);
        return NULL;
    }
    rle->length = 0;

    if (list_len == 0) return rle;

    rle->data[0].value = list[0];
    rle->data[0].count = 1;
    rle->length = 1;

    for (size_t i = 1; i < list_len; i++) {
        if (list[i] == rle->data[rle->length - 1].value && rle->data[rle->length - 1].count < 9) {
            rle->data[rle->length - 1].count++;
        } else {
            if (rle->length >= rle->capacity) {
                rle->capacity *= 2;
                RLEPair *new_data = realloc(rle->data, rle->capacity * sizeof(RLEPair));
                if (!new_data) {
                    free(rle->data);
                    free(rle);
                    return NULL;
                }
                rle->data = new_data;
            }
            rle->data[rle->length].value = list[i];
            rle->data[rle->length].count = 1;
            rle->length++;
        }
    }

    return rle;
}

void rle_free(RLEList *rle) {
    if (rle) {
        free(rle->data);
        free(rle);
    }
}

int main() {
    int input[] = {1, 1, 1, 1, 1, 2, 2, 2, 3, 3, 3, 3, 3, 3, 3, 3, 3, 3, 4, 4, 5};
    size_t input_len = sizeof(input) / sizeof(input[0]);

    RLEList *encoded = rle_encode(input, input_len);
    if (!encoded) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    for (size_t i = 0; i < encoded->length; i++) {
        printf("[%d, %d]", encoded->data[i].count, encoded->data[i].value);
        if (i < encoded->length - 1) {
            printf(", ");
        }
    }
    printf("\n");

    rle_free(encoded);

    return 0;
}