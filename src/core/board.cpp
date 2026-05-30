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
    gameOver = false;
    winner = "";

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

bool Board::isSquareUnderAttack(int row, int col, bool byWhite) const {
    // loop entire board
    for (int r = 0; r < 8; r++) {

        for (int c = 0; c < 8; c++) {

            std::string piece = grid[r][c];

            // empty square
            if (piece.empty()) {
                continue;
            }

            bool isWhitePiece =
                (piece[0] == 'W');

            // wrong color
            if (isWhitePiece != byWhite) {
                continue;
            }

            // get legal moves
            auto moves =
                getLegalMoves(r, c);

            // does any move attack target square?
            for (const auto& move : moves) {
                if (move.first == row &&
                    move.second == col)
                {
                    return true;
                }
            }
        }
    }

    return false;
}

std::pair<int,int> Board::findKing(bool white) const {

    std::string targetKing;

    if (white) {
        targetKing = "WhiteKing";
    }
    else {
        targetKing = "BlackKing";
    }

    // scan board
    for (int row = 0; row < 8; row++) {

        for (int col = 0; col < 8; col++) {

            if (grid[row][col] == targetKing) {
                return {row, col};
            }
        }
    }

    // should never happen
    return {-1, -1};
}

bool Board::isKingInCheck(bool white) const {
    // locate king
    auto [kingRow, kingCol] = findKing(white);

    if (kingRow == -1 || kingCol == -1) {
        return false; // safety fallback
    }

    // check if enemy attacks that square
    bool enemyColor = !white;

    return isSquareUnderAttack(
        kingRow,
        kingCol,
        enemyColor
    );
}

MoveBackup Board::makeMove(int fr, int fc, int tr, int tc) {
    MoveBackup backup;
    backup.captured = grid[tr][tc];

    grid[tr][tc] = grid[fr][fc];
    grid[fr][fc] = "";

    return backup;
}

void Board::undoMove(int fr, int fc, int tr, int tc, const MoveBackup& backup) {
    grid[fr][fc] = grid[tr][tc];
    grid[tr][tc] = backup.captured;
}

bool Board::isLegalMove(int fr, int fc, int tr, int tc) {
    std::string piece = grid[fr][fc];

    if (piece.empty()) return false;

    // 1. basic rule check
    auto moves = getLegalMoves(fr, fc);

    bool found = false;
    for (auto &m : moves)
        if (m.first == tr && m.second == tc)
            found = true;

    if (!found) return false;

    // 2. simulate move
    MoveBackup backup = makeMove(fr, fc, tr, tc);

    bool isWhite = (piece[0] == 'W');

    bool inCheck = isKingInCheck(isWhite);

    // 3. undo move
    undoMove(fr, fc, tr, tc, backup);

    // 4. result
    return !inCheck;
}

bool Board::isCheckmate(bool white) {
    // King must be in check first
    if (!isKingInCheck(white)) {
        return false;
    }

    // Search every piece of this color
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            std::string piece = grid[row][col];

            if (piece.empty()) {
                continue;
            }

            bool isWhitePiece = (piece[0] == 'W');

            if (isWhitePiece != white) {
                continue;
            }

            auto moves = getLegalMoves(row, col);

            for (auto [toRow, toCol] : moves) {
                if (isLegalMove(row, col, toRow, toCol)) {
                    return false;
                }
            }
        }
    }

    return true;
}

bool Board::isGameOver() const {
    return gameOver;
}

void Board::setGameOver(const std::string& winnerName) {
    gameOver = true;
    winner = winnerName;
}

std::string Board::getWinner() const {
    return winner;
}

void Board::resetGame() {
    *this = Board();
}