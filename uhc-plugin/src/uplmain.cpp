#include <string.h>
#include "UHCPlugin.h"

const int cDefaultIntValue = -1;
constexpr int cMaxNumPlayers = 9; // 8 actual players + Mother Nature
int gPlayerDifficulty[cMaxNumPlayers];

void clearPlayerDifficulties(void) {
    for(auto i = 0; i < cMaxNumPlayers; i++)
        gPlayerDifficulty[i] = -1;
}

void setPlayerDifficulty(int player, int difficulty) {
    if (player < 1 || player >= cMaxNumPlayers)
        return;
    gPlayerDifficulty[player] = difficulty;
}

int getPlayerDifficulty(int player) {
    int(*const aiGetWorldDifficulty)() = reinterpret_cast<int(*)()>(0x725b52);

    if (player < 1 || player >= cMaxNumPlayers)
        return aiGetWorldDifficulty();
    
    int difficulty = gPlayerDifficulty[player];
    return difficulty >= 0 ? difficulty : aiGetWorldDifficulty();
}

const char* getWorldDifficultyName(int difficulty) {
    switch(difficulty)
    {
        case 0: return "Level 0 (sandbox)";
        case 1: return "Level 1 (easy)";
        case 2: return "Level 2 (moderate)";
        case 3: return "Level 3 (hard)";
        case 4: return "Level 5 (expert)";
    }

    char digits[10] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'};
    char difficulty_name[255] = "Level ";
    char r_difficulty_level[10] = "";

    do {
        r_difficulty_level[strlen(r_difficulty_level)] = digits[difficulty % 10];
        difficulty /= 10;
    } while(difficulty);

    for(auto i = strlen(r_difficulty_level) - 1; i >= 0; i--) {
        difficulty_name[strlen(difficulty_name)] = r_difficulty_level[i];
    }

    difficulty_name[strlen(difficulty_name)] = '\0';

    return difficulty_name;
}

void CHEATCALL PLVL(void* playerData) {
    bool(*const kbIsPlayerValid)(int) = reinterpret_cast<bool(*)(int)>(0x88537b);
    bool(*const kbIsPlayerHuman)(int) = reinterpret_cast<bool(*)(int)>(0x883aec);
    
    void(*const trChatSend)(int, const char*) = 
        reinterpret_cast<void(*)(int, const char*)>(0x984019);
    
    const char*(*const kbGetPlayerName)(int) =
        reinterpret_cast<const char*(*)(int)>(0x883999);
    
    for(auto i = 1; i < cMaxNumPlayers; i++) {
        if (kbIsPlayerValid(i) == false)
            continue;
        
        if (kbIsPlayerHuman(i) == true)
            continue;
        
        char message[255] = "";

        strcat_s(message, 255, kbGetPlayerName(i));
        strcat_s(message, 255, ": ");
        strcat_s(message, 255, getWorldDifficultyName(getPlayerDifficulty(i)));
        
        trChatSend(0, message);
    }
}

// This function is called during the splash screen when the game is booting up
// Don't call the game's native syscalls here (e.g. kbUnitCount, aiRandInt etc)
extern "C" _declspec(dllexport) int UHCPluginMain(UHCPluginInfo* pluginInfo) {
    clearPlayerDifficulties();

    pluginInfo->RegisterSyscall(GroupUI,
                                SyscallVoid,
                                "clearPlayerDifficulties",
                                clearPlayerDifficulties,
                                0,
                                "");

    UHCSyscall& sSetPlayerDifficulty =
        pluginInfo->RegisterSyscall(GroupUI,
                                    SyscallVoid,
                                    "setPlayerDifficulty",
                                    setPlayerDifficulty,
                                    2,
                                    "");
    pluginInfo->SyscallSetParam(sSetPlayerDifficulty, 0, SyscallInteger,
                                                         &cDefaultIntValue);
    pluginInfo->SyscallSetParam(sSetPlayerDifficulty, 1, SyscallInteger,
                                                         &cDefaultIntValue);

    UHCSyscall& sGetPlayerDifficulty =
        pluginInfo->RegisterSyscall(GroupAI,
                                    SyscallInteger,
                                    "aiGetPlayerDifficulty",
                                    getPlayerDifficulty,
                                    1,
                                    "");
    pluginInfo->SyscallSetParam(sGetPlayerDifficulty, 0, SyscallInteger,
                                                         &cDefaultIntValue);

    pluginInfo->RegisterCheat("plvl", true, PLVL);

    return 0;
}
