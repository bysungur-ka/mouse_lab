#pragma once

#include <string>

enum class AvatarType {
    FemaleLabAssistant,
    MaleLabAssistant
};

struct PlayerProfile {
    std::string name;
    AvatarType avatar = AvatarType::FemaleLabAssistant;
    bool introSeen = false;
};