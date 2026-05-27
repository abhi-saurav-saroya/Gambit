#include "pieces/king.hpp"

std::vector<std::pair<int,int>> King::getLegalMoves(const std::vector<std::vector<std::string>>& grid, int row, int col) {
    std::vector<std::pair<int,int>> moves;

    std::string piece = grid[row][col];

    if (piece != "WhiteKing" && piece != "BlackKing") {
        return moves;
    }

    // all 8 king directions
    int dr[8] = {1, -1, 0, 0, 1, 1, -1, -1};
    int dc[8] = {0, 0, 1, -1, 1, -1, 1, -1};

    for (int i = 0; i < 8; i++) {
        int nr = row + dr[i];
        int nc = col + dc[i];

        // boundary check
        if (nr < 0 || nr >= 8 || nc < 0 || nc >= 8) {
            continue;
        }

        std::string target = grid[nr][nc];

        // empty square OR enemy piece
        if (target.empty() || target[0] != piece[0]) {
            moves.push_back({nr, nc});
        }
    }

    return moves;
}