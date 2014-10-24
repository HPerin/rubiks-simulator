/*
 * Cube.h
 *
 *  Created on: Oct 23, 2014
 *      Author: Lucas Hennemann Perin
 */

#ifndef CUBE_H_
#define CUBE_H_

#include <iostream>
using namespace std;

/*
* Possible moves received by executeCommand
*
* YOU CAN FREELY CHANGE THE LETTERS
* YOU WILL SEND TO YOUR PREFERENCE!
*/
namespace MOVES {
	enum {
		RIGHTUP90 = 'a',
		RIGHTDOWN90 = 'b',
		LEFTUP90 = 'c',
		LEFTDOWN90 = 'd',
		LEFTTOGGLE = 'e',
		RIGHTTOGGLE = 'f',
		FINAL_STATE = 'S'
	};
}

/*
 * Rubik's Cube Possible
 * Colors
 *
 * YOU CAN FREELY CHANGE THE LETTERS
 * YOU WILL SEND TO YOUR PREFERENCE!
 */
namespace RUBIKCOLORS {
	enum {
		WHITE = 'W',
		RED = 'R',
		BLUE = 'B',
		GREEN = 'G',
		ORANGE = 'O',
		YELLOW = 'Y'
	};
}

/*
 * DONT CHANGE ANYTHING FROM HERE ON!!!
 *
 * ____________________________________
 *
 *
 */

/*
 * Constants to detect errors
 */
#define ERROR -1

/*
 * The number of time you have to
 * execute an left move to reach
 * an equivalent side right move
 */
#define LEFT_TO_RIGHT_TIMES 3

/*
 * Number of Sides the Rubik's Cube has
 *
 * DONT CHANGE THIS!
 */
#define CUBE_SIDES 6

/*
 * Number of Colors each Side of the Rubik's
 * Cube has
 *
 * DONT CHANGE THIS!
 */
#define SIDE_COLORS 9

/*
 * Side Possible Positions
 */
namespace POSITION {
	enum {
		FRONT = 0,
		BACK,
		LEFT,
		RIGHT,
		UP,
		DOWN
	};
}

/*
 * Claw states
 */
namespace CLAWSTATE {
	enum {
		OPEN = 0,
		CLOSED
	};
}

class Cube {
public:
	Cube(char[CUBE_SIDES][SIDE_COLORS + 1]);
	virtual ~Cube();

	/*
	 * Performs an action to the cube
	 * defined by the letter given
	 *
	 * BY DEFAULT:
	 *
	 * RIGHT UP 90 = 'a'
	 * RIGHT DOWN 90 = 'b'
	 * LEFT UP 90 = 'c'
	 * LEFT DOWN 90 = 'd'
	 * LEFT TOGGLE = 'e'
	 * RIGHT TOGGLE = 'f'
	 *
	 * FINAL_STATE = 'S'
	 */
	bool executeCommand(char);

	/*
	 * Returns wheter or not the cube
	 * has been solved, on other words
	 * if in all sides this pattern is
	 * followed:
	 * All colors on the side are the same
	 */
	bool isSolved(void);

	/*
	 * Checks if the Cube given is Valid
	 * that is:
	 *
	 * has 9 of each of the Given Colors
	 */
	void checkIsValid(void);

	/*
	 * DEBUG PRINT
	 */
	void debugPrint(void);

private:
	/*
	 * Rotates the whole cube to left from
	 * the Side given
	 */
	void rotateCubeLeft(int);

	/*
	 * Rotates the closest 1/3 of the cube
	 * to the left
	 */
	void rotateCubeClosePartLeft(int);

	/*
	 * update which side the claw is
	 * holding when you rotate the cube
	 * to the left
	 */
	void updateClawsRotateLeft(int);

	/*
	 * Rotates the given side to left
	 */
	void rotateSideLeft(int);

	/*
	 * Rotate the position of the sides
	 * around the side given to left
	 */
	void rotateSideSidesLeft(int);

	/*
	 * Rotate the closest colors of the others sides closest
	 * to the given side to left
	 */
	void rotateSideCloseColorsLeft(int);

	/*
	 * Calls rotateCubeLeft(int) 3 times
	 * in a row, simulating the results of one
	 * turn to the right
	 */
	void rotateCubeRight(int);

	/*
	 * Calls rotateCubeClosePartLeft(int)
	 * 3 times in a row, simulating the results
	 * of one turn to the right
	 */
	void rotateCubeClosePartRight(int);

	/*
	 * Calls rotateSideRight(int)
	 * 3 times in a row, simulating the
	 * results of one turn to the right
	 */
	void rotateSideRight(int);

	/*
	 * Reverse color string
	 *
	 * Changes from back to up,
	 * and back to down need this
	 */
	char *reverseColorString(char*);

	/*
	 * Adjusts color string for
	 * Counter clockwise Position Change
	 *
	 * Useful when rotating on the Front axis
	 */
	char *updateSideCounterclockwise(char*);

	/*
	 * Adjusts color string for
	 * Clockwise Position Change
	 *
	 * Useful when rotating on the Back axis
	 */
	char *updateSideClockwise(char*);

	/*
	 * Returns the oposite side number to the
	 * given side
	 */
	int getOpositeSide(int);

	/*
	 * The main Cube's Colors Positioning
	 * matrix.
	 *
	 * The row is in which side you are looking at.
	 * Possible Sides:
	 * POSITION::FRONT
	 * POSITION::BACK
	 * POSITION::LEFT
	 * POSITION::RIGHT
	 * POSITION::UP
	 * POSITION::DOWN
	 *
	 * And the col is which color of the given row (Side)
	 * you are looking at.
	 * Possible Colors:
	 * COLORS::WHITE
	 * COLORS::GREEN
	 * COLORS::BLUE
	 * COLORS::YELLOW
	 * COLORS::RED
	 * COLORS::ORANGE
	 */
	char **CubeColors;

	/*
	 * State of the RightClaw
	 *
	 * Possible values:
	 * STATECLAW::OPEN
	 * STATECLAW::CLOSED
	 */
	int rightClawState;

	/*
	 * State of the LeftClaw
	 *
	 * Possible values:
	 * STATECLAW::OPEN
	 * STATECLAW::CLOSED
	 */
	int leftClawState;

	/*
	 * Side the right claw is holding
	 *
	 * Possible values:
	 * POSITION::FRONT
	 * POSITION::BACK
	 * POSITION::LEFT
	 * POSITION::RIGHT
	 * POSITION::UP
	 * POSITION::DOWN
	 */
	int rightClawSide;

	/*
	 * Side the left claw is holding
	 *
	 * Possible values:
	 * POSITION::FRONT
	 * POSITION::BACK
	 * POSITION::LEFT
	 * POSITION::RIGHT
	 * POSITION::UP
	 * POSITION::DOWN
	 */
	int leftClawSide;
};

#endif /* CUBE_H_ */
