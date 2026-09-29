#include <stdio.h>
#include <stdlib.h>

typedef union {
    int int_val;
    float float_val;
    double double_val;
    char char_val;
    char *str_val;
    void *ptr_val;
} TupleValue;

typedef struct {
    int type;
    TupleValue value;
} TupleElement;

typedef struct {
    TupleElement *elements;
    int size;
} Tuple;

int check_same_type(Tuple *tuple) {
    if (tuple == NULL || tuple->elements == NULL || tuple->size <= 0) {
        return 0;
    }
    
    int first_type = tuple->elements[0].type;
    
    for (int i = 1; i < tuple->size; i++) {
        if (tuple->elements[i].type != first_type) {
            return 0;
        }
    }
    
    return 1;
}

void print_tuple_value(TupleElement *element) {
    switch (element->type) {
        case 1:
            printf("Type 1 (int): %d\n", element->value.int_val);
            break;
        case 2:
            printf("Type 2 (float): %.2f\n", element->value.float_val);
            break;
        case 3:
            printf("Type 3 (double): %.2f\n", element->value.double_val);
            break;
        case 4:
            printf("Type 4 (char): %c\n", element->value.char_val);
            break;
        case 5:
            printf("Type 5 (string): %s\n", element->value.str_val);
            break;
        case 6:
            printf("Type 6 (pointer): %p\n", element->value.ptr_val);
            break;
        default:
            printf("Unknown type: %d\n", element->type);
            break;
    }
}

void print_tuple_contents(Tuple *tuple) {
    if (tuple == NULL || tuple->elements == NULL || tuple->size <= 0) {
        printf("Tuple is empty or invalid\n");
        return;
    }
    
    printf("Tuple contents (%d elements):\n", tuple->size);
    for (int i = 0; i < tuple->size; i++) {
        printf("Element %d: ", i);
        print_tuple_value(&tuple->elements[i]);
    }
}

int main(void) {
    TupleElement elements1[] = {
        {1, .value.int_val = 10},
        {1, .value.int_val = 20},
        {1, .value.int_val = 30}
    };
    Tuple tuple1 = {elements1, 3};
    
    TupleElement elements2[] = {
        {1, .value.int_val = 10},
        {2, .value.float_val = 20.5f},
        {1, .value.int_val = 30}
    };
    Tuple tuple2 = {elements2, 3};
    
    TupleElement elements3[] = {
        {3, .value.double_val = 1.5},
        {3, .value.double_val = 2.5}
    };
    Tuple tuple3 = {elements3, 2};
    
    char test_str[] = "Hello";
    int test_int = 42;
    TupleElement elements4[] = {
        {4, .value.char_val = 'A'},
        {5, .value.str_val = test_str},
        {6, .value.ptr_val = &test_int}
    };
    Tuple tuple4 = {elements4, 3};
    
    printf("Tuple 1 same type: %s\n", check_same_type(&tuple1) ? "Yes" : "No");
    print_tuple_contents(&tuple1);
    printf("\n");
    
    printf("Tuple 2 same type: %s\n", check_same_type(&tuple2) ? "Yes" : "No");
    print_tuple_contents(&tuple2);
    printf("\n");
    
    printf("Tuple 3 same type: %s\n", check_same_type(&tuple3) ? "Yes" : "No");
    print_tuple_contents(&tuple3);
    printf("\n");
    
    printf("Tuple 4 same type: %s\n", check_same_type(&tuple4) ? "Yes" : "No");
    print_tuple_contents(&tuple4);
    printf("\n");
    
    Tuple empty_tuple = {NULL, 0};
    printf("Empty tuple same type: %s\n", check_same_type(&empty_tuple) ? "Yes" : "No");
    print_tuple_contents(&empty_tuple);
    
    return 0;
}