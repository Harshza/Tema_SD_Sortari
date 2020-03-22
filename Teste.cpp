#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <chrono>
#include <algorithm>
#include <queue>
#include <utility>

using namespace std;
using namespace std::chrono;

ifstream fin("date.in");

bool test(long long v[], long long low, long long high)
{
    for(long long i = low + 1; i <= high; i++)
        if(v[i] < v[i-1])
            return false;
    return true;
}

void bubbleSort(long long v[], long long low, long long high);

void countSort(long long v[], long long low, long long high);

void mergeSort(long long v[], long long low, long long high);

void merge(long long v[], long long low, long long m, long long high);

void quickSort(long long v[], long long low, long long high);

void radixSort(long long v[], long long low, long long high); // baza 2^8

mt19937 eng(time(0));
long long inf[]={0, 0, 700, 20000, 638, 64675, 9683064, 46457};
long long sup[]={10000, 10000, 9359636, 50000, 400000, 58376937536508166, 745684665, 60000};
long long lungime[]={1000, 1000, 100, 2000, 100000, 1000000, 50000, 7893};
int main()
{
    long long *v = new long long[100000002], n;
    for(int teste = 0; teste < 8; teste++)
    {
        cout << "Testul " << teste << ":\n";
        n = lungime[teste];
        uniform_int_distribution<long long unsigned> distr(inf[teste], sup[teste]);
        for(long long i = 0; i < n; i++)
            v[i] = distr(eng);
        n--;
        long long *cop = new long long[100000002];

        for(long long i = 0; i <= n; i++)
            cop[i] = v[i];
        cout << "Pentru Bubblesort:";
        if(n >= 10000)
            cout << "\nDureaza prea mult!\n";
        else
        {
            auto start1 = high_resolution_clock::now();
            bubbleSort(cop, 0, n);
            auto stop1 = high_resolution_clock::now();
            auto duration1 = duration_cast<nanoseconds>(stop1 - start1);
            if(test(cop, 0, n))
                cout << "\nSirul returnat este sortat!\n";
            else
                cout <<"\nSortarea nu a functionat\n";
            cout << "Sortarea a durat: " << double(duration1.count())/1000000000 << " secunde.\n\n";
        }

        for(long long i = 0; i <= n; i++)
            cop[i] = v[i];
        long long maxim = v[0], minim = v[0];
        for(long long i = 0; i <= n; i++)
        {
            cop[i] = v[i];
            if(maxim < v[i])
                maxim = v[i];
            else
                if(minim > v[i])
                    minim = v[i];
        }
        cout << "Pentru Countsort:";
        if(maxim - minim + 1 >= 10000000)
            cout << "\nDureaza prea mult!\n";
        else
        {
            auto start2 = high_resolution_clock::now();
            countSort(cop, 0, n);
            auto stop2 = high_resolution_clock::now();
            auto duration2 = duration_cast<nanoseconds>(stop2 - start2);
            if(test(cop, 0, n))
                cout << "\nSirul returnat este sortat!\n";
            else
                cout <<"\nSortarea nu a functionat\n";
            cout << "Sortarea a durat: " << double(duration2.count())/1000000000 << " secunde.\n\n";
        }

        for(long long i = 0; i <= n; i++)
            cop[i] = v[i];
        cout << "Pentru MergeSort:";
        auto start3 = high_resolution_clock::now();
        mergeSort(cop, 0, n);
        auto stop3 = high_resolution_clock::now();
        auto duration3 = duration_cast<nanoseconds>(stop3 - start3);
        if(test(cop, 0, n))
            cout << "\nSirul returnat este sortat!\n";
        else
            cout <<"\nSortarea nu a functionat\n";
        cout << "Sortarea a durat: " << double(duration3.count())/1000000000 << " secunde.\n\n";

        for(long long i = 0; i <= n; i++)
            cop[i] = v[i];
        cout << "Pentru QuickSort:";
        auto start4 = high_resolution_clock::now();
        quickSort(cop, 0, n);
        auto stop4 = high_resolution_clock::now();
        auto duration4 = duration_cast<nanoseconds>(stop4 - start4);
        if(test(cop, 0, n))
            cout << "\nSirul returnat este sortat!\n";
        else
            cout <<"\nSortarea nu a functionat\n";
        cout << "Sortarea a durat: " << double(duration4.count())/1000000000 << " secunde.\n\n";

        for(long long i = 0; i <= n; i++)
            cop[i] = v[i];
        cout << "Pentru RadixSort:";
        auto start6 = high_resolution_clock::now();
        radixSort(cop, 0, n);
        auto stop6 = high_resolution_clock::now();
        auto duration6 = duration_cast<nanoseconds>(stop6 - start6);
        if(test(cop, 0, n))
            cout << "\nSirul returnat este sortat!\n";
        else
            cout <<"\nSortarea nu a functionat\n";
        cout << "Sortarea a durat: " << double(duration6.count())/1000000000 << " secunde.\n\n";

        for(long long i = 0; i <= n; i++)
            cop[i] = v[i];
        cout << "Pentru STLSort:";
        auto start5 = high_resolution_clock::now();
        sort(cop, cop + n + 1);
        auto stop5 = high_resolution_clock::now();
        auto duration5 = duration_cast<nanoseconds>(stop5 - start5);
        if(test(cop, 0, n))
            cout << "\nSirul returnat este sortat!\n";
        else
            cout <<"\nSortarea nu a functionat\n";
        cout << "Sortarea a durat: " << double(duration5.count())/1000000000 << " secunde.\n\n";
        delete cop;
    } 
    return 0;
}

// Corpul Sortarilor

void merge(long long v[], long long low, long long m, long long high) 
{ 
    long long i, j, k; 
    long long n1 = m - low + 1; 
    long long n2 =  high - m; 
  
    long long *L = new long long[n1], *R = new long long[n2]; 
  
    for (i = 0; i < n1; i++) 
        L[i] = v[low + i]; 
    for (j = 0; j < n2; j++) 
        R[j] = v[m + 1+ j]; 
  
    i = 0;  
    j = 0;  
    k = low;  
    while (i < n1 && j < n2) 
    { 
        if (L[i] <= R[j]) 
        { 
            v[k] = L[i]; 
            i++; 
        } 
        else
        { 
            v[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
  
    while (i < n1) 
    { 
        v[k] = L[i]; 
        i++; 
        k++; 
    } 
  
    while (j < n2) 
    { 
        v[k] = R[j]; 
        j++; 
        k++; 
    } 
}

void mergeSort(long long v[], long long low, long long high) 
{ 
    if (low < high) 
    { 
        long long m = low+(high-low)/2; 
   
        mergeSort(v, low, m); 
        mergeSort(v, m+1, high); 
  
        merge(v, low, m, high); 
    } 
} 

void countSort(long long v[], long long low, long long high)
{
    long long maxi = v[low], mini = v[low];

    for(long long i = low + 1; i <= high; i++)
    {
        if(v[i] > maxi)
            maxi = v[i];
        else
            if(v[i] < mini)
                mini = v[i];
    }

    long long val = maxi - mini + 1;

    long long *frecv = new long long[val];
    for(long long i = 0; i < val; i++)
        frecv[i] = 0;

    for(long long i = low; i <= high; i++)
        frecv[v[i] - mini]++;

    long long k = low;
    for(long long i = 0; i < val; i++)
        for(long long j = 1; j <= frecv[i]; j++)
        {
            v[k] = i + mini;
            k++;
        }
}

void bubbleSort(long long v[], long long low, long long high)
{
    bool schimbat = true;
    while(schimbat)
    {
        schimbat = false;
        for(long long i = low + 1; i <= high; i++)
            if(v[i] < v[i-1])
            {
                swap(v[i],v[i-1]);
                schimbat = true;
            }
    }
}

void quickSort(long long v[], long long low, long long high)
{
    if(low < high)
    {
        long long pivot;
        if(high - low + 1 <= 3)
            pivot = low;
        else
        {
            long long *mediane = new long long[3];
            long long capat = high;
            for(int i = 0; i < 3; i++)
            {
                uniform_int_distribution<long long unsigned> interv(low, capat);
                long long x = interv(eng);
                swap(v[x],v[capat]);
                mediane[i] = v[capat];
                capat--;
            }
            long long mini = 0, maxi = 0;
            for(int i = 1; i < 3; i++)
            {
                if(mediane[i] > mediane[maxi])
                    maxi = i;
                else
                    if(mediane[i] < mediane[mini])
                        mini = i;
            }
            pivot = high - (3 - mini - maxi);
        }
        
        swap(v[pivot],v[high]);
        long long st = low, dr = high-1;
        while(st < dr)
        {
            if(v[st] > v[high] && v[dr] <= v[high])
            {
                swap(v[st],v[dr]);
                st++;
                dr--;
            }
            else
                if(v[st] > v[high])
                    dr--;
            else
                st++;
        }
        if(v[st] >= v[high])
        {
            swap(v[st],v[high]);
            quickSort(v, low, st-1);
            quickSort(v, st+1, high);
        }
        else
        {
            swap(v[st+1],v[high]);
            quickSort(v, low, st);
            quickSort(v, st+2, high);
        }
    }
}

void radixSort(long long v[], long long low, long long high) // baza 2^8
{
    queue<long long> L[256];
    long long maxi = v[low];
    for(long long i = low + 1; i <= high; i++)
        if(v[i] > maxi)
            maxi = v[i];
    long long putere = 0;
    long long STOP = 1 << 56; //nush dc da warning aici,am cautat,long long e pana in 2^63
    if(maxi >= STOP)
        putere = 64;
    else
        while(maxi >= 1 << putere)
            putere += 8;
    for(int k = 0; k < putere; k+=8)
    {
        for(long long i = low; i <= high; i++)
            L[(v[i] >> k) & 255].push(v[i]);
        long long t = low;
        for(int i = 0; i < 256; i++)
            while(!L[i].empty())
            {
                v[t] = L[i].front();
                t++;
                L[i].pop();
            }
    }
}
