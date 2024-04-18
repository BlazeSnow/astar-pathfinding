#include "iostream"
#include "vector"
#include "cstring"
#include "stack"

using namespace std;
//地图大小
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
    //是否找到
    bool find = false;
    //是否找过
    int pathMap[lie][hang] = {0};
    //找了几次
    int times = 0;
    //起点
    A start{1, 1};
    //终点
    A end{6, 8};
    //开始位置的A
    A *pCurrent = newA(start.lienum, start.hangnum);
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
                map[pChild->lienum][pChild->hangnum] != 1 && pathMap[pChild->lienum][pChild->hangnum] != 1) {
                //标记为已找过
                pathMap[pChild->lienum][pChild->hangnum] = 1;
                //计算H的值
                pChild->h = getH(*pChild, end);
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
        if (end.lienum == pCurrent->lienum && end.hangnum == pCurrent->hangnum) {
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
        //输出路径到栈
        while (pCurrent) {
            auto temp = newA(pCurrent->hangnum, pCurrent->lienum);
            show.push(temp);
            pCurrent = pCurrent->parent;
        }
        delete pCurrent;
        //出栈
        while (!show.empty()) {
            auto temp = show.top();
            show.pop();
            cout << "(" << temp->hangnum << "," << temp->lienum << ") ";
        }
    } else {
        cout << "没找到终点" << endl;
    }
    return 0;
}
