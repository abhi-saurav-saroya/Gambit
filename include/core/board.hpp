#pragma once
#include <vector>
#include <string>

struct MoveBackup {
    std::string captured;
};

class Board {
    public:
        Board();
    
        const std::vector<std::vector<std::string>>& getGrid() const;
    
        void selectSquare(int row, int col);
        void clearSelection();
    
        bool hasSelection() const;
        std::pair<int,int> getSelection() const;
        void selectPiece(int row, int col);

        void movePiece(int fromRow, int fromCol, int toRow, int toCol);

        std::vector<std::pair<int, int>> getLegalMoves(int row, int col) const;
        void setLegalMoves(const std::vector<std::pair<int,int>>& moves);
        const std::vector<std::pair<int,int>>& getLegalMovesList() const;
        void clearLegalMoves();

        bool isWhiteTurn() const;
        void switchTurn();
        bool isCurrentPlayersPiece(int row, int col) const;

        bool isSquareUnderAttack(int row, int col, bool byWhite) const;
        std::pair<int,int> findKing(bool white) const;
        bool isKingInCheck(bool white) const;

        MoveBackup makeMove(int fr, int fc, int tr, int tc);
        void undoMove(int fr, int fc, int tr, int tc, const MoveBackup& backup);
        bool isLegalMove(int fr, int fc, int tr, int tc);

        bool isCheckmate(bool white);

        bool isGameOver() const;
        void setGameOver(const std::string& winnerName);
        std::string getWinner() const;
        void resetGame();
    
    private:
        std::vector<std::vector<std::string>> grid;
        std::vector<std::pair<int,int>> legalMoves;
    
        int selectedRow;
        int selectedCol;
        bool whiteTurn;
        bool gameOver;
        std::string winner;
};