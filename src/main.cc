#include <iostream>
#include <exception>
#include "board.hh"
#include "given/listener.hh"
#include <boost/program_options.hpp>
#include <dlfcn.h>

constexpr char init_setup[] = \
                            "RNBQKBNR/PPPPPPPP/8/8/8/8/pppppppp/rnbqkbnr";

namespace po = boost::program_options;

int main (int argc, char *argv[])
{
    po::options_description desc ("Options");
    desc.add_options()
        ("help,h", "List of possible commands")
        ("pgn", po::value<std::string>(), "Pgn option")
        ("listeners,l", po::value<std::string>() , "Path to listener plugins")
        ("perft", po::value<std::string>(), "path to perft file");
    
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
            std::cout << "FIXME\n";
        }
        else if(vm.count("listeners"))
        {
            std::cout << "FIXME\n";
        }
        else if(vm.count("perft"))
        {
            std::cout << "FIXME\n";
        }
        else
        {
            board::ChessBoard game(init_setup);
            void *handle = dlopen("../src/given/tests/libbasic-output.so", RTLD_LAZY);
            void * create = dlsym(handle, "listener_create");
                listener::Listener *lis = reinterpret_cast<listener::Listener*(*)()>(create)();
            lis->register_board(game);
            game.dump_board();
            dlclose(handle);

        }
    }
    catch(std::exception& e)
    {
        std::cout << e.what() << "\n";
    }
}

