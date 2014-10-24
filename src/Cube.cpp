/*
 * Cube.cpp
 *
 *  Created on: Oct 23, 2014
 *      Author: Lucas Hennemann Perin
 */

#include "Cube.h"

Cube::Cube(char Colors[CUBE_SIDES][SIDE_COLORS + 1]) {

	/*
	 * Allocate the matrix of sides
	 */
	CubeColors = new char*[CUBE_SIDES];
	for ( int i=0; i<CUBE_SIDES; i++ ) {
		CubeColors[i] = new char[SIDE_COLORS];
	}

	/*
	 * Copy the initial condition of the Cube
	 */
	for ( int i=0; i<CUBE_SIDES; i++ ) {
		for ( int j=0; j<SIDE_COLORS; j++ ) {
			CubeColors[i][j] = Colors[i][j];
		}
	}

	/*
	 * The claws start closed
	 */
	leftClawState = CLAWSTATE::CLOSED;
	rightClawState = CLAWSTATE::CLOSED;

	/*
	 * leftClaw start holding the back Side
	 * rightClaw start holding the left Side
	 */
	leftClawSide = POSITION::BACK;
	rightClawSide = POSITION::RIGHT;

}

Cube::~Cube() {
	/*
	 * Deallocate the Cube Matrix
	 */
	for ( int i=0; i<CUBE_SIDES; i++ ) {
		delete CubeColors[i];
	}
	delete CubeColors;
}

bool Cube::executeCommand(char Command) {
	/*
	 * You can iterate on the sendCommand
	 * function until it returns false, in which
	 * case you can stop
	 */
	if (Command == MOVES::FINAL_STATE) {
		return false;
	}

	/*
	 * Switch of the possible commands received
	 *
	 * if the command is invalid, nothing is done
	 */
	switch (Command) {
	case MOVES::LEFTUP90:
		if (leftClawState == CLAWSTATE::CLOSED) {
			if (rightClawState == CLAWSTATE::OPEN) {
				rotateCubeLeft(leftClawSide);
			} else {
				rotateCubeClosePartLeft(leftClawSide);
			}
		}
		break;
	case MOVES::LEFTDOWN90:
		if (leftClawState == CLAWSTATE::CLOSED) {
			if (rightClawState == CLAWSTATE::OPEN) {
				rotateCubeRight(leftClawSide);
			} else {
				rotateCubeClosePartRight(leftClawSide);
			}
		}
		break;
	case MOVES::LEFTTOGGLE:
		if (leftClawState == CLAWSTATE::OPEN) {
			leftClawState = CLAWSTATE::CLOSED;
		} else {
			leftClawState = CLAWSTATE::OPEN;
		}
		break;
	case MOVES::RIGHTUP90:
		if (rightClawState == CLAWSTATE::CLOSED) {
			if (leftClawState == CLAWSTATE::OPEN) {
				rotateCubeRight(rightClawSide);
			} else {
				rotateCubeClosePartRight(rightClawSide);
			}
		}
		break;
	case MOVES::RIGHTDOWN90:
		if (rightClawState == CLAWSTATE::CLOSED) {
			if (leftClawState == CLAWSTATE::OPEN) {
				rotateCubeLeft(rightClawSide);
			} else {
				rotateCubeClosePartLeft(rightClawSide);
			}
		}
		break;
	case MOVES::RIGHTTOGGLE:
		if (rightClawState == CLAWSTATE::OPEN) {
			rightClawState = CLAWSTATE::CLOSED;
		} else {
			rightClawState = CLAWSTATE::OPEN;
		}
		break;
	}

	return true;
}

void Cube::debugPrint() {
	for ( int i=0; i<CUBE_SIDES; i++ ) {
		for ( int j=0; j<SIDE_COLORS; j++ ) {
			std::cout << CubeColors[i][j];
		}
		std::cout << std::endl;
	}
}

bool Cube::isSolved() {

	/*
	 * Iterates on all sides
	 */
	for ( int i=0; i<CUBE_SIDES; i++ ) {

		/*
		 * Check if that side's colors are all
		 * the same
		 */
		char curColor = CubeColors[i][0];
		for ( int j=1; j<SIDE_COLORS; j++ ) {
			if (CubeColors[i][j] != curColor) {
				return false;
			}
		}

	}

	return true;
}

void Cube::rotateCubeLeft(int Side) {
	/*
	 * First we make the color moves
	 */
	rotateSideSidesLeft(Side);

	rotateSideLeft(Side);
	rotateSideRight(getOpositeSide(Side));

	/*
	 * Now we need to update the side the
	 * claw is holding
	 */
	//updateClawsRotateLeft(Side);
}

void Cube::rotateCubeClosePartLeft(int Side) {
	/*
	 * Here we make the color moves
	 */
	rotateSideCloseColorsLeft(Side);

	rotateSideLeft(Side);

	/*
	 * We have no need to update the
	 * side the claw is holding, because
	 * it is still the same
	 */
}

void Cube::updateClawsRotateLeft(int Side) {
	/*
	 * if the left claw
	 * is holding the Cube
	 */
	if (Side == leftClawSide) {

		switch(rightClawSide) {
		case POSITION::BACK: {

			switch(leftClawSide) {
			case POSITION::LEFT:
				rightClawSide = POSITION::UP;
				break;
			case POSITION::UP:
				rightClawSide = POSITION::RIGHT;
				break;
			case POSITION::RIGHT:
				rightClawSide = POSITION::DOWN;
				break;
			case POSITION::DOWN:
				rightClawSide = POSITION::LEFT;
				break;
			}

			break;
		}
		case POSITION::UP: {

			switch(leftClawSide) {
			case POSITION::LEFT:
				rightClawSide = POSITION::BACK;
				break;
			case POSITION::BACK:
				rightClawSide = POSITION::RIGHT;
				break;
			case POSITION::RIGHT:
				rightClawSide = POSITION::FRONT;
				break;
			case POSITION::FRONT:
				rightClawSide = POSITION::LEFT;
				break;
			}

			break;
		}
		case POSITION::DOWN: {

			switch(leftClawSide) {
			case POSITION::FRONT:
				rightClawSide = POSITION::RIGHT;
				break;
			case POSITION::RIGHT:
				rightClawSide = POSITION::BACK;
				break;
			case POSITION::BACK:
				rightClawSide = POSITION::LEFT;
				break;
			case POSITION::LEFT:
				rightClawSide = POSITION::FRONT;
				break;
			}

			break;
		}
		case POSITION::FRONT: {

			switch(leftClawSide) {
			case POSITION::UP:
				rightClawSide = POSITION::RIGHT;
				break;
			case POSITION::RIGHT:
				rightClawSide = POSITION::DOWN;
				break;
			case POSITION::DOWN:
				rightClawSide = POSITION::LEFT;
				break;
			case POSITION::LEFT:
				rightClawSide = POSITION::UP;
				break;
			}

			break;
		}
		case POSITION::LEFT: {

			switch(leftClawSide) {
			case POSITION::UP:
				rightClawSide = POSITION::FRONT;
				break;
			case POSITION::FRONT:
				rightClawSide = POSITION::DOWN;
				break;
			case POSITION::DOWN:
				rightClawSide = POSITION::BACK;
				break;
			case POSITION::BACK:
				rightClawSide = POSITION::UP;
				break;
			}

			break;
		}
		case POSITION::RIGHT: {

			switch(leftClawSide) {
			case POSITION::FRONT:
				rightClawSide = POSITION::UP;
				break;
			case POSITION::UP:
				rightClawSide = POSITION::BACK;
				break;
			case POSITION::BACK:
				rightClawSide = POSITION::DOWN;
				break;
			case POSITION::DOWN:
				rightClawSide = POSITION::FRONT;
				break;
			}

			break;
		}
		}
	}
	/*
	 * else if the right claw
	 * is holding the Cube
	 */
	else if (Side == rightClawSide) {

		switch(leftClawSide) {
		case POSITION::BACK: {

			switch(rightClawSide) {
			case POSITION::LEFT:
				leftClawSide = POSITION::DOWN;
				break;
			case POSITION::DOWN:
				leftClawSide = POSITION::RIGHT;
				break;
			case POSITION::RIGHT:
				leftClawSide = POSITION::UP;
				break;
			case POSITION::UP:
				leftClawSide = POSITION::LEFT;
				break;
			}

			break;
		}
		case POSITION::UP: {

			switch(rightClawSide) {
			case POSITION::RIGHT:
				leftClawSide = POSITION::FRONT;
				break;
			case POSITION::FRONT:
				leftClawSide = POSITION::LEFT;
				break;
			case POSITION::LEFT:
				leftClawSide = POSITION::BACK;
				break;
			case POSITION::BACK:
				leftClawSide = POSITION::RIGHT;
				break;
			}

			break;
		}
		case POSITION::DOWN: {

			switch(rightClawSide) {
			case POSITION::FRONT:
				leftClawSide = POSITION::RIGHT;
				break;
			case POSITION::RIGHT:
				leftClawSide = POSITION::BACK;
				break;
			case POSITION::BACK:
				leftClawSide = POSITION::LEFT;
				break;
			case POSITION::LEFT:
				leftClawSide = POSITION::FRONT;
				break;
			}

			break;
		}
		case POSITION::FRONT: {

			switch(rightClawSide) {
			case POSITION::UP:
				leftClawSide = POSITION::RIGHT;
				break;
			case POSITION::RIGHT:
				leftClawSide = POSITION::DOWN;
				break;
			case POSITION::DOWN:
				leftClawSide = POSITION::LEFT;
				break;
			case POSITION::LEFT:
				leftClawSide = POSITION::UP;
				break;
			}

			break;
		}
		case POSITION::LEFT: {

			switch(rightClawSide) {
			case POSITION::UP:
				leftClawSide = POSITION::FRONT;
				break;
			case POSITION::FRONT:
				leftClawSide = POSITION::DOWN;
				break;
			case POSITION::DOWN:
				leftClawSide = POSITION::BACK;
				break;
			case POSITION::BACK:
				leftClawSide = POSITION::UP;
				break;
			}

			break;
		}
		case POSITION::RIGHT: {

			switch(rightClawSide) {
			case POSITION::FRONT:
				leftClawSide = POSITION::UP;
				break;
			case POSITION::UP:
				leftClawSide = POSITION::BACK;
				break;
			case POSITION::BACK:
				leftClawSide = POSITION::DOWN;
				break;
			case POSITION::DOWN:
				leftClawSide = POSITION::FRONT;
				break;
			}

			break;
		}
		}
	}
}

void Cube::rotateSideCloseColorsLeft(int Side) {

	/*
	 * Once again we made it the dumb way,
	 * we move one color by line
	 */
	switch (Side) {
	case POSITION::FRONT: {
		char *leftSide = new char[SIDE_COLORS];
		for ( int i=0; i<SIDE_COLORS; i++ ) {
			leftSide[i] = CubeColors[POSITION::LEFT][i];
		}

		CubeColors[POSITION::LEFT][2] = CubeColors[POSITION::UP][8];
		CubeColors[POSITION::LEFT][5] = CubeColors[POSITION::UP][7];
		CubeColors[POSITION::LEFT][8] = CubeColors[POSITION::UP][6];

		CubeColors[POSITION::UP][6] = CubeColors[POSITION::RIGHT][0];
		CubeColors[POSITION::UP][7] = CubeColors[POSITION::RIGHT][3];
		CubeColors[POSITION::UP][8] = CubeColors[POSITION::RIGHT][6];

		CubeColors[POSITION::RIGHT][0] = CubeColors[POSITION::DOWN][2];
		CubeColors[POSITION::RIGHT][3] = CubeColors[POSITION::DOWN][1];
		CubeColors[POSITION::RIGHT][6] = CubeColors[POSITION::DOWN][0];

		CubeColors[POSITION::DOWN][2] = leftSide[8];
		CubeColors[POSITION::DOWN][1] = leftSide[5];
		CubeColors[POSITION::DOWN][0] = leftSide[2];

		delete leftSide;
		break;
		}
	case POSITION::BACK: {
		char *leftSide = new char[SIDE_COLORS];
		for ( int i=0; i<SIDE_COLORS; i++ ) {
			leftSide[i] = CubeColors[POSITION::LEFT][i];
		}

		CubeColors[POSITION::LEFT][0] = CubeColors[POSITION::DOWN][6];
		CubeColors[POSITION::LEFT][3] = CubeColors[POSITION::DOWN][7];
		CubeColors[POSITION::LEFT][6] = CubeColors[POSITION::DOWN][8];

		CubeColors[POSITION::DOWN][8] = CubeColors[POSITION::RIGHT][2];
		CubeColors[POSITION::DOWN][7] = CubeColors[POSITION::RIGHT][5];
		CubeColors[POSITION::DOWN][6] = CubeColors[POSITION::RIGHT][8];

		CubeColors[POSITION::RIGHT][2] = CubeColors[POSITION::UP][0];
		CubeColors[POSITION::RIGHT][5] = CubeColors[POSITION::UP][1];
		CubeColors[POSITION::RIGHT][8] = CubeColors[POSITION::UP][2];

		CubeColors[POSITION::UP][2] = leftSide[0];
		CubeColors[POSITION::UP][1] = leftSide[3];
		CubeColors[POSITION::UP][0] = leftSide[6];

		delete leftSide;
		break;
		}
	case POSITION::LEFT: {
		char *frontSide = new char[SIDE_COLORS];
		for ( int i=0; i<SIDE_COLORS; i++ ) {
			frontSide[i] = CubeColors[POSITION::FRONT][i];
		}

		CubeColors[POSITION::FRONT][0] = CubeColors[POSITION::DOWN][0];
		CubeColors[POSITION::FRONT][3] = CubeColors[POSITION::DOWN][3];
		CubeColors[POSITION::FRONT][6] = CubeColors[POSITION::DOWN][6];

		CubeColors[POSITION::DOWN][0] = CubeColors[POSITION::BACK][8];
		CubeColors[POSITION::DOWN][3] = CubeColors[POSITION::BACK][5];
		CubeColors[POSITION::DOWN][6] = CubeColors[POSITION::BACK][2];

		CubeColors[POSITION::BACK][2] = CubeColors[POSITION::UP][6];
		CubeColors[POSITION::BACK][5] = CubeColors[POSITION::UP][3];
		CubeColors[POSITION::BACK][8] = CubeColors[POSITION::UP][0];

		CubeColors[POSITION::UP][0] = frontSide[0];
		CubeColors[POSITION::UP][3] = frontSide[3];
		CubeColors[POSITION::UP][6] = frontSide[6];

		delete frontSide;
		break;
		}
	case POSITION::RIGHT: {
		char *frontSide = new char[SIDE_COLORS];
		for ( int i=0; i<SIDE_COLORS; i++ ) {
			frontSide[i] = CubeColors[POSITION::FRONT][i];
		}

		CubeColors[POSITION::FRONT][2] = CubeColors[POSITION::UP][2];
		CubeColors[POSITION::FRONT][5] = CubeColors[POSITION::UP][5];
		CubeColors[POSITION::FRONT][8] = CubeColors[POSITION::UP][8];

		CubeColors[POSITION::UP][2] = CubeColors[POSITION::BACK][6];
		CubeColors[POSITION::UP][5] = CubeColors[POSITION::BACK][3];
		CubeColors[POSITION::UP][8] = CubeColors[POSITION::BACK][0];

		CubeColors[POSITION::BACK][0] = CubeColors[POSITION::DOWN][8];
		CubeColors[POSITION::BACK][3] = CubeColors[POSITION::DOWN][5];
		CubeColors[POSITION::BACK][6] = CubeColors[POSITION::DOWN][2];

		CubeColors[POSITION::DOWN][2] = frontSide[2];
		CubeColors[POSITION::DOWN][5] = frontSide[5];
		CubeColors[POSITION::DOWN][8] = frontSide[8];

		delete frontSide;
		break;
		}
	case POSITION::DOWN: {
		char *frontSide = new char[SIDE_COLORS];
		for ( int i=0; i<SIDE_COLORS; i++ ) {
			frontSide[i] = CubeColors[POSITION::FRONT][i];
		}

		CubeColors[POSITION::FRONT][6] = CubeColors[POSITION::RIGHT][6];
		CubeColors[POSITION::FRONT][7] = CubeColors[POSITION::RIGHT][7];
		CubeColors[POSITION::FRONT][8] = CubeColors[POSITION::RIGHT][8];

		CubeColors[POSITION::RIGHT][6] = CubeColors[POSITION::BACK][6];
		CubeColors[POSITION::RIGHT][7] = CubeColors[POSITION::BACK][7];
		CubeColors[POSITION::RIGHT][8] = CubeColors[POSITION::BACK][8];

		CubeColors[POSITION::BACK][6] = CubeColors[POSITION::LEFT][6];
		CubeColors[POSITION::BACK][7] = CubeColors[POSITION::LEFT][7];
		CubeColors[POSITION::BACK][8] = CubeColors[POSITION::LEFT][8];

		CubeColors[POSITION::LEFT][6] = frontSide[6];
		CubeColors[POSITION::LEFT][7] = frontSide[7];
		CubeColors[POSITION::LEFT][8] = frontSide[8];

		delete frontSide;
		break;
		}
	case POSITION::UP: {
		char *frontSide = new char[SIDE_COLORS];
		for ( int i=0; i<SIDE_COLORS; i++ ) {
			frontSide[i] = CubeColors[POSITION::FRONT][i];
		}

		CubeColors[POSITION::FRONT][0] = CubeColors[POSITION::LEFT][0];
		CubeColors[POSITION::FRONT][1] = CubeColors[POSITION::LEFT][1];
		CubeColors[POSITION::FRONT][2] = CubeColors[POSITION::LEFT][2];

		CubeColors[POSITION::LEFT][0] = CubeColors[POSITION::BACK][0];
		CubeColors[POSITION::LEFT][1] = CubeColors[POSITION::BACK][1];
		CubeColors[POSITION::LEFT][2] = CubeColors[POSITION::BACK][2];

		CubeColors[POSITION::BACK][0] = CubeColors[POSITION::RIGHT][0];
		CubeColors[POSITION::BACK][1] = CubeColors[POSITION::RIGHT][1];
		CubeColors[POSITION::BACK][2] = CubeColors[POSITION::RIGHT][2];

		CubeColors[POSITION::RIGHT][0] = frontSide[0];
		CubeColors[POSITION::RIGHT][1] = frontSide[1];
		CubeColors[POSITION::RIGHT][2] = frontSide[2];

		delete frontSide;
		break;
		}
	}
}

void Cube::rotateSideSidesLeft(int Side) {

	/*
	 * We made a switch to move the sides according to
	 * the given current side
	 */
	switch (Side) {
	case POSITION::FRONT: {
		char *rightSide = CubeColors[POSITION::RIGHT];

		CubeColors[POSITION::RIGHT] = updateSideCounterclockwise(CubeColors[POSITION::DOWN]);
		CubeColors[POSITION::DOWN] = updateSideCounterclockwise(CubeColors[POSITION::LEFT]);
		CubeColors[POSITION::LEFT] = updateSideCounterclockwise(CubeColors[POSITION::UP]);
		CubeColors[POSITION::UP] = updateSideCounterclockwise(rightSide);
		break;
		}
	case POSITION::BACK: {
		char *leftSide = CubeColors[POSITION::LEFT];

		CubeColors[POSITION::LEFT] = updateSideClockwise(CubeColors[POSITION::DOWN]);
		CubeColors[POSITION::DOWN] = updateSideClockwise(CubeColors[POSITION::RIGHT]);
		CubeColors[POSITION::RIGHT] = updateSideClockwise(CubeColors[POSITION::UP]);
		CubeColors[POSITION::UP] = updateSideClockwise(leftSide);
		break;
		}
	case POSITION::LEFT: {
		char *frontSide = CubeColors[POSITION::FRONT];

		CubeColors[POSITION::FRONT] = CubeColors[POSITION::DOWN];
		CubeColors[POSITION::DOWN] = reverseColorString(CubeColors[POSITION::BACK]);
		CubeColors[POSITION::BACK] = reverseColorString(CubeColors[POSITION::UP]);
		CubeColors[POSITION::UP] = frontSide;
		break;
		}
	case POSITION::RIGHT: {
		char *backSide = CubeColors[POSITION::BACK];

		CubeColors[POSITION::BACK] =reverseColorString(CubeColors[POSITION::DOWN]);
		CubeColors[POSITION::DOWN] = CubeColors[POSITION::FRONT];
		CubeColors[POSITION::FRONT] = CubeColors[POSITION::UP];
		CubeColors[POSITION::UP] = reverseColorString(backSide);
		break;
		}
	case POSITION::DOWN: {
		char *rightSide = CubeColors[POSITION::RIGHT];

		CubeColors[POSITION::RIGHT] = CubeColors[POSITION::BACK];
		CubeColors[POSITION::BACK] = CubeColors[POSITION::LEFT];
		CubeColors[POSITION::LEFT] = CubeColors[POSITION::FRONT];
		CubeColors[POSITION::FRONT] = rightSide;
		break;
		}
	case POSITION::UP: {
		char *rightSide = CubeColors[POSITION::RIGHT];

		CubeColors[POSITION::RIGHT] = CubeColors[POSITION::FRONT];
		CubeColors[POSITION::FRONT] = CubeColors[POSITION::LEFT];
		CubeColors[POSITION::LEFT] = CubeColors[POSITION::BACK];
		CubeColors[POSITION::BACK] = rightSide;
		break;
		}
	}
}

void Cube::rotateSideLeft(int Side) {
	char *newSide = new char[SIDE_COLORS];

	/*
	 * For now we implemented it in the dumb way, so i choose
	 * manually the sides to change
	 */
	newSide[0] = CubeColors[Side][2];
	newSide[1] = CubeColors[Side][5];
	newSide[2] = CubeColors[Side][8];

	newSide[3] = CubeColors[Side][1];
	newSide[4] = CubeColors[Side][4];
	newSide[5] = CubeColors[Side][7];

	newSide[6] = CubeColors[Side][0];
	newSide[7] = CubeColors[Side][3];
	newSide[8] = CubeColors[Side][6];

	delete CubeColors[Side];

	CubeColors[Side] = newSide;
}

void Cube::rotateCubeRight(int Side) {
	for ( int i=0; i<LEFT_TO_RIGHT_TIMES; i++ ) {
		rotateCubeLeft(Side);
	}
}

void Cube::rotateCubeClosePartRight(int Side) {
	for ( int i=0; i<LEFT_TO_RIGHT_TIMES; i++ ) {
		rotateCubeClosePartLeft(Side);
	}
}

void Cube::rotateSideRight(int Side) {
	for ( int i=0; i<LEFT_TO_RIGHT_TIMES; i++ ) {
		rotateSideLeft(Side);
	}
}

int Cube::getOpositeSide(int Side) {

	switch(Side) {
	case POSITION::FRONT:
		return POSITION::BACK;
	case POSITION::BACK:
		return POSITION::FRONT;
	case POSITION::DOWN:
		return POSITION::UP;
	case POSITION::UP:
		return POSITION::DOWN;
	case POSITION::LEFT:
		return POSITION::RIGHT;
	case POSITION::RIGHT:
		return POSITION::LEFT;
	}

	return -1;
}

char *Cube::reverseColorString(char *Side) {
	char *newSide = new char[SIDE_COLORS];

	for (int i=0; i<SIDE_COLORS; i++) {
		newSide[i] = Side[SIDE_COLORS-1-i];
	}

	delete Side;
	return newSide;
}

char *Cube::updateSideCounterclockwise(char *Side) {
	char *newSide = new char[SIDE_COLORS];

	newSide[0] = Side[6];
	newSide[1] = Side[3];
	newSide[2] = Side[0];

	newSide[3] = Side[7];
	newSide[4] = Side[4];
	newSide[5] = Side[1];

	newSide[6] = Side[8];
	newSide[7] = Side[5];
	newSide[8] = Side[2];

	delete Side;

	return newSide;
}

char *Cube::updateSideClockwise(char *Side) {
	char *newSide = new char[SIDE_COLORS];

	newSide[0] = Side[2];
	newSide[1] = Side[5];
	newSide[2] = Side[8];

	newSide[3] = Side[1];
	newSide[4] = Side[4];
	newSide[5] = Side[7];

	newSide[6] = Side[0];
	newSide[7] = Side[3];
	newSide[8] = Side[6];

	delete Side;

	return newSide;
}
