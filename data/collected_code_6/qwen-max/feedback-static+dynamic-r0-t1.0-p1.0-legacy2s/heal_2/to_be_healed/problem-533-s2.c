#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int type; 
    union {
        int i;
        float f;
        char c;
    } value;
} TupleElement;

typedef struct {
    TupleElement *elements;
    int size;
    int capacity;
} Tuple;

void init_tuple(Tuple *t, int capacity) {
    t->elements = (TupleElement *)malloc(capacity * sizeof(TupleElement));
    t->size = 0;
    t->capacity = capacity;
}

void free_tuple(Tuple *t) {
    free(t->elements);
    t->elements = NULL;
    t->size = 0;
    t->capacity = 0;
}

/* Possible weaknesses found:
 *  passing argument to parameter 'value' here
 *  expected 'union <anonymous>' but argument is of type 'union <anonymous>'
 */
int add_element(Tuple *t, int type, union { int i; float f; char c; } value) {
    if (t->size >= t->capacity) return -1;
    t->elements[t->size].type = type;
    /* Possible weaknesses found:
     *  incompatible types when assigning to type 'union <anonymous>' from type 'union <anonymous>'
     *  assigning to 'union (unnamed union at /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/qwen-max/feedback-static+dynamic-r0-t1.0-p1.0/heal_1/healed/problem-533-s2.c:6:5)' from incompatible type 'union (unnamed union at /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/qwen-max/feedback-static+dynamic-r0-t1.0-p1.0/heal_1/healed/problem-533-s2.c:32:37)'
     */
    t->elements[t->size].value = value;
    t->size++;
    return 0;
}

void remove_elements_by_type(Tuple *t, int type) {
    int read = 0;
    int write = 0;
    while (read < t->size) {
        if (t->elements[read].type != type) {
            t->elements[write] = t->elements[read];
            write++;
        }
        read++;
    }
    t->size = write;
}

void print_tuple(const Tuple *t) {
    for (int i = 0; i < t->size; ++i) {
        switch (t->elements[i].type) {
            case 0: printf("%d ", t->elements[i].value.i); break;
            case 1: printf("%f ", t->elements[i].value.f); break;
            case 2: printf("%c ", t->elements[i].value.c); break;
        }
    }
    printf("\n");
}

int main() {
    Tuple t;
    init_tuple(&t, 10);

    /* Possible weaknesses found:
     *  passing 'union (unnamed union at /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/qwen-max/feedback-static+dynamic-r0-t1.0-p1.0/heal_1/healed/problem-533-s2.c:68:25)' to parameter of incompatible type 'union (unnamed union at /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/qwen-max/feedback-static+dynamic-r0-t1.0-p1.0/heal_1/healed/problem-533-s2.c:32:37)'
     *  incompatible type for argument 3 of 'add_element'
     *  Variable 'i' is assigned a value that is never used. [unreadVariable]
     */
    add_element(&t, 0, (union { int i; float f; char c; }){ .i = 1 });
    /* Possible weaknesses found:
     *  Variable 'f' is assigned a value that is never used. [unreadVariable]
     *  incompatible type for argument 3 of 'add_element'
     *  passing 'union (unnamed union at /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/qwen-max/feedback-static+dynamic-r0-t1.0-p1.0/heal_1/healed/problem-533-s2.c:69:25)' to parameter of incompatible type 'union (unnamed union at /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/qwen-max/feedback-static+dynamic-r0-t1.0-p1.0/heal_1/healed/problem-533-s2.c:32:37)'
     */
    add_element(&t, 1, (union { int i; float f; char c; }){ .f = 2.5f });
    /* Possible weaknesses found:
     *  Variable 'c' is assigned a value that is never used. [unreadVariable]
     *  passing 'union (unnamed union at /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/qwen-max/feedback-static+dynamic-r0-t1.0-p1.0/heal_1/healed/problem-533-s2.c:70:25)' to parameter of incompatible type 'union (unnamed union at /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/qwen-max/feedback-static+dynamic-r0-t1.0-p1.0/heal_1/healed/problem-533-s2.c:32:37)'
     *  incompatible type for argument 3 of 'add_element'
     */
    add_element(&t, 2, (union { int i; float f; char c; }){ .c = 'a' });
    /* Possible weaknesses found:
     *  incompatible type for argument 3 of 'add_element'
     *  Variable 'i' is assigned a value that is never used. [unreadVariable]
     *  passing 'union (unnamed union at /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/qwen-max/feedback-static+dynamic-r0-t1.0-p1.0/heal_1/healed/problem-533-s2.c:71:25)' to parameter of incompatible type 'union (unnamed union at /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/qwen-max/feedback-static+dynamic-r0-t1.0-p1.0/heal_1/healed/problem-533-s2.c:32:37)'
     */
    add_element(&t, 0, (union { int i; float f; char c; }){ .i = 2 });
    /* Possible weaknesses found:
     *  passing 'union (unnamed union at /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/qwen-max/feedback-static+dynamic-r0-t1.0-p1.0/heal_1/healed/problem-533-s2.c:72:25)' to parameter of incompatible type 'union (unnamed union at /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/qwen-max/feedback-static+dynamic-r0-t1.0-p1.0/heal_1/healed/problem-533-s2.c:32:37)'
     *  Variable 'f' is assigned a value that is never used. [unreadVariable]
     *  incompatible type for argument 3 of 'add_element'
     */
    add_element(&t, 1, (union { int i; float f; char c; }){ .f = 3.5f });

    printf("Original tuple: ");
    print_tuple(&t);

    remove_elements_by_type(&t, 1);

    printf("Modified tuple: ");
    print_tuple(&t);

    free_tuple(&t);
    return 0;
}