# A星寻路

1. 此程序用于**A星寻路**
2. 此程序可以**自定义地图**
3. 需要自定义地图请在输出的目录中找到```astar-pathfinding.txt```并修改

- ```0``` -> ```空地```
- ```1``` -> ```障碍物```
- ```2``` -> ```起点```(**仅1个**)
- ```3``` -> ```终点```(**仅1个**)

## 默认地图

```ansi
1 1 0 0 0 1 0 0 0 0 
1 2 0 0 0 1 0 0 0 0 
1 1 0 1 0 1 1 0 0 0 
1 1 0 1 0 1 1 1 1 1 
0 0 0 0 1 1 0 0 0 0 
0 0 1 1 1 0 0 0 0 0 
0 0 0 0 0 0 0 0 3 0 
0 0 0 0 0 1 0 0 0 0
```

## 输出演示

```ansi
1   1   0   0   0   1   0   0   0   0
1  a2  a0   0   0   1   0   0   0   0
1   1  a0   1   0   1   1   0   0   0
1   1  a0   1   0   1   1   1   1   1
0  a0  a0   0   1   1   0   0   0   0
0  a0   1   1   1   0   0   0   0   0
0  a0  a0  a0  a0  a0  a0  a0  a3   0
0   0   0   0   0   1   0   0   0   0
```

## 如何下载？

前往 [GitHub Release](https://github.com/BlazeSnow/astar-pathfinding/releases/latest) 下载对应系统的可执行文件。

文件命名格式为 `astar-pathfinding-<版本>-<系统>-<架构>`，各平台对应关系如下：

| 文件名后缀           | 适用平台               |
| -------------------- | ---------------------- |
| `-windows-x64.exe`   | Windows x64            |
| `-windows-arm64.exe` | Windows ARM64          |
| `-linux-x64`         | Linux x64              |
| `-linux-arm64`       | Linux ARM64            |
| `-macos-x64`         | macOS（Intel）         |
| `-macos-arm64`       | macOS（Apple Silicon） |

## Linux / macOS 额外处理

```sh
sudo chmod +x <可执行文件>
```

## 更新日志

见 [CHANGELOG.md](./CHANGELOG.md)

## 许可证

[MIT](./LICENSE)
