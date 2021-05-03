#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "../inc/array_list.h"

#define ARRAY_CAPACITY 20000000

struct _ArrayList {
    void **array;
    int capacity;
    int size;
};

/* Creates a new ArrayList with the given initial capacity */
ArrayList *new_array_list(int capacity) {
    ArrayList *al = (ArrayList *) malloc(sizeof(ArrayList));
    al->array = (void **) malloc(sizeof(void *) * capacity);
    al->capacity = capacity;
    al->size = 0;
    return al;
}

/* Free up the resources */
void free_array_list (ArrayList *al) {
    for (int i = 0; i < get_size(al) - 1; i++) {
        free(al->array[i]);
    }
    free(al);
}

void resize_array_list(ArrayList *al) {
    al->capacity = al->capacity * 2;
    al->array = (void **) realloc(al->array, sizeof(void *) * al->capacity);
}

int get_size(ArrayList *al) {
    return al->size;
}

int get_capacity(ArrayList *al) {
    return al->capacity;
}

void *get_obj(ArrayList *al, int i) {
    if (i > al->size - 1 || i < 0) {
        return NULL;
    }
    return al->array[i];
}

void remove_obj(ArrayList *al, int pos) {
    if ((pos >= 0) && (pos > al->size) - 1) {
        for (int i = pos; i < al->size - 1; i++) {
            al->array[i] = al->array[i + 1];
        }
        al->size--;
    }
}

void add_element(ArrayList *al, void *obj) {
    if (al->size == al->capacity) {
        resize_array_list(al);
    }
    al->array[al->size] = obj;
    al->size++;
}

int is_ordered(ArrayList *al, compare_fun cmp) {
    for (int i = 0; i < al->size - 1; i++) {
        if (cmp(al->array[i], al->array[i + 1]) > 0) {
            return 0;
        }
    }
    return 1;
}

/* void merge(ArrayList *al, int p, int q, int r, compare_fun cmp) { */
/*     ArrayList *b = new_array_list(1); // Concettualmente non e' necessario un nuovo arraylist */
/*     int i, j, k=0; */
/*     i = p; */
/*     j = q+1; */
/*     int x; */

/*     while (i<=q && j<=r) { */
/*         if (cmp(al->array[i], al->array[j]) < 0) */
/*         { */
/*             b->array[k] = al->array[i]; */
/*             i++; */
/*         } else { */
/*             b->array[k] = al->array[j]; */
/*             j++; */
/*         } */
/*         k++; */
/*     } */
/*     while (i <= q) { */
/*         b->array[k] = al->array[i]; */
/*         i++; */
/*         k++; */
/*     } */
/*     while (j <= r) { */
/*         b->array[k] = al->array[j]; */
/*         j++; */
/*         k++; */
/*     } */
/*     for (k=p; k<=r; k++) */
/*         al->array[k] = b->array[k-p]; */

/*     return; */
/* } */

void merge(ArrayList *al, int l, int m, int u, compare_fun cmp) {
    // create a temp array
    void* temp[u - l + 1];

    // crawlers for both intervals and for temp
    int i = l, j = m+1, k = 0;

    // traverse both arrays and in each iteration add smaller of both elements in temp
    while(i <= m && j <= u) {
        if(cmp(al->array[i], al->array[j])) {
            temp[k] = al->array[i];
            k += 1; i += 1;
        }
        else {
            temp[k] = al->array[j];
            k += 1; j += 1;
        }
    }

    // add elements left in the first interval
    while(i <= m) {
        temp[k] = al->array[i];
        k += 1; i += 1;
    }

    // add elements left in the second interval
    while(j <= u) {
        temp[k] = al->array[j];
        k += 1; j += 1;
    }

    // copy temp to original interval
    for(i = l; i <= u; i += 1) {
        al->array[i] = temp[i - l];
    }
}

/*int binarySearch(ArrayList *al, int item, int low, int high)
{
    if (high <= low)
        return (item > al->array[low]) ?
                (low + 1) : low;

    int mid = (low + high) / 2;

    if (item == al->array[mid])
        return mid + 1;

    if (item > al->array[mid])
        return binarySearch(al, item,
                            mid + 1, high);
    return binarySearch(al, item, low,
                        mid - 1);
}

// Function to sort an array a[] of size 'n'
void insertionSort(ArrayList *al, int n)
{
    int i, loc, j, k, elemento;
    void *selected;

    for (i = 1; i < n; ++i)
    {
        j = i - 1;
        selected = al->array[i];

        // find location where selected sould be inseretd
        loc = binarySearch(al, selected, 0, j);

        // Move all elements after location to create space
        while (j >= loc)
        {
            al->array[j + 1] = al->array[j];
            j--;
        }
        al->array[j + 1] = selected;
    }
}*/

/* NOTA: Qui ve l'ho riscritta in snake case, prima era in camel case (snake
 * case e molto standard in linguaggi come C e C++)*/
void merge_sort_rec(ArrayList *al, int l, int u, compare_fun cmp) {
    int m; // l=lowerbound, u=upperbound, m=midpoint
    if (l < u) {
        m = (l+u)/2;
        merge_sort_rec(al, l, m, cmp);
        merge_sort_rec(al, m+1, u, cmp);
        merge(al, l, m, u, cmp);
    }
}

/* NOTA: La vostra API deve avere dei metodi e delle funzioni che nascondano il */
/* piu' possibile i dettagli implementativi della struttura dati. Una signature */
/* come quella di merge_sort_rec non va bene perche' il programmatore deve */
/* conoscere tali dettagli. L'idea e' quella di utilizzare un metodo wrapper. */
/* Guarda https://en.wikipedia.org/wiki/Recursion_(computer_science)#Wrapper_function */
/* per capirne di piu'. */
void merge_sort(ArrayList *al, compare_fun cmp) {
    merge_sort_rec(al, 0, al->size, cmp);
}


/*int main()
{
    int a[]= { 1,2,3,5,6,7,8,6,4,2,1,4,6,7,7,77,8,8,5,44};
    int n = sizeof(a) / sizeof(a[0]);
    int k=0;
    ArrayList *al = new_array_list(ARRAY_CAPACITY);
    lald_data_into_array(al,a,n);
    void* cmp;
    mergeSort(al,0,n-1,cmp);
    int *rec;
    int x;
    for(int i =0; i<n; i++) {
        //ArrayList *rec = get_obj(al, i);
        rec=al->array[i];
        x=*rec;
        printf("%d",x);
    }
    //printArray(al,n);
    //mergeSort(a, 0, n-1):
}*/
