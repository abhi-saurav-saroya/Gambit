#include "pieces/move_gen.hpp"

std::vector<std::pair<int, int>> Moves::sliding(const Grid& grid, int row, int col,
                                                const Offsets& dirs) {
    std::vector<std::pair<int, int>> moves;

    const std::string& piece = grid[row][col];

    for (const auto& d : dirs) {
        int nr = row + d.first;
        int nc = col + d.second;

        // keep moving until blocked
        while (nr >= 0 && nr < 8 && nc >= 0 && nc < 8) {
            const std::string& target = grid[nr][nc];

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

            nr += d.first;
            nc += d.second;
        }
    }

    return moves;
}

std::vector<std::pair<int, int>> Moves::stepping(const Grid& grid, int row, int col,
                                                 const Offsets& offsets) {
    std::vector<std::pair<int, int>> moves;

    const std::string& piece = grid[row][col];

    for (const auto& o : offsets) {
        int nr = row + o.first;
        int nc = col + o.second;

        // boundary check
        if (nr < 0 || nr >= 8 || nc < 0 || nc >= 8) {
            continue;
        }

        const std::string& target = grid[nr][nc];

        // empty square OR enemy piece
        if (target.empty() || target[0] != piece[0]) {
            moves.push_back({nr, nc});
        }
    }

    return moves;
}
