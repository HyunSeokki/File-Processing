// delim.h
#ifndef DELIM_H
#define DELIM_H

#include <iostream>
#include "varlen.h"

class DelimFieldBuffer: public VariableLengthBuffer
// a buffer which holds delimited text fields.
// Record variables can be packed into and extracted from a buffer.
// Input and Output of packed buffers 
// 
// To use this class, create a DelimFieldBuffer variable and associate definitions with the fields.
// operations are provided to allow values to be associated with the fields (Pack)
//	and to fetch the values of fields (Unpack)
{  public:
	DelimFieldBuffer (char Delim, int maxBytes); // construct with a maximum of maxBytes
		// construct with fields with delimeters
	DelimFieldBuffer (const DelimFieldBuffer & buffer); // copy constructor

	void Clear (); // clear fields from buffer
	int Pack (const void*, int size); // set the value of the next field of the buffer;
	int Unpack (void * field, int maxBytes); // extract the value of the next field of the buffer
	int ReadHeader (istream & stream);
	int WriteHeader (ostream & stream) const;
	void Print (ostream &) const;
 	int Init (char delim);
	static void SetDefaultDelim (char delim);
 protected:
	char Delim;
	static char DefaultDelim;
};


inline DelimFieldBuffer :: DelimFieldBuffer 
	(const DelimFieldBuffer & buffer) // copy constructor
		: VariableLengthBuffer (buffer)
{
	Init (buffer . Delim);
}


#endif

