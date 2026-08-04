#include "GameApp.h"

#include <optional>

GameApp::GameApp()
    : context(),
      mainMenu(context),
      profileSetup(context),
      intro(context),
      activeScreen(ScreenType::MainMenu)
{
}

void GameApp::Update()
{
    std::optional<ScreenType> nextScreen = std::nullopt;

    if (activeScreen == ScreenType::MainMenu) {
        nextScreen = mainMenu.Update();
    }
    else if (activeScreen == ScreenType::ProfileSetup) {
        nextScreen = profileSetup.Update();
    }
    else if (activeScreen == ScreenType::Intro) {
        nextScreen = intro.Update();
    }

    if (nextScreen.has_value()) {
        activeScreen = nextScreen.value();
    }
}

void GameApp::Draw() const
{
    if (activeScreen == ScreenType::MainMenu) {
        mainMenu.Draw();
    }
    else if (activeScreen == ScreenType::ProfileSetup) {
        profileSetup.Draw();
    }
    else if (activeScreen == ScreenType::Intro) {
        intro.Draw();
    }
}

int GameApp::GetScreenWidth() const
{
    return context.screenWidth;
}

int GameApp::GetScreenHeight() const
{
    return context.screenHeight;
}