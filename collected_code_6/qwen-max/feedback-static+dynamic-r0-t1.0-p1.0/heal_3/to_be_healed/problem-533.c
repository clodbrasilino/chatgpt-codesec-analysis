#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int type; // 0 for int, 1 for float, 2 for char
    union {
        int i;
        float f;
        char c;
    } value;
} TupleElement;

typedef struct {
    TupleElement *data;
    size_t size;
    size_t capacity;
} Tuple;

Tuple* create_tuple(size_t capacity) {
    Tuple *t = (Tuple*)malloc(sizeof(Tuple));
    t->data = (TupleElement*)malloc(capacity * sizeof(TupleElement));
    t->size = 0;
    t->capacity = capacity;
    return t;
}

/* Possible weaknesses found:
 *  passing argument to parameter 'value' here
 *  expected 'union <anonymous>' but argument is of type 'union <anonymous>'
 */
void tuple_add(Tuple *t, int type, union { int i; float f; char c; } value) {
    if (t->size == t->capacity) {
        t->capacity *= 2;
        t->data = (TupleElement*)realloc(t->data, t->capacity * sizeof(TupleElement));
    }
    t->data[t->size].type = type;
    /* Possible weaknesses found:
     *  incompatible types when assigning to type 'union <anonymous>' from type 'union <anonymous>'
     *  assigning to 'union (unnamed union at /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/qwen-max/feedback-static+dynamic-r0-t1.0-p1.0/heal_2/healed/problem-533.c:6:5)' from incompatible type 'union (unnamed union at /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/qwen-max/feedback-static+dynamic-r0-t1.0-p1.0/heal_2/healed/problem-533.c:27:36)'
     */
    t->data[t->size].value = value;
    t->size++;
}

Tuple* remove_elements_by_type(Tuple *t, int type) {
    Tuple *result = create_tuple(t->size);
    for (size_t i = 0; i < t->size; ++i) {
        if (t->data[i].type != type) {
            /* Possible weaknesses found:
             *  passing 'union (unnamed union at /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/qwen-max/feedback-static+dynamic-r0-t1.0-p1.0/heal_2/healed/problem-533.c:6:5)' to parameter of incompatible type 'union (unnamed union at /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/qwen-max/feedback-static+dynamic-r0-t1.0-p1.0/heal_2/healed/problem-533.c:27:36)'
             *  incompatible type for argument 3 of 'tuple_add'
             */
            tuple_add(result, t->data[i].type, t->data[i].value);
        }
    }
    return result;
}

void free_tuple(Tuple *t) {
    free(t->data);
    free(t);
}

int main() {
    Tuple *t = create_tuple(5);
    /* Possible weaknesses found:
     *  passing 'union (unnamed union at /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/qwen-max/feedback-static+dynamic-r0-t1.0-p1.0/heal_2/healed/problem-533.c:54:22)' to parameter of incompatible type 'union (unnamed union at /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/qwen-max/feedback-static+dynamic-r0-t1.0-p1.0/heal_2/healed/problem-533.c:27:36)'
     *  Variable 'i' is assigned a value that is never used. [unreadVariable]
     *  incompatible type for argument 3 of 'tuple_add'
     */
    tuple_add(t, 0, (union { int i; float f; char c; }){.i = 1});
    /* Possible weaknesses found:
     *  Variable 'f' is assigned a value that is never used. [unreadVariable]
     *  passing 'union (unnamed union at /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/qwen-max/feedback-static+dynamic-r0-t1.0-p1.0/heal_2/healed/problem-533.c:55:22)' to parameter of incompatible type 'union (unnamed union at /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/qwen-max/feedback-static+dynamic-r0-t1.0-p1.0/heal_2/healed/problem-533.c:27:36)'
     *  incompatible type for argument 3 of 'tuple_add'
     */
    tuple_add(t, 1, (union { int i; float f; char c; }){.f = 2.5});
    /* Possible weaknesses found:
     *  passing 'union (unnamed union at /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/qwen-max/feedback-static+dynamic-r0-t1.0-p1.0/heal_2/healed/problem-533.c:56:22)' to parameter of incompatible type 'union (unnamed union at /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/qwen-max/feedback-static+dynamic-r0-t1.0-p1.0/heal_2/healed/problem-533.c:27:36)'
     *  Variable 'c' is assigned a value that is never used. [unreadVariable]
     *  incompatible type for argument 3 of 'tuple_add'
     */
    tuple_add(t, 2, (union { int i; float f; char c; }){.c = 'a'});
    /* Possible weaknesses found:
     *  passing 'union (unnamed union at /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/qwen-max/feedback-static+dynamic-r0-t1.0-p1.0/heal_2/healed/problem-533.c:57:22)' to parameter of incompatible type 'union (unnamed union at /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/qwen-max/feedback-static+dynamic-r0-t1.0-p1.0/heal_2/healed/problem-533.c:27:36)'
     *  Variable 'i' is assigned a value that is never used. [unreadVariable]
     *  incompatible type for argument 3 of 'tuple_add'
     */
    tuple_add(t, 0, (union { int i; float f; char c; }){.i = 3});
    /* Possible weaknesses found:
     *  Variable 'f' is assigned a value that is never used. [unreadVariable]
     *  passing 'union (unnamed union at /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/qwen-max/feedback-static+dynamic-r0-t1.0-p1.0/heal_2/healed/problem-533.c:58:22)' to parameter of incompatible type 'union (unnamed union at /Users/clodbrasilino/zju-workspace/chatgpt-codesec-analysis/collected_code_6/qwen-max/feedback-static+dynamic-r0-t1.0-p1.0/heal_2/healed/problem-533.c:27:36)'
     *  incompatible type for argument 3 of 'tuple_add'
     */
    tuple_add(t, 1, (union { int i; float f; char c; }){.f = 4.5});

    Tuple *filtered = remove_elements_by_type(t, 1);

    for (size_t i = 0; i < filtered->size; ++i) {
        switch (filtered->data[i].type) {
            case 0:
                printf("%d\n", filtered->data[i].value.i);
                break;
            case 1:
                printf("%.2f\n", filtered->data[i].value.f);
                break;
            case 2:
                printf("%c\n", filtered->data[i].value.c);
                break;
        }
    }

    free_tuple(t);
    free_tuple(filtered);
    return 0;
}