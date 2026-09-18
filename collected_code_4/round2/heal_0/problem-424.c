#include <stdio.h>
#include <string.h>

char *extract_rear_elements(char **input, int length) {
    char *rear_elements = malloc(length * sizeof(char));
    if(rear_elements == NULL) {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    for(int i = 0; i < length; i++) {
        int str_len = strlen(input[i]);

        if(str_len > 0) {
            rear_elements[i] = input[i][str_len - 1];
        } else {
            printf("Empty string at index %d.\n", i);
            exit(1);
        }
    }
    return rear_elements;
}

int main() {
    const int length = 3;
    char *strings[length] = {"Hello", "World", "!"};

    char *rear_elements = extract_rear_elements(strings, length);

    for (int i = 0; i < length; i++)
        printf("%c\n", rear_elements[i]);

    free(rear_elements);

    return 0;
}