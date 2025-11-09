#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void bubble(int arr[],int n)
{
    for(int i=0;i<n-1;i++)
    {
        for(int j=0;j<n-i-1;j++)
        {
            if(arr[j]>arr[j+1])
            {
                int temp=arr[j];
                arr[j]=arr[j+1];
                arr[j+1]=temp;
            }
        }
    }
}

int scan(int req[],int n,int head,int disk)
{
    int total=0;
    int i;

    for(i=0;i<n;i++)
    {
        if(req[i]>head)
        {
            break;
        }
    }

    int current=head;
    printf("\n===== SCAN Disk Scheduling =====\nSequence of movements:\n");

    for(int j=i;j<n;j++)
    {
        printf("%d->",req[j]);
        total+=abs(current-req[j]);
        current=req[j];
    }
    if(current<disk-1)
    {
        total+=abs(current-(disk-1));
        printf("%d->",(disk-1));
        current=disk-1;
    }

    for(int j=i-1;j>=0;j--){
        printf("%d->",req[j]);
        total+=abs(current-req[j]);
        current=req[j];
    }
    printf("END\nTotal Head Movement (SCAN): %d\n", total);
    printf("Average Seek Distance (SCAN): %.2f\n", (float)total / n);

    return total;
}

int look(int req[],int n,int head)
{
    int total=0;
    int i;

    for(i=0;i<n;i++)
    {
        if(req[i]>head)
        {
            break;
        }
    }

    int current=head;

    printf("\n===== LOOK Disk Scheduling =====\nSequence of movements:\n");

    for(int j=i;j<n;j++)
    {
        printf("%d -> ", req[j]);
        total += abs(current - req[j]);
        current = req[j];
    }

    for(int j=i-1;j>=0;j--)
    {
        printf("%d->",req[j]);
        total+=abs(current-req[j]);
        current=req[j];
    }

    printf("END\nTotal Head Movement (LOOK): %d\n", total);
    printf("Average Seek Distance (LOOK): %.2f\n", (float)total / n);

    return total;
}

int main() {
    int requests[] = {20, 229, 39, 450, 18, 145, 120, 380, 20, 250};
    int n = sizeof(requests) / sizeof(requests[0]);
    int head = 185;
    int disk_size = 500;

    bubble(requests, n);

    printf("Initial Head Position: %d\n", head);
    printf("Pending Requests: ");
    for (int i = 0; i < n; i++)
        printf("%d ", requests[i]);
    printf("\n");

    int total_scan = scan(requests, n, head, disk_size);
    int total_look = look(requests, n, head);

    printf("\n===  Comparison ===\n");
    if (total_scan < total_look)
        printf(" SCAN performed better (less head movement).\n");
    else if (total_look < total_scan)
        printf("  LOOK performed better (less head movement).\n");
    else
        printf(" Both performed equally.\n");

    return 0;
}