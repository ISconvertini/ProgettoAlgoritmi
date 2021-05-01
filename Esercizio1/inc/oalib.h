#pragma once


#define CATCH_ERROR     if(errno) { dprintf(STDERR_FILENO, \
                        "Error PID %d, file %s at line %d: errno %d (%s)\n", \
                        getpid(), __FILE__, __LINE__, errno, strerror(errno));}

/**
 * Define struct OrderedArray that contain info about array
 */
typedef struct _OrderedArray OrderedArray;

/**
 * Define function pointer with generic parameters used for sort
 * @return less than zero if (void* < void*)
 *         equal to zero if (void* == void*)
 *         more than zero if (void* > void*)
 */
typedef int (*compare_fun)(void *, void *);

/**
 * Create new OrderedArray whit default parameters
 * @return [OrderedArray*] OrderedArray struct pointer
 */
OrderedArray *new_ordered_array(int);

/**
 * Frees the memory allocated by new_ordered_array().
 */
void free_ordered_array(OrderedArray *);

/**
 * Insert generic object into array
 */
void insert_obj(OrderedArray *, void *);

/**
 * Get the obj in position i
 * @return [void*] Generic obj pointer
 */
void *get_obj(OrderedArray *, int);

/**
 * Remove obj in position i
 */
void remove_obj(OrderedArray *, int);

/**
 * Get the current numbers of obj into array
 * @return [int] array size
 */
int get_size(OrderedArray *);

/**
 * Get the current array capacity
 * @return [int] array capacity
 */
int get_capacity(OrderedArray *);

/**
 * Sort the array increasingly
 */
void mergeSort(OrderedArray *,int,int compare_fun);

/**
 * Sort the array increasingly
 */