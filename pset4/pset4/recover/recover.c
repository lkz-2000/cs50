#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int main(int argc, char *argv[])
{
    if(argc!=2)
    {
        printf("please do the right thing\n");
        return 1;
    }
    FILE *file;
    if((file=fopen(argv[1], "r"))==NULL)
    {
        printf("please do the right thing\n");
        return 1;
    }
    typedef uint8_t BYTE;
    BYTE buffer[512];
    int counter=0;
    char*filename=malloc(sizeof(int)*3);
    FILE*img;
    while(fread(buffer,512,1,file)==1)
    {
        if(buffer[0] == 0xff &&buffer[1] == 0xd8 &&buffer[2] == 0xff &&(buffer[3] & 0xf0) == 0xe0)
        {
            if(counter>0)
            fclose(img);
            sprintf(filename, "%03i.jpg",counter);
            img = fopen(filename, "w");
            fwrite(&buffer, 512, 1, img);
            counter++;
        }
        else
        {
            if(counter>0)
            fwrite(buffer,512,1,img);
        }
    }
    fclose(file);
    fclose(img);
    return 0;
    /*typedef uint8_t BYTE;
    BYTE  buffer[513];
    int count=0;
    char* filename = malloc(3 * sizeof(int));
    FILE*img=NULL;
    while(count<50)
    {
        int flag=0;
        do{
            fread(buffer,1,1,file);
            if(buffer[0]==0xff)
            {
                fread(&buffer[1],1,1,file);
                if(buffer[1]==0xd8)
                {
                    fread(&buffer[2],1,1,file);
                    if(buffer[2]==0xff)
                    {
                        fread(&buffer[3],1,1,file);
                        if((buffer[3]&0xf0)==0xe0)
                        {

                            flag=1;
                            if(count>0)
                            fclose(img);
                            fread(&buffer[4],1,508,file);
                            count++;
                            sprintf(filename,"%03i.jpg",count-1);
                            img=fopen(filename,"w");
                            fwrite(buffer,1,512,img);
                        }
                    }
                }
            }
           }while(flag==0);
    }
    fclose(file);
    fclose(img);
    free(filename);
    return 0;*/


}