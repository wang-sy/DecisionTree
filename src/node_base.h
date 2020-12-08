//
// Created by wangsy on 2020/12/7.
//

#ifndef DESITIONTREE_NODE_BASE_H
#define DESITIONTREE_NODE_BASE_H

// 决策树基类，所有决策树节点都必须集成本基类进行设计
class NodeBase {
protected:
    bool _is_result{}; // 标记当前节点是否是最终节点
public:
    virtual ~NodeBase() = 0;
    /**
     * 返回当前节点是否是一个结果类型的节点
     * @return 一个布尔值，表示当前的节点是否是一个结果类型的节点
     */
    inline bool is_result() const;
};

/**
 * 返回当前节点是否是一个结果类型的节点
 * @return 一个布尔值，表示当前的节点是否是一个结果类型的节点
 */
bool NodeBase::is_result() const {
    return this->_is_result;
}


#endif //DESITIONTREE_NODE_BASE_H
