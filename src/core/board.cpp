#include "core/board.hpp"
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
    promotionPending = false;
    promotionRow = -1;
    promotionCol = -1;
    promotionIsWhite = false;
    whiteKingMoved = false;
    blackKingMoved = false;
    whiteLeftRookMoved = false;
    whiteRightRookMoved = false;
    blackLeftRookMoved = false;
    blackRightRookMoved = false;
    enPassantAvailable = false;
    enPassantRow = -1;
    enPassantCol = -1;
    lastFromRow = -1;
    lastFromCol = -1;
    lastToRow = -1;
    lastToCol = -1;
    gameOverReason = "";

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
    lastFromRow = fromRow;
    lastFromCol = fromCol;
    lastToRow = toRow;
    lastToCol = toCol;

    bool oldEnPassantAvailable = enPassantAvailable;
    int oldEnPassantRow = enPassantRow;
    int oldEnPassantCol = enPassantCol;

    enPassantAvailable = false;
    enPassantRow = -1;
    enPassantCol = -1;

    std::string piece = grid[fromRow][fromCol];
    bool capture = !grid[toRow][toCol].empty();

    std::string moveText;
    if (capture) {
        moveText =
            getPieceName(piece)
            + ": "
            + squareToNotation(fromRow, fromCol)
            + " x "
            + squareToNotation(toRow, toCol);
    }
    else {
        moveText =
            getPieceName(piece)
            + ": "
            + squareToNotation(fromRow, fromCol)
            + " -> "
            + squareToNotation(toRow, toCol);
    }

    std::string capturedPiece = grid[toRow][toCol];
    if (!capturedPiece.empty()) {
        bool movingWhite = (piece[0] == 'W');
        if (movingWhite)
            whiteCaptures.push_back(capturedPiece);
        else
            blackCaptures.push_back(capturedPiece);
    }

    grid[toRow][toCol] = piece;
    grid[fromRow][fromCol] = "";

    // WHITE EN PASSANT
    if (piece == "WhitePawn" && oldEnPassantAvailable && toRow == oldEnPassantRow && toCol == oldEnPassantCol) {
        grid[toRow + 1][toCol] = "";
    }

    // BLACK EN PASSANT
    if (piece == "BlackPawn" && oldEnPassantAvailable && toRow == oldEnPassantRow && toCol == oldEnPassantCol) {
        grid[toRow - 1][toCol] = "";
    }

    // WHITE KINGSIDE CASTLE
    if (piece == "WhiteKing" && fromRow == 7 && fromCol == 4 && toRow == 7 && toCol == 6) {
        grid[7][5] = grid[7][7];
        grid[7][7] = "";
    }

    // WHITE QUEENSIDE CASTLE
    if (piece == "WhiteKing" && fromRow == 7 && fromCol == 4 && toRow == 7 && toCol == 2) {
        grid[7][3] = grid[7][0];
        grid[7][0] = "";
    }

    // BLACK KINGSIDE CASTLE
    if (piece == "BlackKing" && fromRow == 0 && fromCol == 4 && toRow == 0 && toCol == 6) {
        grid[0][5] = grid[0][7];
        grid[0][7] = "";
    }

    // BLACK QUEENSIDE CASTLE
    if (piece == "BlackKing" && fromRow == 0 && fromCol == 4 && toRow == 0 && toCol == 2) {
        grid[0][3] = grid[0][0];
        grid[0][0] = "";
    }

    if (piece == "BlackKing")
        blackKingMoved = true;
    if(piece == "WhiteKing")
        whiteKingMoved = true;

    if (piece == "BlackRook") {
        if (fromRow == 0 && fromCol == 0)
            blackLeftRookMoved = true;
        if (fromRow == 0 && fromCol == 7)
            blackRightRookMoved = true;
    }

    if (piece == "WhiteRook") {
        if (fromRow == 7 && fromCol == 0)
            whiteLeftRookMoved = true;
        if (fromRow == 7 && fromCol == 7)
            whiteRightRookMoved = true;
    }

    if(piece == "WhitePawn") {
        if(fromRow == 6 && toRow == 4) {
            enPassantAvailable = true;
            enPassantRow = 5;
            enPassantCol = fromCol;
        }
    }

    if(piece == "BlackPawn") {
        if(fromRow == 1 && toRow == 3) {
            enPassantAvailable = true;
            enPassantRow = 2;
            enPassantCol = fromCol;
        }
    }

    bool enemyWhite = !isWhiteTurn();
    if (isCheckmate(enemyWhite)) {
        moveText += " #";
    }
    else if (isKingInCheck(enemyWhite)) {
        moveText += " +";
    }
    moveHistory.push_back(moveText);
}

bool Board::canCastleKingside(bool white) const {
    if (white) {
        if (whiteKingMoved)
            return false;
        if (whiteRightRookMoved)
            return false;
        if (!grid[7][5].empty())
            return false;
        if (!grid[7][6].empty())
            return false;
        if (isSquareUnderAttack(7, 4, false))
            return false;
        if (isSquareUnderAttack(7, 5, false))
            return false;
        if (isSquareUnderAttack(7, 6, false))
            return false;
        return true;
    }

    else {
        if (blackKingMoved)
            return false;
        if (blackRightRookMoved)
            return false;
        if (!grid[0][5].empty())
            return false;
        if (!grid[0][6].empty())
            return false;
        if (isSquareUnderAttack(0, 4, true))
            return false;
        if (isSquareUnderAttack(0, 5, true))
            return false;
        if (isSquareUnderAttack(0, 6, true))
            return false;
        return true;
    }
}

bool Board::canCastleQueenside(bool white) const {
    if (white) {
        if (whiteKingMoved)
            return false;
        if (whiteLeftRookMoved)
            return false;
        if (!grid[7][1].empty())
            return false;
        if (!grid[7][2].empty())
            return false;
        if (!grid[7][3].empty())
            return false;
        if (isSquareUnderAttack(7, 4, false))
            return false;
        if (isSquareUnderAttack(7, 3, false))
            return false;
        if (isSquareUnderAttack(7, 2, false))
            return false;
        return true;
    }

    else {
        if (blackKingMoved)
            return false;
        if (blackLeftRookMoved)
            return false;
        if (!grid[0][1].empty())
            return false;
        if (!grid[0][2].empty())
            return false;
        if (!grid[0][3].empty())
            return false;
        if (isSquareUnderAttack(0, 4, true))
            return false;
        if (isSquareUnderAttack(0, 3, true))
            return false;
        if (isSquareUnderAttack(0, 2, true))
            return false;
        return true;
    }
}

std::vector<std::pair<int, int>> Board::getLegalMoves(int row, int col) const {
    std::string piece = grid[row][col];

    if (piece == "WhitePawn" || piece == "BlackPawn") {
        auto moves = Pawn::getLegalMoves(grid, row, col);

        if (enPassantAvailable) {

            if (piece == "WhitePawn") {
                if (row == 3 && ::abs(col - enPassantCol) == 1 && enPassantRow == 2) {
                    moves.push_back({
                        enPassantRow,
                        enPassantCol
                    });
                }
            }

            else {
                if (row == 4 && std::abs(col - enPassantCol) == 1 && enPassantRow == 5) {
                    moves.push_back({
                        enPassantRow,
                        enPassantCol
                    });
                }
            }
        }

        return moves;
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
        auto moves = King::getLegalMoves(grid, row, col);

        if (piece == "WhiteKing") {
            if (canCastleKingside(true))
                moves.push_back({7, 6});
            if (canCastleQueenside(true))
                moves.push_back({7, 2});
        }

        else {
            if (canCastleKingside(false))
                moves.push_back({0, 6});
            if (canCastleQueenside(false))
                moves.push_back({0, 2});
        }

        return moves;
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

void Board::selectPiece(int row, int col) {
    selectSquare(row, col);
    auto pseudoMoves = getLegalMoves(row, col);
    std::vector<std::pair<int, int>> legalMoves;

    for (auto [r, c] : pseudoMoves) {
        if (isLegalMove(row, col, r, c)) {
            legalMoves.push_back({r, c});
        }
    }

    setLegalMoves(legalMoves);
}

bool Board::canSelectPiece(int row, int col) const {
    std::string piece = grid[row][col];

    // empty square
    if (piece.empty()) {
        return false;
    }

    bool isWhitePiece = (piece[0] == 'W');

    return whiteTurn == isWhitePiece;
}

void Board::checkPromotion() {
    for (int col = 0; col < 8; col++) {

        if (grid[0][col] == "WhitePawn") {
            promotionPending = true;
            promotionRow = 0;
            promotionCol = col;
            promotionIsWhite = true;
            return;
        }

        if (grid[7][col] == "BlackPawn") {
            promotionPending = true;
            promotionRow = 7;
            promotionCol = col;
            promotionIsWhite = false;
            return;
        }
    }
}

bool Board::isPromotionPending() const {
    return promotionPending;
}

bool Board::isPromotionWhite() const {
    return promotionIsWhite;
}

void Board::promoteTo(const std::string& pieceName) {
    grid[promotionRow][promotionCol] = pieceName;

    promotionPending = false;
    promotionRow = -1;
    promotionCol = -1;
}

bool Board::isStalemate(bool white) {
    if (isKingInCheck(white)) {
        return false;
    }

    // Search every piece
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

std::pair<int,int> Board::getLastMoveFrom() const {
    return {lastFromRow, lastFromCol};
}

std::pair<int,int> Board::getLastMoveTo() const {
    return {lastToRow, lastToCol};
}

const std::vector<std::string>& Board::getWhiteCaptures() const {
    return whiteCaptures;
}

const std::vector<std::string>& Board::getBlackCaptures() const {
    return blackCaptures;
}

const std::vector<std::string>& Board::getMoveHistory() const {
    return moveHistory;
}

std::string Board::squareToNotation(int row, int col) const {
    char file = 'a' + col;
    char rank = '8' - row;

    return std::string(1, file) + std::string(1, rank);
}

std::string Board::getPieceName(const std::string& piece) const {
    if (piece.find("Pawn") != std::string::npos)
        return "Pawn";

    if (piece.find("Knight") != std::string::npos)
        return "Knight";

    if (piece.find("Bishop") != std::string::npos)
        return "Bishop";

    if (piece.find("Rook") != std::string::npos)
        return "Rook";

    if (piece.find("Queen") != std::string::npos)
        return "Queen";

    if (piece.find("King") != std::string::npos)
        return "King";

    return "Unknown";
}

void Board::setGameOver(const std::string& winnerName, const std::string& reason) {
    gameOver = true;
    winner = winnerName;
    gameOverReason = reason;
}

std::string Board::getGameOverReason() const {
    return gameOverReason;
}