#include <iostream>
#include <exception>
#include <boost/program_options.hpp>
#include <dlfcn.h>
#include <vector>
#include "board.hh"
#include "given/listener.hh"
#include "tools.hh"
#include "parsing.hh"

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
            auto tmp = create_chessboard_pgn(vm["pgn"].as<std::string>());
            if(tmp != std::nullopt)
            {
                auto game=tmp.value();
                game.dump_board();
            }
        }
        else if(vm.count("listeners"))
        {
            std::cout << "FIXME\n";
        }
        else if(vm.count("perft"))
        {
            auto tmp = create_chessboard_perft(vm["perft"].as<std::string>());
            if(tmp != std::nullopt)
            {
                auto game=tmp.value();
                game.dump_board();
            }
        }
        else
        {
            board::ChessBoard game(init_setup);
            void *handle = dlopen("../src/given/tests/libbasic-output.so", RTLD_LAZY);
            void * create = dlsym(handle, "listener_create");
            listener::Listener *lis = reinterpret_cast<listener::Listener*(*)()>(create)();
            lis->register_board(game);
            free(lis);
            game.dump_board();
            game.possible_moves();
            tools::dump_board_from_fen(init_setup);
            dlclose(handle);

        }
    }
    catch(std::exception& e)
    {
        std::cout << e.what() << "\n";
    }
}

