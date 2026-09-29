#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char *str;
} StringData;

void map(void *data, void (*func)(void *)) {
    if (data && func) {
        func(data);
    }
}

/* Possible weaknesses found:
 *  Parameter 'data' can be declared as pointer to const
 *  Parameter 'data' can be declared as pointer to const. However it seems that 'printString' is a callback function, if 'data' is declared with const you might also need to cast function pointer(s). [constParameterCallback]
 */
void printString(void *data) {
    const StringData *const strData = (const StringData *)data;
    if (strData->str) {
        printf("%s\n", strData->str);
    }
}

int main() {
    StringData strings[] = {
        {"Hello"},
        {"World"},
        {"C Programming"},
        {NULL}
    };

    for (int i = 0; strings[i].str != NULL; ++i) {
        /* Possible weaknesses found:
         *  You might need to cast the function pointer here
         */
        map((void *)&strings[i], printString);
    }

    return 0;
}