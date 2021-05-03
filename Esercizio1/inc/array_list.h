#pragma once


#define CATCH_ERROR     if(errno) { dprintf(STDERR_FILENO, \
                        "Error PID %d, file %s at line %d: errno %d (%s)\n", \
                        getpid(), __FILE__, __LINE__, errno, strerror(errno));}

/**
 * Define struct ArrayList that contain info about array
 */
typedef struct _ArrayList ArrayList;

/**
 * Define function pointer with generic parameters used for sort
 * @return less than zero if (void* < void*)
 *         equal to zero if (void* == void*)
 *         more than zero if (void* > void*)
 */
typedef int (*compare_fun)(void *, void *);

/**
 * Create new ArrayList whit default parameters
 * @return [ArrayList*] ArrayList struct pointer
 */
ArrayList *new_array_list(int);

/**
 * Frees the memory allocated by new_array_list().
 */
void free_array_list(ArrayList *);

/**
 * Insert generic object into array
 */
void add_element(ArrayList *, void *);

/**
 * Get the obj in position i
 * @return [void*] Generic obj pointer
 */
void *get_obj(ArrayList *, int);

/**
 * Remove obj in position i
 */
void remove_obj(ArrayList *, int);

/**
 * Get the current numbers of obj into array
 * @return [int] array size
 */
int get_size(ArrayList *);

/**
 * Get the current array capacity
 * @return [int] array capacity
 */
int get_capacity(ArrayList *);

/**
 * Sort the array increasingly
 */
void merge_sort(ArrayList *, compare_fun);
