#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

typedef struct Array {
  int capacity;  // How many elements can this array hold?
  int count;  // How many states does the array currently hold?
  char **elements;  // The string elements contained in the array
} Array;


/************************************
 *
 *   CREATE, DESTROY, RESIZE FUNCTIONS
 *
 ************************************/

/*****
 * Allocate memory for a new array
 *****/
Array *create_array (int capacity) {
  // Allocate memory for the Array struct
  Array *arr = malloc(sizeof(Array));

  // Set initial values for capacity and count
arr->capacity = capacity;
arr->count = 0;
  // Allocate memory for elements
arr->elements = malloc(sizeof(char *) * capacity);

return arr;
}


/*****
 * Free memory for an array and all of its stored elements
 *****/
void destroy_array(Array *arr) {

  // Free all elements
  for(int i = 0; i < arr->capacity; i++)
  {
    free(arr->elements[i]);
  }
  // Free array
  free(arr);
}

/*****
 * Create a new elements array with double capacity and copy elements
 * from old to new
 *****/
void resize_array(Array *arr) {
  int new_cap = arr->capacity * 2;

  // Create a new element storage with double capacity
  char **new_storage = malloc(sizeof(char **) * new_cap);
  // Copy elements into the new storage
  for (int i = 0; i < arr->count; i++)
  {
    new_storage[i] = arr->elements[i];
    free(arr->elements[i]);
  }
  // Free the old elements array (but NOT the strings they point to)

  // Update the elements and capacity to new values
  arr->elements = new_storage;
  arr->capacity = new_cap;
}



/************************************
 *
 *   ARRAY FUNCTIONS
 *
 ************************************/

/*****
 * Return the element in the array at the given index.
 *
 * Throw an error if the index is out of range.
 *****/
int validate_index(Array *arr, int index) {
  if(index >= arr->count || index < 0)
  {
    return -1;
  }
  return index;
}

char *arr_read(Array *arr, int index) {

  index = validate_index(arr,index);

  // Throw an error if the index is greater than the current count
  if(index == -1)
  {
    perror("No element at index");
  }
  else
  {
    return arr->elements[index];
  }
  return NULL;
  // Otherwise, return the element at the given index
}


/*****
 * Insert an element to the array at the given index
 *****/
void arr_insert(Array *arr, char *element, int index) {
  index = validate_index(arr, index);
  // Throw an error if the index is greater than the current count
  if (index == -1)
  {
    perror("Index out of range.");
    return;
  }

  // Resize the array if the number of elements is over capacity
  if(arr->count == arr->capacity)
  {
    resize_array(arr);
  }
  // Move every element after the insert index to the right one position
  for(int i = arr->count ; i > index; i--)
  {
    arr->elements[i] = arr->elements[i-1];
  }
  // Copy the element and add it to the array
  arr->elements[index] = strdup(element);

  // Increment count by 1
  arr->count ++;
}

/*****
 * Append an element to the end of the array
 *****/
void arr_append(Array *arr, char *element) {

  // Resize the array if the number of elements is over capacity
  // or throw an error if resize isn't implemented yet.
  if(arr->count == arr->capacity)
  {
    resize_array(arr);
  }

  // Copy the element and add it to the end of the array
  arr->elements[arr->count] = strdup(element);
  // Increment count by 1
  arr->count++;

}

/*****
 * Remove the first occurence of the given element from the array,
 * then shift every element after that occurence to the left one slot.
 *
 * Throw an error if the value is not found.
 *****/
void arr_remove(Array *arr, char *element) {

  // Search for the first occurence of the element and remove it.
  // Don't forget to free its memory!
  int is_found = 0;
  // Shift over every element after the removed element to the left one position
  for(int i = 0; i < arr->count; i++)
  {
    if(!is_found)
    {
      if(strcmp(element, arr->elements[i]) == 0)
      {
        is_found = 1;
        free(arr->elements[i]);
      }
    }
    if(is_found)
    {
      arr->elements[i] = arr->elements[i + 1];
    }
  }
  // Decrement count by 1
  if (!is_found)
  {
    perror("Element not in array.");
  }
  else
  {
    arr->count--;
  }

}


/*****
 * Utility function to print an array.
 *****/
void arr_print(Array *arr) {
  printf("[");
  for (int i = 0 ; i < arr->count ; i++) {
    printf("%s", arr->elements[i]);
    if (i != arr->count - 1) {
      printf(",");
    }
  }
  printf("]\n");
}


#ifndef TESTING
int main(void)
{

  Array *arr = create_array(1);

  arr_insert(arr, "STRING1", 0);
  arr_append(arr, "STRING4");
  arr_insert(arr, "STRING2", 0);
  arr_insert(arr, "STRING3", 1);
  arr_print(arr);
  arr_remove(arr, "STRING3");
  arr_print(arr);

  destroy_array(arr);

  return 0;
}
#endif
