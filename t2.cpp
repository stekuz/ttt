#include <bits/stdc++.h>
using namespace std;
#define ll long long

ll p[100009],a[100009],l[100009],r[100009],sumsl[100009];
vector<pair<ll,ll>> c;
vector<ll> adj[100009];
bool filled[100009];
ll n,i,j,t,ans;
bool no;

void timet(){
	n=100000;
	p[1]=0;
	c.clear();
	ll t1;
	for(i=2;i<=n;i++)p[i]=i-1;
	for(i=1;i<=n;i++)c.emplace_back(19,i);
	for(i=1;i<=n;i++)l[i]=2,r[i]=5;
	
	filled[0]=1;
	for(i=1;i<=n;i++)adj[i].clear(),filled[i]=0,sumsl[i]=0;
	for(i=2;i<=n;i++)adj[p[i]].push_back(i);
}

void input(){
	cin>>n;
	p[1]=0;
	c.clear();
	ll t1;
	for(i=2;i<=n;i++)cin>>p[i];
	for(i=1;i<=n;i++){
		cin>>t1;
		c.emplace_back(t1,i);
	}
	for(i=1;i<=n;i++)cin>>l[i]>>r[i];
	
	filled[0]=1;
	for(i=1;i<=n;i++)adj[i].clear(),filled[i]=0,sumsl[i]=0;
	for(i=2;i<=n;i++)adj[p[i]].push_back(i);
}

/*
1 для каждой вершины v сумма l всех детей должна быть <= r[v],
	иначе выполнить все условия невозможно,
	при этом l[v] после обхода детей v должна быть равна макс. из l[v] и суммы l детей,
	т.к. в поддереве вершины не может находиться меньше элементов чем в сумме поддеревьев ее детей

2 чтобы заполнить дерево оптимально, можно отсортировать пары (стоимость, вершина) по стоимости
	и заполнять вершины по алгоритму 3 от вершины с меньшей стоимостью до вершины с большей

считаем, что родитель корня заполнен изначально

3 заполнение вершины v c родителем p[v] и суммой l детей sumsl[v]:
	если родитель заполнен:
		a[v] = l[v]-sumsl[v],
	иначе:
		a[v] = мин. из:
			макс. емкости v: r[v]-sumsl[v]
			и мин. емкости родителя: l[p[v]]-(sumsl[p[v]]-(l[v]-sumsl[v]))
			
	т.к l[v] изменилась, то нужно обновить sumsl[p[v]]:
		sumsl[p[v]]-=l[v];
		l[v]=sumsl[v]+a[v];
		sumsl[p[v]]+=l[v];
		
	помечаем вершину как заполненную, т.к. нет смысла заполнять для нее более дорогие вершины
*/

void dfs1(){
	ll suml,now;
	vector<bool> visited(n+2,0);
	stack<ll> s;
	s.push(1);
	
	while(!s.empty()){
		suml=0;
		now=-1;
		
		while(now!=s.top()){
			now=s.top();
			for(ll v:adj[now]){
				if(!visited[v]){
					s.push(v);
					visited[v]=1;
				}
			}
		}
		
		for(ll v:adj[now])suml+=l[v];
		if(suml>r[now])no=1;
		l[now]=max(l[now],suml);
		for(ll v:adj[now])sumsl[now]+=l[v];
		
		s.pop();
	}
}

ll fill(ll v){
	if(filled[p[v]])a[v]=l[v]-sumsl[v];
	else a[v]=min(r[v]-sumsl[v],l[p[v]]-(sumsl[p[v]]-(l[v]-sumsl[v])));
	
	sumsl[p[v]]-=l[v];
	l[v]=sumsl[v]+a[v];
	sumsl[p[v]]+=l[v];
	
	filled[v]=1;
	return a[v];
}

void solve(){
	no=0;
	ans=0;
	dfs1();
	if(no){
		cout<<"-1\n";
		return;
	}
	sort(c.begin(),c.end());
	for(i=0;i<n;i++)ans+=fill(c[i].second)*c[i].first;
	
	cout<<ans<<'\n';
	for(i=1;i<=n;i++)cout<<a[i]<<' ';
	cout<<'\n';
}

int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>t;
	clock_t t_start=clock();
	while(t--)input(),solve();
	//timet();solve();
	clock_t t_end=clock();
	//cout<<setprecision(4)<<"time: "<<1000.0*(t_end-t_start)/CLOCKS_PER_SEC<<" ms\n";
    return 0;
}

/*
2
3
1 1
3 1 2
5 7
1 2
2 4
2
1
5 5
0 1
2 2

*/