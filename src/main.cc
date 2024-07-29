/*
    main entry point for program, holds main game loop
*/
#include "subject.h"
#include "piece.h"
#include "gamemanager.h"
#include "blank.h"
#include "pawn.h"
#include "bishop.h"
#include "rook.h"
#include "knight.h"
#include "queen.h"
#include "king.h"
#include "observer.h"
#include "graphicdisplay.h"
#include "textdisplay.h"
#include "player.h"
#include "human.h"
#include "game.h"

#include <utility>
#include <memory>
#include <iostream>
#include <string>

int main(int arc, char **argv)
{
    bool setup = false;
    int white_score = 0;
    int black_score = 0;

    std::string inp;
    Board *head = nullptr;
    GameManager *gm = nullptr;
    Game *game = nullptr;
    Observer *txt = nullptr;
    Observer *graph = nullptr;

    std::cout << "Welcome to Chess - the CS246 orignal game" << std::endl;
    std::cout << "Use the command --help at any time to display your current options" << std::endl;
    while (std::cin >> inp)
    {
        if (inp == "game")
        {
            if (!setup)
            {
                std::cout << "The game must be setup before continuing." << std::endl;
            }
            else
            {
                char res = game->playGame();
                if (res == 'w')
                {
                    white_score++;
                }
                else if (res == 'b')
                {
                    black_score++;
                }
                delete game;
                setup = false;
                std::cout << "Setup another game to continue playing UwU" << std::endl;
            }
        }
        else if (inp == "setup")
        {
            head = new Blank{};
            gm = new GameManager{&head};
            game = new Game{&head, gm, nullptr, nullptr};
            game->setPlayer1(new Human{});
            game->setPlayer2(new Human{});
            txt = new TextDisplay{*gm, 8, 8, 8};
            gm->attach(txt);
            graph = new GraphicDisplay{*gm, 8, 8};
            gm->attach(graph);

            std::cin >> inp;
            if (inp == "default")
            {
                game->defaultSetup();
                setup = true;
            }
            else if (inp == "custom")
            {
                game->customSetup();
                setup = true;
            }
            else
            {
                std::cout << "Invalid command " << inp << " use --help for more options" << std::endl;
            }
        }
        else if (inp == "--help")
        {
            std::cout << "Commands:" << std::endl;
            std::cout << "- game <white-player> <black-player>" << std::endl;
            std::cout << "\twhere <white-player> or <black-player> can be <human> or <computer[x]>" << std::endl;
            std::cout << " - setup" << std::endl;
            std::cout << "\t followed by either <default> or <custom>" << std::endl;
        }
        else
        {
            std::cout << "Invalid Input " << inp << " use --help to display options" << std::endl;
            ;
        }
    }
    std::cout << "Final Score:" << std::endl;
    std::cout << "White: " << white_score << std::endl;
    std::cout << "Black: " << black_score << std::endl;
    return 0;
}
