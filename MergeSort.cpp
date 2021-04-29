#include <iostream>
#include<cstdlib>
#include<fstream>
#include<ctime>
#define C_P_S ((clock_t)10000)
clock_t t=clock();
using namespace std;
void merge(int *,int, int , int );
void mergesort(int *a, int low, int high)
{
    int mid;
    if (low < high)
    {
        mid=(low+high)/2;
        mergesort(a,low,mid);
        mergesort(a,mid+1,high);
        merge(a,low,high,mid);
    }
    return;
}
void merge(int *a, int low, int high, int mid)
{
    int i, j, k, c[50];
    i = low;
    k = low;
    j = mid + 1;
    while (i <= mid && j <= high)
    {
        if (a[i] < a[j])
        {
            c[k] = a[i];
            k++;
            i++;
        }
        else
        {
            c[k] = a[j];
            k++;
            j++;
        }
    }
    while (i <= mid)
    {
        c[k] = a[i];
        k++;
        i++;
    }
    while (j <= high)
    {
        c[k] = a[j];
        k++;
        j++;
    }
    for (i = low; i < k; i++)
    {
        a[i] = c[i];
    }
}
int main()
{
    int a[20], i;
    for (i = 0; i < 10; i++)
    {
        a[i]=rand();
    }
    cout<<"\nUnsorted array is:";
    for(i=0;i<10;i++)
    {
    	cout<<a[i]<<" ";
    	t=clock();
	}
	ofstream file;
	file.open("merge.txt");
	for(i=0;i<10;i++)
	{
		file<<a[i];
	}
	file.close();
    mergesort(a, 0, 9);
    ifstream fin;
    fin.open("merge.txt");
    while(fin)
    {
    	fin>>a[i];
	}
    cout<<"\nSorted array\n";
    for (i = 0; i < 5; i++)
    {
        cout<<a[i]<<" ";
    }
    cout<<"\nTime taken="<<(double)t/C_P_S;
    return 0;
}


