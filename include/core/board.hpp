#pragma once
#include <vector>
#include <string>

class Board {
    public:
        Board();
    
        const std::vector<std::vector<std::string>>& getGrid() const;
    
        void selectSquare(int row, int col);
        void clearSelection();
    
        bool hasSelection() const;
        std::pair<int,int> getSelection() const;

        void movePiece(int fromRow, int fromCol, int toRow, int toCol);

        std::vector<std::pair<int, int>> getLegalMoves(int row, int col) const;
        bool isLegalMove(int fromRow, int fromCol, int toRow, int toCol) const;
        void setLegalMoves(const std::vector<std::pair<int,int>>& moves);
        const std::vector<std::pair<int,int>>& getLegalMovesList() const;
        void clearLegalMoves();

        bool isWhiteTurn() const;
        void switchTurn();
        bool isCurrentPlayersPiece(int row, int col) const;
    
    private:
        std::vector<std::vector<std::string>> grid;
        std::vector<std::pair<int,int>> legalMoves;
    
        int selectedRow;
        int selectedCol;
        bool whiteTurn;
};