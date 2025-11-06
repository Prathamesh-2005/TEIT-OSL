#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void sort(int arr[],int n)
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

int cscan(int request[],int n,int head,int disk_size)
{
    int total=0;
    int i;

    for( i=0;i<n;i++)
    {
        if(request[i]>head){
            break;
        }
    }

    int current=head;
    
    printf("\n===== 🌀 C-SCAN Disk Scheduling =====\nSequence of movements:\n");

    for(int j=i;j<n;j++)
    {
        printf("%d->",request[j]);
        total+=abs(current-request[j]);
        current=request[j];
    }

    if(current<disk_size-1)
    {
        total+=abs(current-(disk_size-1));
        printf("%d->",(disk_size-1));
        current=disk_size-1;
    }
    
    total+=(disk_size-1);
    printf("0->");
    current=0;

    for(int j=0;j<i;j++)
    {
        printf("%d->",request[j]);
        total+=abs(current-request[j]);
        current=request[j];
    }
     printf("END\nTotal Head Movement (C-SCAN): %d\n", total);
     printf("Average Seek time is : %.2f\n",(float)total/n);

     return total;

}

int clook(int request[],int n,int head)
{
    int total=0;
    int i=0;
    
    for(i=0;i<n;i++)
    {
        if(request[i]>head)
        {
            break;
        }
    }
    int current=head;

    printf("\n===== 🔁 C-LOOK Disk Scheduling =====\nSequence of movements:\n");

    for(int j=i;j<n;j++)
    {
        printf("%d->",request[j]);
        total+=abs(current-request[j]);
        current=request[j];
    }

    total+=abs(current-request[0]);
    printf("%d->",request[0]);
    current=request[0];

    for(int j=1;j<i;j++)
    {
        total+=abs(current-request[j]);
        printf("%d->",request[j]);
        current=request[j];
    }

    printf("END\nTotal Head Movement (C-LOOK): %d\n", total);
    printf("Average Seek Distance (C-LOOK): %.2f\n",
           (float)total/ n);

    return total;
}

int main() {
    int requests[] = {10, 229, 39, 400, 18, 145, 120, 480, 20, 250};
    int n = sizeof(requests) / sizeof(requests[0]);
    int head = 85;
    int disk_size = 500;

    sort(requests, n);

    printf("Initial Head Position: %d\n", head);
    printf("Requests: ");
    for (int i = 0; i < n; i++)
        printf("%d ", requests[i]);
    printf("\n");

    int total_cscan = cscan(requests, n, head, disk_size);
    int total_clook = clook(requests, n, head);

    printf("\n=== 📊 Comparison ===\n");
    if (total_cscan < total_clook)
        printf("➡️  C-SCAN performed better (less head movement).\n");
    else if (total_clook < total_cscan)
        printf("➡️  C-LOOK performed better (less head movement).\n");
    else
        printf("➡️  Both performed equally.\n");

    return 0;
}