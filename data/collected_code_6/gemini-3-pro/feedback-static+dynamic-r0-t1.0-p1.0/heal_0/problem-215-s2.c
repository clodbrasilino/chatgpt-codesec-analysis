#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int value;
    int count;
} RLEElement;

typedef struct {
    int *data;
    size_t length;
    size_t capacity;
} DecodedList;

int initDecodedList(DecodedList *list, size_t initialCapacity) {
    list->data = (int *)malloc(initialCapacity * sizeof(int));
    if (list->data == NULL) {
        return 0;
    }
    list->length = 0;
    list->capacity = initialCapacity;
    return 1;
}

int appendDecodedList(DecodedList *list, int value) {
    if (list->length == list->capacity) {
        size_t newCapacity = list->capacity == 0 ? 1 : list->capacity * 2;
        int *newData = (int *)realloc(list->data, newCapacity * sizeof(int));
        if (newData == NULL) {
            return 0;
        }
        list->data = newData;
        list->capacity = newCapacity;
    }
    list->data[list->length++] = value;
    return 1;
}

void freeDecodedList(DecodedList *list) {
    if (list->data != NULL) {
        free(list->data);
        list->data = NULL;
    }
    list->length = 0;
    list->capacity = 0;
}

int decodeRLE(const RLEElement *encodedList, size_t encodedLength, DecodedList *decodedList) {
    if (encodedList == NULL || decodedList == NULL) {
        return 0;
    }

    if (!initDecodedList(decodedList, encodedLength * 2)) {
        return 0;
    }

    for (size_t i = 0; i < encodedLength; ++i) {
        if (encodedList[i].count < 0) {
            freeDecodedList(decodedList);
            return 0;
        }
        for (int j = 0; j < encodedList[i].count; ++j) {
            if (!appendDecodedList(decodedList, encodedList[i].value)) {
                freeDecodedList(decodedList);
                return 0;
            }
        }
    }

    return 1;
}

int main(void) {
    RLEElement encoded[] = {
        {1, 3},
        {2, 1},
        {4, 4},
        {8, 0},
        {9, 2}
    };
    size_t encodedLength = sizeof(encoded) / sizeof(encoded[0]);

    DecodedList decoded;
    if (decodeRLE(encoded, encodedLength, &decoded)) {
        for (size_t i = 0; i < decoded.length; ++i) {
            printf("%d ", decoded.data[i]);
        }
        printf("\n");
        freeDecodedList(&decoded);
    } else {
        fprintf(stderr, "Failed to decode list.\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}