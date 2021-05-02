#pragma once

#include "Player.h"
#include <limits>
class AI_Player : public Player {
private:

public:

	AI_Player(std::string name) : Player(name) {

	}

	int get_move(std::shared_ptr<Board> board, std::shared_ptr<Player> player) override {

		auto possible_moves = board->get_possible_moves(player);
		auto move_value = std::make_pair(possible_moves[0], std::numeric_limits<int>::min());
		for (int move : possible_moves) {
			auto temp_move_value = std::make_pair(move, get_min(*board, move, player, 6, false));
			if (temp_move_value.second > move_value.second)
				move_value = temp_move_value;
		}
		int move = move_value.first;
		std::cout << std::endl <<this->get_name() <<" will play move: "<<move<<std::endl<<": ";
		std::cin.get();
		return move;
	}

	int get_max(Board board, int move_to_perform, std::shared_ptr<Player> move_performer, int how_deep, bool is_dry_move) {
		
		--how_deep;

		
		bool do_dry_move = false;

		//board has now desirable state
		if(!is_dry_move)
			do_dry_move = board.make_move(move_to_perform, move_performer);

		//next move performer is opposite player
		move_performer = board.get_opposite_player(move_performer);

		if (how_deep <= 0)
			return board.get_quality(this->get_name());
		
		
		
		int move_value = std::numeric_limits<int>::min();
		for (int move : board.get_possible_moves(move_performer)) {
			int temp_value = get_min(board, move, move_performer, how_deep,do_dry_move);
			if (move_value < temp_value)
				move_value = temp_value;
		}

		return move_value;
	}

	int get_min(Board board, int move_to_perform, std::shared_ptr<Player> move_performer, int how_deep, bool is_dry_move) {
		--how_deep;


		bool do_dry_move = false;

		//board has now desirable state
		if (!is_dry_move)
			do_dry_move = board.make_move(move_to_perform, move_performer);

		//next move performer is opposite player
		move_performer = board.get_opposite_player(move_performer);

		if (how_deep <= 0)
			return board.get_quality(this->get_name());



		int move_value = std::numeric_limits<int>::max();
		for (int move : board.get_possible_moves(move_performer)) {
			int temp_value = get_min(board, move, move_performer, how_deep, do_dry_move);
			if (move_value > temp_value)
				move_value = temp_value;
		}

		return move_value;
	}

	~AI_Player()
	{

	}
};
