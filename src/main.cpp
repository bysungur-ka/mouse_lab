#include "raylib.h"
#include "screens/AppContext.h"
#include "screens/MainMenuScreen.h"
#include "screens/ProfileSetupScreen.h"
#include <optional>

int main()
{

    AppContext context;
    MainMenuScreen mainMenu(context);
    ProfileSetupScreen profileSetup(context);
    ScreenType activeScreen = ScreenType::MainMenu;

    InitWindow(
        context.screenWidth,
        context.screenHeight,
        "Mouse Lab");

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        std::optional<ScreenType> nextScreen = std::nullopt;

        if (activeScreen == ScreenType::MainMenu)
        {
            nextScreen = mainMenu.Update();
        }

        if (activeScreen == ScreenType::ProfileSetup)
        {
            nextScreen = profileSetup.Update();
        }

        if (nextScreen.has_value()) {
            activeScreen = nextScreen.value();
        }

        BeginDrawing();

        if (activeScreen == ScreenType::MainMenu) mainMenu.Draw();
        if (activeScreen == ScreenType::ProfileSetup) profileSetup.Draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}