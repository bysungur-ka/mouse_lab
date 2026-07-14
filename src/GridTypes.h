#pragma once

struct Cell {
    int row;
    int col;
};

enum class Action {
    None,
    Up,
    Down,
    Left,
    Right
};