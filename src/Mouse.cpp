#include "Mouse.h"

Mouse::Mouse(Cell startCell)
    : cell(startCell)  //при создании Mouse сразу инициализировать поле cell значением startCell
{
}

Cell Mouse::GetCell() const
{
    return cell;
}

void Mouse::MoveTo(Cell targetCell)
{
    cell = targetCell;
}