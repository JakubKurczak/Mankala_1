#pragma once

#include "Player.h"
#include "StateTree.h"
class AI_Player : public Player {
private:

public:

	AI_Player(std::string name) : Player(name) {

	}

	int get_move(std::shared_ptr<Board> board, std::shared_ptr<Player> player) override {

		
		StateTree stateTree(player,board,3);
		int move = stateTree.get_best_move();
		
		std::cout << std::endl <<this->get_name() <<" will play move: "<<move<<std::endl<<": ";
		char dummy;
		std::cin >> dummy;
		return move;
	}

	~AI_Player()
	{

	}
};
