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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Blue[height][width], Green[height][width], Red[height][width];
    int tmpblue[height+2][width+2],tmpgreen[height+2][width+2],tmpred[height+2][width+2];
    for(int i=0;i<height+2;i++)
    {
        for(int j=0;j<width+2;j++)
        {
            tmpblue[i][j]=0;
            tmpgreen[i][j]=0;
            tmpred[i][j]=0;
        }
    }
    for(int i=1;i<height+1;i++)
    {
        for(int j=1;j<width+1;j++)
        {
            tmpblue[i][j]=image[i-1][j-1].rgbtBlue;
            tmpgreen[i][j]=image[i-1][j-1].rgbtGreen;
            tmpred[i][j]=image[i-1][j-1].rgbtRed;
        }
    }

    for(int i=1;i<height+1;i++)
    {
        for(int j=1;j<width+1;j++)
        {
            double gxb=0,gxg=0,gxr=0,gyb=0,gyg=0,gyr=0;
            gxb=tmpblue[i-1][j+1]+2*tmpblue[i][j+1]+tmpblue[i+1][j+1]-
            tmpblue[i-1][j-1]-2*tmpblue[i][j-1]-tmpblue[i+1][j-1];

            gxg=tmpgreen[i-1][j+1]+2*tmpgreen[i][j+1]+tmpgreen[i+1][j+1]-
            tmpgreen[i-1][j-1]-2*tmpgreen[i][j-1]-tmpgreen[i+1][j-1];

            gxr=tmpred[i-1][j+1]+2*tmpred[i][j+1]+tmpred[i+1][j+1]-
            tmpred[i-1][j-1]-2*tmpred[i][j-1]-tmpred[i+1][j-1];

            gyb=tmpblue[i+1][j-1]+2*tmpblue[i+1][j]+tmpblue[i+1][j+1]-tmpblue[i-1][j-1]-2*tmpblue[i-1][j]-tmpblue[i-1][j+1];
            gyg=tmpgreen[i+1][j-1]+2*tmpgreen[i+1][j]+tmpgreen[i+1][j+1]-tmpgreen[i-1][j-1]-2*tmpgreen[i-1][j]-tmpgreen[i-1][j+1];
            gyr=tmpred[i+1][j-1]+2*tmpred[i+1][j]+tmpred[i+1][j+1]-tmpred[i-1][j-1]-2*tmpred[i-1][j]-tmpred[i-1][j+1];

            Blue[i-1][j-1]=round(sqrt(gxb*gxb+gyb*gyb));
            if(Blue[i-1][j-1]>255)
            Blue[i-1][j-1]=255;
            Green[i-1][j-1]=round(sqrt(gxg*gxg+gyg*gyg));
            if(Green[i-1][j-1]>255)
            Green[i-1][j-1]=255;
            Red[i-1][j-1]=round(sqrt(gxr*gxr+gyr*gyr));
            if(Red[i-1][j-1]>255)
            Red[i-1][j-1]=255;
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
