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

void print_sublists(Sublist* sublists, int count) {
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

/* Possible weaknesses found:
 *  Parameter 'list' can be declared as pointer to const [constParameterPointer]
 */
Sublist* generate_sublists(int* list, int size, int* out_count) {
    if (list == NULL && size != 0) {
        *out_count = 0;
        return NULL;
    }

    int total_sublists = 1 << size;
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
        if (sublists[i].items == NULL) {
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