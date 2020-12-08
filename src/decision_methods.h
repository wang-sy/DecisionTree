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
 * ���ú������ϣ� �����ⲻ���ż���
 */
namespace _decision_methods_self_use {

    /**
     * ����x���Զ���y�����������
     * @param _train_x x����
     * @param _train_y y���
     * @return ����һ������������ʾ�������������
     */
    template<class AttributeType, class ResultType>
    float generate_gain(std::vector<AttributeType>& _train_x,
                        std::vector<ResultType> &_train_y) {
        std::map<AttributeType, std::map<ResultType, float>> attribute_counter; // ��¼��ͬ���ԵĲ�ͬ�𰸵�����
        // ͳ��������ÿ������������Լ�ÿ�������е���Ϣ�أ�������м�Ȩƽ�����Լ������ǰ����ȷ��ʱ����Ϣ��
        for(int index= 0; index < _train_y.size(); ++ index) {
            attribute_counter[_train_x[index]][_train_y[index]] ++;
        }
        float res = 0.0;
        // ѭ����������¼ÿ������ȷ������£���ͬ�𰸵ĵ��صļ�Ȩƽ����
        // Ȼ���ٶ�ÿ������ȷ�����ؽ��м�Ȩƽ��
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
 * ʹ����Ϣ�������ѡ�������
 * @param _train_x ��ǰ�ڵ�����ѵ��������
 * @param _train_y ��ǰѵ�����ݶ�Ӧ�Ľ��
 * @param _attribute_name_list ��ǰӵ�е����Եļ���
 * @param _attribute_name2attribute_list ������������������Ӧ��ѡ���ӳ��
 * @param _result_list ���п��ܵĴ𰸵ļ���
 * @return ����һ���ַ�������ʾѡ�����ھ��ߵ�����
 */
template<class AttributeType, class ResultType>
std::string KILC_method(std::map<std::string, std::vector<AttributeType>> &_train_x,
                        std::vector<ResultType> &_train_y,
                        std::vector<std::string> &_attribute_name_list) {
    // ���ȼ�¼ÿ�����Ե�������
    // �ҵ���Ϣ�����������ԣ�ѡ������ԣ���Ϊ����������ľ�������
    // ���ڸ��ڵ����Ϣ�ع̶�����ô������ԽС����ô��Ϣ�����Խ��
    // ����ֻ��Ҫ�ҵ���������С�ģ���Ϊ���ֵľ��߽ڵ���з��ؼ���
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
