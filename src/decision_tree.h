//
// Created by wangsy on 2020/12/7.
//

#ifndef DESITIONTREE_DECISION_TREE_H
#define DESITIONTREE_DECISION_TREE_H

#include "result_node.h"
#include "decision_node.h"
#include "decision_methods.h"
#include <map>
#include <vector>

#define GAIN ("KILC")
#define GAIN_RATIO ("GAIN_RATIO")
#define GINI_INDEX ("GINI_INDEX")


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
    std::map<std::string, std::vector<AttributeType>> _attribute_list; // 每种属性的可能属性的列表
    std::vector<ResultType> _result_list; // 可行结果的列表
    /**
     * 清空以root为根的所有节点及其记录的所有信息
     * @param root 需要清除的子树的根节点
     */
    void _do_clear(NodeBase* root);

    bool can_stop(std::vector<ResultType>& _train_y);

    /**
     * 以某一节点为树根，根据已有数据进行建树
     * @param _train_x 一个map<string, vector<AttributeType>>，表示训练数据集，string代表属性的名字，相同下标的代表同一个数据
     * @param _train_y 一个一维数组，表示_train_x的每一行的结果
     * @param _attribute_name_list 一个一维数组，表示_train_x的每一列所属的属性名
     */
    NodeBase* _do_decision(std::map<std::string, std::vector<AttributeType>>& _train_x, std::vector<ResultType>& _train_y, std::vector<std::string>& _attribute_name_list, bool is_cut=false, std::string& cut_method= (std::string &) "prev", std::string& _decision_method= (std::string &) "KILC");

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
    void fit(std::map<std::string, std::vector<AttributeType>>& _train_x, std::vector<ResultType>& _train_y, std::vector<std::string>& _attribute_name_list, bool is_cut=false, std::string& cut_method= (std::string &) "prev", std::string& _decision_method= (std::string &) "KILC");

    /**
     * 给出数据，使用当前的模型进行预测
     * @param _test_x 用于预测的数据
     * @param _test_y 预测的结果，直接写入到_test_y中，在此之前会对_test_y进行清空
     */
    void transform(std::map<std::string, AttributeType>& _test_x, std::vector<ResultType>& _test_y);

    /**
     * 通过当前的数据集以及相应的方法，选择最适合的属性，并且返回相应的属性名。 这里本质上是一个选择器
     * @param _train_x 一个map<string, vector<AttributeType>>，表示训练数据集，string代表属性的名字，相同下标的代表同一个数据
     * @param _train_y 一个一维数组，表示_train_x的每一行的结果
     * @param _attribute_name_list 一个一维数组，表示_train_x的每一列所属的属性名
     * @param _decision_method 进行选择的方法，可以选择 信息增益(KILC)、增益率(GAIN_RATIO)、基尼系数(GINI_INDEX)
     * @return 返回一个字符串，表示选择的属性的名称
     */
    std::string select_decision_attribute(std::map<std::string, std::vector<AttributeType>>& _train_x,
                                          std::vector<ResultType>& _train_y,
                                          std::vector<std::string>& _attribute_name_list, std::string& _decision_method);
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
 * 对决策树模型进行训练，传入训练样本的自变量、结果、参数名，进行训练
 * @param _train_x 一个map<string, vector<AttributeType>>，表示训练数据集，string代表属性的名字，相同下标的代表同一个数据
 * @param _train_y 一个一维数组，表示_train_x的每一行的结果
 * @param _attribute_name_list 一个一维数组，表示_train_x的每一列所属的属性名
 */
template<class AttributeType, class ResultType>
void DecisionTree<AttributeType, ResultType>::fit(
        std::map<std::string, std::vector<AttributeType>>& _train_x, std::vector<ResultType>& _train_y, std::vector<std::string>& _attribute_name_list,
        bool is_cut, std::string& cut_method, std::string& _decision_method){
    // 初始化自身的 _attribute_list, 记录所有属性的可能
    for(std::string& iter: _attribute_name_list) {
        for(AttributeType& _attribute: _train_x[iter]) {
            bool found = false;
            for(auto& it: this->_attribute_list[iter]){
                if(it == _attribute){
                    found = true;
                    break;
                }
            }
            if (!found) {
                this->_attribute_list[iter].push_back(_attribute);
            }
        }
    }
    // 初始化自身的 _result_list, 记录所有可能的结果
    for(ResultType& iter: _train_y) {
        bool found = false;
        for(auto& it: this->_result_list){
            if(it == iter){
                found = true;
                break;
            }
        }
        if (!found) {
            this->_result_list.push_back(iter);
        }
    }
    this->_root = this->_do_decision(_train_x, _train_y, _attribute_name_list, is_cut, cut_method, _decision_method);
}

/**
 * 给出数据，使用当前的模型进行预测
 * @param _test_x 用于预测的数据，一个map，从string映射到AttributeType
 * @param _test_y 预测的结果，直接追加到_test_y的末尾
 */
template<class AttributeType, class ResultType>
void DecisionTree<AttributeType, ResultType>::transform(std::map<std::string, AttributeType> &_test_x,
                                                        std::vector<ResultType>& _test_y) {
    NodeBase* _cur = this->_root;
    // 从根节点开始遍历
    // 如果为空节点那么就直接退出，如果为结果节点，那么就跳出循环进行预测
    // 如果为决策节点，那么就使用do_decision函数进行一次决策
    while(true) {
        if (_cur == nullptr) return;
        if (_cur->is_result()) {
            break;
        }
        // 如果是决策点，那么使用节点的决策功能进行决策，
        DecisionNode<AttributeType>* _node = (DecisionNode<AttributeType>*)_cur;
        _cur = _node->do_decision(_test_x[_node->get_attribute_name()]);
    }
    ResultNode<ResultType>* _node = (ResultNode<ResultType>*)_cur;
    _test_y.push_back(_node->get_result());
}

/**
 * 以某一节点为树根，根据已有数据进行建树，会建立出一个节点，并且进行返回
 * @param _train_x 一个map<string, vector<AttributeType>>，表示训练数据集，string代表属性的名字，相同下标的代表同一个数据
 * @param _train_y 一个一维数组，表示_train_x的每一行的结果
 * @param _attribute_name_list 一个一维数组，表示_train_x的每一列所属的属性名
 * @param is_cut 表示是否进行剪枝
 * @param _method 表示选择的
 */
template<class AttributeType, class ResultType>
NodeBase *DecisionTree<AttributeType, ResultType>::_do_decision(std::map<std::string, std::vector<AttributeType>> &_train_x,
                                                                std::vector<ResultType> &_train_y,
                                                                std::vector<std::string> &_attribute_name_list,
                                                                bool is_cut,std::string& cut_method, std::string& _decision_method) {
    if(_attribute_name_list.empty()) {
        return nullptr;
    }
    if (_attribute_name_list.size() == 1) {
        // 如果当前节点只剩下一种选择，那么就必须强制停止
        // 从所有可行解中找到众数，作为最终选择的答案
        std::map<ResultType, int> answer_count;
        for(ResultType& iter: _train_y) {
            answer_count[iter] ++;
        }
        int max_count = - 1;
        ResultType select_res;
        for(std::pair<ResultType, int> iter: answer_count) {
            if (iter.second > max_count) {
                select_res = iter.first;
                max_count = iter.first;
            }
        }
        return (NodeBase*)new ResultNode<ResultType>(select_res);
    }
    // 如果当前节点能够停止，那么就将当前节点作为结果点进行返回
    if (this->can_stop(_train_y)) {
        if(_train_y.empty()) { // 如果当前结果为空
            return (NodeBase*)new ResultNode<ResultType>(this->_result_list[0]);
        } else {
            return (NodeBase*)new ResultNode<ResultType>(_train_y[0]);
        }
    }
    // 上方已经对终止条件进行了考虑，在此处我们只需要对树的递归创建方法进行考虑即可
    std::string decision_attribute = DecisionTree<AttributeType, ResultType>::select_decision_attribute(
                _train_x, _train_y, _attribute_name_list, _decision_method);

    auto* res = new DecisionNode<AttributeType>(decision_attribute);
    // 获取了作为根节点的属性
    // 根据属性进行分别建树
    // 创建属性列表
    std::vector<std::string> new_attribute_name_list;
    for(const std::string& iter: _attribute_name_list){
        if(iter != decision_attribute){
            new_attribute_name_list.push_back(iter);
        }
    }
    // 对属性进行选择，遍历每一种属性，将数据集对不同属性进行拆分
    for(AttributeType& iter: this->_attribute_list[decision_attribute]) {
        std::map<std::string, std::vector<AttributeType>> new_train_x;
        std::vector<ResultType> new_train_y;
        int index = 0;
        // 遍历寻找数据集，一旦属性相同，就添加到new数据集中
        for(int i = 0; i < _train_y.size(); ++i){
            if(_train_x[decision_attribute][i] == iter) { // 检测到与当前检测的属性相同，进行添加操作
                new_train_y.push_back(_train_y[i]);
                for(std::string& _attribute: _attribute_name_list) { // 将每个属性的对应值进行添加
                    if(_attribute != decision_attribute){
                        new_train_x[_attribute].push_back(_train_x[_attribute][i]);
                    }
                }
            }
        }
        // 创建子树
        res->insert_decision(iter, this->_do_decision(
                new_train_x, new_train_y, new_attribute_name_list, is_cut, cut_method, _decision_method
                ));
    }
    return (NodeBase*)res;
}

/**
 * 通过当前的数据集以及相应的方法，选择最适合的属性，并且返回相应的属性名。 这里本质上是一个选择器
 * @param _train_x 一个map<string, vector<AttributeType>>，表示训练数据集，string代表属性的名字，相同下标的代表同一个数据
 * @param _train_y 一个一维数组，表示_train_x的每一行的结果
 * @param _attribute_name_list 一个一维数组，表示_train_x的每一列所属的属性名
 * @param _decision_method 进行选择的方法，可以选择 信息增益(KILC)、增益率(GAIN_RATIO)、基尼系数(GINI_INDEX)
 * @return 返回一个字符串，表示选择的属性的名称
 */
template<class AttributeType, class ResultType>
std::string DecisionTree<AttributeType, ResultType>::select_decision_attribute(
        std::map<std::string, std::vector<AttributeType>> &_train_x, std::vector<ResultType> &_train_y,
        std::vector<std::string> &_attribute_name_list, std::string &_decision_method) {
    // 分发器，根据_decision_method选择适配的方法即可
    std::string res;
    if(_decision_method == "KILC") {
        res = KILC_method(_train_x, _train_y, _attribute_name_list);
    }
    return res;
}

/**
 * 判断当前的数据集能否结束
 * @param _train_y 用于判断的数据集结果
 * @return 返回一个布尔值，表示是否能够结束分割
 */
template<class AttributeType, class ResultType>
bool DecisionTree<AttributeType, ResultType>::can_stop(std::vector<ResultType> &_train_y) {
    if(_train_y.empty()) return true;
    for(int i = 1 ; i < _train_y.size(); ++ i) {
        if (_train_y[i] != _train_y[i - 1]) {
            return false;
        }
    }
    return true;
}

#endif //DESITIONTREE_DECISION_TREE_H
