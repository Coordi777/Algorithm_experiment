#include "RBTree.h"

//对于出现同名函数，请参考以下关于函数重载的定义理解
//函数重载是一种特殊情况，C++允许在同一作用域中声明几个类似的同名函数，
//这些同名函数的形参列表（参数个数，类型，顺序）必须不同，常用来处理实现功能类似数据类型不同的问题。

/*
 * 构造函数
 */

RBTree ::RBTree() :mRoot(NULL)
{
    mRoot = NULL;
}

//定义查找树中最小关键字元素
RBTNode* findmin(RBTNode* x) {
    while (x->left != NULL) {
        x = x->left;
    }
    return x;
}

/*
 * 析构函数
 */

RBTree ::~RBTree()
{
    destroy();
}

/*
 * 前序遍历"红黑树"
 */
void RBTree ::preOrder(RBTNode * tree) const
{
    if (tree != NULL)
    {
        cout << tree->index << " " << tree->mac << endl;
        preOrder(tree->left);
        preOrder(tree->right);
    }
}

void RBTree ::preOrder()
{
    preOrder(mRoot);
}



/*
 * 中序遍历"红黑树"
 */
void RBTree ::inOrder(RBTNode * tree) const
{
    if (tree != NULL)
    {
        inOrder(tree->left);
        cout << tree->index << " " << tree->mac << endl;
        inOrder(tree->right);
    }
}


void RBTree ::inOrder()
{
    inOrder(mRoot);
}

/*
 * 后序遍历"红黑树"
 */

void RBTree ::postOrder(RBTNode * tree) const
{
    if (tree != NULL)
    {
        postOrder(tree->left);
        postOrder(tree->right);
        cout << tree->index << " " << tree->mac;
    }
}


void RBTree ::postOrder()
{
    postOrder(mRoot);
}

/*
 * (递归实现)查找"红黑树x"中键值为index的节点
 */
RBTNode * RBTree ::search(RBTNode * x, int index) const
{
    if (x == NULL || x->index == index) {
        return x;
    }

    if (index < x->index) {
        return search(x->left, index);
    }
    else {
        return search(x->right, index);
    }

}


RBTNode * RBTree ::search(int index)
{
    RBTNode* x = search(mRoot, index);
    return x;
}


/*
 * 对红黑树的节点(x)进行左旋转
 *
 * 左旋示意图(对节点x进行左旋)：
 *      px                              px
 *     /                               /
 *    x                               y
 *   /  \      --(左旋)-->           / \                #
 *  lx   y                          x  ry
 *     /   \                       /  \
 *    ly   ry                     lx  ly
 *
 *
 */

void RBTree::leftRotate(RBTNode*& root, RBTNode* x)
{
    RBTNode* y = x->right;
    x->right = y->left;
    if (y->left != NULL) {
        y->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        root = y;
    }
    else if (x == x->parent->left) {
        x->parent->left = y;
    }
    else {
        x->parent->right = y;
    }
    y->left = x;
    x->parent = y;
}

/*
 * 对红黑树的节点(y)进行右旋转
 *
 * 右旋示意图(对节点y进行左旋)：
 *            py                               py
 *           /                                /
 *          y                                x
 *         /  \      --(右旋)-->            /  \                     #
 *        x   ry                           lx   y
 *       / \                                   / \                   #
 *      lx  rx                                rx  ry
 *
 */

void RBTree::rightRotate(RBTNode*& root, RBTNode* x)
{
    RBTNode* y = x->left;
    x->left = y->right;

    if (x->left != NULL) {
        x->left->parent = x;
    }
    y->parent = x->parent;
    if (x->parent == NULL) {
        root = y;

    }
    else if (x->parent->right == x) {
        x->parent->right = y;

    }
    else {
        x->parent->left = y;

    }
    y->right = x;
    x->parent = y;
    
}

/*
 * 红黑树插入修正函数
 *
 * 在向红黑树中插入节点之后(失去*衡)，再调用该函数；
 * 目的是将它重新塑造成一颗红黑树。
 *
 * 参数说明：
 *     root 红黑树的根
 *     node 插入的结点        // 对应《算法导论》中的z
 */

void RBTree::insertFixUp(RBTNode*& root, RBTNode* node)
{
    while (node->parent != NULL && node->parent->color == RED) {    //增加边界条件 并且当父母节点为红色时

        if (node->parent == node->parent->parent->left) {           //父节点为左子节点情况
            //case 1 叔节点不为空并且也为红色 （增加边界条件）
            RBTNode* y = node->parent->parent->right;
            if (y != NULL&& y->color == RED) {
                node->parent->color = BLACK;            //父辈节点变为黑色 祖辈变红 当前指针变为祖辈 继续循环
                y->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            }
            //case 2 插入节点为右孩子
            else if (node == node->parent->right) {
                node = node->parent;        //对父节点左旋 并设为当前节点
                leftRotate(root, node);
            }

            //case 3 插入节点为左孩子
            else {                                  //祖父节点右旋 交换父亲和祖父的颜色
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rightRotate(root, node->parent->parent);
            }
        }

        else {                                          //父节点为右子节点情况 对称操作
            RBTNode* y = node->parent->parent->left;
            if (y && y->color == RED) {
                y->color = BLACK;
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;

            }

            else if (node == node->parent->left) {
               node = node->parent;
               rightRotate(root, node);

            }
            else {
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                leftRotate(root, node->parent->parent);
            }
        }

    }

    root->color = BLACK;        //根置黑

}

/*
 * 将结点插入到红黑树中
 *
 * 参数说明：
 *     root 红黑树的根结点
 *     node 插入的结点        // 对应《算法导论》中的node
 */

void RBTree ::insert(RBTNode *& root, RBTNode * node)
{
    RBTNode* y = NULL;              //记录
    RBTNode* x = root;              //根
    while (x != NULL) {             //从根开始寻找插入位置
        y = x;
        if (node->index < x->index) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }
    node->parent = y;           //记录插入位的父节点
    if (y == NULL) {            //插入位置为根
        root = node;
    }
    else if (node->index < y->index) {  //其余情况
        y->left = node;
    }
    else {
        y->right = node;
    }
    node->left = NULL;                  //插入节点剩余操作
    node->right = NULL;
    node->color = RED;
    insertFixUp(root, node);            //修复
}

/*
 * 将结点(index为节点键值)插入到红黑树中
 *
 * 参数说明：
 *     tree 红黑树的根结点
 *     index 插入结点的键值
 */

void RBTree::insert(int index, string mac)
{
    RBTNode * z = NULL;

    // 如果新建结点失败，则返回。【这里提高了一种新建结点的方法】
    if ((z = new RBTNode (index, mac, BLACK, NULL, NULL, NULL)) == NULL)
        return;

    insert(mRoot, z);
}

void RBTree::RB_TRANSPLANT(RBTNode*& root, RBTNode* u, RBTNode* v) {

    if (v != NULL)
        v->parent = u->parent;

    if (u->parent != NULL) {
        if (u->parent->left == u)
            u->parent->left = v;
        else
            u->parent->right = v;
    }
    else          //若u是根节点
        root = v;
}

/*
 * 红黑树删除修正函数
 *
 * 在从红黑树中删除插入节点之后(红黑树失去平衡)，再调用该函数；
 * 目的是将它重新塑造成一颗红黑树。
 *
 * 参数说明：
 *     root 红黑树的根
 *     node 待修正的节点
 */

void RBTree::removeFixUp(RBTNode*& root, RBTNode* node, RBTNode* parent){
    RBTNode* w;
    //若N为根或者红色 直接设置黑色就行了
    //反之要进行如下调整
    while ((node == NULL || node->color==BLACK) && node != root) //增设边界条件
    {
        if (parent->left == node){
            w = parent->right;
            if (w->color == RED){
                // Case 1: x的兄弟w是红色的
                //将W设为黑色 P设为红色 对P进行旋转 继续进行判断 此时可能转化为case1234
                w->color = BLACK;
                parent->color = RED;
                leftRotate(root, parent);
                w = parent->right;
            }
            if ((w->left == NULL|| w->left->color  == BLACK) && (w->right != NULL|| w->right->color == BLACK)){
                // Case 2: x的兄弟节点是黑色，且孩子也都是黑色的
                //将W设为红色，将P设为当前节点 此时可能为case1、2、3、4
                w->color = RED;
                node = parent;
                parent = node->parent;
            }
            else{
                if (!w->right || w->right->color==BLACK){
                    // Case 3: x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。
                    //交换W与其左孩子的颜色，并对W进行旋转，旋转后N的新兄弟W有一个红色右孩子，转换为情况4
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(root, w);
                    w = parent->right;
                }
                // Case 4: 兄弟节点是黑色的；并且兄弟的右孩子是红色的
                //将W设为P的颜色，P和W右孩子设为黑色，并对P进行旋转，N设为根
                w->color= parent->color;
                parent->color = BLACK;
                w->right->color=BLACK;
                leftRotate(root, parent);
                node = root;
                break;
            }
        }
        else{
            w = parent->left;
            if (w->color==RED){
                // Case 1: x的兄弟w是红色的
                w->color=BLACK;
                parent->color=RED;
                rightRotate(root, parent);
                w = parent->left;
            }
            if ((!w->left || (w->left->color == BLACK)) && (!w->right || (w->right->color == BLACK)))
            {
                // Case 2: x的兄弟w是黑色，且w的俩个孩子也都是黑色的
                w->color = RED;
                node = parent;
                parent = node->parent;
            }
            else
            {
                if (!w->left || (w->left->color == BLACK))
                {
                    // Case 3: x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(root, w);
                    w = parent->left;
                }
                // Case 4: x的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
                w->color = parent->color;
                parent->color = BLACK;
                w->left->color = BLACK;
                rightRotate(root, parent);
                node = root;
                break;
            }
        }
    }
    if (node != NULL)
        node->color = BLACK;
}

/*
 * 删除结点(node)，并返回被删除的结点
 *
 * 参数说明：
 *     root 红黑树的根结点
 *     node 删除的结点
 */

void RBTree::remove(RBTNode*& root, RBTNode* node)
{
    RBTNode* child, * parent;
    RBTColor color;

    // 被删除节点的"左右孩子都不为空"的情况。
    if ((node->left != NULL) && (node->right != NULL))
    {
        // 替代节点
        RBTNode* y = node;

        // 获取后继节点
        y = y->right;
        while (y->left != NULL)
            y = y->left;

        // node不是根节点
        if (rb_parent(node))
        {
            if (rb_parent(node)->left == node)
                rb_parent(node)->left = y;
            else
                rb_parent(node)->right = y;
        }
        else
            // node是根节点
            root = y;

        // child是替代代节点的右孩子
        child = y->right;
        parent = rb_parent(y);
        // 保存"取代节点"的颜色
        color = rb_color(y);

        // "被删除节点"是后继节点的父节点
        if (parent == node)
        {
            parent = y;
        }
        else
        {
            // child不为空
            if (child)
                rb_set_parent(child, parent);
            parent->left = child;

            y->right = node->right;
            rb_set_parent(node->right, y);
        }

        y->parent = node->parent;
        y->color = node->color;
        y->left = node->left;
        node->left->parent = y;

        if (color == BLACK)
            removeFixUp(root, child, parent);
        return;
    }

    if (node->left != NULL)
        child = node->left;
    else
        child = node->right;

    parent = node->parent;
    color = node->color;

    if (child)
        child->parent = parent;

    // node不是根节点
    if (parent)
    {
        if (parent->left == node)
            parent->left = child;
        else
            parent->right = child;
    }
    else
        root = child;

    if (color == BLACK)
        removeFixUp(root, child, parent);
}

/*
 * 删除红黑树中键值为index的节点
 *
 * 参数说明：
 *     tree 红黑树的根结点
 */

void RBTree ::remove(int index)
{
    RBTNode* del;
    // 查找index对应的节点(node)，找到的话就删除该节点（调用前一个remove函数）
    del = search(index);
    remove(mRoot, del);
}

/*
 * 销毁红黑树
 */

void RBTree ::destroy(RBTNode *& tree)
{
    if (tree == NULL)
        return;

    if (tree->left != NULL)
        return destroy(tree->left);
    if (tree->right != NULL)
        return destroy(tree->right);

    delete tree;
    tree = NULL;
}


void RBTree ::destroy()
{
    destroy(mRoot);
}

/*
 * 打印"二叉查找树"
 *
 * index       -- 节点的键值
 * direction  --  0，表示该节点是根节点;
 *               -1，表示该节点是它的父结点的左孩子;
 *                1，表示该节点是它的父结点的右孩子。
 */

void RBTree ::print(RBTNode * tree, int index, int direction)
{
    if (tree != NULL)
    {
        if (direction == 0)    // tree是根节点
            cout << setw(2) << tree->index << "(B) is root" << endl;
        else                // tree是分支节点
            cout << setw(2) << tree->index << (rb_is_red(tree) ? "(R)" : "(B)") << " is " << setw(2) << index << "'s " << setw(12) << (direction == 1 ? "right child" : "left child") << endl;

        print(tree->left, tree->index, -1);
        print(tree->right, tree->index, 1);
    }
}


void RBTree ::print()
{
    if (mRoot != NULL)
        print(mRoot, mRoot->index, 0);
}


