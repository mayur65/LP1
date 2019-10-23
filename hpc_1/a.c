#include<iostream>
#include<time.h>
#include<omp.h>
#include<vector>
using namespace std;

vector<int> initialize(vector<int>,int);

/*
Reference for learning openmp concepts: https://www.openmp.org/wp-content/uploads/omp-hands-on-SC08.pdf

*/

int main()
{
    int SIZE = 1<<20;
    int arr[SIZE];

    vector<int> v;
    v = initialize(v,SIZE); //Function defined to initialize vectoe with random values
    
    int x = 0;
    vector<int>::iterator ptr;
    //Copy vector to array
    for (ptr = v.begin(); ptr < v.end(); ptr++)
    {
        arr[x]=*ptr;
	//cout<<*ptr<<endl;
        x+=1;
    }

    double start,end;
    start  =omp_get_wtime(); //Record start time

    cout<<"\n=====Reduction operation name = MAX=====\n";
    int max_val = 0;
    int j;
	//Execute below loop parallely using omp compiler direcives
    #pragma omp parallel for reduction(max:max_val)
    for(j=0;j<SIZE;j++)
    {
        if(arr[j]>max_val)
            max_val=arr[j];
    }

    cout<<"\nMAX value from array is = "<<max_val<<endl;


    cout<<"\n=====Reduction operation name = MIN=====\n";
    int min_val = 10000; //MAX VALUE is given as input
    
    #pragma omp parallel for reduction(min:min_val)
    for(j=0;j<SIZE;j++)
    {
        if(arr[j]<min_val)
            min_val=arr[j];
    }

    cout<<"\nMIN value from array is = "<<min_val<<endl;

    cout<<"\n=====Reduction operation name = SUM=====\n";
    int sum = 0;
    #pragma omp  parallel for reduction(+:sum)
    for(int i=0;i<SIZE;i++)
    {
        sum+=arr[i];
    }

    cout<<"\nSUM value from array is = "<<sum<<endl;

    cout<<"\n=====Reduction operation name = AVERAGE=====\n";
     sum = 0;
    #pragma omp  parallel for reduction(+:sum)
    for(int i=0;i<SIZE;i++)
    {
        sum+=arr[i];
    }
    int average = sum/SIZE;

    cout<<"\nAVERAGE value from array is = "<<average<<endl;


    end = omp_get_wtime();

    cout<<"execution time = "<<end-start<<endl;


}

vector<int> initialize(vector<int> v,int n)
{
    srand(time(0));
    for(int i=0;i<n;i++)
        v.push_back(rand()%10000);


    return v;

}
