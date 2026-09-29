#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct{
    char *first;
    char *second;
} StringTuple;

StringTuple* concatenate_tuples(StringTuple *t1, StringTuple *t2){
    if(!t1 || !t2){
        return NULL;
    }

    StringTuple *result = (StringTuple*) malloc(sizeof(StringTuple));

    if(result == NULL) {
        return NULL;
    }

    result->first = malloc(strlen(t1->first) + strlen(t2->first) + 1);
    result->second = malloc(strlen(t1->second) + strlen(t2->second) + 1);

    if(result->first == NULL || result->second == NULL) {
        if(result->first != NULL) free(result->first);
        if(result->second != NULL) free(result->second);
        free(result);
        return NULL;
    }

    strcpy(result->first, t1->first);
    strcat(result->first, t2->first);
    strcpy(result->second, t1->second);
    strcat(result->second, t2->second);

    return result;
}

int main(){
    StringTuple t1;
    StringTuple t2;
    
    t1.first = "Hello";
    t1.second = "World";
    t2.first = "Goodbye";
    t2.second = "Universe";

    StringTuple *result = concatenate_tuples(&t1, &t2);

    if(result != NULL){
        printf("%s %s\n", result->first, result->second);
    }

    free(result->first);
    free(result->second);
    free(result);
    
    return 0;
}