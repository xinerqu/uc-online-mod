# uc-online (改)

本项目基于 [uc-online](https://github.com/UnionCrax-Team/uc-online/tree/main) 进行改进和优化。

## 主要改动

### 1. AppID 配置不再被写死
- 原版 `main64.cpp` 中硬编码了 `SetCustomAppID(480)`，导致 config.ini 中修改 AppID 不生效
- 现已改为从 `config.ini` 读取 AppID 配置，用户可自由修改

### 2. 新增 OGAppID 参数
- 新增 `OGAppID` 配置项，用于 Steam Overlay 显示正确游戏名称
- 启动游戏时自动设置 `SteamOverlayGameId` 环境变量
- 如果未配置 OGAppID 或为 0，则使用 AppID 的值

### 3. 取消 steam_appid.txt 依赖
- 原版通过 `steam_appid.txt` 文件传递 AppID
- 改为通过 `SetEnvironmentVariableA("SteamAppId", ...)` 设置环境变量
- 用户只需在 `config.ini` 中配置即可，无需额外的文件

### 4. 配置项
| 参数 | 说明 | 默认值 |
|------|------|--------|
| `AppID` | 伪装的 Steam AppID | 480 |
| `OGAppID` | 原始 Steam AppID（Overlay 显示用） | 0 |
| `GameExecutable` | 要启动的游戏路径 | (空) |
| `GameArguments` | 游戏启动参数 | (空) |
| `SteamApiDLLPath` | steam_api.dll 目录 | (空) |
| `EnableLogging` | 启用日志 | false |
| `LogFile` | 日志文件名 | uc_online.log |

## 构建

需要 CMake + Visual Studio 2022 + Windows SDK。

```bash
# x86
mkdir build-x86 && cd build-x86
cmake .. -G "Visual Studio 17 2022" -A Win32
cmake --build . --config Release

# x64
mkdir build-x64 && cd build-x64
cmake .. -G "Visual Studio 17 2022" -A x64
cmake --build . --config Release
```

GitHub Actions 会自动构建并上传 artifacts。
