#include "core/Board.hpp"
#include "pieces/pawn.hpp"
#include "pieces/knight.hpp"
#include "pieces/rook.hpp"
#include "pieces/bishop.hpp"
#include "pieces/queen.hpp"
#include "pieces/king.hpp"

Board::Board() {
    selectedRow = -1;
    selectedCol = -1;
    whiteTurn = true;

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

std::vector<std::pair<int, int>> Board::getLegalMoves(int row, int col) const {
    std::string piece = grid[row][col];

    if (piece == "WhitePawn" || piece == "BlackPawn") {
        return Pawn::getLegalMoves(grid, row, col);
    }

    if (piece == "WhiteKnight" || piece == "BlackKnight") {
        return Knight::getLegalMoves(grid, row, col);
    }

    if (piece == "WhiteRook" || piece == "BlackRook") {
        return Rook::getLegalMoves(grid, row, col);
    }

    if (piece == "WhiteBishop" || piece == "BlackBishop") {
        return Bishop::getLegalMoves(grid, row, col);
    }

    if (piece == "WhiteQueen" || piece == "BlackQueen") {
        return Queen::getLegalMoves(grid, row, col);
    }

    if (piece == "WhiteKing" || piece == "BlackKing") {
        return King::getLegalMoves(grid, row, col);
    }

    return {};
}

bool Board::isLegalMove(int fromRow, int fromCol, int toRow, int toCol) const {
    auto legalMoves = getLegalMoves(fromRow, fromCol);

    for (const auto& move : legalMoves) {
        if (move.first == toRow && move.second == toCol) {
            return true;
        }
    }

    return false;
}

bool Board::isWhiteTurn() const {
    return whiteTurn;
}

void Board::switchTurn() {
    whiteTurn = !whiteTurn;
}

bool Board::isCurrentPlayersPiece(int row, int col) const {
    std::string piece = grid[row][col];

    if (piece.empty())
        return false;

    // White turn
    if (whiteTurn) {
        return piece[0] == 'W';
    }

    // Black turn
    return piece[0] == 'B';
}

void Board::setLegalMoves(const std::vector<std::pair<int,int>>& moves) {
    legalMoves = moves;
}

const std::vector<std::pair<int,int>>& Board::getLegalMovesList() const {
    return legalMoves;
}

void Board::clearLegalMoves() {
    legalMoves.clear();
}