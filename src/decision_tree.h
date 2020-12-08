//
// Created by wangsy on 2020/12/7.
//

#ifndef DESITIONTREE_DECISION_TREE_H
#define DESITIONTREE_DECISION_TREE_H

#include "result_node.h"
#include "decision_node.h"
#include <vector>

/**
 * 决策树， 记录决策树的树根，并且内置了一系列的训练方法
 * 决策树中的节点一定继承于NodeBase类，
 * 决策节点一定拥有函数：
 * <ul>
 *  <li>do_decision(_attribute) 来进行决策，该函数会根据给出的属性值返回一个决策的结果（一个节点的指针）</li>
 *  <li>insert_decision(_attribute, NodeBase*) 用于添加决策， 该函数会根据给出的属性值和节点指针，记录相应的映射关系</li>
 * </ul>
 *
 * 结果节点一定拥有函数：
 * <ul>
 *  <li>get_result() 获取相应的结果</li>
 * </ul>
 *
 * 同时，无论是什么类型的节点，都应当注意把控自身的_is_result属性，否则会在决策过程中出错
 */
template<class AttributeType, class ResultType>
class DecisionTree {
private:
    NodeBase* _root{}; // 决策树的树根

    /**
     * 清空以root为根的所有节点及其记录的所有信息
     * @param root 需要清除的子树的根节点
     */
    void _do_clear(NodeBase* root);

    /**
     * 以某一节点为树根，根据已有数据进行建树
     * @param _train_x 一个map<string, vector<AttributeType>>，表示训练数据集，string代表属性的名字，相同下标的代表同一个数据
     * @param _train_y 一个一维数组，表示_train_x的每一行的结果
     * @param _attribute_name_list 一个一维数组，表示_train_x的每一列所属的属性名
     */
    NodeBase* _do_decision(std::map<std::vector<AttributeType>>& _train_x, std::vector<ResultType>& _train_y, std::vector<std::stirng>& _attribute_name_list);

public:
    /**
     * 决策树的构造函数，会将树根进行初始化，初始化为一个空指针
     */
    DecisionTree();

    /**
     * 决策树的析构函数，会对当前的树进行递归式删除(借助DecisionNode类型的析构函数)
     */
    ~DecisionTree();

    /**
     * 清空决策树中的所有节点及其记录的所有信息
     */
    void clear();

    /**
     * 对决策树模型进行训练，传入训练样本的自变量、结果、参数名，进行训练
     * @param _train_x 一个map<string, vector<AttributeType>>，表示训练数据集，string代表属性的名字，相同下标的代表同一个数据
     * @param _train_y 一个一维数组，表示_train_x的每一行的结果
     * @param _attribute_name_list 一个一维数组，表示_train_x的每一列所属的属性名
     */
    void fit(std::map<std::string, std::vector<AttributeType>>& _train_x, std::vector<ResultType>& _train_y, std::vector<std::stirng>& _attribute_name_list);

    /**
     * 给出数据，使用当前的模型进行预测
     * @param _test_x 用于预测的数据
     * @param _test_y 预测的结果，直接写入到_test_y中，在此之前会对_test_y进行清空
     */
    void transform(std::map<std::vector<AttributeType>>& _test_x, std::vector<ResultType>& _test_y);
};

/**
 * 决策树的构造函数，会将树根进行初始化，初始化为一个空指针
 */
template<class AttributeType, class ResultType>
DecisionTree<AttributeType, ResultType>::DecisionTree() {
    this->_root = nullptr;
}

/**
 * 决策树的析构函数，会对当前的树进行递归式删除(借助DecisionNode类型的析构函数)
 */
template<class AttributeType, class ResultType>
DecisionTree<AttributeType, ResultType>::~DecisionTree() {
    this->_root;
}

/**
 * 清空决策树中的所有节点及其记录的所有信息
 * 递归式删除，并且将根结点所指向的设置为nullptr
 */
template<class AttributeType, class ResultType>
void DecisionTree<AttributeType, ResultType>::clear() {
    this->_do_clear(this->_root);
    this->_root = nullptr;
}

/**
 * 清空以root为根的所有节点及其记录的所有信息
 * @param root 需要清除的子树的根节点
 */
template<class AttributeType, class ResultType>
void DecisionTree<AttributeType, ResultType>::_do_clear(NodeBase *root) {
    if (root == nullptr) { // 如果当前的树根指向一个空指针，那么就无需进行更改，直接退出
        return;
    }
    if (root->is_result()) { // 如果当前点是一个结果点，那么就直接删除并且退出
        ResultNode<ResultType>* del_ptr = root;
        delete del_ptr;
        return;
    }
    // 执行到这里就说明，当前点是一个决策点，我们先对其子节点进行递归删除，然后再对当前节点进行删除
    DecisionNode<AttributeType>* del_ptr = root;
    for(std::pair<AttributeType, NodeBase*>& item: del_ptr->_attribute_map) {
        this->_do_clear(del_ptr->_attribute_map[item.first]); // 递归删除
    }
    delete root; // 递归删除结束后，删除子树的根节点的信息
}

/**
 * 以某一节点为树根，根据已有数据进行建树，会建立出一个节点，并且进行返回
 * @param _train_x 一个map<string, vector<AttributeType>>，表示训练数据集，string代表属性的名字，相同下标的代表同一个数据
 * @param _train_y 一个一维数组，表示_train_x的每一行的结果
 * @param _attribute_name_list 一个一维数组，表示_train_x的每一列所属的属性名
 */
template<class AttributeType, class ResultType>
NodeBase *DecisionTree<AttributeType, ResultType>::_do_decision(std::map<std::vector<AttributeType>> &_train_x,
                                                                std::vector<ResultType> &_train_y,
                                                                std::vector<std::stirng> &_attribute_name_list) {

}

/**
 * 对决策树模型进行训练，传入训练样本的自变量、结果、参数名，进行训练
 * @param _train_x 一个map<string, vector<AttributeType>>，表示训练数据集，string代表属性的名字，相同下标的代表同一个数据
 * @param _train_y 一个一维数组，表示_train_x的每一行的结果
 * @param _attribute_name_list 一个一维数组，表示_train_x的每一列所属的属性名
 */
template<class AttributeType, class ResultType>
void DecisionTree<AttributeType, ResultType>::fit(std::map<std::string, std::vector<AttributeType>> &_train_x,
                                                  std::vector<ResultType> &_train_y,
                                                  std::vector<std::stirng> &_attribute_name_list) {
    this->root = this->_do_decision(_train_x, _train_y, _attribute_name_list);
}

/**
 * 给出数据，使用当前的模型进行预测
 * @param _test_x 用于预测的数据
 * @param _test_y 预测的结果，直接写入到_test_y中，在此之前会对_test_y进行清空
 */
template<class AttributeType, class ResultType>
void DecisionTree<AttributeType, ResultType>::transform(std::map<std::vector<AttributeType>> &_test_x,
                                                        std::vector<ResultType> &_test_y) {

}


#endif //DESITIONTREE_DECISION_TREE_H
