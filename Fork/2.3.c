#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>

int is_prime(int x)
{
    if(x<2)
    {
        return 0;
    }
    if(x%2==0)
    {
        return x==2;
    }
    
    for(int i=3;i*i<=x;i+=2)
    {
        if(x%i==0)
        {
            return 0;
        }
    }
    return 1;
}

int main(int argc,char* argv[])
{
    if(argc!=2)
    {
        fprintf(stderr,"check usage");
        return 1;
    }

    int n=atoi(argv[1]);
    if(n<=0)
    {
        fprintf(stderr,"Please pass a + integer");
        return 1;
    }

    pid_t pid=fork();

    if(pid<0)
    {
        perror("Fork failed");
        return 1;
    }
    else if(pid==0)
    {
        int cnt=0;
        int num=2;

        while(cnt<=n)
        {
            if(is_prime(num))
            {
                if(cnt)
                {
                    printf(" ,");
                }
                printf("%d",num);
                fflush(stdout);
                cnt++;
            }
            num++;
        }

        printf("\n");
    }
    else {
        int status;
        waitpid(pid,&status,0);
        return 0;
    }
}