#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NUM 100

long long int ConvertToInt(int *list, int len) {
    char str[MAX_NUM] = "";
    char buffer[10];
    for(int i = 0; i < len; i++){
        sprintf(buffer, "%d", list[i]);
        strcat(str, buffer);
    }
    return atoll(str);
}

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    int len = sizeof(numbers)/sizeof(numbers[0]);
    long long int result = ConvertToInt(numbers, len);
    printf("%lld\n", result);
    return 0;
}
