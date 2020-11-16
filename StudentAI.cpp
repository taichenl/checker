#include "StudentAI.h"
#include <random>
#include <iostream>

//First, evulation function
//second, get possible path(already done by the board.getPossiblePath9))
//third, iterative function /recursive with the depth using minimax
//forth, eveulate each and return the largest value;


StudentAI::StudentAI(int col,int row,int p)
	:AI(col, row, p)
{
    board = Board(col,row,p);
    board.initializeGame();
    player = 2;
}

int StudentAI::evaluate(Board board, int p){
    if (p==1){
        return board.blackCount-board.whiteCount;
    }
    else{
        return board.whiteCount- board.blackCount;
    }
}



int StudentAI::minMoves(int depth, Board b, int p){
  vector<vector<Move>> moves = b.getAllPossibleMoves(p);
  if (depth == 0 or moves.size()==0){
    return evaluate(b, p);
    }
    else{
        int min = 1000000;
        int oppo = (p == 1)? 2: 1;
        for (auto a :moves){ //change later
            for (auto i : a){
                Board temp = b;
                temp.makeMove(i, p); //change
                int v = maxMoves(depth-1, temp, oppo);
                if (v < min) min = v;
            }
        }
	return min;
    }
}


int StudentAI::maxMoves(int depth, Board b, int p){
  vector<vector<Move>> moves = b.getAllPossibleMoves(p);
  if (depth == 0 or moves.size()==0){
    return evaluate(board, p);
    }
    else{
        int max = -1000000;
        int oppo = (p == 1)? 2: 1;
        for (auto a :moves){ //change later
            for (auto i : a){
                Board temp = b;
                temp.makeMove(i, p); //change
                int v = minMoves(depth-1, temp, oppo);
                if (v > max) max = v;
            }
        }
	return max;
    }
}




//in the last part
Move StudentAI::GetMove(Move move)
{
    if (move.seq.empty())
    {
        player = 1;
    } else{
        board.makeMove(move,player == 1?2:1);
    }
    int oppo = (player == 1)? 2: 1; Move m;
    vector<vector<Move> > moves = board.getAllPossibleMoves(player);
    int max = -10000;
    for (auto a: moves){
      for (auto i : a){
	    Board temp = board;
            temp.makeMove(i, player);
	    int v = minMoves(3, temp, oppo);
            if (v > max){
	      m = i;
	    }
	}
    }
    board.makeMove(m,player);
    return m;
    //int i = rand() % (moves.size());
    //vector<Move> checker_moves = moves[2];
    //int j = rand() % (checker_moves.size());
    //Move res = checker_moves[j];
    //board.makeMove(res,player);
    //return res;
}



