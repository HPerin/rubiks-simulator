/*
 * PET COMPUTACAO UFRGS
 * Rubik's Cube Robot Simulator
 *
 *  Created on: Oct 23, 2014
 *      Author: Lucas Hennemann Perin
 */

#include <iostream>
#include <cstring>

#include "Cube.h"

using namespace std;

bool inputTest(char Colors[6][10], string Cmd) {

	Cube *cube = new Cube(Colors);

	cout << endl << "TEST:" << endl;

	int operationIndex=0;
	while (cube->executeCommand(Cmd[operationIndex])) {
		operationIndex++;
	}

	bool isSolved = cube->isSolved();
	delete cube;

	if (isSolved) {
		cout << "The cube has been solved!" << endl << "Operations: " << operationIndex << endl;
	} else {
		cout << "There was an error solving the cube." << endl;
	}

	return isSolved;

}

bool testZero() {
	// F:WWOWWOWWO B:RYYRYYRYY L:BBBBBBBBB R:GGGGGGGGG U:RRWRRWRRW D:OOYOOYOOY

	char Colors[7][10] = {
		"WWOWWOWWO",
		"RYYRYYRYY",
		"BBBBBBBBB",
		"GGGGGGGGG",
		"RRWRRWRRW",
		"OOYOOYOOY"
	};

	string Cmd = "afbfaafbbfS";

	return inputTest(Colors, Cmd);
}

bool testOne() {
	// F:GGGWWOWWO B:BBBRYYRYY L:WWOBBBBBB R:RYYGGGGGG U:RRRRRRWWW D:OOYOOYOOY

	char Colors[6][10] = {
			"GGGWWOWWO",
			"BBBRYYRYY",
			"WWOBBBBBB",
			"RYYGGGGGG",
			"RRRRRRWWW",
			"OOYOOYOOY"
	};

	string Cmd = "eaefbfcedefafebeafbfaafbbfS";

	return inputTest(Colors, Cmd);
}

bool testTwo() {
	// F:YOOYWWGWW B:WWBBYYBRR L:WWROBRYBW R:YBROGYOGY U:RGGRRRBGG D:OBBOOYGGO

	char Colors[6][10] = {
			"YOOYWWGWW",
			"WWBBYYBRR",
			"WWROBRYBW",
			"YBROGYOGY",
			"RGGRRRBGG",
			"OBBOOYGGO"
	};

	string Cmd = "eaacedebbcedfccfafbddfeaefbfcedefafebefccafbfddfeaefbfcedefafebeafbfaafbbfS";

	return inputTest(Colors, Cmd);
}

bool testThree() {
	// F:BGWWWOYYR B:WOYRYWGYY L:BRWRGBBBG R:OBBWBYYGR U:RGRGOOOWG D:OBGRRYOOW

	char Colors[6][10] = {
		"BGWWWOYYR",
		"WOYRYWGYY",
		"BRWRGBBBG",
		"OBBWBYYGR",
		"RGRGOOOWG",
		"OBGRRYOOW"
	};

	string Cmd = 		"afbfcceddefccfaafbbddfcedeaafbbfeaefbfecedfa"
			"febefccafbfddfeaefbfecedfafeacedebbeaafbfebcedeaefbccfaa"
			"fbbddfeaefbfcedefafeaecceddbefbfcedefafebeaafbfebeccedda"
			"efbfcceddaefbfcedefafebefccfaafbbddafebcedeaefbfS";

	return inputTest(Colors, Cmd);
}

bool testFour() {
	// F:WBBYWOYRR B:GOGWYRYWW L:OBRBBGBBO R:OROWGRBOR U:YYWYRGGWW D:BYYOOGRGG

	char Colors[6][10] = {
		"WBBYWOYRR",
		"GOGWYRYWW",
		"OBRBBGBBO",
		"OROWGRBOR",
		"YYWYRGGWW",
		"BYYOOGRGG"
	};

	string Cmd = 			"cedefafbeaaecedbbefccfaafbbddafebecceddaefb"
			"fcedaefbfecedfafebeafbfeaaecceddbefbfcedefafeaecceddbef"
			"bfcceddefafebeaafbfebecedaefbfcceddefccfaafbbddfeaefbfc"
			"ceddefafebefccfaafbbddafebecedaefbccfaafbbddafebcedeaef"
			"bccfaafbbddfeaaecceddbbeS";

	return inputTest(Colors, Cmd);
}

bool testFive() {
	// F:RYOBWRYWG B:GOOWYBBYR L:BBWRBOYBG R:WWWGGOOYR U:YGRYRGBRB D:ORWWOGGOY

	char Colors[6][10] = {
			"RYOBWRYWG",
			"GOOWYBBYR",
			"BBWRBOYBG",
			"WWWGGOOYR",
			"YGRYRGBRB",
			"ORWWOGGOY"
	};

	string Cmd = 		"eaefbfecedfafebefafbfafebecceddaefbfeaaeccedd"
			"befbfecedfafeacedebbeafbfecedfafebcedeaefbfecedeaaecceddb"
			"befafebcedeaefbfeaaecceddbefbfecedfafeaecceddbbefccfaafbb"
			"ddfeaefbfcceddefafebecceddaefbfcceddefafebecceddaefbfeced"
			"fafebefccfaafbbddfS";

	return inputTest(Colors, Cmd);
}

int main(int argc, char* argv[]) {
	testZero();
	testOne();
	testTwo();
	testThree();
	testFour();
	testFive();
}
