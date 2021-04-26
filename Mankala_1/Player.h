#pragma once

#include <string>
#include <memory>
#include <iostream>

class Board;

class Player {
private:
	std::string name;

public:

	Player(std::string name) {
		this->name = name;
	}

	Player() {

	}

	bool operator==(Player& other) {
		return other.name == this->name;
	}

	~Player()
	{

	}

	virtual int get_move(std::shared_ptr<Board> board, std::shared_ptr<Player> player) =0;

	std::string get_name() {
		return this->name;
	}

};
