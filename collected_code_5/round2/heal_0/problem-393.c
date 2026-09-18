#include <stdio.h>

// Node structure
struct Node {
    int data;
    struct Node* next;
};

// Function to get length of a linked list
int getLength(struct Node* head){
    int count = 0;
    while (head != NULL){
        head = head->next;
        count++;
    }
    return count;
}

// Function to find max length list
struct Node* maxLengthList(struct Node* head1, struct Node* head2){
   
    int len1 = getLength(head1);
    int len2 = getLength(head2);
    
    if (len1 >= len2)
        return head1;
    else
        return head2;
}

// Main function
int main(){
    struct Node* head1 = NULL;
    struct Node* head2 = NULL;
    
    // assuming some code here that creates and fill two linked lists pointed by head1 and head2

    /* Function call to find list with maximum length */
    struct Node* maxList = maxLengthList(head1, head2);
    if (maxList == head1){
        printf("List 1 is longer or equally long as list 2\n");
    } else {
        printf("List 2 is longer\n");
    }
    
    return 0;
}