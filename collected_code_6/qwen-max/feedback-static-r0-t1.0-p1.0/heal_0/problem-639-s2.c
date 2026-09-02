#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int sum_name_lengths(char *names[], int count) {
    int total_length = 0;
    for (int i = 0; i < count; ++i) {
        if (isupper(names[i][0])) {
            total_length += strlen(names[i]);
        }
    }
    return total_length;
}

int main() {
    char *names[] = {
        "Alice",
        "bob",
        "Charlie",
        "diana",
        "Eve"
    };
    int count = sizeof(names) / sizeof(names[0]);
    
    int result = sum_name_lengths(names, count);
    printf("Total length: %d\n", result);

    return 0;
}