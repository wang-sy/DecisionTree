//
// Created by wangsy on 2020/12/7.
//

#ifndef DESITIONTREE_RESULT_NODE_H
#define DESITIONTREE_RESULT_NODE_H
#include "node_base.h"

/**
 * 决策树结果节点，继承于NodeBase类，是决策树上的一类点
 * 结果的类型可以进行自定义
 * @param ResultType: 结果的类型
 */
template<class ResultType>
class ResultNode: NodeBase {
private:
    ResultType _result;
public:
    /**
     * 用于获取点的信息的函数
     * @return 返回结果点中存储的信息
     */
    ResultType get_result();
    /**
     * 构造函数，用于创建一个结果点，创建过程中，需要给出一个 ResultType 类型的数据，作为当前点所代表的结果
     * 该结果会被写入到当前点的 _result 成员变量中，写入后不可更改，仅可使用 get_result 函数进行访问
     * @param _result 当前点所代表的结果
     */
    explicit ResultNode(ResultType _result);
    /**
     * 析够函数，本节点不需要析构(使用默认的即可)，但是需要重写父类的无参析构函数
     */
    ~ResultNode() override = default;
};

/**
 * 构造函数，用于创建一个结果点，创建过程中，需要给出一个 ResultType 类型的数据，作为当前点所代表的结果
 * 该结果会被写入到当前点的 _result 成员变量中，写入后不可更改，仅可使用 get_result 函数进行访问
 * @param _result 当前点所代表的结果
 */
template<class ResultType>
ResultNode<ResultType>::ResultNode(ResultType _result) {
    this->_is_result = true; // 标记当前点是结果点
    this->_result = _result;
}

/**
 * 用于获取点的信息的函数
 * @return 返回结果点中存储的信息
 */
template<class ResultType>
ResultType ResultNode<ResultType>::get_result() {
    return this->_result;
}


#endif //DESITIONTREE_RESULT_NODE_H
