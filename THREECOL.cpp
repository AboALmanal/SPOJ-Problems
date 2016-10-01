#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define inf INFINITY
#define l curr -> seg[1]
#define r curr -> seg[2]
#define MOD 1000000007

using namespace std;
typedef long long ll;
const int MAX = 1e5 + 10;
const int MIN = 5e3 + 10;
const int MAXI = 1e4;
const int MINI = -INT_MAX;
const ll MAXL = 1e17 + 10;
const ll MINL = -(1e17 + 10);

struct node {
	struct node* seg[5];
} *head = new node();

int a1, a2, a3;
char s[MAX];
map <pair <node*, int>, int> dp1, dp2;

int build (node* curr, int p) {
	dp1[mp(curr, 0)] = dp1[mp(curr, 1)] = dp1[mp(curr, 2)] = -1;
	dp2[mp(curr, 0)] = dp2[mp(curr, 1)] = dp2[mp(curr, 2)] = -1;
	curr -> seg[1] = NULL;
	curr -> seg[2] = NULL;
 	if (s[p] == '0') 
		return p;
	if (s[p] == '1') {
		curr -> seg[1] = new node();
		int tmp = build(curr -> seg[1], p + 1);
		return tmp;
	}
	else {
		curr -> seg[1] = new node();
		curr -> seg[2] = new node();
		int tmp1 = build(curr -> seg[1], p + 1);
		int tmp2 = build(curr -> seg[2], tmp1 + 1);
		return tmp2;
	}
}

int bt1 (node* curr, int color) {
	int ret = 0;
	if (curr -> seg[1] == NULL && curr -> seg[2] == NULL)
		return 0;
	if (dp1[mp(curr, color)] != -1) return dp1[mp(curr, color)];
	if (curr -> seg[1] != NULL && curr -> seg[2] == NULL) {
		if (color == 0) {
			ret = max (ret, bt1(l, 1));
			ret = max (ret, bt1(l, 2));
		}
		if (color == 1) {
			ret = max (ret, bt1(l, 0) + 1);
			ret = max (ret, bt1(l, 2));
		}
		if (color == 2) {
			ret = max (ret, bt1(l, 0) + 1);
			ret = max (ret, bt1(l, 1));
		}
	}
	else {
		if (color == 0) {
			ret = max (ret, bt1(l, 1) + bt1(r, 2));
			ret = max (ret, bt1(l, 2) + bt1(r, 1));
		}
		if (color == 1) {
			ret = max (ret, (bt1(l, 0) + 1) + bt1 (r, 2));
			ret = max (ret, (bt1(r, 0) + 1) + bt1 (l, 2));
		}
		if (color == 2) {
			ret = max (ret, (bt1(l, 0) + 1) + bt1 (r, 1));
			ret = max (ret, (bt1(r, 0) + 1) + bt1 (l, 1));
		}
	}
	dp1[mp(curr, color)] = ret;
	return ret;
}

int bt2 (node* curr, int color) {
	int ret = MAXI;
	if (curr -> seg[1] == NULL && curr -> seg[2] == NULL)
		return 0;
	if (dp2[mp(curr, color)] != -1) return dp2[mp(curr, color)];
	if (curr -> seg[1] != NULL && curr -> seg[2] == NULL) {
		if (color == 0) {
			ret = min (ret, bt2(l, 1));
			ret = min (ret, bt2(l, 2));
		}
		if (color == 1) {
			ret = min (ret, bt2(l, 0) + 1);
			ret = min (ret, bt2(l, 2));
		}
		if (color == 2) {
			ret = min (ret, bt2(l, 0) + 1);
			ret = min (ret, bt2(l, 1));
		}
	}
	else {
		if (color == 0) {
			ret = min (ret, bt2(l, 1) + bt2(r, 2));
			ret = min (ret, bt2(l, 2) + bt2(r, 1));
		}
		if (color == 1) {
			ret = min (ret, (bt2(l, 0) + 1) + bt2 (r, 2));
			ret = min (ret, (bt2(r, 0) + 1) + bt2 (l, 2));
		}
		if (color == 2) {
			ret = min (ret, (bt2(l, 0) + 1) + bt2 (r, 1));
			ret = min (ret, (bt2(r, 0) + 1) + bt2 (l, 1));
		}
	}
	dp2[mp(curr, color)] = ret;
	return ret;
}

int main ()
{
	int t = 1, ans = 0;
	scanf("%d", &t);
	while (t--) {
		scanf("%s", &s);
		build (head, 0);
		a1 = bt1(head, 0) + 1;
		a2 = bt1(head, 1);
		a3 = bt1(head, 2);
		ans = max (a1, max(a2, a3));
		cout << ans << ' ';
		a2 = bt2(head, 0) + 1;
		a2 = bt2(head, 1);
		a3 = bt2(head, 2);
		ans = min (a1, min(a2, a3));
		cout << ans;
		if (t != 0) cout << endl;
	}
	return 0;
}
