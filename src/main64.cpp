// 无控制台窗口模式：Windows 子系统 + mainCRTStartup 入口
#pragma comment(linker, "/subsystem:windows")
#pragma comment(linker, "/entry:mainCRTStartup")

#include "uc_online64.hpp"
#include <thread>
#include <chrono>

int main() {
    UCOnline64 uc_online;

    try {
        uc_online.GetLogger()->Log("Now starting uc-online initialization");
        uc_online.GetLogger()->Log("Appid set to: " + std::to_string(uc_online.GetCurrentAppID()));

        if (!uc_online.InitializeUCOnline()) {
            uc_online.GetLogger()->LogError("uc-online initialization failed");
            return 1;
        }

        uc_online.GetLogger()->Log("Steam initialized successfully");

        if (!uc_online.GetGameExecutable().empty()) {
            if (uc_online.LaunchGame()) {
                // 等待游戏进程退出，游戏退出后 launcher 自动 shutdown 退出，无残留
                uc_online.WaitForGameExit();
                return 0;
            }
        } else {
            uc_online.GetLogger()->LogError("No game executable configured in config.ini");
            return 1;
        }
    } catch (const std::exception& ex) {
        uc_online.GetLogger()->LogError(std::string("Exception: ") + ex.what());
        return 1;
    }

    return 0;
}