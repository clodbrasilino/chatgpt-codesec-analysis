#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 256

char* flatten_tuple_list(int num, int tuple_list[][2]) {
    char* buffer = malloc(MAX_SIZE);
    char temp[50];
    int total_length = 0;
    if (buffer == NULL) {
        printf("Memory allocation failed.\n");
        exit(0);
    }
    buffer[0] = '\0';
    for (int i = 0; i < num; i++) {
        int written = sprintf(temp, "(%d, %d)", tuple_list[i][0], tuple_list[i][1]);
        if (total_length + written < MAX_SIZE - 1) {
            strcat(buffer, temp);
            total_length += written;
        } else {
            break;
        }
    }
    return buffer;
}

int main(void) {
    int tuple_list[3][2] = {{1,2}, {3,4}, {5,6}};
    char* result = flatten_tuple_list(3, tuple_list);
    printf("%s\n", result);
    free(result);
    return 0;
}