#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
using namespace std;

ifstream f_in("teste.txt");

//AFLAM MAXIMUL
int maxim(int v[], int n)       //aflam maximul din vector
{
    int max;
    max=v[1];
    for(int i=2; i<=n; i++)
       if(v[i]>max)
         max=v[i];
    return max;

}

//COUNTINGSORT
void countingsort (int* v, int n)
{
    int max = maxim (v,n);
    int fr[max+1]={0};
    int i, j,nr=0;

    for (i=1; i<=n; i++)     //pentru fiecare element
        fr[v[i]]++;          //crestem frecventa (numarul de aparitii)

    for( i=0; i<=max; i++)  // luam fiecare numaral pana la maximul
    {
      if(fr[i]!= 0)
        for( j=1;j<=fr[i]; j++)          //daca frecventa lui nu e 0, il punem in vetor de cate ori apare
           v[++nr]= i;

    }

}

//RADIX
void countsort(int v[], int n, int p)
{
    int aux[n];                  //vectorul auxiliar in care stocam
    int i, fr[10] = { 0 };

    for (i = 0; i < n; i++)                 // aflam numarul de aparitii
        fr[(v[i] / p) % 10]++;

    for (i = 1; i < 10; i++)          // adaugam la frecventa ca sa contina pozitia cifrei din aux
        fr[i] =fr[i] + fr[i - 1];

    for (i = n-1 ; i >= 0; i--)                   //adaugam in vectorul auxiliar
    {
        aux[fr[(v[i] / p) % 10] - 1] = v[i];
        fr[(v[i] / p) % 10]--;
    }

    for (i = 0; i < n; i++)                     // compiem in vectorul initial vectorul sortat(aux)
        v[i] = aux[i];
}

void radixsort(int v[], int n)
{
    int max = maxim(v, n);                         //aflam maximul

    for (int p = 1; max / p > 0; p =p* 10)               //facem sortarea pentru fiecare cifra din numere si crestem p=ul
        countsort(v, n, p);
}

//BUBBLE SORT
void bubblesort(int* v, int primul, int ultimul)
{
    int aux, ok, i;
    ok = 0;                   //ok va fi factorul de decizie
    while (ok == 0)
    {
        ok = 1;                //ok=1 ca sa ne oprim in cazul in care elem sunt ordonate
        for (i = primul; i < ultimul; i++)
            if (v[i] > v[i + 1])    // verific daca cate doua elm alaturate sunt ordonate
            {
                aux = v[i];      // daca nu sunt, le interschimbam
                v[i] = v[i + 1];
                v[i + 1] = aux;
                ok = 0;           // ok=0 ptc am modificat vectorul, deci trb iar parcurs
            }
    }
}


//MERGE SORT
void merge(int *v, int primul, int ultimul, int mijloc)                 // facem INTERCLASAREA intre cele doua jumatati ale vectorului
{
    int i, j, nr, c[ultimul+1];
    i = primul;
    nr = primul;                                                    // cu i parcurgem prima jumatate pana la mijloc
    j = mijloc + 1;                                                // prin j parcurgem a doua jumatate pana la final
    while (i <= mijloc && j <= ultimul)
    {
        if (v[i] < v[j])                                         //punem elementul mai mic intr-un nou vector
        {
            c[nr] = v[i];
            nr++;
            i++;                                                // crestem index ul jumatatii din care am stocat elemtul
        }
        else
        {
            c[nr] = v[j];
            nr++;
            j++;
        }
    }
    while (i <= mijloc)                                    //in cazul in care o jumatate a fost parcursa integral se iese din WHILE
    {                                                      // dar cealalta jumatate mai poate avea elemente de parcurs
        c[nr] = v[i];
        nr++;                                 // verificam fiecare jumatate si adaugam ce a ramas
        i++;
    }
    while (j <= ultimul)
    {
        c[nr] = v[j];
        nr++;
        j++;
    }
    for (i =primul; i <nr; i++)                          // vectorul initial se transforma in vectorul sortat
     v[i] = c[i];

}
void mergesort(int* v, int primul, int ultimul)              //MERGESORT
{
    if (primul < ultimul)
    {
        int mijloc;
        mijloc = (primul+ultimul)/2;                     // hotaram care e mijlocul si impartim vectorul in doua
        mergesort(v, primul, mijloc);                  // sortam recursiv pentru cele doua jumatati
        mergesort(v, mijloc+1, ultimul);
        merge(v,primul,ultimul,mijloc);               // interclasej jumatatile vectorului
    }
}




int aranjare(int* v, int primul, int ultimul)             // aranjam numerele mai mici decat pivotul in stanga si cele mai mari in dreapta
{


    int pivot = v[ultimul];                            //alegem PIVOTUL, care e pe ultima pozitie
    int p_index = primul - 1;
    int i, aux;
    for (i = primul; i < ultimul; i++)
        if (v[i] < pivot)                            //daca elemtul e mai mic il punem in partea stanga
        {
            p_index++;                                      // schimbandu-l cu primul element mai mare decat pivotul
            aux = v[i];
            v[i] = v[p_index];
            v[p_index] = aux;
                                    //pozitia primului element mai mare decat pivotul
        }
    aux = v[ultimul];                             // mut pivotul pe pozitia primului element mai mare decat element
    v[ultimul] = v[p_index+1];                     // acum avem pivotul in mijloc (stanga tot ce e mai mic si dreapta tot ce e mai mare)
    v[p_index+1] = aux;
    return p_index + 1;
}

void quicksort(int* v, int primul, int ultimul)                //PARTEA RECURSIVA
{
    if (primul < ultimul)                  //merge pana cand se ajunge la un singur element
    {
        int p_index = aranjare(v, primul, ultimul);     // indexul= poziatia pe care se afla pivotul curent
        quicksort(v, primul, p_index - 1);                  // facem recursiv pentru cele doua segmente determinate de pivot
        quicksort(v, p_index + 1, ultimul);
    }
}


void copiere(int* vector, int* v, int n)
{
    for (int i = 1; i <= n; i++)
        v[i] = vector[i];
}

int main()
{
    int n,maxi;
    int nr_teste;
    f_in>>nr_teste;
    for(int test = 1; test <= nr_teste; test++)
        {f_in>>n>>maxi;

    cout << "Sortarea a " << n << " numere cu valori mai mici de " << maxi << '\n';

    srand (time(NULL));                                // initializare random
    int *vector { new int[n+1]{}};                      // alocare memorie vector
    for (int i = 1; i <= n; i++)
    {
        vector[i] = rand() % maxi + 1;               // atribuire valori vector
    }
    int *v { new int[n+1]{}};
    copiere( vector,  v,  n);
    clock_t start_time = clock();
    sort(v+1, v+n+1);
    clock_t end_time = clock();
    double time_passed = (double) (end_time-start_time) / CLOCKS_PER_SEC;
    cout << "C Sort: " << time_passed << " seconds." << endl;

    copiere( vector,  v,  n);
    start_time = clock();
    quicksort(v, 1, n);
    end_time = clock();
    time_passed = (double) (end_time-start_time) / CLOCKS_PER_SEC;
    cout << "Quicksort: " << time_passed << " seconds." << endl;


    copiere( vector,  v,  n);
    start_time = clock();
    mergesort(v+1, 0, n-1);
    end_time = clock();
    time_passed = (double) (end_time-start_time) / CLOCKS_PER_SEC;
    cout << "Mergesort: " << time_passed << " seconds." << endl;


    copiere( vector,  v,  n);
    start_time = clock();
    bubblesort(v, 1, n);
    end_time = clock();
    time_passed = (double) (end_time-start_time) / CLOCKS_PER_SEC;
    cout << "Bubblesort: " << time_passed << " seconds." << endl;



    copiere( vector,  v,  n);
    start_time = clock();
    radixsort(v+1, n);
    end_time = clock();
    time_passed = (double) (end_time-start_time) / CLOCKS_PER_SEC;
    cout << "Radixsort: " << time_passed << " seconds." << endl;

    copiere( vector,  v,  n);
    start_time = clock();
    countingsort(v, n);
    end_time = clock();
    time_passed = (double) (end_time-start_time) / CLOCKS_PER_SEC;
    cout << "Countingsort: " << time_passed << " seconds." << endl;

    delete[] vector; // dezalocare memorie
    delete[] v;
        cout <<endl<<endl;
        }
    return 0;
}

