#include <bits/stdc++.h>
using namespace std;

long long n,ans,i,j;
long long a[3003],suf[3003],pref[3003],pos[3003];

void timet(){
	for(i=1;i<=3000;i++)a[i]=i;
	n=3000;
}

/*
для каждой пары есть три варианта оптимальной сортировки:
1 весь массив
2 префикс с левым элементом
3 суффикс с правым элементом

макс. расстояние:
1 разность элементов
2 разность индексов + кол-во элементов в префиксе левого, которые больше него
3 разность индексов + кол-во элементов в суффиксе правого, которые меньше него

---

1 считаем префиксные и суффиксные кол-ва для каждого индекса
2 для каждой пары к ответу прибавляем макс. из трех возможных расстояний
*/

void solve(){
	for(i=1;i<=n;i++)pos[a[i]]=i;
	for(i=1;i<=n;i++)suf[i]=0,pref[i]=0;
	
	for(i=1;i<=n;i++)for(j=i;j<=n;j++)suf[i]+=(a[j]<a[i]);
	for(i=1;i<=n;i++)for(j=i;j>=1;j--)pref[i]+=(a[j]>a[i]);
	
	ans=0;
	for(i=1;i<n;i++)for(j=i+1;j<=n;j++){
		if(pos[i]>pos[j]){
			ans+=max(j-i,pos[i]-pos[j]+max(suf[pos[i]],pref[pos[j]]));
		}
		else{
			ans+=max(j-i,pos[j]-pos[i]+max(suf[pos[j]],pref[pos[i]]));
		}
	}
	cout<<ans<<'\n';
}

int main(){
	ios::sync_with_stdio(0);cin.tie(0);
	cin>>n;for(i=1;i<=n;i++)cin>>a[i];
	//timet();
	clock_t t_start=clock();
	solve();
	clock_t t_end=clock();
	//cout<<setprecision(4)<<"time: "<<1000.0*(t_end-t_start)/CLOCKS_PER_SEC<<" ms\n";
    return 0;
}

/*
10
2 1 6 8 3 5 9 10 7 4

*/