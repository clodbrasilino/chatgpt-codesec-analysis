#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int get_colon_of_tuple(const char* tuple) {
    if (tuple == NULL) {
        printf("Tuple cannot be NULL\n");
        return -1;
    }

    int colon_index = -1;
    for(int i = 0; tuple[i] != '\0'; i++) {
        if(tuple[i] == ':') {
            colon_index = i;
            break;
        }
}

    if (colon_index == -1) {
        printf("No colon found in the tuple\n");
        return -1;
    }

    const char* number = tuple + colon_index + 1;
    return atoi(number);
}

int main() {
    const char* tuple = "(1:22)";
    int valueAfterColon = get_colon_of_tuple(tuple);

    if(valueAfterColon != -1) {
        printf("The value after the colon in the tuple is %d\n", valueAfterColon);
    }
    return 0;
}