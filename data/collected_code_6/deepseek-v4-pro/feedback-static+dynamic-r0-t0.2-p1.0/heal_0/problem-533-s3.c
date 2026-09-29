#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

typedef enum {
    TYPE_INT,
    TYPE_FLOAT,
    TYPE_DOUBLE,
    TYPE_CHAR,
    TYPE_STRING,
    TYPE_UNKNOWN
} DataType;

typedef struct {
    DataType type;
    void *data;
} TupleElement;

typedef struct {
    TupleElement *elements;
    size_t size;
} Tuple;

DataType get_type_from_string(const char *type_str) {
    if (strcmp(type_str, "int") == 0) return TYPE_INT;
    if (strcmp(type_str, "float") == 0) return TYPE_FLOAT;
    if (strcmp(type_str, "double") == 0) return TYPE_DOUBLE;
    if (strcmp(type_str, "char") == 0) return TYPE_CHAR;
    if (strcmp(type_str, "string") == 0) return TYPE_STRING;
    return TYPE_UNKNOWN;
}

Tuple* remove_elements_by_type(const Tuple *input, DataType type_to_remove) {
    if (input == NULL) {
        return NULL;
    }

    size_t count = 0;
    for (size_t i = 0; i < input->size; i++) {
        if (input->elements[i].type != type_to_remove) {
            count++;
        }
    }

    Tuple *result = (Tuple*)malloc(sizeof(Tuple));
    if (result == NULL) {
        return NULL;
    }

    result->size = count;
    if (count == 0) {
        result->elements = NULL;
        return result;
    }

    result->elements = (TupleElement*)malloc(count * sizeof(TupleElement));
    if (result->elements == NULL) {
        free(result);
        return NULL;
    }

    size_t index = 0;
    for (size_t i = 0; i < input->size; i++) {
        if (input->elements[i].type != type_to_remove) {
            result->elements[index].type = input->elements[i].type;
            
            switch (input->elements[i].type) {
                case TYPE_INT:
                    result->elements[index].data = malloc(sizeof(int));
                    if (result->elements[index].data != NULL) {
                        *(int*)result->elements[index].data = *(int*)input->elements[i].data;
                    }
                    break;
                case TYPE_FLOAT:
                    result->elements[index].data = malloc(sizeof(float));
                    if (result->elements[index].data != NULL) {
                        *(float*)result->elements[index].data = *(float*)input->elements[i].data;
                    }
                    break;
                case TYPE_DOUBLE:
                    result->elements[index].data = malloc(sizeof(double));
                    if (result->elements[index].data != NULL) {
                        *(double*)result->elements[index].data = *(double*)input->elements[i].data;
                    }
                    break;
                case TYPE_CHAR:
                    result->elements[index].data = malloc(sizeof(char));
                    if (result->elements[index].data != NULL) {
                        *(char*)result->elements[index].data = *(char*)input->elements[i].data;
                    }
                    break;
                case TYPE_STRING: {
                    const char *str = (const char*)input->elements[i].data;
                    size_t len = strlen(str) + 1;
                    result->elements[index].data = malloc(len);
                    if (result->elements[index].data != NULL) {
                        memcpy(result->elements[index].data, str, len);
                    }
                    break;
                }
                default:
                    result->elements[index].data = NULL;
                    break;
            }
            index++;
        }
    }

    return result;
}

void free_tuple(Tuple *tuple) {
    if (tuple == NULL) {
        return;
    }

    if (tuple->elements != NULL) {
        for (size_t i = 0; i < tuple->size; i++) {
            if (tuple->elements[i].data != NULL) {
                free(tuple->elements[i].data);
            }
        }
        free(tuple->elements);
    }
    free(tuple);
}

void print_tuple(const Tuple *tuple) {
    if (tuple == NULL) {
        printf("NULL tuple\n");
        return;
    }

    printf("(");
    for (size_t i = 0; i < tuple->size; i++) {
        switch (tuple->elements[i].type) {
            case TYPE_INT:
                printf("%d", *(int*)tuple->elements[i].data);
                break;
            case TYPE_FLOAT:
                printf("%f", *(float*)tuple->elements[i].data);
                break;
            case TYPE_DOUBLE:
                printf("%lf", *(double*)tuple->elements[i].data);
                break;
            case TYPE_CHAR:
                printf("'%c'", *(char*)tuple->elements[i].data);
                break;
            case TYPE_STRING:
                printf("\"%s\"", (char*)tuple->elements[i].data);
                break;
            default:
                printf("unknown");
                break;
        }
        if (i < tuple->size - 1) {
            printf(", ");
        }
    }
    printf(")\n");
}

int main(void) {
    Tuple tuple;
    tuple.size = 6;
    tuple.elements = (TupleElement*)malloc(tuple.size * sizeof(TupleElement));
    
    if (tuple.elements == NULL) {
        return 1;
    }

    int int_val = 42;
    float float_val = 3.14f;
    double double_val = 2.71828;
    char char_val = 'A';
    const char *str_val = "hello";
    int int_val2 = 100;

    tuple.elements[0].type = TYPE_INT;
    tuple.elements[0].data = &int_val;
    
    tuple.elements[1].type = TYPE_FLOAT;
    tuple.elements[1].data = &float_val;
    
    tuple.elements[2].type = TYPE_DOUBLE;
    tuple.elements[2].data = &double_val;
    
    tuple.elements[3].type = TYPE_CHAR;
    tuple.elements[3].data = &char_val;
    
    tuple.elements[4].type = TYPE_STRING;
    tuple.elements[4].data = (void*)str_val;
    
    tuple.elements[5].type = TYPE_INT;
    tuple.elements[5].data = &int_val2;

    printf("Original tuple: ");
    print_tuple(&tuple);

    Tuple *result = remove_elements_by_type(&tuple, TYPE_INT);
    printf("After removing int: ");
    print_tuple(result);

    Tuple *result2 = remove_elements_by_type(&tuple, TYPE_STRING);
    printf("After removing string: ");
    print_tuple(result2);

    Tuple *result3 = remove_elements_by_type(&tuple, TYPE_FLOAT);
    printf("After removing float: ");
    print_tuple(result3);

    free_tuple(result);
    free_tuple(result2);
    free_tuple(result3);
    free(tuple.elements);

    return 0;
}