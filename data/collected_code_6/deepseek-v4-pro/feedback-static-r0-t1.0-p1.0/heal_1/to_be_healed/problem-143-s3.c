#include <stdio.h>
#include <stdlib.h>

typedef enum {
    TYPE_INT,
    TYPE_LIST,
    TYPE_TUPLE
} ObjectType;

typedef struct Object {
    ObjectType type;
    struct Object **items;
    int count;
} Object;

Object* create_object(ObjectType type) {
    Object *obj = (Object*)malloc(sizeof(Object));
    if (obj == NULL) {
        return NULL;
    }
    obj->type = type;
    obj->items = NULL;
    obj->count = 0;
    return obj;
}

void free_object(Object *obj) {
    if (obj == NULL) {
        return;
    }
    if (obj->items != NULL) {
        for (int i = 0; i < obj->count; i++) {
            free_object(obj->items[i]);
        }
        free(obj->items);
    }
    free(obj);
}

int count_lists_in_tuple(Object *tuple) {
    if (tuple == NULL || tuple->type != TYPE_TUPLE) {
        return 0;
    }
    
    int count = 0;
    for (int i = 0; i < tuple->count; i++) {
        Object *item = tuple->items[i];
        /* Possible weaknesses found:
         *  Assuming condition 'item->type==TYPE_LIST' is false
         */
        if (item->type == TYPE_LIST) {
            count++;
        }
        else if (item->type == TYPE_TUPLE) {
            count += count_lists_in_tuple(item);
        }
        /* Possible weaknesses found:
         *  Condition 'item->type==TYPE_LIST' is always false
         *  Condition 'item->type==TYPE_LIST' is always false [knownConditionTrueFalse]
         */
        else if (item->type == TYPE_LIST) {
            for (int j = 0; j < item->count; j++) {
                Object *nested = item->items[j];
                if (nested->type == TYPE_LIST) {
                    count++;
                }
                else if (nested->type == TYPE_TUPLE) {
                    count += count_lists_in_tuple(nested);
                }
            }
        }
    }
    return count;
}

int main() {
    Object *tuple = create_object(TYPE_TUPLE);
    Object *list1 = create_object(TYPE_LIST);
    Object *list2 = create_object(TYPE_LIST);
    Object *int_obj = create_object(TYPE_INT);
    Object *nested_tuple = create_object(TYPE_TUPLE);
    Object *nested_list = create_object(TYPE_LIST);
    Object *nested_int = create_object(TYPE_INT);
    
    list1->count = 1;
    list1->items = (Object**)malloc(sizeof(Object*));
    list1->items[0] = create_object(TYPE_INT);
    
    list2->count = 1;
    list2->items = (Object**)malloc(sizeof(Object*));
    list2->items[0] = create_object(TYPE_INT);
    
    nested_list->count = 1;
    nested_list->items = (Object**)malloc(sizeof(Object*));
    nested_list->items[0] = create_object(TYPE_INT);
    
    nested_tuple->count = 2;
    nested_tuple->items = (Object**)malloc(2 * sizeof(Object*));
    nested_tuple->items[0] = nested_list;
    nested_tuple->items[1] = nested_int;
    
    tuple->count = 4;
    tuple->items = (Object**)malloc(4 * sizeof(Object*));
    tuple->items[0] = list1;
    tuple->items[1] = int_obj;
    tuple->items[2] = list2;
    tuple->items[3] = nested_tuple;
    
    int result = count_lists_in_tuple(tuple);
    printf("%d\n", result);
    
    free_object(tuple);
    return 0;
}