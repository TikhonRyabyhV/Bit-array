#include <stdlib.h>
#include "breakers.h"
#pragma once

typedef unsigned char data_type; /* type of blocks which are used in array */

typedef struct bit_array {
	data_type *ptr; /* array pointer */
	int data_type_num; /* number of blocks in this array */
	int bit_num; /* number of bits, which are used in this array */
} bit_array_st;


bit_array_st* create_bit_array( int n );  /* create struct for bit array with n blocks and 0 used bits*/


void destroy_bit_array ( bit_array_st* src ); /* destroy struct for bit array */
int read_bit ( bit_array_st* src, int bit ); /* read a bit from src array using masks */

int write_bit ( bit_array_st* src, int bit, int val );  /* write 0/1 on place from src array using masks */

int push_back ( bit_array_st* src, int bit, int val );  /* add new bit after current bit */

int push_front ( bit_array_st* src, int bit, int val );  /* add new bit before current bit */

int delete_bit ( bit_array_st* src, int bit );  /* will delete current bit, if it exists */ 

void print_array ( bit_array_st *src );  /* just print all used bits of src array */
