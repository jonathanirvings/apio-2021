#include <bits/stdc++.h>
#define pii pair<int,int>
#define i1 first
#define i2 second
using namespace std;

const int MAXK=1e5+5;

int N, M, K;
int A[MAXK];
int H[MAXK][4];
int last;
bool trans;
vector <pii> kosong;
set <pii> sisa;
map <int,int> cnt;
priority_queue <pii> best;

void pas() {
  for (int i=1;i<=N&&!sisa.empty()&&sisa.begin()->i1<=M;i++) {
    int id, len, occ;
    for (int j=0;!sisa.empty()&&j<M;j+=len) {
      while (1) {
        len=best.top().i2;
        occ=best.top().i1;
        
        if (cnt[len]==occ) {
          id=sisa.lower_bound({len,0})->i2;
          break;
        }
        
        best.pop();
      }
      if (j+len>M) {
        if (j+sisa.begin()->i1>M) {
          for (int k=M;k>j&&kosong.size()<K;k--) {
            kosong.push_back({i,k});
          }
          break;
        }
        
        auto it=sisa.lower_bound({M-j+1,0});
        --it;
        
        len=it->i1;
        id=it->i2;
      }
      sisa.erase({len,id});
      cnt[len]--;
      best.push({cnt[len],len});
      H[id][0]=i-1;
      H[id][1]=i;
      H[id][2]=j;
      H[id][3]=j+len;
      last=i;
    }
  }
}

void lebih() {
  for (int i=last;!sisa.empty();) {
    int len=sisa.begin()->i1, id=sisa.begin()->i2;
    int row=(len+M-1)/M;
    int col=(len+row-1)/row;
    
    if (i+row>N) {
      break;
    }
    
    for (int j=1;j<=row&&kosong.size()<K;j++) {
      for (int k=M;k>col&&kosong.size()<K;k--) {
        kosong.push_back({i+j,k});
      }
    }
    
    H[id][0]=i;
    H[id][1]=i+row;
    H[id][2]=0;
    H[id][3]=col;
    sisa.erase(sisa.begin());
    i+=row;
  }
}

void kurang() {
  int id;
  pii x;
  
  while (!sisa.empty()) {
    id=sisa.begin()->i2;
    sisa.erase(sisa.begin());
    
    if (kosong.empty()) {
      H[id][0]=-1;
      H[id][1]=-1;
      H[id][2]=-1;
      H[id][3]=-1;
      continue;
    }
    
    x=kosong.back();
    kosong.pop_back();
    H[id][0]=x.i1-1;
    H[id][1]=x.i1;
    H[id][2]=x.i2-1;
    H[id][3]=x.i2;
  }
}

int main () {
  cin>>N>>M>>K;
  
  for (int i=1;i<=K;i++) {
    cin>>A[i];
    sisa.insert({A[i],i});
    cnt[A[i]]++;
  }
  
  for (pii x : cnt) {
    best.push({x.i2,x.i1});
  }
  
  if (N>M) {
    swap(N,M);
    trans=1;
  }
  
  pas();
  lebih();
  kurang();
  
  for (int i=1;i<=K;i++) {
    if (trans) {
      swap(H[i][0],H[i][2]);
      swap(H[i][1],H[i][3]);
    }
    printf("%d %d %d %d\n",H[i][0],H[i][1],H[i][2],H[i][3]);
  }
}
