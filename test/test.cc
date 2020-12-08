//
// Created by wangsy on 2020/12/8.
//

#include "../src/decision_tree.h"
#include "../src/decision_methods.h"
#include <map>
#include <cassert>
using namespace std;

// 下方两个点的数据集来自于 https://zhuanlan.zhihu.com/p/26596036

// 测试信息增益函数(../src/decision_methods.h :: _decision_methods_self_use::generate_gain())
void test_gain(){
    vector<int> x {0,0,0,2,0,0,2,1,1,2,0,0};
    vector<int> y {0,0,1,1,0,0,1,1,1,1,0,0};
    float gain_result = _decision_methods_self_use::generate_gain<int,int>(x,y);
    assert(gain_result - 0.103898 < 0.000001);
}

// 测试KILC方法选择树的节点(../src/decision_methods.h)
void test_KILC_method() {
    vector<int> handsome {1,0,1,0,1,1,1,0,1,0,1,1};
    vector<int> height   {0,0,0,2,0,0,2,1,1,2,0,0};
    vector<int> y        {0,0,1,1,0,0,1,1,1,1,0,0};
    map<string, vector<int>> _train_x;
    _train_x["handsome"] = handsome;
    _train_x["height" ]  = height;
    vector<string> _attribute_name_list = {"handsome", "height"};
    string decision_result = KILC_method<int, int>(_train_x, y, _attribute_name_list);
    assert(decision_result == "height");
}

// 测试decision tree
void test_decision_tree() {
    DecisionTree<int, int> temp;
    vector<int> handsome {1,0,1,0,1,1,1,0,1,0,1,1};
    vector<int> height   {0,0,0,2,0,0,2,1,1,2,0,0};
    vector<int> y        {0,0,1,1,0,0,1,1,1,1,0,0};
    map<string, vector<int>> _train_x;
    _train_x["handsome"] = handsome;
    _train_x["height" ]  = height;
    vector<string> _attribute_name_list = {"handsome", "height"};
    string temp1 = "prev";
    string temp2 = "KILC";
    temp.fit(_train_x, y, _attribute_name_list,false, temp1, temp2);

    std::map<string, int> test_x;
    vector<int> test_y;
    test_x["handsome"] = 1;
    test_x["height"] = 0;
    temp.transform(test_x, test_y);
    cout << test_y[0] << endl;
}

int main () {
    test_gain();
    test_KILC_method();
    test_decision_tree();
    return 0;
}