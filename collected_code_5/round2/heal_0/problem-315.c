#include <stdio.h>
#include <string.h>

int maxLengthEvenWord(char* str)
{
    int n = strlen(str);

    int count = 0, max_length = 0;
    for (int i = 0; i <= n; i++)
    {
        if (str[i] != ' ' && i != n)
            count++;
        else
        {
            if (count % 2 == 0) {
                if (count > max_length)
                    max_length = count;
            }
            count = 0;
        }
    }
    return max_length;
}

int main()
{
    char str[] = "Hello to my big YourWorld Universe";
    int len = maxLengthEvenWord(str);
    if (len > 0)
        printf("Length of longest even word: %d\n", len);
    else
        printf("No word with even length found\n");
    return 0;
}