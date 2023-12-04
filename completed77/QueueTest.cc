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
#include "Queue.h"
#include "Except.h"

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

	AnsiPrint("Integer Queue:", yellow, black);
	cout << endl;

	// test integer queue
	Queue<int> *myIntQPtr=new Queue<int>;

	// enqueue exercises on myIntQPtr
	int buffer;
	while((*is1) >> buffer) {
		myIntQPtr->enqueue(buffer);
	}

	// test copy constructor
	Queue<int> myIntQ = *myIntQPtr;

	// test destructor
	delete myIntQPtr;
	
	// dequeue exercises on myIntQ
	while(!myIntQ.isEmpty()) {
		cout << myIntQ.dequeue() << endl;
	}

	AnsiPrint("Character Queue:", yellow, black);
	cout << endl;

	// test character queue
	Queue<char> myCharQ, myCharQ1;

	// enqueue exercises on myCharQ
	char charBuffer;
	while((*is2) >> charBuffer) {
		myCharQ.enqueue(charBuffer);
	}

	// test assignment operator
	myCharQ1 = myCharQ;

	// dequeue exercise on myCharQ1
	while(!myCharQ1.isEmpty()) {
		cout << myCharQ1.dequeue() << endl;
	}

	try {
		myCharQ1.dequeue();
	} catch(Except e) {
		AnsiPrint((const char*)e, black, yellow);
		cout << endl;
	}

	PrintMyID("110703066");
	return 0;
    
}
