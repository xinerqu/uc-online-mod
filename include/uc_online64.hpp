#pragma once

#include "ini_config.hpp"
#include "logger.hpp"
#include "path_utils.hpp"
#include <string>
#include <memory>
#include <windows.h>
#include <steam/steam_api.h>
#include <steam/isteamgameserver.h>
#include <steam/isteamugc.h>
#include <steam/isteamhttp.h>
#include <steam/isteamnetworking.h>

class UCOnline64 {
public:
    UCOnline64(const std::string& iniFilePath = "config.ini");
    ~UCOnline64();

    bool InitializeUCOnline();
    void ShutdownUCOnline();
    void RunSteamCallbacks();
    void SetCustomAppID(uint32_t appID);
    uint32_t GetCurrentAppID() const;
    uint32_t GetOGAppID() const;
    bool IsSteamInitialized() const;

    bool LaunchGame();
    void SetGameExecutable(const std::string& gameExePath);
    void SetGameArguments(const std::string& arguments);
    std::string GetGameExecutable() const;
    std::string GetGameArguments() const;
    void SaveConfig();
    void ReloadConfig();

    Logger* GetLogger();
    void SetLoggingEnabled(bool enabled);
    bool IsLoggingEnabled() const;
    void ClearLog();

    std::string GetSteamApiDllPath() const;
    void SetSteamApiDllPath(const std::string& dllPath);

    // 等待游戏进程退出（阻塞），退出后自动清理
    void WaitForGameExit();

private:
    bool _steamInitialized = false;
    uint32_t _currentAppID;
    uint32_t _ogAppID;
    std::unique_ptr<IniConfig> _config;
    std::unique_ptr<Logger> _logger;
    std::string _gameExecutable;
    std::string _gameArguments;
    std::string _steamApiDllPath;
    HANDLE _hGameProcess = NULL;

    bool InitializeSteamInterfaces();
    bool InitializeSteamGameServer();
    bool InitializeSteamUGC();
    bool InitializeSteamHTTP();
    bool InitializeSteamNetworking();
    bool InitializeSteamClient();
};
