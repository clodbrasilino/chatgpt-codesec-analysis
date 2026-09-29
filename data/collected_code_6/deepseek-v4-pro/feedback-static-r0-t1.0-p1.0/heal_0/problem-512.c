#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Tuple {
    int value;
    int is_tuple;
    struct Tuple **elements;
    int count;
} Tuple;

typedef struct Frequency {
    int value;
    int count;
    struct Frequency *next;
} Frequency;

Tuple* create_int(int value) {
    Tuple *t = (Tuple*)malloc(sizeof(Tuple));
    if (!t) return NULL;
    t->value = value;
    t->is_tuple = 0;
    t->elements = NULL;
    t->count = 0;
    return t;
}

Tuple* create_tuple(Tuple **elements, int count) {
    Tuple *t = (Tuple*)malloc(sizeof(Tuple));
    if (!t) return NULL;
    t->value = 0;
    t->is_tuple = 1;
    t->elements = elements;
    t->count = count;
    return t;
}

void free_tuple(Tuple *t) {
    if (!t) return;
    if (t->is_tuple && t->elements) {
        for (int i = 0; i < t->count; i++) {
            free_tuple(t->elements[i]);
        }
        free(t->elements);
    }
    free(t);
}

Frequency* add_frequency(Frequency *head, int value) {
    Frequency *current = head;
    while (current) {
        if (current->value == value) {
            current->count++;
            return head;
        }
        current = current->next;
    }
    
    Frequency *new_node = (Frequency*)malloc(sizeof(Frequency));
    if (!new_node) return head;
    new_node->value = value;
    new_node->count = 1;
    new_node->next = head;
    return new_node;
}

void collect_frequencies(Tuple *t, Frequency **head) {
    if (!t) return;
    
    if (!t->is_tuple) {
        *head = add_frequency(*head, t->value);
        return;
    }
    
    for (int i = 0; i < t->count; i++) {
        collect_frequencies(t->elements[i], head);
    }
}

void print_frequencies(Frequency *head) {
    Frequency *current = head;
    while (current) {
        printf("Element %d: %d time(s)\n", current->value, current->count);
        current = current->next;
    }
}

void free_frequencies(Frequency *head) {
    Frequency *current = head;
    while (current) {
        Frequency *next = current->next;
        free(current);
        current = next;
    }
}

int main() {
    Tuple **inner1_elements = (Tuple**)malloc(3 * sizeof(Tuple*));
    if (!inner1_elements) return 1;
    inner1_elements[0] = create_int(5);
    inner1_elements[1] = create_int(3);
    inner1_elements[2] = create_int(5);
    
    Tuple *inner1 = create_tuple(inner1_elements, 3);
    if (!inner1) {
        for (int i = 0; i < 3; i++) free_tuple(inner1_elements[i]);
        free(inner1_elements);
        return 1;
    }
    
    Tuple *int1 = create_int(3);
    if (!int1) {
        free_tuple(inner1);
        return 1;
    }
    
    Tuple **inner2_elements = (Tuple**)malloc(2 * sizeof(Tuple*));
    if (!inner2_elements) {
        free_tuple(inner1);
        free_tuple(int1);
        return 1;
    }
    inner2_elements[0] = create_int(5);
    inner2_elements[1] = create_int(2);
    
    Tuple *inner2 = create_tuple(inner2_elements, 2);
    if (!inner2) {
        for (int i = 0; i < 2; i++) free_tuple(inner2_elements[i]);
        free(inner2_elements);
        free_tuple(inner1);
        free_tuple(int1);
        return 1;
    }
    
    Tuple **outer_elements = (Tuple**)malloc(3 * sizeof(Tuple*));
    if (!outer_elements) {
        free_tuple(inner1);
        free_tuple(int1);
        free_tuple(inner2);
        return 1;
    }
    outer_elements[0] = inner1;
    outer_elements[1] = int1;
    outer_elements[2] = inner2;
    
    Tuple *outer = create_tuple(outer_elements, 3);
    if (!outer) {
        free_tuple(inner1);
        free_tuple(int1);
        free_tuple(inner2);
        free(outer_elements);
        return 1;
    }
    
    Frequency *freq_head = NULL;
    collect_frequencies(outer, &freq_head);
    print_frequencies(freq_head);
    
    free_frequencies(freq_head);
    free_tuple(outer);
    
    return 0;
}