#pragma once
#include "Board.h"
#include <vector>


//its not a binary tree because evaluation of the children comes after we add them
//its not tremendously important info, more of a observation
class StateNode {
private:
	std::shared_ptr<StateNode> parent;
	Board state;
	int made_move;
	std::shared_ptr<Player> move_chooser;
	std::vector<std::shared_ptr<StateNode>> children;
	bool another_move;

public:
	static int tree_depth;
	
	StateNode(Board& board, std::shared_ptr<Player> move_chooser) : state(board), move_chooser{ move_chooser }, another_move{ false }, made_move{0}{

	}


	StateNode(std::shared_ptr<StateNode> parent, Board& board, std::shared_ptr<Player> move_chooser, int chosen_move) : state(board), parent{ parent }, move_chooser{ move_chooser }, made_move{chosen_move}{
		another_move = this->state.make_move(chosen_move, this->state.get_opposite_player(move_chooser));
	}
	
	

	~StateNode()
	{

	}

	void add_child(std::shared_ptr<StateNode> child) {
		children.push_back(child);
	}

	Board& get_state() {
		return state;
	}

	std::shared_ptr<StateNode> get_parent() {
		return parent;
	}

	std::shared_ptr<Player> get_move_chooser() {
		return move_chooser;
	}

	std::vector<std::shared_ptr<StateNode>>& get_children() {
		return children;
	}

	int get_made_move() {
		return made_move;
	}

	int get_quality_from_perspective(std::shared_ptr<Player> player) {
		return state.get_quality(player);
	}


};

int StateNode::tree_depth = 5;