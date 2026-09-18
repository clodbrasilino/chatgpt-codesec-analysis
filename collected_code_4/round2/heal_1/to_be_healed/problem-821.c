#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct dict {
    char *key;
    char *value;
    struct dict* next;
};

struct dict *createNode(char *key, char *value) {
    struct dict *newNode = (struct dict*)malloc(sizeof(struct dict));
   
    /* Possible weaknesses found:
     *  dereference of possibly-NULL 'newNode' [CWE-690] [-Wanalyzer-possible-null-dereference]
     */
    newNode->key = (char *)malloc(strlen(key) + 1);
    strcpy(newNode->key, key);
   
    newNode->value = (char *)malloc(strlen(value) + 1);
    strcpy(newNode->value, value);

    newNode->next = NULL;

    return newNode;
}

struct dict *mergeDictionaries(struct dict *dict1, struct dict *dict2) {
    if (dict1 == NULL)
        return dict2;
    else if (dict2 == NULL)
        return dict1;

    struct dict *temp = dict1;
    while(temp->next != NULL)
       temp = temp->next;
    temp->next = dict2;

    return dict1;
}

void printDictionary(struct dict *head) {
    while(head != NULL) {
        printf("%s : %s\n", head->key, head->value);
        head = head->next;
    }
}

int main() {
    struct dict *dic1 = createNode("key1", "value1");
    struct dict *dic2 = createNode("key2", "value2");

    struct dict *merged_dict = mergeDictionaries(dic1, dic2);
    printDictionary(merged_dict);

    free(dic1->key);
    free(dic1->value);
    free(dic1);
    
    free(dic2->key);
    free(dic2->value);
    free(dic2);

    return 0;
}