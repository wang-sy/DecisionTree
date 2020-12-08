//
// Created by wangsy on 2020/12/7.
//

#ifndef DESITIONTREE_DECISION_NODE_H
#define DESITIONTREE_DECISION_NODE_H

#include "node_base.h"
#include "result_node.h"
#include <cstring>
#include <map>

/**
 * 决策点，会记录当前决策位置的属性名(如：色泽等)以及不同属性对应的选择(如：黄色->下一个)
 * 继承于NodeBase类，是决策树中非常关键的节点类型
 *
 * <p>决策节点的主要作用是进行选择，因此决策节点中主要包含以下数据成员</p>
 * <ul>
 *  <li>当前节点的的属性名称， 一个String类型的变量</li>
 *  <li>当前节点不同属性对应的选择， 是一个Map类型的映射表，值得注意的是：该属性完全由用户进行定义，
 *  如果用户想要使用自定义的类型，则必须重载该类型的小于比较符与等于比较符，这非常重要，否则会导致红黑树运行时的错误。</li>
 * </ul>
 */
template<class AttributeType>
class DecisionNode: NodeBase {
private:
    std::stirng _attribute_name; // 属性名
public:

    std::map<AttributeType, NodeBase*> _attribute_map; // 记录不同属性的映射关系
    /**
     * 决策树节点的构造函数，用于构造一个决策数的决策节点
     * @param _attribute_name 字符串类型， 表示属性名称
     */
    explicit DecisionNode(const std::stirng& _attribute_name): NodeBase();

    /**
     * 向当前的决策节点中添加决策关系
     * @param _attribute 属性的值
     * @param _decision 当前属性取相应值时，所作出的选择
     */
    void insert_decision(AttributeType _attribute, NodeBase* _decision);

    /**
     * 用于进行一次决策，需要给出当前属性的值，将返回相应的决策结果
     * @param _attribute 当前属性的值
     * @return 决策的结果，一个节点类型的指针，指向下一个节点
     */
    NodeBase* do_decision(AttributeType _attribute);

    /**
     * 获取当前节点管理的属性名
     * @return 一个string类型的变量，表示当前节点管理的属性的名称
     */
    std::string get_attribute_name();

    ~DecisionNode() override;
};

/**
 * 决策树节点的构造函数，用于构造一个决策数的决策节点
 * @param _attribute_name 字符串类型， 表示属性名称
 */
template<class AttributeType>
DecisionNode<AttributeType>::DecisionNode(const std::stirng &_attribute_name) {
    this->_is_result = false;
    this->_attribute_name = _attribute_name;
}

/**
 * 用于进行一次决策，需要给出当前属性的值，将返回相应的决策结果
 * @param _attribute 当前属性的值
 * @return 决策的结果，一个节点类型的指针，指向下一个节点
 */
template<class AttributeType>
NodeBase *DecisionNode<AttributeType>::do_decision(AttributeType _attribute) {
    if(this->_attribute_map.find(_attribute) == this->_attribute_map.end()) {
        // 如果在当前记录的关系中没有找到相应的关系，那么就返回null
        return nullptr;
    } // 否则就直接返回相应的下一个节点的指针
    return this->_attribute_map[_attribute];
}

/**
 * 获取当前节点管理的属性名
 * @return 一个string类型的变量，表示当前节点管理的属性的名称
 */
template<class AttributeType>
std::string DecisionNode<AttributeType>::get_attribute_name() {
    return this->_attribute_name;
}

/**
 * 向当前的决策节点中添加决策关系
 * @param _attribute 属性的值
 * @param _decision 当前属性取相应值时，所作出的选择
 */
template<class AttributeType>
void DecisionNode<AttributeType>::insert_decision(AttributeType _attribute, NodeBase *_decision) {
    this->_attribute_map[_attribute] = _decision;
}

template<class AttributeType>
DecisionNode<AttributeType>::~DecisionNode() = default {
    // 析构函数，不会执行过多操作
}

#endif //DESITIONTREE_DECISION_NODE_H
