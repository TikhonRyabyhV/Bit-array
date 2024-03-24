#include "bit_array.h"

bit_array_st* create_bit_array( int n ) { /* create struct for bit array with n blocks and 0 used bits*/
	bit_array_st* res = (bit_array_st* ) calloc( 1, sizeof(bit_array_st) );
	if( res == NULL )
		return NULL;

	if( n <= 0 )
		n = 1;

	res->ptr = (data_type *) calloc( n, sizeof(data_type) );
	if( res->ptr == NULL ) {
		res->data_type_num = 0;
		res->bit_num = 0;
		return NULL;
	}

	res->data_type_num = n;
	res->bit_num = 0;

	return res;
       	       
}

void destroy_bit_array ( bit_array_st* src ) { /* destroy struct for bit array */
	void_func_breaker( src )

	if( src->ptr != NULL )
		free(src->ptr);

	free(src);
}

int read_bit ( bit_array_st* src, int bit ) { /* read a bit from src array using masks */
	program_breaker( src )

	//program_breaker( !((src->bit_num - 1) < bit) )

	int res = 0;

	int data_type_place = bit / sizeof(data_type);
	int bit_place = bit % sizeof(data_type);

	res = ( src->ptr[data_type_place] ) & ( 1 << ( 8 * sizeof(data_type) - 1 - bit_place ) );
	res = res >> ( 8 * sizeof(data_type) - 1 - bit_place );

	return res;
}

int write_bit ( bit_array_st* src, int bit, int val ) { /* write 0/1 on place from src array using masks */
	program_breaker( src )

	program_breaker( !((src->bit_num - 1) < bit) )

	int data_type_place = bit / sizeof(data_type);
	int bit_place = bit % sizeof(data_type);

	val = val % 2;
	if( val )
		src->ptr[data_type_place] = ( src->ptr[data_type_place] ) | ( 1 << ( 8 * sizeof(data_type) - 1 - bit_place ) );

else
		src->ptr[data_type_place] = ( src->ptr[data_type_place] ) & ( ~( 1 << ( 8 * sizeof(data_type) - 1 - bit_place ) ) );

	return 0;
}

int push_back ( bit_array_st* src, int bit, int val ) { /* add new bit after current bit */
	program_breaker( src )

	program_breaker( !( (src->bit_num - 1) < bit  ||  bit < -1 ) )

	if( src->bit_num == src->data_type_num * sizeof(data_type) ) { /* will reallocate, if there are no free places */ 
		src->ptr = (data_type *) realloc( src->ptr, src->data_type_num + 2 );

		program_breaker( src->ptr )

		src->data_type_num = src->data_type_num + 2;
	}

	++src->bit_num;
	
	int store = 0, load = val % 2;

	for( int i = bit + 1; i < src->bit_num; ++i ) { /* displace a part of array after new bit */
		store = read_bit ( src, i );
		load = write_bit ( src, i, load );
		
		load = store;
	}

	return 0;
}

int push_front ( bit_array_st* src, int bit, int val ) { /* add new bit before current bit */
	program_breaker( src )

	/*if( bit <= 0 ||  bit > (src->bit_num - 1) );
		return -2;*/

	if( src->bit_num == src->data_type_num * sizeof(data_type) ) { /* reallocation */
		src->ptr = (data_type *) realloc( src->ptr, src->data_type_num + 2 );

		program_breaker( src->ptr )

		src->data_type_num = src->data_type_num + 2;
	}

	++src->bit_num;
	
	int store = 0, load = val % 2;

	for( int i = bit; i < src->bit_num; ++i ) { /* same displacing */
		store = read_bit ( src, i );
		load = write_bit ( src, i, load );
		
		load = store;
	}

	return 0;
}

int delete_bit ( bit_array_st* src, int bit ) { /* will delete current bit, if it exists */ 
	program_breaker( src )

	program_breaker( !( (src->bit_num - 1) < bit  ||  bit < 0 ) )

	--src->bit_num;
	
	int store = 0, load = 0;

	for( int i = bit + 1; i <= src->bit_num; ++i ) { /* displacing of other part of array */
		store = read_bit ( src, i );
		load = write_bit ( src, i - 1, store );
	}

	return 0;
}

void print_array ( bit_array_st *src ) { /* just print all used bits of src array */
	void_func_breaker( src )

	for( int i = 0; i < src->bit_num; ++i )
		printf( "%d ", read_bit ( src, i ) );

	printf( "\n" );

	return;
}

