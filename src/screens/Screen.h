#pragma once

#include <optional>
#include "ScreenType.h"

class Screen {
public:
    virtual ~Screen() = default;

    virtual std::optional<ScreenType> Update() = 0;
    virtual void Draw() const = 0;
};