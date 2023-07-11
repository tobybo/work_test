#include <iostream>
#include <vector>
#include <random>
#include <cmath>

#include "14_2.h"
using namespace std;

int main(int argNum, char **argv) {
    // vector<vector<int>> input {
    //     {1}, {2}
    // };
    // vector<vector<int>> input {
    //     {1,   4,  7, 11, 15},
    //     {2,   5,  8, 12, 19},
    //     {3,   6,  9, 16, 22},
    //     {10, 13, 14, 17, 24},
    //     {18, 21, 23, 26, 30}
    // };
    // Solution sol;
    // for (int i = -10; i < 31; i++) {
    // //for (int i = 2; i < 3; i++) {
    //     bool ret = sol.findNumberIn2DArray(input, i);
    //     printf("%d 查询结果: %d\n", i, ret);
    // }

    //13.h
    // Solution sol;
    // int ret1 = 0;
    // int ret2 = 0;
    // int ret3 = 0;
    // int ret4 = 0;
    // int ret5 = 0;
    // // ret1 = sol.movingCount(2, 3, 1);
    // // ret2 = sol.movingCount(3, 1, 0);
    // // ret3 = sol.movingCount(11, 8, 16);
    // // ret4 = sol.movingCount(36, 11, 15);
    // ret5 = sol.movingCount(38, 28, 20);
    // printf("ret1,%d, ret2,%d, ret3,%d, ret4,%d\n", ret1, ret2, ret3, ret5);

    //06.h
    // Solution sol;
    // Solution::ListNode *head = new Solution::ListNode(10);
    // std::default_random_engine generator;
    // std::uniform_int_distribution<int> distribution(-6,6);
    // printf("10, ");
    // int dice_roll;
    // Solution::ListNode *tail = head;
    // for (int i = 1; i < 10; ++i) {
    //     dice_roll = distribution(generator);
    //     tail->next = new Solution::ListNode(dice_roll);
    //     tail = tail->next;
    //     printf("%d, ", dice_roll);
    // }
    // printf("\n");
    // vector<int> reser = sol.reversePrint(head);
    // for (unsigned int j = 0; j < reser.size(); ++j) {
    //     printf("%d, ", reser[j]);
    // }
    // printf("\n");

    //24.h
    // Solution sol;
    // Solution::ListNode *head = new Solution::ListNode(10);
    // std::default_random_engine generator;
    // std::uniform_int_distribution<int> distribution(-6,6);
    // printf("10, ");
    // int dice_roll;
    // Solution::ListNode *tail = head;
    // for (int i = 1; i < 10; ++i) {
    //     dice_roll = distribution(generator);
    //     tail->next = new Solution::ListNode(dice_roll);
    //     tail = tail->next;
    //     printf("%d, ", dice_roll);
    // }
    // printf("\n");
    // Solution::ListNode *reser = sol.reverseList(head);
    // while (reser) {
    //     printf("%d, ", reser->val);
    //     reser = reser->next;
    // }
    // printf("\n");

    //45.h
    // Solution sol;
    // vector<int> nums = {2, 1};
    // string s = sol.minNumber(nums);
    // std::cout<<"{10,2} s: "<<s<<endl;
    //
    // vector<int> nums1 = {121,12};
    // string s1 = sol.minNumber(nums1);
    // std::cout<<"{2} s: "<<s1<<endl;
    //
    // //[3,30,34,5,9]
    // vector<int> nums3 = {3,30,34,5,9};
    // string s3 = sol.minNumber(nums3);
    // std::cout<<"{2} s: "<<s3<<endl;
    //
    // vector<int> nums2 = {2, 2, 34, 3, 0, 32, 324, 0, 321, 23};
    // string s2 = sol.minNumber(nums2);
    // std::cout<<"{2, 2, 34, 3, 32, 324, 321, 23} s: "<<s2<<endl;

    // lambda
    // int a = 10;
    // auto fun = [&](){a++;};
    // fun();
    // printf("a,%d\n", a);

    Solution sol;
    int ret;
    for (int i = 2; i <= 10; ++i) {
        ret = sol.cuttingRope(i);
        printf("i,%d, ret, %d\n", i, ret);
    }
    printf("i,1000, ret, %d\n", sol.cuttingRope(1000));

    return 0;
}






