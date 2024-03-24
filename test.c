#include <stdio.h>
#include "bit_array.h"
#include "bit_iterator.h"

int main( void ) {
	const int data1[] = { 1, 0, 1, 0, 0, 0, 1 };
	const int data2[] = { 0, 1, 0, 0, 1, 1, 1 };
	
	bit_array_st *massive_1 = create_bit_array( 1 );

	if( massive_1 == NULL ) {
		printf( "Cannot create bit array N1!\n" );
		return 0;
	}


	bit_array_st *massive_2 = create_bit_array( 1 );

	if( massive_2 == NULL ) {
		printf( "Cannot create bit array N2!\n" );

		destroy_bit_array ( massive_1 );
		return 0;
	}

	for( int i = -1; i < 6; ++i ) 
		push_back( massive_1, i, data1[i + 1] );

	for( int i = -1; i < 6; ++i ) 
		push_back( massive_2, i, data2[i + 1] );

	printf( "Massive N1: \n" );
	print_array ( massive_1 );

	printf( "Massive N2: \n" );
	print_array ( massive_2 );


	bit_iterator_st *iter_1 = create_iter( massive_1, 2 );
	bit_iterator_st *iter_2 = create_iter( massive_2, 5 );
	if( iter_1 == NULL || iter_2 == NULL ) {
		printf( "Cannot create iterators!\n" );
		
		destroy_bit_array ( massive_1 );
		destroy_bit_array ( massive_2 );

		return 0;
		
	}

	printf( "Iter_1: bit = %d, place = %d; iter_2: bit = %d, place = %d.\n", iter_1->bit, iter_1->bit_place, iter_2->bit, iter_2->bit_place );

	{
		printf( "--------------------------------------------\n" );
		replace_iter ( iter_1, 4 );
		replace_iter ( iter_2, -6 );
		printf( "Iter_1: bit = %d, place = %d (replaced to 4); iter_2: bit = %d, place = %d (replaced to -6).\n", iter_1->bit, iter_1->bit_place, iter_2->bit, iter_2->bit_place );
	}

	
	{
		printf( "--------------------------------------------\n" );
		add_back_iter ( iter_1, 1 );
		add_front_iter ( iter_2, 1 );
		
		printf( "Iter_1: bit = %d, place = %d; iter_2: bit = %d, place = %d.\n", iter_1->bit, iter_1->bit_place, iter_2->bit, iter_2->bit_place );
		printf( "Massive N1 (add 1 after iter_1): \n" );
		print_array ( massive_1 );

		printf( "Massive N2 (add 1 before iter_2): \n" );
		print_array ( massive_2 );
	}

	{
		printf( "--------------------------------------------\n" );
		delete_bit_iter ( iter_1 );
		delete_bit_iter ( iter_2 );
		
		printf( "Iter_1: bit = %d, place = %d (bit on place 4 was deleted); iter_2: bit = %d, place = %d (bit on place 0 was deleted).\n", iter_1->bit, iter_1->bit_place, iter_2->bit, iter_2->bit_place );
		
		printf( "Massive N1: \n" );
		print_array ( massive_1 );

		printf( "Massive N2: \n" );
		print_array ( massive_2 );
	}

	
	{
		
		printf( "--------------------------------------------\n" );
		change_bit_iter ( iter_1 );
		change_bit_iter ( iter_2 );
		
		printf( "Iter_1: bit = %d, place = %d (bit was changed); iter_2: bit = %d, place = %d (bit was changed).\n", iter_1->bit, iter_1->bit_place, iter_2->bit, iter_2->bit_place );
		
		printf( "Massive N1: \n" );
		print_array ( massive_1 );

		printf( "Massive N2: \n" );
		print_array ( massive_2 );


	}



	printf( "--------------------------------------------\n" );
	destroy_iter ( iter_1 );
	destroy_iter ( iter_2 );
	destroy_bit_array ( massive_1 );
	destroy_bit_array ( massive_2 );

	return 0;
}
