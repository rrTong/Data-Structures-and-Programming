        #ifndef _QUADRATIC_PROBING_H_
        #define _QUADRATIC_PROBING_H_
 
        #include "vector.h"
        #include "mystring.h"
 
        // QuadraticProbing Hash table class
        //
        // CONSTRUCTION: an initialization for ITEM_NOT_FOUND
        //               and an approximate initial size or default of 101
        //
        // ******************PUBLIC OPERATIONS*********************
        // void insert( x )       --> Insert x
        // void remove( x )       --> Remove x
        // Hashable find( x )     --> Return item that matches x
        // void makeEmpty( )      --> Remove all items
        // int hash( String str, int tableSize )
        //                        --> Static method to hash strings
        class Char20
        {


        public:
            char char20[20];
            char *Word()
            {
                return char20;
            }
        };

        template <class HashedObj>
        class QuadraticHashTable
        {
          public:
            explicit QuadraticHashTable( const HashedObj & notFound, int size = 101 );
            QuadraticHashTable( const QuadraticHashTable & rhs )
              : ITEM_NOT_FOUND( rhs.ITEM_NOT_FOUND ),
                array( rhs.array ), currentSize( rhs.currentSize ) { }
 
            ~QuadraticHashTable();
 
            const HashedObj & find( const HashedObj & x ) const;
 
            void makeEmpty( );
            void insert( const HashedObj & x );
 
            enum EntryType { ACTIVE, EMPTY, DELETED };
            Char20 Word20[100000];
          private:
            struct HashEntry
            {
                HashedObj element;
                EntryType info;
 
                HashEntry( const HashedObj & e = HashedObj( ), EntryType i = EMPTY )
                  : element( e ), info( i ) { }
            };
 
            int newSize;
            vector<HashEntry> array;
            int currentSize;
            const HashedObj ITEM_NOT_FOUND;
            bool isPrime( int n ) const;
            int nextPrime( int n ) const;
            bool isActive( int currentPos ) const;
            int findPos( const HashedObj & x ) const;
            int hash( const char* key, int tableSize ) const;
        };
 
        #include "QuadraticProbing.cpp"
        #endif
 
