#ifndef STUDENTAI_H
#define STUDENTAI_H
#include "AI.h"
#include "Board.h"
#pragma once

//The following part should be completed by students.
//Students can modify anything except the class name and exisiting functions and varibles.
class StudentAI :public AI
{
public:
    Board board;
	StudentAI(int col, int row, int p);
	virtual Move GetMove(Move b);

	//evulation function
	int evaluate(Board board, int);
	int maxMoves(int, Board, int player);
	int minMoves(int, Board, int player);
};

#endif //STUDENTAI_H
