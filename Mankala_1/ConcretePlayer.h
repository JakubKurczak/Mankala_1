#pragma once

#include "Player.h"
#include "Board.h"
#include <string>
class ConcretePlayer : public Player {
public:


	ConcretePlayer(std::string name) : Player(name) {

	}

	int get_move(std::shared_ptr<Board> board) {
		while (true) {
			std::cout << this->get_name() << ": ";
			char choice;
			std::cin >> choice;

			if (std::isdigit(choice) && board->is_legal_move(std::atoi(&choice), this)) {
				return std::atoi(&choice);
			}

		}
	}

};