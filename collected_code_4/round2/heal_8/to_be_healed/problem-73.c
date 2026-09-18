#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<regex.h>

#define MAX_MATCHES 100

typedef struct {
    char** array;
    size_t used;
    size_t size;
} Array;

void initArray(Array* a, size_t initialSize);
void insertArray(Array* a, char* element);
void freeArray(Array* a);
Array* regex_split(const char* string, const char* regex_pattern);
int main(int argc, char**argv);

void initArray(Array* a, size_t initialSize) {
    a->array = (char**)malloc(initialSize * sizeof(char*));
    if(a->array == NULL){
        exit(EXIT_FAILURE);
    }
    a->used = 0;
    a->size = initialSize;
}

void insertArray(Array* a, char* element) {
    if (a->used == a->size) {
        a->size *= 2;
        char** temp = (char**)realloc(a->array, a->size * sizeof(char*));
        if(temp == NULL) {
            /* Possible weaknesses found:
             *  leak of '<unknown>' [CWE-401] [-Wanalyzer-malloc-leak]
             */
            free(a->array);
            exit(EXIT_FAILURE);
        }
        a->array = temp;
    }
    a->array[a->used++] = strdup(element);
    if(a->array[a->used - 1] == NULL) {
        freeArray(a);
        free(a);
        exit(EXIT_FAILURE);
    }
}

void freeArray(Array* a) {
    for (size_t i = 0; i < a->used; i++) {
        free(a->array[i]);
    }
    free(a->array);
    a->array = NULL;
    a->used = a->size = 0;
}

Array* regex_split(const char* string, const char* regex_pattern) {
    regmatch_t matches[MAX_MATCHES];
    regex_t regex_compiled;
    const char* p = string;
    Array *arr = (Array *)malloc(sizeof(Array));

    if(arr == NULL){
        exit(EXIT_FAILURE);
    }
    
    initArray(arr, 1);

    if (regcomp(&regex_compiled, regex_pattern, REG_EXTENDED)) {
        /* Possible weaknesses found:
         *  leak of '<unknown>' [CWE-401] [-Wanalyzer-malloc-leak]
         */
        free(arr);
        exit(EXIT_FAILURE);
    }

    while (1) {
        if (regexec(&regex_compiled, p, MAX_MATCHES, matches, 0) != 0){
            break;
        }
        if (matches[0].rm_so != 0) {
            char* new_str = (char*)malloc(matches[0].rm_so + 1);
            if(new_str == NULL) {
                freeArray(arr);
                free(arr);
                regfree(&regex_compiled);
                exit(EXIT_FAILURE);
            }
            memcpy(new_str, p, matches[0].rm_so);
            new_str[matches[0].rm_so] = '\0';
            insertArray(arr, new_str);
            free(new_str);
        }
        p += matches[0].rm_eo;
    }
    
    regfree(&regex_compiled);
    return arr;
}

int main(int argc, char**argv) {
    Array* arr = regex_split("TextColor=Yellow", "[=]");

    if(arr != NULL) {
        for (size_t i = 0; i<arr->used; i++) {
            printf("%s\n", arr->array[i]);
        }
        freeArray(arr);
        free(arr);
    }

    return 0;
}