#pragma once

#include <string>
#include <memory>
#include "Player.h"
#include "Field.h"

class Board {
private:

	std::shared_ptr<Player> players[2];
	std::shared_ptr<Field> field;
public:

	Board(std::shared_ptr<Player> player_1, std::shared_ptr<Player> player_2) : players{ player_1,player_2 } {
		init_board();
	}

	~Board()
	{

	}

	//check for sure if its ok
	void init_board() {

		field = std::make_shared<Field>(players[0], 4, false, 1);
		std::shared_ptr<Field> previous = field;
		for (int ii = 2; ii < 7; ii++) {
			std::shared_ptr<Field> next = std::make_shared<Field>(players[0], 4, false, ii);
			previous->set_next(next);
			previous = next;
		}

		std::shared_ptr<Field> next = std::make_shared<Field>(players[0], 0, true, 0);
		previous->set_next(next);
		previous = next;

		for (int ii = 1; ii < 7; ii++) {
			std::shared_ptr<Field> next = std::make_shared<Field>(players[1], 4, false, ii);
			previous->set_next(next);
			previous = next;
		}

		next = std::make_shared<Field>(players[1], 0, true, 0);
		previous->set_next(next);
		previous = next;

		previous->set_next(field);
	}

	void show_board() {
		std::cout << "           [" << this->get_field(6, this->players[0])->get_index() << "]   [" << this->get_field(5, this->players[0])->get_index() << "]   [" << this->get_field(4, this->players[0])->get_index() << "]   [" << this->get_field(3, this->players[0])->get_index() << "]   [" << this->get_field(2, this->players[0])->get_index() << "]   [" << this->get_field(1, this->players[0])->get_index() << "]   " << std::endl;
		std::cout << "            " << this->get_field(6, this->players[0])->get_value() << "     " << this->get_field(5, this->players[0])->get_value() << "     " << this->get_field(4, this->players[0])->get_value() << "     " << this->get_field(3, this->players[0])->get_value() << "     " << this->get_field(2, this->players[0])->get_value() << "     " << this->get_field(1, this->players[0])->get_value() << "   " << std::endl;
		std::cout << "    " << this->get_field(0, this->players[0])->get_value() << "                                            " << this->get_field(0, this->players[1])->get_value() << "" << std::endl;
		std::cout << "["<<this->players[0]->get_name()<<"'s well]                                      ["<<this->players[1]->get_name()<<"'s well]" << std::endl;
		std::cout << "            " << this->get_field(1, this->players[1])->get_value() << "     " << this->get_field(2, this->players[1])->get_value() << "     " << this->get_field(3, this->players[1])->get_value() << "     " << this->get_field(4, this->players[1])->get_value() << "     " << this->get_field(5, this->players[1])->get_value() << "     " << this->get_field(6, this->players[1])->get_value() << "   " << std::endl;
		std::cout << "           [" << this->get_field(1, this->players[1])->get_index() << "]   [" << this->get_field(2, this->players[1])->get_index() << "]   [" << this->get_field(3, this->players[1])->get_index() << "]   [" << this->get_field(4, this->players[1])->get_index() << "]   [" << this->get_field(5, this->players[1])->get_index() << "]   [" << this->get_field(6, this->players[1])->get_index() << "]   " << std::endl;
	}

	std::shared_ptr<Field> get_field(int index, std::shared_ptr<Player> player) {
		std::shared_ptr<Field> next = this->field->get_next();

		if (field->get_owner() == player && field->get_index() == index) {
			return this->field;
		}

		while (next != this->field) {
			if (next->get_owner() == player && next->get_index() == index) {
				return next;
			}
			next = next->get_next();
		}
				
	}

	std::shared_ptr<Field> get_field(int index, Player* player) {
		std::shared_ptr<Field> next = this->field->get_next();

		if (field->get_owner().get() == player && field->get_index() == index) {
			return this->field;
		}

		while (next != this->field) {
			if (next->get_owner().get() == player && next->get_index() == index) {
				return next;
			}
			next = next->get_next();
		}

		//return std::make_shared<Field>(nullptr);
	}

	bool make_move(int move, std::shared_ptr<Player> player) {
		std::shared_ptr<Field> start = this->get_field(move, player);

		int value = start->get_value();
		start->set_value(0);

		while (value != 0) {
			start = start->get_next();
			if (this->get_field(0, this->get_opposite_player(player)) != start) {
				start->set_value(start->get_value() + 1);
				value -= 1;
			}
		}

		if (start->get_value() == 1 && start->get_owner() == player && !start->get_is_well() && get_field(7- start->get_index(),this->get_opposite_player(start->get_owner()))->get_value()!=0) {
			this->bicie(start);
			return false;
		}

		return start == this->get_field(0, player);
	}

	void bicie(std::shared_ptr<Field> field) {

		int opposite_index = 7 - field->get_index();

		get_field(0,field->get_owner())->set_value(1 +  get_field(0, field->get_owner())->get_value() + this->get_field(opposite_index, this->get_opposite_player(field->get_owner()))->get_value());
		field->set_value(0);
		this->get_field(opposite_index, this->get_opposite_player(field->get_owner()))->set_value(0);

	}

	std::shared_ptr<Player> get_opposite_player(std::shared_ptr<Player> player) {
		return player == players[0] ? players[1] : players[0];
	}

	void add_remaining_points_to_player(std::shared_ptr<Player> player) {
		std::shared_ptr<Field> curr_field = this->field;
		std::shared_ptr<Field> players_well = this->get_field(0, player);

		if (curr_field->get_index() != 0 && curr_field->get_owner() != player) {
			players_well->set_value(curr_field->get_value() + players_well->get_value());
		}

		curr_field = curr_field->get_next();

		while (curr_field != this->field) {
			if (curr_field->get_index() != 0 && curr_field->get_owner() != player) {
				players_well->set_value(curr_field->get_value() + players_well->get_value());
			}

			curr_field = curr_field->get_next();

		}

	}

	bool is_legal_move(int move, Player* player) {
		if (move == 0)
			return false;
		else if (this->get_field(move, player)->get_value() == 0)
			return false;
		else
			return true;
	}

	bool has_move(std::shared_ptr<Player> player) {
		bool m = false;
		for (int ii = 1; ii < 7; ii++) {
			if (this->get_field(ii, player)->get_value() != 0)
				m = true;
		}
		return m;
	}

	std::shared_ptr<Player> get_winner() {
		
		if (this->get_field(0, players[0])->get_value() == this->get_field(0, players[1])->get_value()) {
			std::cout << "Draw!!!";
		}

		return this->get_field(0, players[0])->get_value() > this->get_field(0, players[1])->get_value() ? players[0] : players[1];
	}
};


