#include "pieces/pawn.hpp"

std::vector<std::pair<int,int>> Pawn::getLegalMoves(const std::vector<std::vector<std::string>>& grid, int row, int col) {
    std::vector<std::pair<int,int>> moves;

    std::string piece = grid[row][col];

    if (piece == "WhitePawn") {
        // One square forward
        if (row - 1 >= 0 && grid[row - 1][col].empty()) {
            moves.push_back({row - 1, col});
        }
        // Two squares forward from start
        if (row == 6 && grid[row - 1][col].empty() && grid[row - 2][col].empty()) {
            moves.push_back({row - 2, col});
        }
    }

    else if (piece == "BlackPawn") {
        // One square forward
        if (row + 1 < 8 && grid[row + 1][col].empty()) {
            moves.push_back({row + 1, col});
        }
        // Two squares forward from start
        if (row == 1 && grid[row + 1][col].empty() && grid[row + 2][col].empty()) {
            moves.push_back({row + 2, col});
        }
    }

    // Diagonal captures
    int leftCol  = col - 1;
    int rightCol = col + 1;

    int nextRow;
    if (piece == "WhitePawn")
        nextRow = row - 1;
    else
        nextRow = row + 1;

    // capture left
    if (nextRow >= 0 && nextRow < 8 && leftCol >= 0) {
        std::string target = grid[nextRow][leftCol];
        // enemy piece exists
        if (!target.empty() &&
            target[0] != piece[0])
        {
            moves.push_back({nextRow, leftCol});
        }
    }

    // capture right
    if (nextRow >= 0 && nextRow < 8 && rightCol < 8) {
        std::string target = grid[nextRow][rightCol];
        // enemy piece exists
        if (!target.empty() && target[0] != piece[0]) {
            moves.push_back({nextRow, rightCol});
        }
    }

    return moves;
}