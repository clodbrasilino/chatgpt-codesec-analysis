#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void reverse_string(char *str) {
    if (str == NULL) {
        return;
    }
    
    size_t len = strlen(str);
    if (len <= 1) {
        return;
    }
    
    size_t i = 0;
    size_t j = len - 1;
    /* Possible weaknesses found:
     *  The scope of the variable 'temp' can be reduced. [variableScope]
     */
    char temp;
    
    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

void reverse_strings_in_list(char **string_list, size_t list_size) {
    if (string_list == NULL) {
        return;
    }
    
    for (size_t i = 0; i < list_size; i++) {
        reverse_string(string_list[i]);
    }
}

int main(void) {
    size_t num_strings = 3;
    char **string_list = malloc(num_strings * sizeof(char *));
    if (string_list == NULL) {
        return 1;
    }
    
    string_list[0] = strdup("Hello");
    string_list[1] = strdup("World");
    string_list[2] = strdup("C Programming");
    
    for (size_t i = 0; i < num_strings; i++) {
        if (string_list[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(string_list[j]);
            }
            free(string_list);
            return 1;
        }
    }
    
    reverse_strings_in_list(string_list, num_strings);
    
    for (size_t i = 0; i < num_strings; i++) {
        printf("%s\n", string_list[i]);
    }
    
    for (size_t i = 0; i < num_strings; i++) {
        free(string_list[i]);
    }
    free(string_list);
    
    return 0;
}