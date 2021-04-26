#pragma once
#include <memory>
#include <algorithm>
#include "StateNode.h"

class StateTree {
private:
	std::shared_ptr<StateNode> root;
	std::shared_ptr<Player> moving_player;

public:


	//smarter way would be probably lazy init
	StateTree(std::shared_ptr<Player> moving_player, std::shared_ptr<Board> board, int tree_depth) : moving_player{moving_player} {
		
		StateNode::tree_depth = tree_depth;
		
		start_making_tree(*board,moving_player, tree_depth);
	}

	void start_making_tree(Board& board, std::shared_ptr<Player> move_chooser, int tree_depth) {
		root = std::make_shared<StateNode>(board, move_chooser);
		for (int move : root->get_state().get_possible_moves(root->get_move_chooser())) {
			make_tree(root, root->get_state(), root->get_state().get_opposite_player(move_chooser), move,tree_depth);
		}
	}

	void make_tree(std::shared_ptr<StateNode> parent, Board& board, std::shared_ptr<Player> move_chooser, int chosen_move, int tree_depth) {
		std::shared_ptr<StateNode> curr_node = std::make_shared<StateNode>(parent, board,move_chooser,chosen_move);
		parent->add_child(curr_node);

		if (curr_node->get_another_move())
			move_chooser = curr_node->get_state().get_opposite_player(move_chooser);

		auto possible_moves = curr_node->get_state().get_possible_moves(move_chooser);
		if (tree_depth > 0) {			
			for (int move : possible_moves) {
				make_tree(curr_node, curr_node->get_state(), curr_node->get_state().get_opposite_player(curr_node->get_move_chooser()), move,tree_depth-1);
								
			}
		}
	}
	
	//MAKE SURE THIS IS OK
	int get_best_move() {
		auto best_outcome = minimax(root);
		while (best_outcome->get_parent() != root) {
			best_outcome = best_outcome->get_parent();
		}
		return best_outcome->get_made_move();
	}

	//gives us a node that is an outcome of best scenario
	virtual std::shared_ptr<StateNode> minimax(std::shared_ptr<StateNode> node) {
		std::vector<std::shared_ptr<StateNode>> game_play;
		if (node->get_children().size() == 0) {
			return node;
		}		

		for (auto node_child : node->get_children()) {
			game_play.push_back(minimax(node_child));			
		}
		if (node->get_move_chooser() == moving_player)
			std::sort(game_play.begin(), game_play.end(), [this](std::shared_ptr<StateNode> a, std::shared_ptr<StateNode> b) {return a->get_quality_from_perspective(this->moving_player) > b->get_quality_from_perspective(this->moving_player); });
		else
			std::sort(game_play.begin(), game_play.end(), [this](std::shared_ptr<StateNode> a, std::shared_ptr<StateNode> b) {return a->get_quality_from_perspective(this->moving_player) < b->get_quality_from_perspective(this->moving_player); });
		return game_play[0];
	}

	~StateTree()
	{

	}
};
