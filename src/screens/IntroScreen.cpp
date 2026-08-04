#include "IntroScreen.h"

IntroScreen::IntroScreen(AppContext& context)
    : context(context)
{
}

std::optional<ScreenType> IntroScreen::Update()
{
    if (IsEnterButtonClicked()) {
        return ScreenType::LaboratoryHub;
    }

    return std::nullopt;
}

void IntroScreen::Draw() const
{
    ClearBackground(Color{18, 22, 28, 255});

    const char* title = "INTRO";
    int titleFontSize = 48;
    int titleWidth = MeasureText(title, titleFontSize);

    DrawText(
        title,
        (context.screenWidth - titleWidth) / 2,
        90,
        titleFontSize,
        RAYWHITE
    );

    const char* subtitle = "Welcome to Mouse Lab";
    int subtitleFontSize = 20;
    int subtitleWidth = MeasureText(subtitle, subtitleFontSize);

    DrawText(
        subtitle,
        (context.screenWidth - subtitleWidth) / 2,
        150,
        subtitleFontSize,
        LIGHTGRAY
    );

    Rectangle button = GetEnterButtonRect();
    bool hovered = CheckCollisionPointRec(GetMousePosition(), button);

    DrawRectangleRec(button, hovered ? LIGHTGRAY : GOLD);
    DrawRectangleLinesEx(button, 2.0f, DARKGRAY);

    const char* buttonText = "ENTER";
    int buttonFontSize = 24;
    int buttonTextWidth = MeasureText(buttonText, buttonFontSize);

    DrawText(
        buttonText,
        static_cast<int>(button.x + (button.width - buttonTextWidth) / 2),
        static_cast<int>(button.y + 13),
        buttonFontSize,
        DARKGRAY
    );
}

Rectangle IntroScreen::GetEnterButtonRect() const
{
    float width = 180.0f;
    float height = 56.0f;

    return {
        (context.screenWidth - width) / 2.0f,
        240.0f,
        width,
        height
    };
}

bool IntroScreen::IsEnterButtonClicked() const
{
    Rectangle button = GetEnterButtonRect();

    return CheckCollisionPointRec(GetMousePosition(), button)
        && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}