#include "raylib.h"
//#include "Game.h"
#include "screens/AppContext.h"
#include "screens/MainMenuScreen.h"

int main()
{

    AppContext context;
    MainMenuScreen mainMenu(context);

    InitWindow(
    context.screenWidth,
    context.screenHeight,
    "Mouse Lab"
    );
    //Game game;

    /*InitWindow(
        game.GetScreenWidth(),
        game.GetScreenHeight(),
        "Mouse Maze"
    );*/

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        //game.Update();

        mainMenu.Update();

        BeginDrawing();
        ClearBackground(RAYWHITE);

        //game.Draw();
        mainMenu.Draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}