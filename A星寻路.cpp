#include "iostream"
#include "vector"
#include "cstring"

using namespace std;

#define hang 10
#define lie 8

//地图信息
const int map[lie][hang] = {{1, 1, 0, 0, 0, 1, 0, 0, 0, 0},
                            {1, 0, 0, 0, 0, 1, 0, 0, 0, 0},
                            {1, 1, 0, 1, 0, 1, 1, 0, 0, 0},
                            {1, 1, 0, 1, 0, 1, 1, 1, 1, 1},
                            {0, 0, 0, 0, 1, 1, 0, 0, 0, 0},
                            {0, 0, 1, 1, 1, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 1, 0, 0, 0, 0},};

//位置信息
struct point {
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
};

//结构体A
struct A {
    //位置信息
    point pos;
    //A的父
    A *parent;
};

//方向字典
enum direction {
    you, zuo, shang, xia
};

//计算某点的H值
int getH(const point start, const point end) {
    int temphang = abs(start.hangnum - end.hangnum);
    int templie = abs(start.lienum - end.lienum);
    return temphang + templie;
}

//将A*指针扩容
A *newA(const int lienum, const int hangnum) {
    A *p = new A;
    memset(p, 0, sizeof(A));
    p->pos.lienum = lienum;
    p->pos.hangnum = hangnum;
    return p;
}

int main() {
    //是否找到
    bool find = false;
    //是否找过
    int pathMap[lie][hang] = {0};
    //找了几次
    int times = 0;
    //起点
    point start{1, 1};
    //终点
    point end{6, 8};
    //开始位置的A
    A *pCurrent = newA(start.lienum, start.hangnum);
    //开始位置标记找过
    pathMap[pCurrent->pos.lienum][pCurrent->pos.hangnum] = 1;
    //队列存储A
    vector<A *> list;
    //主程序
    while (true) {
        for (int i = 0; i < 4; i++) {
            //新建一个指针
            A *pChild = newA(pCurrent->pos.lienum, pCurrent->pos.hangnum);
            //保留G的值
            pChild->pos.g = pCurrent->pos.g;
            //根据四个方向调整坐标
            switch (i) {
                case you:
                    pChild->pos.lienum++;
                    break;
                case zuo:
                    pChild->pos.lienum--;
                    break;
                case shang:
                    pChild->pos.hangnum--;
                    break;
                case xia:
                    pChild->pos.hangnum++;
                    break;
                default:
                    abort();
            }
            //G的值加1
            pChild->pos.g++;
            //如果没障碍并且没找过
            if (map[pChild->pos.lienum][pChild->pos.hangnum] != 1 &&
                pathMap[pChild->pos.lienum][pChild->pos.hangnum] != 1) {
                //标记为已找过
                pathMap[pChild->pos.lienum][pChild->pos.hangnum] = 1;
                //计算H的值
                pChild->pos.h = getH(pChild->pos, end);
                //计算F的值
                pChild->pos.f = pChild->pos.h + pChild->pos.g;
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
            if ((*imin)->pos.f > (*i)->pos.f) {
                imin = i;
            }
        }
        //列表中F最小的作为下一个起点
        pCurrent = *imin;
        //抹掉最小的
        list.erase(imin);
        //如果到达了终点
        if (end.lienum == pCurrent->pos.lienum && end.hangnum == pCurrent->pos.hangnum) {
            find = true;
            break;
        }
        //如果找了超过地图的数量
        if (times > hang * lie * 4) {
            cout << "找了超过" << hang * lie << "次" << endl;
            break;
        }
    }
    //如果找到了
    if (find) {
        cout << "找到终点了" << endl;
        cout << "从后往前为：" << endl;
        while (pCurrent) {
            cout << "(" << pCurrent->pos.hangnum << "," << pCurrent->pos.lienum << ") ";
            pCurrent = pCurrent->parent;
        }
    } else {
        cout << "没找到终点" << endl;
    }
    return 0;
}
