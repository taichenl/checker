#ifndef STUDENTAI_H
#define STUDENTAI_H
#include "AI.h"
#include "Board.h"
#include "Node.h"
#include <cmath>
#pragma once
#include <iostream>
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



	//Draft AI functions
	Node* MCTS(Node* root);
	Node traverse(Node* root);
	bool rollout(const Node& node);
	Node rolloutpolicy(const Node& node);
	void backpropagate(Node&,bool result);
	Node* bestchild(Node*);
	double UCB(const Node& node);
	


private:
	//how do you store all the nodes
	Node* rot;

};

#endif //STUDENTAI_H
