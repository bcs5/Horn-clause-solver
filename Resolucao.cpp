#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>
#define fr(a,b,c) for(int a = b, _ = c; a < _; a++)
#define isVar(c) (c >= 'a' && c <= 'd')
#define pb push_back
using namespace std;
typedef vector<int> vi;
vi adj[6], component[6];
int degree[50][6];
void add(int key, int neg, int v, int n){
	int u = 0;
	fr(i,0,n){
		if(neg & (1<<i)) u |= 1 << (i+2);
	}
	if (!u) u = 2;
	fr(i, 0, n+2){
		if(u & (1 << i)){
			adj[i].pb(v);
			degree[key][v]++;
			component[i].pb(key);
		}
	}
}

bool sat(){
	int q[6], taken = 0;
	int l = 0, r = 0;
	int u, v, key;
	fr(i, 0, adj[1].size()){
		v = adj[1][i];
		if(taken & (1 << v)) continue;
		taken |= 1 << v;
		q[r++] = v;
	}
	while (l < r){
		u = q[l++];
		if (u == 0) return false;
		fr(i, 0, adj[u].size()){
			v = adj[u][i];
			key = component[u][i];
			if(taken & (1 << v)) continue;
			if(degree[key][v]){
				if(--degree[key][v] == 0){
					taken |= 1 << v;
					q[r++] = v;
				}
			}
		}
	}
	return true;
}
 
int main(){
	freopen("Expressoes.in", "r", stdin);
	freopen("Expressoes.out", "w", stdout);
	int c = 0, n, brackets, npos, key;
	string expr;
	int neg, pos;
	bool horn, fnc;
	cin >> n;
	while (n--){
		cin >> expr;
		horn = true;
		fnc = true;
		brackets = 0;
		key = 0;
		neg = pos = 0;
		npos = 0;
		fr(i, 0, expr.length()){
			if(expr[i] == '('){
				brackets++;
				i++;
			}
			if(!brackets && expr[i] != '.') fnc = false;
			if (expr[i] == ')'){
				add(key++, neg, pos, 4);
				neg = pos = 0;
				npos = 0;
				brackets--;
			}
			if (brackets){
				if(isVar(expr[i])){
					if (expr[i - 1] == '-'){
						neg |= 1 << (expr[i] - 'a');
					}else{
						if(npos++) horn = false;
						pos = (expr[i] - 'a')+2;
					}
				}else if(expr[i] != '-' && expr[i] != '+'){
					fnc = false;
				}
			}
		}
		printf("caso #%d: ", ++c);
		if(!fnc){
			printf("nao esta na FNC\n");
		}else if(!horn){
			printf("nem todas as clausulas sao de horn\n");
		}else if(sat()){
			printf("satisfativel\n");
		}else{
			printf("insatisfativel\n");
		}
		memset(degree, 0, sizeof(degree));
		fr(i, 0, 6){
			adj[i].clear();
			component[i].clear();
		}
	}
}
