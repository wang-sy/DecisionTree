//
// Created by wangsy on 2020/12/8.
//

#ifndef DESITIONTREE_DECISION_METHODS_H
#define DESITIONTREE_DECISION_METHODS_H

#include <cstring>
#include <iostream>
#include <map>
#include <vector>
#include <cmath>

/**
 * 自用函数集合， 不对外不开放即可
 */
namespace _decision_methods_self_use {

    /**
     * 计算x属性对于y结果的条件熵
     * @param _train_x x属性
     * @param _train_y y结果
     * @return 返回一个浮点数，表示计算出的条件熵
     */
    template<class AttributeType, class ResultType>
    float generate_gain(std::vector<AttributeType>& _train_x,
                        std::vector<ResultType> &_train_y) {
        std::map<AttributeType, std::map<ResultType, float>> attribute_counter; // 记录不同属性的不同答案的数量
        // 统计样本中每个分类的数量以及每个分类中的信息熵，对其进行加权平均，以计算出当前属性确定时的信息熵
        for(int index= 0; index < _train_y.size(); ++ index) {
            attribute_counter[_train_x[index]][_train_y[index]] ++;
        }
        float res = 0.0;
        // 循环迭代，记录每种属性确定情况下，不同答案的的熵的加权平均数
        // 然后再对每种属性确定的熵进行加权平均
        for(auto& iter: attribute_counter) {
            float total_count = 0.0;
            for(std::pair<ResultType, float> _result_pair: attribute_counter[iter.first]) {
                total_count += _result_pair.second;
            }
            float ent_cur = 0.0;
            for(std::pair<ResultType, float> _result_pair: attribute_counter[iter.first]) {
                float cur_p = _result_pair.second / total_count;
                ent_cur -= cur_p * log(cur_p) / log(10.0);
            }
            res += ent_cur * total_count / _train_y.size();
        }
        return res;
    }

};

/**
 * 使用信息增益计算选择的属性
 * @param _train_x 当前节点用于训练的数据
 * @param _train_y 当前训练数据对应的结果
 * @param _attribute_name_list 当前拥有的属性的集合
 * @param _attribute_name2attribute_list 从属性名到该属性相应的选择的映射
 * @param _result_list 所有可能的答案的集合
 * @return 返回一个字符串，表示选择用于决策的属性
 */
template<class AttributeType, class ResultType>
std::string KILC_method(std::map<std::string, std::vector<AttributeType>> &_train_x,
                        std::vector<ResultType> &_train_y,
                        std::vector<std::string> &_attribute_name_list) {
    // 首先记录每个属性的条件熵
    // 找到信息增益最大的属性，选择该属性，作为本层决策树的决策属性
    // 由于根节点的信息熵固定，那么条件熵越小，那么信息增益就越大
    // 所以只需要找到条件熵最小的，作为本轮的决策节点进行返回即可
    std::map<std::string, float> _attribute_name2gain;
    std::string min_attribute_name = "";
    float min_value = 1e9;
    for(int attribute_index = 0; attribute_index < _attribute_name_list.size(); ++ attribute_index) {
        float value = _decision_methods_self_use::generate_gain<AttributeType, ResultType>(_train_x[_attribute_name_list[attribute_index]],_train_y);
        if(value < min_value) {
            min_value = value;
            min_attribute_name = _attribute_name_list[attribute_index];
        }
    }
    return min_attribute_name;
}

#endif //DESITIONTREE_DECISION_METHODS_H
