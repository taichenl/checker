#ifndef NODE_H
#define NODE_H
#include "AI.h"
#include "Board.h"
#pragma once

class Node{
public:
  Node(){
    win = 0;
    game = 0;


};


  Node(Board b, int pl) //parent
    {
      player = pl;
      curBoard = b;
        parent = nullptr;
        win = 0;
        game = 0;
	visited =false;
    }

    Node(Node* p, Board b, int po, Move c)
    {
      currentMove = c;
        parent = p;
        curBoard = b;
        win = 0;
        game = 0;
        player = po;
	visited = false;
    }

    void fill(){
      std::cout<<"check3"<<std::endl;
      std::cout<<curBoard.getAllPossibleMoves(player).size()<<std::endl;
      for (auto a :curBoard.getAllPossibleMoves(player)){
            for (auto i: a) {
	      std::cout<<"check1"<<std::endl;
                Board temp = curBoard;
                temp.makeMove(i, player);
		int right;
		if (this->player==1){
		  right = 2;
		}
		else{
		  right = 1;
		}
		std::cout<<"check2"<<std::endl;
                Node *current = new Node(this, temp, right, i);
                children.push_back(current);
            }
	    }
    }
    Node* parent;
    Board curBoard;
    std::vector <Node*> children;
    Move currentMove;
    int player;
    int win;
    int game;
    bool visited;
};

#endif //NODE_H
