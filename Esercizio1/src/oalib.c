#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include "../inc/oalib.h"

#define TRUE 1
#define FALSE 0

#define ARRAY_CAPACITY 20000000
#define max 20000000
#define lol 10


//// Da vedere
struct _OrderedArray {
    void **array;
    int capacity;
    int size;
};

OrderedArray *new_ordered_array(int capacity) {
    OrderedArray *oa = (OrderedArray *) malloc(sizeof(OrderedArray));
    oa->array = (void **) malloc(sizeof(void *) * capacity);
    oa->capacity = capacity;
    oa->size = 0;
    return oa;
}

void free_ordered_array (OrderedArray *oa) {
    for (int i = 0; i < get_size(oa) - 1; i++) {
        free(oa->array[i]);
    }
    free(oa);
}

void resize_ordered_array(OrderedArray *oa) {
    oa->capacity = oa->capacity * 2;
    oa->array = (void **) realloc(oa->array, sizeof(void *) * oa->capacity);
}

int get_size(OrderedArray *oa) {
    return oa->size;
}

int get_capacity(OrderedArray *oa) {
    return oa->capacity;
}

void *get_obj(OrderedArray *oa, int i) {
    if (i > oa->size - 1 || i < 0) {
        return NULL;
    }
    return oa->array[i];
}

void remove_obj(OrderedArray *oa, int pos) {
    if ((pos >= 0) && (pos > oa->size) - 1) {
        for (int i = pos; i < oa->size - 1; i++) {
            oa->array[i] = oa->array[i + 1];
        }
        oa->size--;
    }
}

void insert_obj(OrderedArray *oa, void *obj) {
    if (oa->size == oa->capacity) {
        resize_ordered_array(oa);
    }
    oa->array[oa->size] = obj;
    oa->size++;
}

int is_ordered(OrderedArray *oa, compare_fun cmp) {
    for (int i = 0; i < oa->size - 1; i++) {
        if (cmp(oa->array[i], oa->array[i + 1]) > 0) {
            return FALSE;
        }
    }
    return TRUE;
}

/*int compare(OrderedArray *a,OrderedArray *b) {
  printf("Sono a %d - Sono b %d\n",*a,*b);
    return 
}*/

  void merge(OrderedArray *oa, int p, int q, int r,compare_fun cmp) {
  OrderedArray *b = new_ordered_array(max);
  int i, j, k=0;
  i = p;
  j = q+1;
  int x;
  

  while (i<=q && j<=r) {
    if (cmp(oa->array[i],oa->array[j])<0)  
    {
      b->array[k] = oa->array[i];
      i++;
    } else {
      b->array[k] = oa->array[j];
      j++;
    }
    k++;
  }
  while (i <= q) {
    b->array[k] = oa->array[i];
    i++;
    k++;
  }
  while (j <= r) {
    b->array[k] = oa->array[j];
    j++;
    k++;
  }
  for (k=p; k<=r; k++)
    oa->array[k] = b->array[k-p];
  return;
}   



/*int binarySearch(OrderedArray *oa, int item, int low, int high)
{
    if (high <= low)
        return (item > oa->array[low]) ?
                (low + 1) : low;
 
    int mid = (low + high) / 2;
 
    if (item == oa->array[mid])
        return mid + 1;
 
    if (item > oa->array[mid])
        return binarySearch(oa, item,
                            mid + 1, high);
    return binarySearch(oa, item, low,
                        mid - 1);
}
 
// Function to sort an array a[] of size 'n'
void insertionSort(OrderedArray *oa, int n)
{
    int i, loc, j, k, elemento;
    void *selected;
 
    for (i = 1; i < n; ++i)
    {
        j = i - 1;
        selected = oa->array[i];
 
        // find location where selected sould be inseretd
        loc = binarySearch(oa, selected, 0, j);
 
        // Move all elements after location to create space
        while (j >= loc)
        {
            oa->array[j + 1] = oa->array[j];
            j--;
        }
        oa->array[j + 1] = selected;
    }
}*/


void mergeSort(OrderedArray *oa, int p, int r,compare_fun cmp) {
    int q; 
  /*if(r<lol){
      //insertionSort(oa, r+1);
   

  }
  else{*/
  if (p < r) {
    q = (p+r)/2;
    mergeSort(oa, p, q,cmp);
    mergeSort(oa, q+1, r,cmp);
    merge(oa, p, q, r,cmp);
  }
  return;
} 




/*int main()
{
    int a[]= { 1,2,3,5,6,7,8,6,4,2,1,4,6,7,7,77,8,8,5,44};
    int n = sizeof(a) / sizeof(a[0]);
    int k=0;
    OrderedArray *oa = new_ordered_array(ARRAY_CAPACITY);
    load_data_into_array(oa,a,n);
    void* cmp;
    mergeSort(oa,0,n-1,cmp);
    int *rec;
    int x;
    for(int i =0; i<n; i++) { 
        //OrderedArray *rec = get_obj(orderedArray, i);
        rec=oa->array[i];
        x=*rec;
        printf("%d",x);
    }
    //printArray(oa,n);
    //mergeSort(a, 0, n-1);
 

}*/


  


