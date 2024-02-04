#ifndef PARSE_H
#define PARSE_H

#include <stdio.h>
#include <stdlib.h>

void mnist_imageparse(char filename[], float * input[60000])
{
    FILE * file = fopen(filename, "r");

    for (int i = 0 ; i < 60000; i++)
    {   
        float * imageArr;
        imageArr = malloc(sizeof(float) * 784);
        int spacecount = 0;
        int ch;
        while(spacecount < 784)
        {   
            int intercount = 0;
            while(intercount < 28)
            {
                ch = getc(file);
                float value = 0;
                while(ch != 32)
                {
                    value *= 10;
                    value += (ch - 48);
                    ch = getc(file);
                }
                if(value >= 100)
                {
                    value = 1;
                }
                else
                {
                    value = 0;
                }
                imageArr[spacecount] = value;
                intercount++;
                spacecount++;
            }
            getc(file);
        }
        input[i] = imageArr;
        getc(file);
        getc(file);
    }

    fclose(file);
}

void mnisttest_imageparse(char filename[], float * input[10000])
{
    FILE * file = fopen(filename, "r");

    for (int i = 0 ; i < 10000; i++)
    {   
        float * imageArr;
        imageArr = malloc(sizeof(float) * 784);
        int spacecount = 0;
        int ch;
        while(spacecount < 784)
        {   
            int intercount = 0;
            while(intercount < 28)
            {
                ch = getc(file);
                float value = 0;
                while(ch != 32)
                {
                    value *= 10;
                    value += (ch - 48);
                    ch = getc(file);
                }
                if(value >= 50)
                {
                    value = 1;
                }
                else
                {
                    value = 0;
                }
                imageArr[spacecount] = value;
                intercount++;
                spacecount++;
            }
            getc(file);
        }
        input[i] = imageArr;
        getc(file);
        getc(file);
    }

    fclose(file);
}



void mnist_labelparse(char filename[], float desired_output[60000][10])
{
    FILE * file = fopen(filename, "r");

    int value;
    for(int i = 0; i < 60000; i++)
    {
        value = getc(file) - 48;
        for(int j = 0; j < 10; j++)
        {
            if(value == j)
            {
                desired_output[i][j] = 1;
            }
            else
            {
                desired_output[i][j] = 0;
            }
        }
        getc(file);
    }
}

void mnisttest_labelparse(char filename[], float desired_output[10000][10])
{
    FILE * file = fopen(filename, "r");

    int value;
    for(int i = 0; i < 10000; i++)
    {
        value = getc(file) - 48;
        for(int j = 0; j < 10; j++)
        {
            if(value == j)
            {
                desired_output[i][j] = 1;
            }
            else
            {
                desired_output[i][j] = 0;
            }
        }
        getc(file);
    }
}

#endif
