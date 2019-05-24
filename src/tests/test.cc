#include "knighttest.hh"
#include "bishoptest.hh"
#include "rooktest.hh"
#include "kingtest.hh"
#include "pawntest.hh"
#include "specialtest.hh"
#include "queentest.hh"

int main (int argc, char *argv[])
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
