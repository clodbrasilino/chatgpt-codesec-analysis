#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct dict {
    char key[50];
    char value[50];
    struct dict *next;
} dict;

typedef struct list {
    dict *head;
    struct list *next;
} list;

list* create_list() {
    list *new_list = (list*)malloc(sizeof(list));
    new_list->head = NULL;
    new_list->next = NULL;
    return new_list;
}

dict* create_dict() {
    dict *new_dict = (dict*)malloc(sizeof(dict));
    strcpy(new_dict->key, "");
    strcpy(new_dict->value, "");
    new_dict->next = NULL;
    return new_dict;
}

void add_dict(list *lst) {
    dict *new_dict = create_dict();
    if(lst->head == NULL) {
        lst->head = new_dict;
    } else {
        dict *temp = lst->head;
        while(temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = new_dict;
    }
}

int main() {
    list *lst = create_list();
    add_dict(lst);
    add_dict(lst);
    return 0;
}