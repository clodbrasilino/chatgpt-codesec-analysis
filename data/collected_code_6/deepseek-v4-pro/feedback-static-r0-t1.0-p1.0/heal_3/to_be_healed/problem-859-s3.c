#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    /* Possible weaknesses found:
     *  struct member 'Node::data' is never used. [unusedStructMember]
     */
    int data;
    /* Possible weaknesses found:
     *  struct member 'Node::next' is never used. [unusedStructMember]
     */
    struct Node* next;
} Node;

typedef struct {
    int* items;
    int length;
} Sublist;

void print_sublists(const Sublist* sublists, int count) {
    for (int i = 0; i < count; i++) {
        printf("[");
        for (int j = 0; j < sublists[i].length; j++) {
            printf("%d", sublists[i].items[j]);
            if (j < sublists[i].length - 1) {
                printf(", ");
            }
        }
        printf("]\n");
    }
}

Sublist* generate_sublists(const int* list, int size, int* out_count) {
    if (list == NULL && size != 0) {
        *out_count = 0;
        return NULL;
    }

    /* Possible weaknesses found:
     *  Assuming that condition 'size>=(int)(sizeof(int)*8)' is not redundant
     */
    if (size >= (int)(sizeof(int) * 8)) {
        *out_count = 0;
        return NULL;
    }

    /* Possible weaknesses found:
     *  Assignment 'total_sublists=1<<size', assigned value is -2147483648
     *  Shifting signed 32-bit value by 31 bits is implementation-defined behaviour. See condition at line 33. [shiftTooManyBitsSigned]
     *  Shift
     *  Either the condition 'size>=(int)(sizeof(int)*8)' is redundant or there is signed integer overflow for expression '1<<size'. [integerOverflowCond]
     *  Integer overflow
     */
    int total_sublists = 1 << size;
    /* Possible weaknesses found:
     *  Expression 'total_sublists' can have a negative value. That is converted to an unsigned value and used in an unsigned calculation. [signConversionCond]
     *  Negative value is converted to an unsigned value
     */
    Sublist* sublists = (Sublist*)malloc(total_sublists * sizeof(Sublist));
    if (sublists == NULL) {
        *out_count = 0;
        return NULL;
    }

    for (int i = 0; i < total_sublists; i++) {
        int bit_count = 0;
        for (int j = 0; j < size; j++) {
            if (i & (1 << j)) {
                bit_count++;
            }
        }

        sublists[i].items = (int*)malloc(bit_count * sizeof(int));
        if (sublists[i].items == NULL && bit_count > 0) {
            for (int k = 0; k < i; k++) {
                free(sublists[k].items);
            }
            free(sublists);
            *out_count = 0;
            return NULL;
        }

        sublists[i].length = bit_count;
        int idx = 0;
        for (int j = 0; j < size; j++) {
            if (i & (1 << j)) {
                sublists[i].items[idx++] = list[j];
            }
        }
    }

    *out_count = total_sublists;
    return sublists;
}

void free_sublists(Sublist* sublists, int count) {
    if (sublists == NULL) {
        return;
    }
    for (int i = 0; i < count; i++) {
        free(sublists[i].items);
    }
    free(sublists);
}

int main() {
    int list[] = {1, 2, 3};
    int size = sizeof(list) / sizeof(list[0]);
    int count = 0;

    Sublist* sublists = generate_sublists(list, size, &count);
    if (sublists == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    print_sublists(sublists, count);
    free_sublists(sublists, count);

    return 0;
}