#pragma once

#include "../PlayerProfile.h"

struct AppContext {
    PlayerProfile profile;
    int screenWidth = 960;
    int screenHeight = 540;
};