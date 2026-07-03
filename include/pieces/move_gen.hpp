#pragma once

#include <vector>
#include <utility>
#include <string>

// Shared move-generation primitives for the pieces.
//
// Every piece previously carried its own copy of the same board-walking loop;
// the two shapes below are all that actually differ between them:
//   * sliding  — bishop / rook / queen: ray-cast along each direction until the
//                board edge, a friendly piece, or (inclusively) the first enemy.
//   * stepping — king / knight: a single hop per offset, taken when the target
//                square is empty or holds an enemy.
// A piece file now only declares its guard string and its offset table.
namespace Moves {
    using Grid = std::vector<std::vector<std::string>>;
    using Offsets = std::vector<std::pair<int, int>>;

    std::vector<std::pair<int, int>> sliding(const Grid& grid, int row, int col,
                                             const Offsets& dirs);

    std::vector<std::pair<int, int>> stepping(const Grid& grid, int row, int col,
                                              const Offsets& offsets);
}
