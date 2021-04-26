#pragma once
#include "Board.h"
#include <vector>


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

	//move chooser is for minmax
	//its person that will choose next move
	//but current state is made by opposite player
	StateNode(std::shared_ptr<StateNode> parent, Board& board, std::shared_ptr<Player> move_chooser, int chosen_move) : state(board), parent{ parent }, move_chooser{ move_chooser }, made_move{chosen_move}{
		another_move = this->state.make_move(chosen_move, this->state.get_opposite_player(move_chooser));
	}
	
	bool get_another_move() {
		return another_move;
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

	//this is very simple to be sure that everything else works properly
	int get_quality_from_perspective(std::shared_ptr<Player> player) {
		return state.get_quality(player) - state.get_quality(state.get_opposite_player(player));
	}


};

int StateNode::tree_depth = 5;