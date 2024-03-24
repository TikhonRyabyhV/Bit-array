#include "bit_array.h"
#include "breakers.h"
#pragma once

typedef struct bit_iterator { /* smart pointer for bit array */
	bit_array_st *data; /* bit array struct pointer */
	unsigned int bit; /* current bit */
	int bit_place; /* current bit place */
} bit_iterator_st;


bit_iterator_st* create_iter ( bit_array_st *src, unsigned int place );  /* create struct of iterator */

void destroy_iter ( bit_iterator_st *src );  /* remove iterator after using */

void replace_iter ( bit_iterator_st *src, int delta );  /* shift iterator by delta bits (may be delta < 0) */

void add_back_iter ( bit_iterator_st *src, unsigned int val );  /* add new bit after current bit */

void add_front_iter ( bit_iterator_st *src, unsigned int val );  /* add new bit before current bit */

void change_bit_iter ( bit_iterator_st *src );  /* change current bit 0->1 or 1->0 */

void delete_bit_iter ( bit_iterator_st *src );  /* delete current bit */
