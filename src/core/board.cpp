#include "core/Board.hpp"

Board::Board() {
    grid = {
        {"BlackRook","BlackKnight","BlackBishop","BlackQueen","BlackKing","BlackBishop","BlackKnight","BlackRook"},
        {"BlackPawn","BlackPawn","BlackPawn","BlackPawn","BlackPawn","BlackPawn","BlackPawn","BlackPawn"},
        {"","","","","","","",""},
        {"","","","","","","",""},
        {"","","","","","","",""},
        {"","","","","","","",""},
        {"WhitePawn","WhitePawn","WhitePawn","WhitePawn","WhitePawn","WhitePawn","WhitePawn","WhitePawn"},
        {"WhiteRook","WhiteKnight","WhiteBishop","WhiteQueen","WhiteKing","WhiteBishop","WhiteKnight","WhiteRook"}
    };
}

const std::vector<std::vector<std::string>>& Board::getGrid() const {
    return grid;
}