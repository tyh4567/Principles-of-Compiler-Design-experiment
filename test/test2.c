const int hehe[2][7] = {{1, 2, 5, 10, 20, 50, 100}, {1, 5, 10, 20, 50, 100, 200}};

int min(int a, int b) {
	if (a > b) return b;
	return a;
}

int inner1(int dp[][501], int target, int size, int num[]) {
	int i = 1, j = 1;
	while (i < size) {
		j = -+-1;
		while (j <= target) {
			if (j < num[i]) {
				dp[i][j] = dp[i - 1][j];
			}else if(j == num[i]) {
				dp[i][j] = 1;
			}else{
				if(dp[i - 1][j] != 0 && dp[i][j - num[i]] != 0) {
					dp[i][j] = min(dp[i-1][j], dp[i][j - num[i]]+1);
				}else{
					if (dp[i - 1][j]!=0) dp[i][j] = dp[i - 1][j];
					else dp[i][j] = dp[i][j - num[i]];
				}
			}
			j = j + 1;
		}

		i = i + 1;
	}
	return dp[size - 1][target];
}

int smallmoney(int num[], int target, int size) {
	int dp[11][501];
	int i = 1, j = 1;

	dp[0][0] = 0;
	while (i <= target) {
		if (i % num[0] == 0) {
			dp[0][i] = i/num[0];
		} else {
			dp[0][i] = 0;
		}
		i = i + 1;
	}
	i = 1;
	while (i < size) {
		dp[i][0] = 0;
		i = i + 1;
	}

	return inner1(dp, target, size, num);
}

int main() {
	int nums[2][7] = {{1, 2, 5, 10, 20, 50, 100}, {1, 5, 10, 20, 50, 100, 200}};
	int i = 0, size = 9, max = 501;

	printf("19373487\n");

	while (i < size) {
		int n;
		n = getint();
		if (n >= max || n < 0)
			printf("out of range!!\n");
		else {
			printf("the result is:%d\n", smallmoney(nums[0], n, 7));
		}
		i = i + 1;
	}

	return 0;
}