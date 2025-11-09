#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define str 20
#define page_num 10

void generate(int ref[],int n)
{
    srand(time(0));
    for(int i=0;i<n;i++)
    {
        ref[i]=rand()%page_num;
    }
}

void display(int ref[],int n)
{
    printf("Page Reference String:");
    for(int i=0;i<n;i++)
    {
        printf("%d ",ref[i]);
    }
    printf("\n");
}

int fifo(int ref[],int n,int frames)
{
    int frame[frames],front=0,faults=0;

    for(int i=0;i<frames;i++)
    {
        frame[i]=-1;
    }

    for(int i=0;i<n;i++){
        int page=ref[i];
        int found=0;

        for(int j=0;j<frames;j++)
        {
            if(page==frame[j])
            {
                found=1;
                break;
            }
        }

        if(!found)
        {
            frame[front]=page;
            front=(front+1)%frames;
            faults++;
        }
    }

    return faults;
}

int lru(int ref[],int n,int frames)
{
    int frame[frames],counter[frames];
    int faults=0,time=0;

    for(int i=0;i<frames;i++)
    {
        frame[i]=-1;
        counter[i]=0;
    }

    for(int i=0;i<n;i++)
    {
        int page=ref[i];
        int found=0;

        for(int j=0;j<frames;j++)
        {
            if(frame[j]==page)
            {
                found=1;
                counter[j]=++time;
                break;
            }
        }

        if(!found)
        {
            int min=0;
            for(int j=1;j<frames;j++)
            {
                if(counter[j]<counter[min])
                {
                    min=j;
                }
            }
            frame[min]=page;
            counter[min]=++time;
            faults++;
        }
    }

    return faults;
}

int main() {
    int n = str;
    int ref_str[str];

    generate(ref_str, n);
    display(ref_str, n);

    printf("\nNo. of Frames\tFIFO Faults\tLRU Faults\n");
    for (int frames = 1; frames <= 7; frames++) {
        int fifo_faults = fifo(ref_str, n, frames);
        int lru_faults = lru(ref_str, n, frames);
        printf("%d\t\t%d\t\t%d\n", frames, fifo_faults, lru_faults);
    }

    return 0;
}