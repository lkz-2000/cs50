#include <stdio.h>
#include <cs50.h>
#include <string.h>
int main(int argc, char* argv[])
{
    if(argc!=2)
    {
        printf("Usage: ./substitution key");
        return 1;
    }
    if(strlen(argv[1])!=26)
    {
       printf("Key must contain 26 characters.");
       return 1;
    }
    for(int i=0;i<26;i++)
    {
        int j;
        for(j=0;j<26;j++)
        {
            if((argv[1][j]==i+'a')||(argv[1][j]==i+'A')) break;
        }
        if(j==26)
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }


    }
        char* plaintext=get_string("plaintext:");
        char a[strlen(plaintext)];
        for(int i=0; i<strlen(plaintext)+1;i++)
        {
            if((plaintext[i]>='a')&&(plaintext[i]<='z'))
            {
                if((argv[1][plaintext[i]-'a']>='a')&&(argv[1][plaintext[i]-'a']<='z'))
                a[i]=argv[1][plaintext[i]-'a'];
                else
                a[i]=argv[1][plaintext[i]-'a']-'A'+'a';
            }
            else if((plaintext[i]>='A')&&(plaintext[i]<='Z'))
            {
                if((argv[1][plaintext[i]-'A']>='A')&&(argv[1][plaintext[i]-'A']<='Z'))
                a[i]=argv[1][plaintext[i]-'A'];
                else
                a[i]=argv[1][plaintext[i]-'A']-'a'+'A';
            }
            else a[i]=plaintext[i];

        }
        printf("ciphertext: %s\n",a);
        return 0;
}