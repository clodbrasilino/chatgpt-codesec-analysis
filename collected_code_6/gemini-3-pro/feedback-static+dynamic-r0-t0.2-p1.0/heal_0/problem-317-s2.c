#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int count;
    char character;
} RLEElement;

typedef struct {
    RLEElement* elements;
    size_t size;
} RLEList;

char* decode_rle(const RLEList* list) {
    if (list == NULL || list->elements == NULL) {
        return NULL;
    }

    size_t total_length = 0;
    for (size_t i = 0; i < list->size; ++i) {
        if (list->elements[i].count < 0) {
            return NULL;
        }
        total_length += (size_t)list->elements[i].count;
    }

    char* decoded_string = (char*)malloc(total_length + 1);
    if (decoded_string == NULL) {
        return NULL;
    }

    size_t current_pos = 0;
    for (size_t i = 0; i < list->size; ++i) {
        int count = list->elements[i].count;
        char c = list->elements[i].character;
        for (int j = 0; j < count; ++j) {
            decoded_string[current_pos++] = c;
        }
    }

    decoded_string[total_length] = '\0';
    return decoded_string;
}

int main(void) {
    RLEElement elements[] = {
        {4, 'A'},
        {1, 'B'},
        {3, 'C'},
        {2, 'A'}
    };
    
    RLEList list;
    list.elements = elements;
    list.size = sizeof(elements) / sizeof(elements[0]);

    char* decoded = decode_rle(&list);
    if (decoded != NULL) {
        printf("%s\n", decoded);
        free(decoded);
    } else {
        printf("Failed to decode RLE list.\n");
    }

    return 0;
}