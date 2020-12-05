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


int StudentAI::evaluate(Board board){
  int mypaw, myking, mymid, myr, oppopaw, oppoking, oppomid, oppor = 0;
  int length = board.board.size();
  for (int i = 0; i< board.board.size(); ++i){
    for (int j = 0; j< board.board[i].size(); ++j){
      Checker temp = board.board[i][j];
      if (player == 1){       
	if (temp.color == "B"){
	  myr += length - i-1;
	  if (i >=2 and i <= length-3 and j >=2 and j <= length-3){
	    mymid++;
	  }
	  if (temp.isKing){
	    myking++;
	  }
	  else{
	    mypaw++;
	  }
	}
	else{
	  oppor += length - i-1;
          if (i >=2 and i <= length-3 and j >=2 and j <=length-3){
            oppomid++;
          }
          if (temp.isKing){
            oppoking++;
          }
          else{
            oppopaw++;
          }

	}
      }
      else{
	if (temp.color == "W"){
          myr += length - i-1;
          if (i >=2 and i <= length-3 and j >=2 and j <= length-3){
            mymid++;
          }
          if (temp.isKing){
            myking++;
          }
          else{
            mypaw++;
          }
        }
        else{
          oppor += length - i-1;
          if (i >=2 and i <= length-3 and j >=2 and j <=length-3){
            oppomid++;
          }
          if (temp.isKing){
            oppoking++;
          }
          else{
            oppopaw++;
          }

        }	
      }
    }
  }
  return 70*(mypaw-oppopaw)+175*(myking-oppoking)+30*(myr-oppor)+20*(mymid-oppomid);
}



int StudentAI::minMoves(int depth, Board b, int p){
  vector<vector<Move>> moves = b.getAllPossibleMoves(p);
  if (depth == 0 or moves.size()==0){
    return evaluate(b);
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
    return evaluate(board);
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

Node* StudentAI::MCTS(Node* root){
  int i = 0;
  if (root->curBoard.getAllPossibleMoves(root->player).size()==1){
    Node* a = new Node(nullptr, board, 1, root->curBoard.getAllPossibleMoves(root->player)[0][0]);
    return a;
  }
  while(i <1000){
    ++i;
    //std::cout<<i<<"Problem at 15"<<std::endl;
    Node* leaf = traverse(root);
    //std::cout<<i<<"It pass traverse"<<std::endl; 
    bool result = rollout(leaf);
    //std::cout<<i<<"It pass rollout"<<std::endl; 
    backpropagate(leaf, result);
    //std::cout<<i<<"It pass backgate"<<std::endl;
  } 
  //std::cout<<root->children.size()<<std::endl;
  return bestchild(root);
};


Node* StudentAI::traverse(Node* root){
  Node *current = root;
  while (current->visited){
    //std::cout<<"It can reach traverse4"<<std::endl;
    if (current->curBoard.getAllPossibleMoves(current->player).size()!= 0){
      current->fill();
      current = bestchild(current);
    }
    else{
      std::cout<<"It can reach traverse loop"<<std::endl;    
      return current;
    }//std::cout<<"It can reach traverse loop"<<std::endl;
  }
  //std::cout<<current->curBoard.getAllPossibleMoves(current->player).size()<<std::endl;
  current->visited = true;
  //std::cout<<"It can reach traverse2"<<std::endl;
  if (current->curBoard.getAllPossibleMoves(current->player).size()!= 0) current->fill();
  //std::cout<<"It can reach traverse3"<<std::endl;
  return current;
};

bool StudentAI::rollout(Node* node){
  Node *current = node;
  int temp;
  while (current->curBoard.getAllPossibleMoves(current->player).size()!= 0){
    if (current->children.size()!=0)current = rolloutpolicy(current);
    current->fill();
    }
  if (current->curBoard.blackCount >current->curBoard.whiteCount){
    return player ==1;
  }
  else{
    return player ==2;
  }

};

Node* StudentAI::rolloutpolicy(Node* node){
  //int i = rand()%(node->children.size());
  /*Node* result;
  int max = -999999;
  Board temp;
  for (auto a: node->children){
    temp = node->curBoard;
    temp.makeMove(a->currentMove, node->player);
    if (evaluate(node->curBoard) >max) result = a;  
  }
  return result;*/
  int turn; //whose turn is it
  if (node->player == player){
    Node* result;                                                                         
    int max = -999999;                                                                      
    Board temp;                                                                           
    for (auto a: node->children){                                                           
      temp = node->curBoard;                                                                
      temp.makeMove(a->currentMove, node->player);                                          
      if (evaluate(node->curBoard) >max) result = a;                                        
    }                                                                                    
    return result;
  }
  else{ //not your turn, want the worst
    Node* result;                                                                         
    int min= 999999;                                                                      
    Board temp;                                                                             
    for (auto a: node->children){                                                           
      temp = node->curBoard;                                                                
      temp.makeMove(a->currentMove, node->player);                                          
      if (evaluate(node->curBoard) <min) result = a;                                        
    }                                                                                       
    return result;
  }
};

void StudentAI::backpropagate(Node* node, bool result){
  Node *temp = node;
  while (temp->parent != nullptr){
    ++temp->game;
    if (result) ++temp->win;
    temp = temp->parent;
  }
};


Node* StudentAI::bestchild(Node * node){
  int max = -9999999;
  Node* best;
  for (auto i: node->children){
    // std::cout<<i->currentMove.toString()<<"DEBUG"<<std::endl;
    if (UCB(i)> max){
      max = UCB(i);
      best = i;
    }
  }
  return best;
};

double StudentAI::UCB(Node* node){
  if (node->game == 0) return 99999999;
  return node->win*1.0/node->game + 
    1.95 * sqrt(2*log(node->parent->game*1.0)/node->game);
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

    rot = new Node(board, player);
    m= MCTS(rot)->currentMove;
    //std::cout<<1111111111111111111<<std::endl;
    //std::cout<<m.toString()<<123<<std::endl;
    board.makeMove(m,player);
    return m;
    //vector<vector<Move> > moves = board.getAllPossibleMoves(player);
    /*int max = -10000;
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
    return m;*/
    //int i = rand() % (moves.size());
    //vector<Move> checker_moves = moves[2];
    //int j = rand() % (checker_moves.size());
    //Move res = checker_moves[j];
    //board.makeMove(res,player);
    //return res;
}



