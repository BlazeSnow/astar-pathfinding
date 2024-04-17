#include <cstring>
#include "iostream"
#include "vector"

using namespace std;

#define hang 10
#define lie 8

const int map[lie][hang] = {{0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 1, 1, 0, 0, 0},
                            {0, 0, 0, 0, 0, 1, 1, 1, 1, 1},
                            {0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                            {0, 0, 0, 0, 0, 1, 0, 0, 0, 0},};

struct point {
    int lienum;//列位置
    int hangnum;//行位置
    int f;//总代价
    int g;//移动代价
    int h;//估算代价
};

struct treeNode {
    point pos{};
    vector<treeNode *> child;
    treeNode *parent{};
};

vector<treeNode *> buff;
vector<treeNode *>::iterator it;
vector<treeNode *>::iterator itMin;

treeNode *createTree(int lienum, int hangnum) {
    auto *pNew = new treeNode;
    memset(pNew, 0, sizeof(treeNode));
    pNew->pos.lienum = lienum;
    pNew->pos.hangnum = hangnum;
    return pNew;
}

enum direction {
    you, zuo, shang, xia
};

int getH(point start, point end) {
    int temphang = abs(start.hangnum - end.hangnum);
    int templie = abs(start.lienum - end.lienum);
    return temphang + templie;
}

int main() {
    bool find = false;
    bool pathMap[lie][hang] = {false};
    point start{1, 1};
    point end{6, 8};
    treeNode *pRoot = createTree(start.lienum, start.hangnum);
    pathMap[pRoot->pos.lienum][pRoot->pos.hangnum] = true;
    treeNode *pCurrent = pRoot;
    treeNode *pChild;
    while (true) {
        for (int i = 0; i < 4; ++i) {
            pChild = createTree(pCurrent->pos.lienum, pCurrent->pos.hangnum);
            switch (i) {
                case you:
                    pChild->pos.lienum++;
                    pChild->pos.g++;
                    break;
                case zuo:
                    pChild->pos.lienum--;
                    pChild->pos.g++;
                    break;
                case shang:
                    pChild->pos.hangnum--;
                    pChild->pos.g++;
                    break;
                case xia:
                    pChild->pos.hangnum++;
                    pChild->pos.g++;
                    break;
                default:
                    abort();
            }
            if (map[pChild->pos.lienum][pChild->pos.hangnum] == 0 &&
                !pathMap[pChild->pos.lienum][pChild->pos.hangnum]) {
                pChild->pos.h = getH(pChild->pos, end);
                pChild->pos.f = pChild->pos.h + pChild->pos.g;
                pCurrent->child.push_back(pChild);
                pChild->parent = pCurrent;
                buff.push_back(pChild);
            } else {
                delete pChild;
            }
        }
        it = buff.begin();
        itMin = buff.begin();
        for (; it != buff.end(); it++) {
            if ((*itMin)->pos.f > (*it)->pos.f) {
                itMin = it;
            }
        }
        pCurrent = *itMin;
        pathMap[pCurrent->pos.lienum][pCurrent->pos.hangnum] = true;
        buff.erase(itMin);
        if (end.lienum == pCurrent->pos.lienum && end.hangnum == pCurrent->pos.hangnum) {
            find = true;
            break;
        }
        if (buff.empty()) {
            break;
        }
    }
    if (!find) {
        cout << "没找到终点" << endl;
    } else {
        cout << "找到终点了" << endl;
        while (pCurrent) {
            cout << "(" << pCurrent->pos.hangnum << "," << pCurrent->pos.lienum << ")" << endl;
            pCurrent = pCurrent->parent;
        }
    }
    return 0;
}
