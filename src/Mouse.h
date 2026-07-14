#pragma once

#include "GridTypes.h"

class Mouse {
public:
    explicit Mouse(Cell startCell); //

    Cell GetCell() const;
    void MoveTo(Cell targetCell);

private:
    Cell cell;
};