/*

	For the matrix class, add a resize member function and zero-parameter constructor.

*/

//Answer

#ifndef MATRIX_H
#define MATRIX_H

#include <vector>

using namespace std;

template <typename Object>
class matrix
{
	public:

		matrix( int rows, int cols ) : array( rows ) {
			for( auto & thisRow : array )
				thisRow.resize( cols );
		}

		// Default constructor. Default matrix will be 10 x 10.
		matrix(): matrix(10,10) {} 

		matrix( vector<vector<Object>> v ) : array{ v } { }
		matrix( vector<vector<Object>> && v ) : array{ std::move( v ) } { }

		// resize method.
		void resize( int rows, int cols ){
			array.resize( rows );
			for( auto & thisRow : array )
				thisRow.resize( cols );
		}

		const vector<Object> & operator[]( int row ) const
		{ return array[ row ]; }

		vector<Object> & operator[]( int row )
		{ return array[ row ]; }

		int numrows( ) const
		{ return array.size( ); }

		int numcols( ) const
		{ return numrows( ) ? array[ 0 ].size( ) : 0; }

	private:
		vector<vector<Object>> array;
};
#endif
