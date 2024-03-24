#include "bit_iterator.h"

bit_iterator_st* create_iter ( bit_array_st *src, unsigned int place ) { /* create struct of iterator */
	if( src == NULL )
		return NULL;

	place = place % 2;

	bit_iterator_st *res = (bit_iterator_st *) calloc( 1, sizeof(bit_iterator_st) );
	if( res == NULL )
		return NULL;

	res->data = src;

	if( place ) {
		res->bit_place = src->bit_num - 1;
		res->bit = read_bit ( src, res->bit_place );
	}

	else {
		res->bit_place = 0;
		res->bit = read_bit ( src, 0 );
	}


	return res;
}

void destroy_iter ( bit_iterator_st *src ) { /* remove iterator after using */
	void_func_breaker( src )

	free(src);
}

void replace_iter ( bit_iterator_st *src, int delta ) { /* shift iterator by delta bits (may be delta < 0) */
	void_func_breaker( src )

	void_func_breaker( !(src->bit_place + delta > (src->data->bit_num - 1) || src->bit_place + delta < 0) )
	
	src->bit_place = src->bit_place + delta;
	src->bit = read_bit ( src->data, src->bit_place );

	return;
}

void add_back_iter ( bit_iterator_st *src, unsigned int val ) { /* add new bit after current bit */
	void_func_breaker( src )

	void_func_breaker( !( src->bit_place < -1 || src->bit_place > (src->data->bit_num - 1) ) )

	push_back ( src->data, src->bit_place, val % 2 );

	return;
}


void add_front_iter ( bit_iterator_st *src, unsigned int val ) { /* add new bit before current bit */
	void_func_breaker( src )

	void_func_breaker( !( src->bit_place < 0 || src->bit_place > src->data->bit_num ) )

	push_front ( src->data, src->bit_place, val % 2 );

	replace_iter ( src, 1 );
	return;
}

void change_bit_iter ( bit_iterator_st *src ) { /* change current bit 0->1 or 1->0 */
	void_func_breaker( src )
	
	if( src->bit )
		write_bit( src->data, src->bit_place, 0 );
	else
		write_bit( src->data, src->bit_place, 1 );

	src->bit = read_bit ( src->data, src->bit_place );

	return;

}

void delete_bit_iter ( bit_iterator_st *src ) { /* delete current bit */
	void_func_breaker( src )

	if( src->bit_place == src->data->bit_num - 1 ) {
		delete_bit ( src->data, src->bit_place );
		replace_iter ( src, -1 );
	}

	else {
		delete_bit ( src->data, src->bit_place );
		replace_iter (src, 0 );
	}

	return;
}

