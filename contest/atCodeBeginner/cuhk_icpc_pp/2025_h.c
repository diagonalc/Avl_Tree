#include <stdio.h>
#include <string.h>

int main()
{
    char s[1000];
    int k;
    int dc = 0;
    scanf("%s", s);
    int l = strlen(s);
    scanf("%d", &k);
    if (k > l)
    {
        printf("impossible");
    }
    int abc[27] = {0};
    for (int i = 0; i < l; i++)
    {
        abc[s[i] - 'a'] = 1;
    }
    for (int i = 0; i < 26; i++)
    {
        if (abc[i] == 1)
        {
            dc++;
        }
    }
    int same = l - dc;
    int num_needtochange = ;

}