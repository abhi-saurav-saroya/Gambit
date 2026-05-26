#include "core/Board.hpp"

Board::Board() {
    selectedRow = -1;
    selectedCol = -1;

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

void Board::selectSquare(int row, int col) {
    selectedRow = row;
    selectedCol = col;
}

void Board::clearSelection() {
    selectedRow = -1;
    selectedCol = -1;
}

bool Board::hasSelection() const {
    return selectedRow != -1;
}

std::pair<int,int> Board::getSelection() const {
    return {selectedRow, selectedCol};
}

void Board::movePiece(int fromRow, int fromCol, int toRow, int toCol) {
    grid[toRow][toCol] = grid[fromRow][fromCol];
    grid[fromRow][fromCol] = "";
}