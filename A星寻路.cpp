#include "iostream"
#include "vector"
#include "cstring"
#include "stack"
#include "fstream"
#include "filesystem"

using namespace std;
//地图大小
#define hang 10
#define lie 8

//结构体A
class A {
public:
    //列位置
    int lienum;
    //行位置
    int hangnum;
    //总代价
    int f;
    //移动代价
    int g;
    //估算代价
    int h;
    //A的父
    A *parent;
};

//地图类
class MAP {
public:
    //地图存放
    int map[lie][hang] = {0};
    //起点
    A start{1, 1};
    //终点
    A end{6, 8};

    //输入地图，返回1则读取完地图，返回0终止整个程序
    int inputMap() {
        //判断输入或者输出文件
        int in_or_out = -1;
        cout << "需要读取地图文件(1)或生成全新的地图文件(0)：" << endl;
        cin >> in_or_out;
        //读取地图文件
        if (in_or_out == 1) {
            fstream file("map.txt", ios::in);
            if (file.is_open()) {
                //读取
                for (int i = 0; i < lie; i++) {
                    for (int j = 0; j < hang; j++) {
                        file >> map[i][j];
                        //录入起点
                        if (map[i][j] == 2) {
                            start.lienum = i;
                            start.hangnum = j;
                        } //录入终点
                        else if (map[i][j] == 3) {
                            end.lienum = i;
                            end.hangnum = j;
                        }
                    }
                }
                file.close();
                cout << "文件读取成功" << endl;
                return 1;
            } else {
                std::filesystem::path path = std::filesystem::current_path();
                cout << "ERROR:文件打开失败，目录为：" << path << endl;
                return 0;
            }
        } //输出地图文件
        else if (in_or_out == 0) {
            fstream file("map.txt", ios::out);
            if (file.is_open()) {
                //输出地图
                for (const auto &i: templateMap) {
                    for (int j: i) {
                        file << j << " ";
                    }
                    file << endl;
                }
                //输出路径
                std::filesystem::path path = std::filesystem::current_path();
                file.close();
                cout << "文件map.txt创建成功，目录为：" << path << endl;
                return 0;
            } else {
                std::filesystem::path path = std::filesystem::current_path();
                cout << "ERROR:文件创建失败，目录为：" << path << endl;
                return 0;
            }
        } else {
            cout << "ERROR:输入不合法，请重新开始程序" << endl;
            return 0;
        }
    };
private:
    //地图信息
    const int templateMap[lie][hang] = {{1, 1, 0, 0, 0, 1, 0, 0, 0, 0},
                                        {1, 2, 0, 0, 0, 1, 0, 0, 0, 0},
                                        {1, 1, 0, 1, 0, 1, 1, 0, 0, 0},
                                        {1, 1, 0, 1, 0, 1, 1, 1, 1, 1},
                                        {0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
                                        {0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
                                        {0, 0, 0, 0, 0, 0, 0, 0, 3, 0},
                                        {0, 0, 0, 0, 0, 1, 0, 0, 0, 0},};
};

//计算某点的H值
int getH(const A start, const A end) {
    int temphang = abs(start.hangnum - end.hangnum);
    int templie = abs(start.lienum - end.lienum);
    return temphang + templie;
}

//方向字典
enum direction {
    you, zuo, shang, xia
};

//将A*指针扩容
A *newA(const int lienum, const int hangnum) {
    A *p = new A;
    memset(p, 0, sizeof(A));
    p->lienum = lienum;
    p->hangnum = hangnum;
    return p;
}

int main() {
    //引入地图类
    MAP map;
    //如果地图类主程序返回0代表程序结束
    if (map.inputMap() == 0) {
        return 0;
    }
    //是否找到
    bool find = false;
    //是否找过
    int pathMap[lie][hang] = {0};
    //找了几次
    int times = 0;
    //开始位置的A
    A *pCurrent = newA(map.start.lienum, map.start.hangnum);
    //开始位置标记找过
    pathMap[pCurrent->lienum][pCurrent->hangnum] = 1;
    //队列存储A
    vector<A *> list;
    //主程序
    while (true) {
        for (int i = 0; i < 4; i++) {
            //新建一个指针
            A *pChild = newA(pCurrent->lienum, pCurrent->hangnum);
            //保留G的值
            pChild->g = pCurrent->g;
            //根据四个方向调整坐标
            switch (i) {
                case you:
                    pChild->lienum++;
                    break;
                case zuo:
                    pChild->lienum--;
                    break;
                case shang:
                    pChild->hangnum--;
                    break;
                case xia:
                    pChild->hangnum++;
                    break;
                default:
                    abort();
            }
            //G的值加1
            pChild->g++;
            //如果没越界，没障碍并且没找过
            if (pChild->lienum >= 0 && pChild->lienum <= lie && pChild->hangnum >= 0 && pChild->hangnum <= hang &&
                map.map[pChild->lienum][pChild->hangnum] != 1 && pathMap[pChild->lienum][pChild->hangnum] != 1) {
                //标记为已找过
                pathMap[pChild->lienum][pChild->hangnum] = 1;
                //计算H的值
                pChild->h = getH(*pChild, map.end);
                //计算F的值
                pChild->f = pChild->h + pChild->g;
                //标记父
                pChild->parent = pCurrent;
                //写入待处理列表
                list.push_back(pChild);
            }
            times++;
        }
        //处理列表
        auto imin = list.begin();
        for (auto i = list.begin(); i != list.end(); i++) {
            if ((*imin)->f > (*i)->f) {
                imin = i;
            }
        }
        //列表中F最小的作为下一个起点
        pCurrent = *imin;
        //抹掉最小的
        list.erase(imin);
        //如果到达了终点
        if (map.end.lienum == pCurrent->lienum && map.end.hangnum == pCurrent->hangnum) {
            find = true;
            break;
        }
        //如果找了超过地图的数量
        if (times > hang * lie * 4) {
            cout << "找了超过" << hang * lie * 4 << "次" << endl;
            break;
        }
    }
    //如果找到了
    if (find) {
        //输出
        cout << "找到终点了" << endl;
        cout << "从前往后为：" << endl;
        //存放路径的栈
        stack<A *> show;
        //存放路径点的数组，用于地图输出
        vector<A *> show_on_map;
        //输出路径到栈和数组
        while (pCurrent) {
            auto temp = newA(pCurrent->hangnum, pCurrent->lienum);
            show.push(temp);
            show_on_map.push_back(temp);
            pCurrent = pCurrent->parent;
        }
        delete pCurrent;
        //出栈
        while (!show.empty()) {
            auto temp = show.top();
            show.pop();
            cout << "(" << temp->hangnum << "," << temp->lienum << ") ";
        }
        cout << endl;
        //输出地图
        for (int i = 0; i < lie; i++) {
            for (int j = 0; j < hang; j++) {
                //判断保存路径的数组中的点的位置
                bool panduan = false;
                for (auto k: show_on_map) {
                    if (k->lienum == j && k->hangnum == i) {
                        panduan = true;
                    }
                }
                if (panduan) {
                    cout << " a" << map.map[i][j] << " ";
                } else {
                    cout << "  " << map.map[i][j] << " ";
                }
            }
            cout << endl;
        }
    } else {
        cout << "没找到终点" << endl;
    }
    return 0;
}
