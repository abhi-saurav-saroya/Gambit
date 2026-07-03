#include "pieces/rook.hpp"
#include "pieces/move_gen.hpp"

std::vector<std::pair<int,int>> Rook::getLegalMoves(const std::vector<std::vector<std::string>>& grid, int row, int col) {
    const std::string& piece = grid[row][col];

    if (piece != "WhiteRook" && piece != "BlackRook") {
        return {};
    }

    // rook directions
    static const Moves::Offsets dirs = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };

    return Moves::sliding(grid, row, col, dirs);
}
