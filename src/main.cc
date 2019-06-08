#include <iostream>
#include <exception>
#include <boost/program_options.hpp>
#include <vector>
#include "board.hh"
#include "given/listener.hh"
#include "tools.hh"
#include "parsing.hh"
#include "perft.hh"
#include "game.hh"

constexpr char init_setup[] = \
                            "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR";

namespace po = boost::program_options;

int main (int argc, char *argv[])
{
    po::options_description desc ("Options");
    desc.add_options()
        ("help,h", "List of possible commands")
        ("pgn", po::value<std::string>(), "Pgn option")
        ("listeners,l", po::value<std::string>()->required(),\
                        "Path to listener plugins")
        ("perft", po::value<std::string>()->required(),\
                        "path to perft file");
    po::variables_map vm;
    try
    {
        po::store(po::parse_command_line(argc, argv, desc),vm);
        if(vm.count("help"))
        {
            std::cout << desc;
        }
        else if(vm.count("pgn"))
        {
            auto list = pgn_parser::parse_pgn(vm["pgn"].as<std::string>());
            board::ChessBoard game(init_setup);
            gameloop::gameloop(game, list);
        }
        else if(vm.count("listeners"))
        {
            std::cout << "FIXME\n";
        }
        else if(vm.count("perft"))
        {
            auto tmp = create_chessboard_perft(vm["perft"].as<std::string>());
            std::cout << "perft " << tmp << "\n";
        }
        else
        {
            ai::engine();
        }
    }
    catch(std::exception& e)
    {
        std::cout << e.what() << "\n";
    }
}

