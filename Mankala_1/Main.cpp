#include <iostream>
#include "ConcretePlayer.h"
#include "Board.h"

constexpr auto DEBUG_MODE = true;

void draw_board() {
    std::cout << "           [6]   [5]   [4]   [3]   [2]   [1]   " << std::endl;
    std::cout << "            4     4     4     4     4     4   " << std::endl;
    std::cout << "    0                                            0" << std::endl;
    std::cout << "[N well]                                      [S well]" << std::endl;
    std::cout << "            4     4     4     4     4     4   " << std::endl;
    std::cout << "           [1]   [2]   [3]   [4]   [5]   [6]   " << std::endl;
}

void player_vs_player() {
    std::string players[] = { "player_1","player_2" };
    std::string current_player = "player_1";
    char choice;

    std::system("cls");
    draw_board();
    std::cout << current_player << ": ";
    std::cin >> choice;
}

void player_vs_ai() {

}

void ai_vs_ai() {

}

void game(std::shared_ptr<Player> player_1, std::shared_ptr<Player> player_2) {

    std::shared_ptr<Player> players[] = { player_1, player_2 };
    std::shared_ptr<Player> current_player = player_1;
    std::shared_ptr<Board> board = std::make_shared<Board>(player_1, player_2);
    std::system("cls");
    while (board->has_move(current_player)) {

        board->show_board();

        int move = current_player->get_move(board);

        bool next_move = board->make_move(move, current_player);

        if (!next_move)
            current_player = current_player == players[0] ? players[1] : players[0];
        std::system("cls");
    }

    board->add_remaining_points_to_player(current_player);
    std::shared_ptr<Player> winner = board->get_winner();
    std::cout << "Winner is: " + winner->get_name();
    int dummy;
    std::cin >> dummy;
}



int main()
{
    bool proceed = true;
    while (proceed) {

        std::system("cls");

        std::cout << "Welcome to Mankala!" << std::endl;
        std::cout << "Choose game mode:" << std::endl;
        std::cout << "[1] Player vs Player" << std::endl;
        std::cout << "[2] Player vs AI" << std::endl;
        std::cout << "[3] AI vs AI:" << std::endl;
        std::cout << "[4] Quit\nInput :";

        char choice;
        std::cin >> choice;
        if (isdigit(choice)) {
            switch (atoi(&choice)) {
            case 1:
                game(std::make_shared<ConcretePlayer>("jakub"), std::make_shared<ConcretePlayer>("maciek"));
                break;

            case 2:
                player_vs_ai();
                break;
            case 3:
                ai_vs_ai();
                break;
            case 4:
                proceed = false;
                break;
            default:
                break;
            }
        }
    }
}
