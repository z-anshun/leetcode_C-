#include "iostream"
#include "vector"

using namespace std;

// 求最大子字符串，并赋值开始，结束节点下标
class SoMaxSubStr {

public:
    // 枚举，暴力解法
    // 时间复杂度：O(n^2)
    int EnumFun(vector<int> &arr, int &left, int &right) {
        left = 0;
        right = 0;
        int maxsum = INT_MIN;

        for (int i = 0; i < arr.size(); i++) {
            int sum = 0;
            for (int k = i; k < arr.size(); k++) {
                sum += arr[k];
                if (sum > maxsum) {
                    maxsum = sum;
                    left = i;
                    right = k;
                }
            }
        }
        return maxsum;
    }

    // 分治法
    // 思路：首先，若存在一个i（0<i<arr.size()）,
    // 那么这个最大子字符串一定在[l,i]、[l,r]、[i,r]中的一个
    // 时间复杂度：O(n*lg n)
    int DvFun(vector<int> &arr, int &left, int &right) {
        int l = 0, r = arr.size() - 1;
        return findArr(arr, l, r, left, right);
    }

    // 动态规划
    // 思路：我们使用v[i]表示0到i的最大子字符串的和
    // 那么v[i]=max(v[i-1]+arr[i],arr[i])
    // 时间复杂度：O(n)
    int DyFun(vector<int> &arr, int &left, int &right) {
        int maxsum = INT_MIN, maxnow = 0;
        int b = 0;
        for (int i = 0; i < arr.size(); i++) {
            if (maxnow + arr[i] < arr[i]) {
                maxnow = arr[i];
                b = i; // 记录当前左边位置
            } else {
                maxnow += arr[i];
            }
            if (maxnow > maxsum) {
                maxsum = maxnow;
                left = b;
                right = i;
            }
        }
        return maxsum;
    }

    // 对于一个循环的数组，找到最大子数组
    // 思路：这里有两种情况：
    // 1. 当最大子数组没循环时，跟上面一样
    // 2. 当最大子数组循环时，那么它就是除去最小子数组的部分
    // 因此，我们先将这串数组的最大子字符串和最小子字符串找到，令其合分别为max和min
    // 那么，sum=max+min+c,因此，当max+min>=sum -> c<0 -> 最大子数组不循环
    // 反之，max+min<sum时 -> c>0 -> 最大子数组=c+max=sum-min
    int DyCirculateArr(vector<int> &arr, int &left, int &right) {
        int sum = 0;// 数组的合
        int nowMax = 0, nowMin = 0;
        int trMax = INT_MIN, trMin = INT_MAX;
        int minleft, minright, maxleft, maxright = 0;
        int temp1, temp2 = 0;
        for (int i = 0; i < arr.size(); i++) {
            sum += arr[i];
            if (nowMax + arr[i] < arr[i]) {
                temp1 = i;
                nowMax = arr[i];
            } else {
                nowMax += arr[i];
            }

            if (trMax < nowMax) {

                trMax = nowMax;
                maxleft = temp1;
                maxright = i;
            }

            if (nowMin + arr[i] > arr[i]) {
                temp2 = i;
                nowMin = arr[i];
            } else {
                nowMin += arr[i];
            }
            if (trMin > nowMin) {

                trMin = nowMin;
                minleft = temp2;
                minright = i;
            }
        }

        if (trMax + trMin > sum) {
            left = maxleft;
            right = maxright;
            return trMax;
        } else {
            // 循环
            left = minright + 1;
            right = minleft - 1;
            return sum - trMin;
        }
    }

private:
    // 找对应的最大子字符串
    int findArr(vector<int> &arr, int begin, int end, int &left, int &right) {
        if (begin == end) {
            left = begin;
            right = left;
            return arr[begin];
        }

        int mid = begin + ((end - begin) >> 1);
        int ll, lr, rl, rr;
        // 找左边最大
        int maxLeft = findArr(arr, begin, mid, ll, lr);
        // 找右边最大
        int maxRight = findArr(arr, mid + 1, end, rl, rr);
        int maxLeftBorder = arr[mid], maxRightBorder = arr[mid + 1], ml = mid, mr = mid + 1;
        int temp = arr[mid];
        // 从中往左边找最大
        for (int i = mid - 1; i >= begin; i--) {
            temp += arr[i];
            if (temp > maxLeftBorder) {
                maxLeftBorder = temp;
                ml = i;
            }
        }
        temp = arr[mid + 1];
        // 从中往右边找
        for (int i = mid + 2; i <= end; i++) {
            temp += arr[i];
            if (temp > maxRightBorder) {
                maxRightBorder = temp;
                mr = i;
            }
        }

        int res = max(max(maxLeft, maxRight), maxLeftBorder + maxRightBorder);
        if (res == maxLeft) {
            left = ll;
            right = lr;
        } else if (res == maxRight) {
            left = rl;
            right = rr;
        } else {
            left = ml;
            right = mr;
        }
        return res;
    }
};

int main() {
    SoMaxSubStr s;
    int arr[5] = {4, -1, -1, -1, 5};
    vector<int> vet(arr, arr + 5);
    int l, r = 0;
    cout << s.EnumFun(vet, l, r) << endl;
    cout << l << r << endl;
    cout << s.DvFun(vet, l, r) << endl;
    cout << l << r << endl;
    cout << s.DyFun(vet, l, r) << endl;
    cout << l << r << endl;
    cout << s.DyCirculateArr(vet, l, r) << endl;
    cout << l << r << endl;

}

