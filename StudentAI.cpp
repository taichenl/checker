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

Node* StudentAI::MCTS(Node* root){
  int i = 0;
  while(i <1000){
    ++i;
    std::cout<<i<<"Problem at 15"<<std::endl;
    Node leaf = traverse(root);
    std::cout<<i<<"It pass traverse"<<std::endl; 
    bool result = rollout(leaf);
    std::cout<<i<<"It pass rollout"<<std::endl; 
    backpropagate(leaf, result);
    std::cout<<i<<"It pass backgate"<<std::endl;
  } 
  std::cout<<root->children.size()<<std::endl;
  return bestchild(root);
};


Node StudentAI::traverse(Node* root){
  Node *current = root;
  while (current->visited){
    std::cout<<"It can reach traverse4"<<std::endl;
    if (current->curBoard.getAllPossibleMoves(current->player).size()!= 0){
      current = bestchild(current);
    }
    else{
      std::cout<<"It can reach traverse loop"<<std::endl;    
      return *current;
    }//std::cout<<"It can reach traverse loop"<<std::endl;
  }
  std::cout<<current->curBoard.getAllPossibleMoves(current->player).size()<<std::endl;
  current->visited = true;
  std::cout<<"It can reach traverse2"<<std::endl;
  if (current->curBoard.getAllPossibleMoves(current->player).size()!= 0) current->fill();
  std::cout<<"It can reach traverse3"<<std::endl;

  return *current;
};

bool StudentAI::rollout(const Node& node){
  Node current = node;
  int temp;
  if (node.player == 1)
    {
      temp = 1;
    }
  else{
    temp = 2;
      }
  std::cout<<"It can reach rollout 1"<<std::endl;    
  while (current.curBoard.isWin(temp)!= 0){
    current = rolloutpolicy(current);
    current.fill();//player side
    temp = (temp ==1)? 2:1;
    }
  std::cout<<"It can reach rollout 1"<<std::endl;
  if (current.curBoard.isWin(temp) == player){
    return true;
  }
  else{
    return false;
  }

};

Node StudentAI::rolloutpolicy(const Node& node){
  int i = rand()%(node.children.size());
  return *node.children[i];
};

void StudentAI::backpropagate(Node& node, bool result){
  Node *temp = &node;
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
    if (UCB(*i)> max){
      max = UCB(*i);
      best = i;
    }
  }
  return best;
};

double StudentAI::UCB(const Node& node){
  if (node.game == 0) return 99999999;
  return node.win*1.0/node.game + 
    1.95 * sqrt(2*log(node.parent->game/node.game));
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



