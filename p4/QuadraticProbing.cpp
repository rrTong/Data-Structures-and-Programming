        #include "QuadraticProbing.h"
        #include <cstring>
        #include <iostream>
 
        /**
         * Internal method to test if a positive number is prime.
         * Not an efficient algorithm.
         */
        template <class HashedObj>
        bool QuadraticHashTable<HashedObj>::isPrime( int n ) const
        {
            if( n == 2 || n == 3 )
                return true;
 
            if( n == 1 || n % 2 == 0 )
                return false;
 
            for( int i = 3; i * i <= n; i += 2 )
                if( n % i == 0 )
                    return false;
 
            return true;
        }
 
        /**
         * Internal method to return a prime number at least as large as n.
         * Assumes n > 0.
         */
        template <class HashedObj>
        int QuadraticHashTable<HashedObj>::nextPrime( int n ) const
        {
            if( n % 2 == 0 )
                n++;
 
            for( ; !isPrime( n ); n += 2 )
                ;
 
            return n;
        }
 
        /**
         * Construct the hash table.
         */
        template <class HashedObj>
        QuadraticHashTable<HashedObj>::QuadraticHashTable( const HashedObj & notFound, int size )
          : array( nextPrime( size ) ), ITEM_NOT_FOUND( notFound )
        {
            newSize = size;
            currentSize = 0;
            for(int i = 0; i < newSize; i++)
                array[i].info = EMPTY;
        }
 
        /**
         * Destruct the hash table.
         */
        template <class HashedObj>
         QuadraticHashTable<HashedObj>::~QuadraticHashTable()
         {
         }
 
        /**
         * Insert item x into the hash table. If the item is
         * already present, then do nothing.
         */
        template <class HashedObj>
        void QuadraticHashTable<HashedObj>::insert( const HashedObj & x )
        {
                // Insert x as active
            int currentPos = findPos( x );
            if( isActive( currentPos ) )
                return;
            array[ currentPos ] = HashEntry( x, ACTIVE );
        }
  
        /**
         * Method that performs quadratic probing resolution.
         * Return the position where the search for x terminates.
         */
        template <class HashedObj>
        int QuadraticHashTable<HashedObj>::findPos( const HashedObj & x ) const
        {
/* 2*/      int currentPos = hash( x, newSize );
 
/* 3*/      while( array[ currentPos ].info != EMPTY &&
                   strcmp(array[currentPos].element, x) )
            {
/* 4*/          currentPos += 1;  // Compute ith probe
/* 5*/          if( currentPos >= newSize )
/* 6*/              currentPos -= newSize;
            }
 
/* 7*/      return currentPos;
        }
 
        /**
         * Find item x in the hash table.
         * Return the matching item, or ITEM_NOT_FOUND, if not found.
         */
        template <class HashedObj>
        const HashedObj & QuadraticHashTable<HashedObj>::find( const HashedObj & x ) const
        {
            int currentPos = findPos( x );
            return isActive( currentPos ) ? array[ currentPos ].element : ITEM_NOT_FOUND;
        }
 
        /**
         * Make the hash table logically empty.
         */
        template <class HashedObj>
        void QuadraticHashTable<HashedObj>::makeEmpty( )
        {
            currentSize = 0;
            for( int i = 0; i < newSize; i++ )
            {
                array[ i ].info = EMPTY;
            }
        }
 
 
        /**
         * Return true if currentPos exists and is active.
         */
        template <class HashedObj>
        bool QuadraticHashTable<HashedObj>::isActive( int currentPos ) const
        {
            return array[ currentPos ].info == ACTIVE;
        }
 
        /**
         * A hash routine for char* objects.
         */
        template <class HashedObj>
        int QuadraticHashTable<HashedObj>::hash( const char* key, int tableSize ) const
        {
            int hashVal = 0;
            for( int i = 0; i < (int)strlen(key); i++ )
                hashVal = 37 * hashVal + key[ i ];
 
            hashVal %= tableSize;
            if( hashVal < 0 )
                hashVal += tableSize;
 
            return hashVal;
        }
