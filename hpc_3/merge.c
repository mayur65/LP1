#include <stdio.h>
#include <stdlib.h>

#include "omp.h"

void mergesort(int a[],int i,int j);
void merge(int a[],int i1,int j1,int i2,int j2);

int main()
{
    int *a, num, i;
   
     FILE *myFile;
    myFile = fopen("mergenumbers.txt", "r");
    
     fscanf(myFile, "%d", &num);

   a = (int *)malloc(sizeof(int) * num);
   
    for (i=0;i<num;i++)
    {
        fscanf(myFile,"%d",&a[i]);
    }
        
    mergesort(a, 0, num-1);
    
    printf("\nSorted array :\n");
    for(i=0;i<num;i++)
        printf("%d ",a[i]);
        
    return 0;
}
 
void mergesort(int a[],int i,int j)
{
    int mid;
        
    if(i<j)
    {
        mid=(i+j)/2;
        
        #pragma omp parallel sections 
        {

            #pragma omp section
            {
                mergesort(a,i,mid);       
            }

            #pragma omp section
            {
                mergesort(a,mid+1,j);    
            }
        }

        merge(a,i,mid,mid+1,j);   
    }
}
 
void merge(int a[],int i1,int j1,int i2,int j2)
{
    int temp[1000];    
    int i,j,k;
    i=i1;   
    j=i2;    
    k=0;
    
    while(i<=j1 && j<=j2)    
    {
        if(a[i]<a[j])
            temp[k++]=a[i++];
        else
            temp[k++]=a[j++];
    }
    
    while(i<=j1)    
        temp[k++]=a[i++];
        
    while(j<=j2)   
        temp[k++]=a[j++];
        
   
    for(i=i1,j=0;i<=j2;i++,j++)
        a[i]=temp[j];
}
