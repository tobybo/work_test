// 剑指 Offer 64. 求1+2+…+n
//
// 求 1+2+...+n ，要求不能使用乘除法、for、while、if、else、switch、case等关键字及条件判断语句（A?B:C）。
//
// 示例 1：
//
// 输入: n = 3
// 输出: 6
// 示例 2：
//
// 输入: n = 9
// 输出: 45
//
// 限制：
//
// 1 <= n <= 10000

// n(n + 1)/2 => (n^2 + n)>>1

int count = 0;
int base = n;
int sum = 0;
int dyn_base = base;

while (n > 1) {
	if (n & 1) {
		sum += base;
	}
	if ((n >> 1) > 0) {
		dyn_base <<= 1;
		sum += dyn_base;
	}
}

// 特例
n = 1: 1
// 一般
n = 2: 4
n = 3: 9
n = 4: 16
n = 5: 30


