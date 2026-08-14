#pragma once

#include "screens/AppContext.h"
#include "screens/MainMenuScreen.h"
#include "screens/ProfileSetupScreen.h"
#include "screens/IntroScreen.h"
#include "screens/LaboratoryHubScreen.h"
#include "screens/MazeRunScreen.h"


class GameApp
{
public:
    GameApp();
    void Update();
    void Draw() const;

    int GetScreenWidth() const;
    int GetScreenHeight() const;

private:
    AppContext context;
    MainMenuScreen mainMenu;
    ProfileSetupScreen profileSetup;
    IntroScreen intro;
    LaboratoryHubScreen laboratoryHub;
    MazeRunScreen mazeRun;
    ScreenType activeScreen;
};