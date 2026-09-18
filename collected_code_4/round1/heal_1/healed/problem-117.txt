#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

typedef struct Node{
    char* data;
    struct Node* next;
}Node;

float convertToFloat(char* str){
    float result = 0;
    int i = 0;

    while (i < strlen(str)){
        if (!isdigit(str[i]) && str[i] != '.'){
            return -1;
        }
        i++;
    }
    
    result = strtof(str, NULL);
    return result;
}

Node* convertListElementsToFloat(Node* head){
    Node* currNode = head;

    while(currNode != NULL){
        float floatData = convertToFloat(currNode->data);
        if(floatData == -1){
            printf("Warning: Node data is not a number.\n");
        } else{
            free(currNode->data);
            currNode->data = (char*) malloc(sizeof(float) * 4 + 1);
            sprintf(currNode->data, "%f", floatData);
        }
        
        currNode = currNode->next;
    }
    
    return head;
}

Node* addToLinkedList(Node* head, char* data){
    Node* newNode = (Node*) malloc(sizeof(Node));

    if(newNode == NULL){
        return head;
    }

    newNode->data = (char*) malloc(strlen(data) + 1);
    strcpy(newNode->data, data);
    newNode->next = NULL;

    if(head == NULL){
        head = newNode;
    } else{
        Node* lastNode = head;
        while(lastNode->next != NULL){
            lastNode = lastNode->next;
        }
        lastNode->next = newNode;
    }

    return head;
}

void printLinkedList(Node* head){
    Node* temp = head;

    while(temp != NULL){
        printf("%s -> ", temp->data);
        temp = temp->next;
    }
    
    printf("NULL\n");
}

void freeLinkedList(Node* head){
    Node* temp;

    while(head != NULL){
        temp = head;
        head = head->next;
        free(temp->data);
        free(temp);
    }
}

int main(){
    Node* head = NULL;

    head = addToLinkedList(head, "10");
    head = addToLinkedList(head, "20.5");
    head = addToLinkedList(head, "abc");
    
    printf("Original List: \n");
    printLinkedList(head);
    
    printf("\nList After Conversion: \n");
    head = convertListElementsToFloat(head);
    printLinkedList(head);

    freeLinkedList(head);

    return 0;
}