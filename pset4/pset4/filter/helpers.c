#include "helpers.h"
#include <stdio.h>
#include <math.h>
#include <string.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            uint8_t av=round((image[i][j].rgbtBlue+image[i][j].rgbtGreen+image[i][j].rgbtRed)/3.0);
            image[i][j].rgbtBlue=av;
            image[i][j].rgbtGreen=av;
            image[i][j].rgbtRed=av;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            double sepiaRed,sepiaGreen,sepiaBlue;
            sepiaRed = 0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue;
            if(sepiaRed>255)
            sepiaRed=255;
            sepiaGreen = 0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue;
            if(sepiaGreen>255)
            sepiaGreen=255;
            sepiaBlue = 0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue;
            if(sepiaBlue>255)
            sepiaBlue=255;
            image[i][j].rgbtRed=round(sepiaRed);
            image[i][j].rgbtGreen=round(sepiaGreen);
            image[i][j].rgbtBlue=round(sepiaBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width/2;j++)
        {
            RGBTRIPLE tmp;
            tmp=image[i][j];
            image[i][j]=image[i][width-j-1];
            image[i][width-j-1]=tmp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int Blue[height][width], Green[height][width], Red[height][width];
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            Blue[i][j]=0;
            Green[i][j]=0;
            Red[i][j]=0;
        }
    }
    double num=0;
    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {

            for(int k=i-1;k<i+2;k++)
            {
                for(int l=j-1;l<j+2;l++)
                {
                    //printf("out%d %d %d %d %d\n", i, j, k, l, num);
                    if((k>=0)&&(k<height)&&(l>=0)&&(l<width))
                    {
                        num++;
                        //printf("in%d %d %d %d %d\n", i, j, k, l, num);
                        Blue[i][j]=image[k][l].rgbtBlue+Blue[i][j];
                        Green[i][j]=image[k][l].rgbtGreen+Green[i][j];
                        Red[i][j]=image[k][l].rgbtRed+Red[i][j];
                    }

                }

            }
            Blue[i][j]=round(Blue[i][j]/num);
            Green[i][j]=round(Green[i][j]/num);
            Red[i][j]=round(Red[i][j]/num);
            num=0;
        }
    }

    for(int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            image[i][j].rgbtBlue=(BYTE)Blue[i][j];
            image[i][j].rgbtGreen=(BYTE)Green[i][j];
            image[i][j].rgbtRed=(BYTE)Red[i][j];
        }
    }

    return;
}
