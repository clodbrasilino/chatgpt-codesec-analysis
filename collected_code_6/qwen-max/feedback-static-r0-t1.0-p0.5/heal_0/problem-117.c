#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <float.h>

typedef struct {
    char *str;
} Element;

typedef struct {
    Element *elements;
    int size;
} List;

List* create_list(int size) {
    List *list = (List*)malloc(sizeof(List));
    list->size = size;
    list->elements = (Element*)malloc(size * sizeof(Element));
    for (int i = 0; i < size; ++i) {
        list->elements[i].str = NULL;
    }
    return list;
}

void free_list(List *list) {
    if (list) {
        for (int i = 0; i < list->size; ++i) {
            free(list->elements[i].str);
        }
        free(list->elements);
        free(list);
    }
}

int is_convertible_to_float(const char *str) {
    if (str == NULL || *str == '\0') {
        return 0;
    }
    while (*str) {
        if (!isdigit(*str) && *str != '.' && *str != '-' && *str != '+') {
            return 0;
        }
        str++;
    }
    return 1;
}

float convert_to_float(const char *str) {
    return atof(str);
}

void convert_elements_to_float(List *list) {
    for (int i = 0; i < list->size; ++i) {
        if (is_convertible_to_float(list->elements[i].str)) {
            float value = convert_to_float(list->elements[i].str);
            asprintf(&list->elements[i].str, "%f", value);
        }
    }
}

int main() {
    List *list = create_list(4);
    list->elements[0].str = strdup("123");
    list->elements[1].str = strdup("456.789");
    list->elements[2].str = strdup("abc");
    list->elements[3].str = strdup("-123.45");

    convert_elements_to_float(list);

    for (int i = 0; i < list->size; ++i) {
        printf("%s\n", list->elements[i].str);
    }

    free_list(list);
    return 0;
}