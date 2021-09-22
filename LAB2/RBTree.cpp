#include "RBTree.h"

//���ڳ���ͬ����������ο����¹��ں������صĶ������
//����������һ�����������C++������ͬһ�������������������Ƶ�ͬ��������
//��Щͬ���������β��б��������������ͣ�˳�򣩱��벻ͬ������������ʵ�ֹ��������������Ͳ�ͬ�����⡣

/*
 * ���캯��
 */

RBTree ::RBTree() :mRoot(NULL)
{
    mRoot = NULL;
}

//�������������С�ؼ���Ԫ��
RBTNode* findmin(RBTNode* x) {
    while (x->left != NULL) {
        x = x->left;
    }
    return x;
}

/*
 * ��������
 */

RBTree ::~RBTree()
{
    destroy();
}

/*
 * ǰ�����"�����"
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
 * �������"�����"
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
 * �������"�����"
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
 * (�ݹ�ʵ��)����"�����x"�м�ֵΪindex�Ľڵ�
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
 * �Ժ�����Ľڵ�(x)��������ת
 *
 * ����ʾ��ͼ(�Խڵ�x��������)��
 *      px                              px
 *     /                               /
 *    x                               y
 *   /  \      --(����)-->           / \                #
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
 * �Ժ�����Ľڵ�(y)��������ת
 *
 * ����ʾ��ͼ(�Խڵ�y��������)��
 *            py                               py
 *           /                                /
 *          y                                x
 *         /  \      --(����)-->            /  \                     #
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
 * �����������������
 *
 * ���������в���ڵ�֮��(ʧȥ*��)���ٵ��øú�����
 * Ŀ���ǽ������������һ�ź������
 *
 * ����˵����
 *     root ������ĸ�
 *     node ����Ľ��        // ��Ӧ���㷨���ۡ��е�z
 */

void RBTree::insertFixUp(RBTNode*& root, RBTNode* node)
{
    while (node->parent != NULL && node->parent->color == RED) {    //���ӱ߽����� ���ҵ���ĸ�ڵ�Ϊ��ɫʱ

        if (node->parent == node->parent->parent->left) {           //���ڵ�Ϊ���ӽڵ����
            //case 1 ��ڵ㲻Ϊ�ղ���ҲΪ��ɫ �����ӱ߽�������
            RBTNode* y = node->parent->parent->right;
            if (y != NULL&& y->color == RED) {
                node->parent->color = BLACK;            //�����ڵ��Ϊ��ɫ �汲��� ��ǰָ���Ϊ�汲 ����ѭ��
                y->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            }
            //case 2 ����ڵ�Ϊ�Һ���
            else if (node == node->parent->right) {
                node = node->parent;        //�Ը��ڵ����� ����Ϊ��ǰ�ڵ�
                leftRotate(root, node);
            }

            //case 3 ����ڵ�Ϊ����
            else {                                  //�游�ڵ����� �������׺��游����ɫ
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                rightRotate(root, node->parent->parent);
            }
        }

        else {                                          //���ڵ�Ϊ���ӽڵ���� �ԳƲ���
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

    root->color = BLACK;        //���ú�

}

/*
 * �������뵽�������
 *
 * ����˵����
 *     root ������ĸ����
 *     node ����Ľ��        // ��Ӧ���㷨���ۡ��е�node
 */

void RBTree ::insert(RBTNode *& root, RBTNode * node)
{
    RBTNode* y = NULL;              //��¼
    RBTNode* x = root;              //��
    while (x != NULL) {             //�Ӹ���ʼѰ�Ҳ���λ��
        y = x;
        if (node->index < x->index) {
            x = x->left;
        }
        else {
            x = x->right;
        }
    }
    node->parent = y;           //��¼����λ�ĸ��ڵ�
    if (y == NULL) {            //����λ��Ϊ��
        root = node;
    }
    else if (node->index < y->index) {  //�������
        y->left = node;
    }
    else {
        y->right = node;
    }
    node->left = NULL;                  //����ڵ�ʣ�����
    node->right = NULL;
    node->color = RED;
    insertFixUp(root, node);            //�޸�
}

/*
 * �����(indexΪ�ڵ��ֵ)���뵽�������
 *
 * ����˵����
 *     tree ������ĸ����
 *     index ������ļ�ֵ
 */

void RBTree::insert(int index, string mac)
{
    RBTNode * z = NULL;

    // ����½����ʧ�ܣ��򷵻ء������������һ���½����ķ�����
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
    else          //��u�Ǹ��ڵ�
        root = v;
}

/*
 * �����ɾ����������
 *
 * �ڴӺ������ɾ������ڵ�֮��(�����ʧȥƽ��)���ٵ��øú�����
 * Ŀ���ǽ������������һ�ź������
 *
 * ����˵����
 *     root ������ĸ�
 *     node �������Ľڵ�
 */

void RBTree::removeFixUp(RBTNode*& root, RBTNode* node, RBTNode* parent){
    RBTNode* w;
    //��NΪ�����ߺ�ɫ ֱ�����ú�ɫ������
    //��֮Ҫ�������µ���
    while ((node == NULL || node->color==BLACK) && node != root) //����߽�����
    {
        if (parent->left == node){
            w = parent->right;
            if (w->color == RED){
                // Case 1: x���ֵ�w�Ǻ�ɫ��
                //��W��Ϊ��ɫ P��Ϊ��ɫ ��P������ת ���������ж� ��ʱ����ת��Ϊcase1234
                w->color = BLACK;
                parent->color = RED;
                leftRotate(root, parent);
                w = parent->right;
            }
            if ((w->left == NULL|| w->left->color  == BLACK) && (w->right != NULL|| w->right->color == BLACK)){
                // Case 2: x���ֵܽڵ��Ǻ�ɫ���Һ���Ҳ���Ǻ�ɫ��
                //��W��Ϊ��ɫ����P��Ϊ��ǰ�ڵ� ��ʱ����Ϊcase1��2��3��4
                w->color = RED;
                node = parent;
                parent = node->parent;
            }
            else{
                if (!w->right || w->right->color==BLACK){
                    // Case 3: x���ֵ�w�Ǻ�ɫ�ģ�����w�������Ǻ�ɫ���Һ���Ϊ��ɫ��
                    //����W�������ӵ���ɫ������W������ת����ת��N�����ֵ�W��һ����ɫ�Һ��ӣ�ת��Ϊ���4
                    w->left->color = BLACK;
                    w->color = RED;
                    rightRotate(root, w);
                    w = parent->right;
                }
                // Case 4: �ֵܽڵ��Ǻ�ɫ�ģ������ֵܵ��Һ����Ǻ�ɫ��
                //��W��ΪP����ɫ��P��W�Һ�����Ϊ��ɫ������P������ת��N��Ϊ��
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
                // Case 1: x���ֵ�w�Ǻ�ɫ��
                w->color=BLACK;
                parent->color=RED;
                rightRotate(root, parent);
                w = parent->left;
            }
            if ((!w->left || (w->left->color == BLACK)) && (!w->right || (w->right->color == BLACK)))
            {
                // Case 2: x���ֵ�w�Ǻ�ɫ����w����������Ҳ���Ǻ�ɫ��
                w->color = RED;
                node = parent;
                parent = node->parent;
            }
            else
            {
                if (!w->left || (w->left->color == BLACK))
                {
                    // Case 3: x���ֵ�w�Ǻ�ɫ�ģ�����w�������Ǻ�ɫ���Һ���Ϊ��ɫ��
                    w->right->color = BLACK;
                    w->color = RED;
                    leftRotate(root, w);
                    w = parent->left;
                }
                // Case 4: x���ֵ�w�Ǻ�ɫ�ģ�����w���Һ����Ǻ�ɫ�ģ�����������ɫ��
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
 * ɾ�����(node)�������ر�ɾ���Ľ��
 *
 * ����˵����
 *     root ������ĸ����
 *     node ɾ���Ľ��
 */

void RBTree::remove(RBTNode*& root, RBTNode* node)
{
    RBTNode* child, * parent;
    RBTColor color;

    // ��ɾ���ڵ��"���Һ��Ӷ���Ϊ��"�������
    if ((node->left != NULL) && (node->right != NULL))
    {
        // ����ڵ�
        RBTNode* y = node;

        // ��ȡ��̽ڵ�
        y = y->right;
        while (y->left != NULL)
            y = y->left;

        // node���Ǹ��ڵ�
        if (rb_parent(node))
        {
            if (rb_parent(node)->left == node)
                rb_parent(node)->left = y;
            else
                rb_parent(node)->right = y;
        }
        else
            // node�Ǹ��ڵ�
            root = y;

        // child��������ڵ���Һ���
        child = y->right;
        parent = rb_parent(y);
        // ����"ȡ���ڵ�"����ɫ
        color = rb_color(y);

        // "��ɾ���ڵ�"�Ǻ�̽ڵ�ĸ��ڵ�
        if (parent == node)
        {
            parent = y;
        }
        else
        {
            // child��Ϊ��
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

    // node���Ǹ��ڵ�
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
 * ɾ��������м�ֵΪindex�Ľڵ�
 *
 * ����˵����
 *     tree ������ĸ����
 */

void RBTree ::remove(int index)
{
    RBTNode* del;
    // ����index��Ӧ�Ľڵ�(node)���ҵ��Ļ���ɾ���ýڵ㣨����ǰһ��remove������
    del = search(index);
    remove(mRoot, del);
}

/*
 * ���ٺ����
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
 * ��ӡ"���������"
 *
 * index       -- �ڵ�ļ�ֵ
 * direction  --  0����ʾ�ýڵ��Ǹ��ڵ�;
 *               -1����ʾ�ýڵ������ĸ���������;
 *                1����ʾ�ýڵ������ĸ������Һ��ӡ�
 */

void RBTree ::print(RBTNode * tree, int index, int direction)
{
    if (tree != NULL)
    {
        if (direction == 0)    // tree�Ǹ��ڵ�
            cout << setw(2) << tree->index << "(B) is root" << endl;
        else                // tree�Ƿ�֧�ڵ�
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


