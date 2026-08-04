#include "screens/AppContext.h"
#include "screens/MainMenuScreen.h"
#include "screens/ProfileSetupScreen.h"

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
    ScreenType activeScreen;
};