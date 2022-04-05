#include <iostream>
#include <cstring>
#include <cstdio>
#include <algorithm>
#define lson  rt<<1, l, mid
#define rson  rt<<1|1, mid+1, r 
using namespace std;
const int maxn = 1e5;
int a[maxn];
struct node{
	int l, r;
	int sum;
	int lazy;
}tree[4*maxn];
int n, m;
void up(int rt){
	tree[rt].sum = tree[rt<<1].sum + tree[rt<<1|1].sum;
}
void down(int rt){
	if(tree[rt].lazy){
		tree[rt<<1].lazy += tree[rt].lazy;
		tree[rt<<1|1].lazy += tree[rt].lazy;
		tree[rt<<1].sum += tree[rt].lazy * (tree[rt<<1].r-tree[rt<<1].l+1);
		tree[rt<<1|1].sum += tree[rt].lazy * (tree[rt<<1|1].r-tree[rt<<1|1].l+1);
		tree[rt].lazy = 0;
	}
}
void build(int rt, int l, int r){
	tree[rt].l = l, tree[rt].r = r;
	tree[rt].lazy = 0;
	// 如果当前节点记录的区间只有一个值，说明找到了叶子结点，直接赋值
	// 否则递归构造左右子树，最后回溯的时候给当前节点赋值
	if(l == r){
		tree[rt].sum = a[l];
		return ;
	}
	int mid = (l + r) >> 1;
	build(rt<<1, l, mid);
	build(rt<<1|1, mid+1, r);
	tree[rt].sum = tree[rt<<1].sum + tree[rt<<1|1].sum;
}
/*
void update(int rt, int p, int val){
	// 单点修改 
	// 这个if语句就是判断是否到达叶子结点 
	if(tree[rt].l == tree[rt].r){
		tree[rt].sum = val;
		return ;
	}
	int mid = (tree[rt].l + tree[rt].r) >> 1;
	if(p <= mid)	update(rt<<1, p, val);
	else	 		update(rt<<1|1, p, val);
	tree[rt].sum = tree[rt<<1].sum + tree[rt<<1|1].sum;
}
*/
void update(int rt, int l, int r, int c){
	// 区间修改，同时增加c
	if(tree[rt].l >= l && tree[rt].r <= r){
		tree[rt].lazy += c;		// 记录这个标记
		tree[rt].sum += c * (tree[rt].r - tree[rt].l + 1);
		return ; 
	}
	down(rt);
	int mid = (tree[rt].l + tree[rt].r) >> 1;
	if(mid >= r)		update(rt<<1, l, r, c);
	else if(mid < l)	update(rt<<1|1, l, r, c);
	else{
		update(rt<<1, l, mid, c);
		update(rt<<1|1, mid+1, r, c);
	}
	tree[rt].sum = tree[rt<<1].sum + tree[rt<<1|1].sum;
}
/*
int query(int rt, int p){
	// 单点查询
	if(tree[rt].l == tree[rt].r)	
		return tree[rt].sum;
	int mid = (tree[rt].l + tree[rt].r) >> 1; 
//	down(rt);
	int ans;
	if(p <= mid)	ans = query(rt<<1, p);
	else	ans = query(rt<<1|1, p);
	return ans;
}
*/
int query(int rt, int l, int r){
	// 区间查询 
	if(tree[rt].l >= l && tree[rt].r <= r)
		return tree[rt].sum;
	down(rt);		// 用到lazy数组 
	int mid = (tree[rt].l + tree[rt].r) >> 1; 
	if(r <= mid)		return query(rt<<1, l, r);
	else if(mid < l)	return query(rt<<1|1, l, r);
	else
		return query(rt<<1, l, mid) + query(rt<<1|1, mid+1, r);
}
int main(){
	cin >> n ;
	for(int i = 1; i <= n; i++)	
		cin >> a[i];
	build(1, 1, n);
	for(int i = 1; i <= 15; i++)	
		cout << tree[i].sum <<" "<< tree[i].lazy << endl;
		cout << query(1, 3, 6) << endl;		 
	return 0;
}

