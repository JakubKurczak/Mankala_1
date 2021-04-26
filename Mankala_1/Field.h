#pragma once

#include <memory>
#include "Board.h"

class Field {
private:
	std::shared_ptr<Player> owner;
	int value;
	bool is_well;
	int index;
	std::shared_ptr<Field> next;

public:

	Field(std::shared_ptr<Player> owner, int value, int index) : owner{ owner }, value{ value }, is_well{ false }, index{ index }{

	}

	Field(std::shared_ptr<Player> owner, int value, bool is_well, int index) : owner{ owner }, value{ value }, is_well{ is_well }, index{ index }{

	}

	Field(Field& other) : owner{ other.owner }, value{ other.value }, index{ other.index }, is_well{other.is_well}
	{

	}

	~Field()
	{

	}

	bool operator==(Field& other) {
		return other.owner == this->owner && other.index == this->index;
	}


	void set_next(std::shared_ptr<Field> next) {
		this->next = next;
	}

	std::shared_ptr<Field> get_next() {
		return this->next;
	}

	int get_index() {
		return this->index;
	}

	std::shared_ptr<Player> get_owner() {
		return this->owner;
	}

	int get_value() {
		return this->value;
	}

	void set_value(int v) {
		this->value = v;
	}

	bool get_is_well() {
		return this->is_well;
	}
};
