#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define WORD_SIZE_MAX 1000

struct wordNode {
    char *word;
    struct wordNode *next;
};

void removeDuplicates(char *str) {
    struct wordNode *head = NULL, *temp, *prev;
    char *token = strtok(str, " ");

    while (token != NULL) {
        temp = head;
        struct wordNode *prev = NULL;
        while (temp) {
            if (temp->word != NULL && strcmp(temp->word, token) == 0)
                break;
            prev = temp;
            temp = temp->next;
        }

        if (temp == NULL) {
            temp = (struct wordNode *) malloc(sizeof(struct wordNode));
            if (temp != NULL) {
                temp->word = strdup(token);
                temp->next = NULL;

                if (head == NULL) {
                    head = temp;
                } else {
                    prev->next = temp;
                }

                printf("%s ", token);
            }
        }

        token = strtok(NULL, " ");
    }

    temp = head;
    struct wordNode *next = NULL;
    while (temp != NULL) {
        next = temp->next;

        if (temp->word != NULL) {
            free(temp->word);
        }
        free(temp);

        temp = next;
    }
}

int main() {
    char str[WORD_SIZE_MAX] = "This is a test. This test is good. test This is also good.";
    removeDuplicates(str);
    return 0;
}
