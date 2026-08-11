#include <string>
#include "ProfileSetupScreen.h"

ProfileSetupScreen::ProfileSetupScreen(AppContext &context)
    : context(context)
{
    if (context.profile.name.empty())
    {
        context.profile.name = "Text here";
    }

    nameCursorPosition = context.profile.name.size();
}

std::optional<ScreenType> ProfileSetupScreen::Update()
{

    UpdateNameInput();

    UpdateAvatarSelection();

    if (IsContinueButtonClicked())
    {
        return ScreenType::Intro;
    }

    return std::nullopt;
}

void ProfileSetupScreen::Draw() const
{
    ClearBackground(Color{18, 22, 28, 255});

    DrawBadge();

    DrawAvatarCards();

    const char *title = "PROFILE SETUP";
    int titleFontSize = 48;
    int titleWidth = MeasureText(title, titleFontSize);

    DrawText(
        title,
        (context.screenWidth - titleWidth) / 2,
        90,
        titleFontSize,
        RAYWHITE);

    const char *subtitle = "Choose your laboratory avatar";
    int subtitleFontSize = 20;
    int subtitleWidth = MeasureText(subtitle, subtitleFontSize);

    DrawText(
        subtitle,
        (context.screenWidth - subtitleWidth) / 2,
        150,
        subtitleFontSize,
        LIGHTGRAY);

    Rectangle button = GetContinueButtonRect();
    bool hovered = CheckCollisionPointRec(GetMousePosition(), button);

    DrawRectangleRec(button, hovered ? LIGHTGRAY : GOLD);
    DrawRectangleLinesEx(button, 2.0f, DARKGRAY);

    const char *buttonText = "CONTINUE";
    int buttonFontSize = 24;
    int buttonTextWidth = MeasureText(buttonText, buttonFontSize);

    DrawText(
        buttonText,
        static_cast<int>(button.x + (button.width - buttonTextWidth) / 2),
        static_cast<int>(button.y + 13),
        buttonFontSize,
        DARKGRAY);
}

Rectangle ProfileSetupScreen::GetContinueButtonRect() const
{
    float width = 180.0f;
    float height = 56.0f;

    return {
        (context.screenWidth - width) / 2.0f,
        context.screenHeight - 1.5f * height,
        width,
        height};
}

bool ProfileSetupScreen::IsContinueButtonClicked() const
{
    Rectangle button = GetContinueButtonRect();

    return CheckCollisionPointRec(GetMousePosition(), button) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

void ProfileSetupScreen::UpdateNameInput()
{
    int key = GetCharPressed();

    while (key > 0)
    {
        if (key >= 32 && key <= 126 && context.profile.name.size() < 18)
        {
            context.profile.name.insert(
                context.profile.name.begin() + nameCursorPosition,
                static_cast<char>(key));

            nameCursorPosition++;
        }

        key = GetCharPressed();
    }

    float dt = GetFrameTime();

    if (IsKeyPressed(KEY_BACKSPACE) && nameCursorPosition > 0)
    {
        context.profile.name.erase(nameCursorPosition - 1, 1);
        nameCursorPosition--;
        backspaceRepeatTimer = 0.35f;
    }
    else if (IsKeyDown(KEY_BACKSPACE))
    {
        backspaceRepeatTimer -= dt;

        if (backspaceRepeatTimer <= 0.0f && nameCursorPosition > 0)
        {
            context.profile.name.erase(nameCursorPosition - 1, 1);
            nameCursorPosition--;
            backspaceRepeatTimer = 0.05f;
        }
    }
    else
    {
        backspaceRepeatTimer = 0.0f;
    }

    if (IsKeyPressed(KEY_LEFT) && nameCursorPosition > 0)
    {
        nameCursorPosition--;
    }

    if (IsKeyPressed(KEY_RIGHT) && nameCursorPosition < context.profile.name.size())
    {
        nameCursorPosition++;
    }
}

Rectangle ProfileSetupScreen::GetBadgeRect() const
{
    return {
        280.0f,
        200.0f,
        400.0f,
        250.0f};
}

Rectangle ProfileSetupScreen::GetNameInputRect() const
{
    Rectangle badge = GetBadgeRect();

    return {
        badge.x + 40.0f,
        badge.y + 90.0f,
        badge.width - 80.0f,
        42.0f};
}

void ProfileSetupScreen::DrawBadge() const
{
    Rectangle badge = GetBadgeRect();
    Rectangle nameInput = GetNameInputRect();

    DrawRectangleRec(badge, Color{235, 235, 225, 255});
    DrawRectangleLinesEx(badge, 3.0f, GOLD);

    DrawText("MOUSE LAB", static_cast<int>(badge.x + 30), static_cast<int>(badge.y + 25), 24, DARKGRAY);

    DrawText("NAME", static_cast<int>(nameInput.x), static_cast<int>(nameInput.y - 24), 16, DARKGRAY);
    DrawRectangleRec(nameInput, RAYWHITE);
    DrawRectangleLinesEx(nameInput, 2.0f, DARKGRAY);

    DrawText(
        context.profile.name.c_str(),
        static_cast<int>(nameInput.x + 10),
        static_cast<int>(nameInput.y + 10),
        20,
        DARKGRAY);

    std::string textBeforeCursor = context.profile.name.substr(0, nameCursorPosition);
    int textBeforeCursorWidth = MeasureText(textBeforeCursor.c_str(), 20);

    int cursorX = static_cast<int>(nameInput.x + 10 + textBeforeCursorWidth);
    int cursorY = static_cast<int>(nameInput.y + 9);

    bool showCursor = static_cast<int>(GetTime() * 2) % 2 == 0;

    if (showCursor)
    {
        DrawRectangle(cursorX, cursorY, 2, 24, DARKGRAY);
    }

    DrawText("POSITION", static_cast<int>(badge.x + 40), static_cast<int>(badge.y + 155), 16, DARKGRAY);
    DrawText("Laboratory Worker", static_cast<int>(badge.x + 40), static_cast<int>(badge.y + 180), 22, DARKGRAY);
}

Rectangle ProfileSetupScreen::GetFemaleAvatarRect() const
{
    Rectangle badge = GetBadgeRect();

    float width = 170.0f;
    float height = 250.0f;
    float gap = 30.0f;

    return {
        badge.x - gap - width,
        badge.y,
        width,
        height
    };
}

Rectangle ProfileSetupScreen::GetMaleAvatarRect() const
{
    Rectangle badge = GetBadgeRect();

    float width = 170.0f;
    float height = 250.0f;
    float gap = 30.0f;

    return {
        badge.x + badge.width + gap,
        badge.y,
        width,
        height
    };
}

void ProfileSetupScreen::UpdateAvatarSelection()
{
    Rectangle female = GetFemaleAvatarRect();
    Rectangle male = GetMaleAvatarRect();

    if (CheckCollisionPointRec(GetMousePosition(), female) &&
        IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        context.profile.avatar = AvatarType::FemaleLabAssistant;
    }

    if (CheckCollisionPointRec(GetMousePosition(), male) &&
        IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
    {
        context.profile.avatar = AvatarType::MaleLabAssistant;
    }
}

void ProfileSetupScreen::DrawAvatarCards() const
{
    Rectangle female = GetFemaleAvatarRect();
    Rectangle male = GetMaleAvatarRect();

    bool femaleSelected =
        context.profile.avatar == AvatarType::FemaleLabAssistant;

    bool maleSelected =
        context.profile.avatar == AvatarType::MaleLabAssistant;

    DrawRectangleRec(female, Color{235, 235, 225, 255});
    DrawRectangleLinesEx(
        female,
        femaleSelected ? 4.0f : 2.0f,
        femaleSelected ? GOLD : DARKGRAY
    );

    DrawText(
        "FEMALE",
        static_cast<int>(female.x + 42),
        static_cast<int>(female.y + 110),
        22,
        DARKGRAY
    );

    DrawRectangleRec(male, Color{235, 235, 225, 255});
    DrawRectangleLinesEx(
        male,
        maleSelected ? 4.0f : 2.0f,
        maleSelected ? GOLD : DARKGRAY
    );

    DrawText(
        "MALE",
        static_cast<int>(male.x + 55),
        static_cast<int>(male.y + 110),
        22,
        DARKGRAY
    );
}
