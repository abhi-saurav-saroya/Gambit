#include "pieces/knight.hpp"

std::vector<std::pair<int,int>> Knight::getLegalMoves(const std::vector<std::vector<std::string>>& grid, int row, int col) {
    std::vector<std::pair<int,int>> moves;

    std::string piece = grid[row][col];

    if (piece != "WhiteKnight" && piece != "BlackKnight")
        return moves;

    // All 8 possible knight moves
    int dr[8] = { 2, 2, -2, -2, 1, 1, -1, -1 };
    int dc[8] = { 1, -1, 1, -1, 2, -2, 2, -2 };

    for (int i = 0; i < 8; i++) {
        int nr = row + dr[i];
        int nc = col + dc[i];

        // boundary check
        if (nr < 0 || nr >= 8 || nc < 0 || nc >= 8)
            continue;

        std::string target = grid[nr][nc];

        // can move if empty OR enemy piece
        if (target.empty() || target[0] != piece[0]) { // different color
            moves.push_back({nr, nc});
        }
    }

    return moves;
}