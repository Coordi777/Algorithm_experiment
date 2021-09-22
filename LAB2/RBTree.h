#pragma once

#define _RED_BLACK_TREE_HPP_
#include <iomanip>
#include <iostream>
#include <string>
using namespace std;

enum RBTColor { RED, BLACK };


class RBTNode {  //定义节点
public:
    RBTColor color;    // 颜色
    int index;            // 关键字(index)
    string mac;           // mac
    RBTNode* left;    // 左孩子
    RBTNode* right;    // 右孩子
    RBTNode* parent; // 父结点

    RBTNode(int key, string value, RBTColor c, RBTNode* p, RBTNode* l, RBTNode* r) :
        index(key), mac(value), color(c), parent(), left(l), right(r) {}
};



//对于出现同名函数，请参考以下关于函数重载的定义理解
//函数重载是一种特殊情况，C++允许在同一作用域中声明几个类似的同名函数，这些同名函数的形参列表（参数个数，类型，顺序）必须不同，常用来处理实现功能类似数据类型不同的问题。

class RBTree {   //定义RBTree类
private:
    RBTNode * mRoot;    // 根结点

public:
    RBTree();
    ~RBTree();

    // 前序遍历"红黑树"
    void preOrder();
    // 中序遍历"红黑树"
    void inOrder();
    // 后序遍历"红黑树"
    void postOrder();

    // (递归实现)查找"红黑树"中键值为index的节点
    RBTNode * search(int index);;

    // 将结点(index为节点键值)插入到红黑树中
    void insert(int index, string mac);

    // 删除结点(index为节点键值)
    void remove(int index);//【需要自行补全，可参考PPT】

    // 销毁红黑树
    void destroy();

    // 打印红黑树
    void print();
private:
    // 前序遍历"红黑树"
    void preOrder(RBTNode * tree) const;
    // 中序遍历"红黑树"
    void inOrder(RBTNode * tree) const;
    // 后序遍历"红黑树"
    void postOrder(RBTNode * tree) const;

    // (递归实现)查找"红黑树x"中键值为index的节点
    RBTNode * search(RBTNode * x, int index) const;//【需要自行补全，可参考PPT】

    // 左旋
    void leftRotate(RBTNode *& root, RBTNode * x);//【需要自行补全，可参考PPT】
    // 右旋
    void rightRotate(RBTNode *& root, RBTNode * y);//【需要自行补全，可参考PPT】
    // 插入函数
    void insert(RBTNode *& root, RBTNode * node);//【需要自行补全，可参考PPT】
    // 插入修正函数
    void insertFixUp(RBTNode *& root, RBTNode * node);//【需要自行补全，可参考PPT】
        // 销毁红黑树
    void destroy(RBTNode*& tree);
    // 删除函数
    void remove(RBTNode *& root, RBTNode * node);//【需要自行补全，可参考PPT】
    // 删除修正函数
    void removeFixUp(RBTNode *& root, RBTNode * node, RBTNode* parent);//【需要自行补全，可参考PPT】
    //交换子树
    void RB_TRANSPLANT(RBTNode*& root, RBTNode* u, RBTNode* v);
    // 打印红黑树
    void print(RBTNode * tree, int index, int direction);

#define rb_parent(r)   ((r)->parent)
#define rb_color(r) ((r)->color)
#define rb_is_red(r)   ((r)->color==RED)
#define rb_is_black(r)  ((r)->color==BLACK)
#define rb_set_black(r)  do { (r)->color = BLACK; } while (0)
#define rb_set_red(r)  do { (r)->color = RED; } while (0)
#define rb_set_parent(r,p)  do { (r)->parent = (p); } while (0)
#define rb_set_color(r,c)  do { (r)->color = (c); } while (0)
// 提供一些便利的宏定义，可选择使用【非必须使用】
};
