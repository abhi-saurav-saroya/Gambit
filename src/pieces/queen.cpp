#include "pieces/queen.hpp"

std::vector<std::pair<int,int>> Queen::getLegalMoves(const std::vector<std::vector<std::string>>& grid, int row, int col) {
    std::vector<std::pair<int,int>> moves;

    std::string piece = grid[row][col];

    if (piece != "WhiteQueen" && piece != "BlackQueen") {
        return moves;
    }

    // queen directions
    int dr[8] = {1, -1, 0, 0, 1, 1, -1, -1};
    int dc[8] = {0, 0, 1, -1, 1, -1, 1, -1};

    // try all 4 directions
    for (int dir = 0; dir < 8; dir++) {
        int nr = row + dr[dir];
        int nc = col + dc[dir];

        // keep moving until blocked
        while (nr >= 0 && nr < 8 && nc >= 0 && nc < 8) {
            std::string target = grid[nr][nc];

            // empty square
            if (target.empty()) {
                moves.push_back({nr, nc});
            }

            // enemy piece
            else if (target[0] != piece[0]) {
                moves.push_back({nr, nc});
                break;
            }

            // friendly piece
            else {
                break;
            }

            nr += dr[dir];
            nc += dc[dir];
        }
    }

    return moves;
}