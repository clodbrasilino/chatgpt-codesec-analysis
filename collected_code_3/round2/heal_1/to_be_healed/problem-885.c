#include <stdio.h>
#include <string.h>
 /* Possible weaknesses found:
  *  'bool' is defined in header '<stdbool.h>'; did you forget to '#include <stdbool.h>'?
  */

#define MAX_CHARS 256

int areIsomorphic(char* str1, char* str2)
{
    int m = strlen(str1);
    int n = strlen(str2);

    if (m != n)
      return 0;

    int map[MAX_CHARS];
    memset(map, -1, sizeof(map));

    /* Possible weaknesses found:
     *  'false' undeclared (first use in this function)
     *  unknown type name 'bool'
     *  each undeclared identifier is reported only once for each function it appears in
     *  'false' is defined in header '<stdbool.h>'; did you forget to '#include <stdbool.h>'?
     */
    bool marked[MAX_CHARS] = {false};

    for (int i = 0; i < n; i++)
    {
        if (map[str1[i]] == -1)
        {
            /* Possible weaknesses found:
             *  'true' undeclared (first use in this function)
             *  'true' is defined in header '<stdbool.h>'; did you forget to '#include <stdbool.h>'?
             */
            if (marked[str2[i]] == true)
                return 0;

            marked[str2[i]] = true;

            map[str1[i]] = str2[i];
        }

        else if (map[str1[i]] != str2[i])
            return 0;
    }

    return 1;
}

int main()
{
   char str1[] = "aab";
   char str2[] = "xxy";
   printf("%s", areIsomorphic(str1, str2) ? "Yes" : "No");
   return 0;
}