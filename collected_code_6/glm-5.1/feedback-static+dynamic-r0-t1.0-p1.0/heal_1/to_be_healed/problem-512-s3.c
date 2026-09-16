#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef enum { TYPE_INT, TYPE_TUPLE } ElementType;

typedef struct Element {
    ElementType type;
    union {
        int int_val;
        struct Element *tuple;
    } data;
} Element;

typedef struct FreqNode {
    int key;
    int count;
    struct FreqNode *next;
} FreqNode;

/* Possible weaknesses found:
 *  Parameter 'tuple' can be declared as pointer to const [constParameterPointer]
 */
void count_frequency(Element *tuple, FreqNode **freq_map) {
    if (tuple == NULL) {
        return;
    }
    size_t i = 0;
    while (1) {
        Element current = tuple[i];
        if (current.type == TYPE_INT) {
            FreqNode *node = *freq_map;
            FreqNode *prev = NULL;
            int found = 0;
            while (node != NULL) {
                if (node->key == current.data.int_val) {
                    node->count++;
                    found = 1;
                    break;
                }
                prev = node;
                node = node->next;
            }
            if (!found) {
                FreqNode *new_node = (FreqNode *)malloc(sizeof(FreqNode));
                if (new_node == NULL) {
                    exit(EXIT_FAILURE);
                }
                new_node->key = current.data.int_val;
                new_node->count = 1;
                new_node->next = NULL;
                if (prev == NULL) {
                    *freq_map = new_node;
                } else {
                    prev->next = new_node;
                }
            }
            i++;
        } else if (current.type == TYPE_TUPLE) {
            if (current.data.tuple != NULL) {
                count_frequency(current.data.tuple, freq_map);
                i++;
            } else {
                return;
            }
        } else {
            return;
        }
    }
}

void free_freq_map(FreqNode *node) {
    while (node != NULL) {
        FreqNode *next = node->next;
        free(node);
        node = next;
    }
}

/* Possible weaknesses found:
 *  Parameter 'tuple' can be declared as pointer to const [constParameterPointer]
 */
void free_tuple(Element *tuple) {
    if (tuple == NULL) {
        return;
    }
    size_t i = 0;
    while (1) {
        Element current = tuple[i];
        if (current.type == TYPE_INT) {
            i++;
        } else if (current.type == TYPE_TUPLE) {
            if (current.data.tuple != NULL) {
                free_tuple(current.data.tuple);
                i++;
            } else {
                return;
            }
        } else {
            return;
        }
    }
}

Element create_int(int val) {
    Element e;
    e.type = TYPE_INT;
    e.data.int_val = val;
    return e;
}

Element create_tuple(Element *tuple) {
    Element e;
    e.type = TYPE_TUPLE;
    e.data.tuple = tuple;
    return e;
}

Element create_sentinel() {
    Element e;
    e.type = -1;
    e.data.int_val = 0;
    return e;
}

int main(void) {
    Element inner1[] = {create_int(1), create_int(2), create_int(2), create_sentinel()};
    Element inner2[] = {create_int(3), create_int(1), create_sentinel()};
    Element inner3[] = {create_int(1), create_int(4), create_sentinel()};
    
    Element nested[] = {
        create_int(1), 
        create_tuple(inner1), 
        create_int(3), 
        create_tuple(inner2), 
        create_tuple(inner3), 
        create_int(5), 
        create_sentinel()
    };

    Element root[] = {create_tuple(nested), create_sentinel()};

    FreqNode *freq_map = NULL;
    count_frequency(root, &freq_map);

    FreqNode *curr = freq_map;
    while (curr != NULL) {
        printf("%d: %d\n", curr->key, curr->count);
        curr = curr->next;
    }

    free_freq_map(freq_map);
    free_tuple(root);

    return 0;
}