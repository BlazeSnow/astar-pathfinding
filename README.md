# 写在最前

1. 此程序用于**A*寻路**
2. 此程序可以**自定义地图**
    - ```0``` -> ```空地```
    - ```1``` -> ```障碍物```
    - ```2``` -> ```起点```(**仅1个**)
    - ```3``` -> ```终点```(**仅1个**)
3. 需要自定义地图请在输出的目录中找到```map.txt```并修改

# 更新日志

- **2024年4月19日15点13分**
    - 增加了自定义地图功能，生成```map.txt```
        - ```0``` -> ```空地```
        - ```1``` -> ```障碍物```
        - ```2``` -> ```起点```
        - ```3``` -> ```终点```
    - 增加了地图输出功能，可以直观地看到程序生成的路径
- **2024年4月18日13点20分**
    - 用```class```改写```struct```
    - 用```栈```存放路径，将路径输出倒转，变成从起点到终点
- **2024年4月18日12点58分**
    - 添加了地图越界的判断
    - 修复了寻找次数输出错误（没×4）的问题
- **2024年4月18日08点56分**
    - 修复了```list```不是```erase```而是```clear```的问题
    - 修复了寻找次数是```行×列```而不是```行×列×4```的问题
- **2024年4月18日08点49分**
    - 删去了```if(list.empty())```
        - 因为```list```每次会抹掉```F值```最小的那一项
        - 所以此项会导致起点只有一个方向可以走时程序提前终止
    - 改用```times```小于地图总量来判断找不到终点的情况
- **2024年4月18日08点16分**
    - 添加```memset```和```string头文件```
    - 添加注释
    - 优化文字描述
    - 删去```A结构体```中的```child```数组
    - 删去```pRoot```
    - 将虚拟地图类型由```bool```改为```int```，优化其的初始化赋值
- **2024年4月17日19点38分**
    - 更新复杂化的地图
    - 删除```memset```和```string头文件```
- **2024年4月17日12点48分**
    - 回退到第一个版本
    - 将仓库从```Gitee```转移到```GitHub```
- **2024年4月10日21点08分**
    - 优化了虚拟地图的赋值，每次```pChild```运算完都将该点设为已经找过
- **2024年4月10日20点53分**
    - 优化代码，删去多余的
        - ```pRoot```
        - ```迭代器```
        - ```find状态```
    - 优化注释内容
- **2024年3月22日16点54分**
    - 跟着教程打出来了A*寻路算法
