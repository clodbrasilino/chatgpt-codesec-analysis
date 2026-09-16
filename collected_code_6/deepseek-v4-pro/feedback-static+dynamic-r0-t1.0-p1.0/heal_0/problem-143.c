#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int type;
    void *data;
    int length;
} Element;

typedef struct {
    Element *elements;
    int length;
} Tuple;

bool is_list(Element element) {
    return element.type == 1;
}

int count_lists(Tuple *tuple) {
    if (tuple == NULL || tuple->elements == NULL) {
        return 0;
    }
    
    int count = 0;
    for (int i = 0; i < tuple->length; i++) {
        if (is_list(tuple->elements[i])) {
            count++;
        }
    }
    
    return count;
}

int main(void) {
    Tuple tuple;
    Element elements[3];
    
    elements[0].type = 1;
    elements[0].data = NULL;
    elements[0].length = 3;
    
    elements[1].type = 0;
    elements[1].data = NULL;
    elements[1].length = 0;
    
    elements[2].type = 1;
    elements[2].data = NULL;
    elements[2].length = 5;
    
    tuple.elements = elements;
    tuple.length = 3;
    
    int result = count_lists(&tuple);
    printf("%d\n", result);
    
    return 0;
}