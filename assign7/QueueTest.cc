/* Copyright (c) 1998 by The National Chengchi Univ. All Rights Reserved */

/***************************************************************************
   NAME
     QueueTest.cc
   PURPOSE
     
   NOTES
     
   AUTHOR
     Tsai-Yen Li (li@cs.nccu.edu.tw)
   HISTORY
     Tsai-Yen Li - Dec 11, 1998: Created.
***************************************************************************/

/* $Log:$ */

extern "C" {
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
}

#include <iostream>
#include <fstream>
#include "AnsiPrint.h"

using namespace std;

/**
 * Print my id 
 */

void
PrintMyID(const char *studId) {

  char *str= new char[strlen(studId)+5];
  sprintf(str,"ID: %s",studId);
  AnsiPrint(str, yellow, red, true, true);
  cout << endl ;
  delete [] str;

}

/**
 * PrintUsage
 */

void
PrintUsage(const char *progName) {

    assert(progName);
    cout << "Usage: " << progName << " [passes [display [seed]]]" << endl;

}

int
main(int argc, char **argv) {

	istream *is1=&cin, *is2=&cin;

	if (argc>3) {
		PrintUsage(argv[0]);
		exit(-1);
	} else if (argc>2) {
		is2 = new ifstream(argv[2]);
		if (is2==NULL) {
			cerr << "Can't open file " << argv[2] << endl;
			exit(1);
		}
	} 
	if (argc>1) {
		is1 = new ifstream(argv[1]);
		if (is1==NULL) {
			cerr << "Can't open file " << argv[1] << endl;
			exit(2);
		}
	}


	// You need to provide testing exercises here
	
	/*............Int_Queue...........*/
	AnsiPrint("Integer Queue:\n", yellow, black);
	cout << endl;

    // test integer queue
	Queue<int> *myIntQPtr = new Queue<int>; 

	// enqueue exercises on myIntQPtr
	int buffer;
	while((*is1) >> buffer){
		myIntQPtr->enqueue(buffer);
	}

	// test copy constructor
	// 複製給 myIntQ
	Queue<int> myIntQ = *myIntQPtr;
	
	// destructor
	delete myIntQPtr;

	// dequeue if queue isn't empty	
	while(!myIntQ.isEmpty()){
		cout << myIntQ.dequeue() << endl;
	}

	/*............Char_Queue...........*/
	AnsiPrint("Character Queue:\n", yellow, black);
	cout << endl;
	
	// test char queue
	Queue <char> myCharQ, myCharQ1;
	
	// enqueue exercises on myCharQ
	char charBuffer;
	while((*is2) >> charBuffer){
		mycharQ.enqueue(charBuffer);
	}	
	// test assignment operator
	myCharQ1 = myCharQ;

	// dequeue exercise on charqueue
	while(!myCharQ1.isEmpty()){
		cout << myCharQ1.dequeue() << endl;
	}
	
	// dequeue an empyty queue is one kind of exception
	try {
		myCharQ1.dequeue();
	} catch(Except e) {
		AnsiPrint((const char*)e, black, yellow);
		cout << endl;
	}
	PrintMyID("110703066");
	return 0;
    
}
