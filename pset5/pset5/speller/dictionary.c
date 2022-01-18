// Implements a dictionary's functionality

#include <stdbool.h>

#include "dictionary.h"
#include <strings.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];
int number=0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    if((word[0]=='t'||word[0]=='T')&&(word[1]=='h'||word[1]=='H')&&(word[2]=='e'||word[2]=='E'))
    return true;
    node *cursor=table[hash(word)];
    while(cursor!=NULL)
    {
        if(strcasecmp(word,cursor->word)==0)
        return true;
        cursor=cursor->next;
    }
    // TODO
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int i;
    if((word[0]>='A')&&(word[0]<='Z'))
    i=word[0]-'a'-'A'+'a';
    else
    i=word[0]-'a';
    return i;// TODO
    return 0;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    FILE*ptr=fopen(dictionary,"r");
    if(ptr==NULL)
    return false;
    char aword[LENGTH + 1];
    while(fscanf(ptr,"%s",aword)!=EOF)
    {
        number++;
        node *n=malloc(sizeof(node));
        if (n == NULL)
        return 1;
        n->next=NULL;
        if(n==NULL)
        return false;
        strcpy(n->word,aword);
        n->next=table[hash(aword)];
        table[hash(aword)]=n;

    }
    if(fscanf(ptr,"%s",aword)==EOF)
    fclose(ptr);
    return true;
     // TODO
    return false;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return number;// TODO
    return 0;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    int i;
    for(i=0;i<N;i++)
    {
        node *cursor=table[i];
        while(cursor!=NULL)
        {
            node *tmp=cursor;
            cursor=cursor->next;
            free(tmp);
        }

    }
    if(i==N)
    return true;

    // TODO
    return false;
}
