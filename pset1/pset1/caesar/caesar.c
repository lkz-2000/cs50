#include <stdio.h>
#include <cs50.h>
#include <string.h>
int main(int argc, char* argv[])
{
    if(argc==1)
    {
        printf("Usage: ./caesar key");
        return 1;
    }
    int num = 0;
    for (int i = 0; argv[1][i]; i ++)
    {
        if((argv[1][i]<'0')||(argv[1][i]>'9'))
        {
            printf("Usage: ./caesar key\n");
            return 1;
        }

        num = num * 10 + (argv[1][i] - '0');
    }
    if(argc>2)
    {
        printf("Usage: ./caesar key");
        return 1;
    }
    else
    {
        char* plaintext=get_string("plaintext:");
        char a[strlen(plaintext)];
        for(int i=0; i<strlen(plaintext);i++)
        {
            if((plaintext[i]>='a')&&(plaintext[i]<='z'))
            {
                a[i]=(plaintext[i] - 'a' + num) % 26 + 'a';
            }
            else if((plaintext[i]>='A')&&(plaintext[i]<='Z'))
            {
                a[i]=(plaintext[i] - 'A' + num) % 26 + 'A';
            }
            else a[i]=plaintext[i];

        }
        printf("ciphertext:%s\n",a);

    }
    return 0;
}