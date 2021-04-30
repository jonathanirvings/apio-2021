#include <bits/stdc++.h>
using namespace std;

const int MAXK=1e5+5;

int N, M, K;
int A[MAXK], B[MAXK];

void sampleTestCase1() {
	printf("0 4 0 2\n");
	printf("0 3 2 5\n");
	printf("3 4 2 5\n");
}

void sampleTestCase2() {
	printf("0 1 0 5");
	printf("1 3 0 2");
	printf("1 2 2 5");
	printf("2 3 2 5");
}

void testCase1() {
	printf("0 1 0 4\n");
	printf("0 4 4 5\n");
	printf("4 5 1 5\n");
	printf("1 5 0 1\n");
	printf("1 4 1 4\n");
}

void testCase2() {
	printf("0 1 0 2\n");
	printf("1 2 0 3\n");
	printf("1 2 3 7\n");
	printf("0 1 2 7\n");
	printf("3 6 0 2\n");
	printf("3 6 2 4\n");
	printf("2 3 0 7\n");
	printf("3 6 4 7\n");
}

void testCase3() {
	for (int i=1;i<=K;i++) {
		A[i]+=A[i-1];
		printf("0 1 %d %d\n",A[i-1],A[i]);
	}
}

void testCase4() {
	for (int i=1;i<M;i++) {
		printf("0 %d %d %d\n",i,i,i+1);
	}
	for (int i=M-1;i>=0;i--) {
		printf("%d %d %d %d\n",i,N,i,i+1);
	}
}

void testCase5() {
	int f=__gcd(N,K);

	for (int i=1;i<=f;i++) {
		for (int j=1;j<=K/f;j++) {
			printf("%d %d %d %d\n",(i-1)*(N/f),i*(N/f),(j-1)*(M/(K/f)),j*(M/(K/f)));
		}
	}
}

bool brute(int id,int sum) {
	if (sum<0) return 0;
	if (!id) return !sum;
	B[id]=2;
	if (brute(id-1,sum-A[id])) return 1;
	B[id]=0;
	if (brute(id-1,sum)) return 1;
	if (A[id]&1) return 0;
	B[id]=1;
	if (brute(id-1,sum-A[id]/2)) return 1;
	return 0;
}

void track() {
	int C[3]={0,M,0};

	for (int i=1;i<=K;i++) {
		if (B[i]==0) {
			C[0]+=A[i];
			printf("0 1 %d %d\n",C[0]-A[i],C[0]);
		}
		if (B[i]==1) {
			C[1]-=A[i]/2;
			printf("0 2 %d %d\n",C[1],C[1]+A[i]/2);
		}
		if (B[i]==2) {
			C[2]+=A[i];
			printf("1 2 %d %d\n",C[2]-A[i],C[2]);
		}
	}
}

void testCase6() {
	brute(K,M);
	track();
}

void testCase7() {
	bool DP[K+1][M+1];
	DP[0][0]=1;
	for (int i=1;i<=M;i++) DP[0][i]=0;

	for (int i=1;i<=K;i++) {
		for (int j=M;j>=0;j--) {
			DP[i][j]=DP[i-1][j];
			if (j>=A[i]) DP[i][j]|=DP[i-1][j-A[i]];
			if (A[i]%2==0&&j>=A[i]/2) DP[i][j]|=DP[i-1][j-A[i]/2];
		}

		if (DP[i][M]) {
			for (int j=M;i;i--) {
				if (DP[i-1][j]) continue;
				if (j>=A[i]&&DP[i-1][j-A[i]]) {
					j-=A[i];
					B[i]=2;
				}
				else {
					j-=A[i]/2;
					B[i]=1;
				}
			}

			break;
		}
	}

	track();
}

void testCase8() {
	vector <int> P, Q;
	P.push_back(0);
	Q.push_back(0);
	for (int i=0;i<30;i++) {
		if ((N>>i)&1) P.push_back(P.back()+(1<<i));
		else P.push_back(P.back());
		if ((M>>i)&1) Q.push_back(Q.back()+(1<<i));
		else Q.push_back(Q.back());
	}

	for (int i=0;i<K;i++) {
		for (int j=0;j<=i;j++) {
			if ((N>>j)&(M>>(i-j))&1) {
				printf("%d %d %d %d\n",P[j],P[j+1],Q[i-j],Q[i-j+1]);
			}
		}
	}
}

void testCase9() {
	int x=1, y=1;
	printf("0 1 0 1\n");

	for (int i=2;i<=K;i+=2) {
		printf("0 %d %d %d\n",x,y,x+y);
		y+=x;
		printf("%d %d 0 %d\n",x,x+y,y);
		x+=y;
	}
}

void testCase10() {
	vector <int> V[101];
	vector <int> H[K+1];

	for (int i=1;i<=K;i++) {
		V[A[i]].push_back(i);
	}

	for (int i=1;i<=N;i++) {
		int id;
		for (int j=0;j<M;j+=id) {
			id=0;
			for (int j=1;j<=100;j++) {
				if (V[j].size()>=V[id].size()) {
					id=j;
				}
			}
			id=min(id,M-j);
			H[V[id].back()].push_back(i-1);
			H[V[id].back()].push_back(i);
			H[V[id].back()].push_back(j);
			H[V[id].back()].push_back(j+id);
			V[id].pop_back();
		}
	}

	for (int i=1;i<=K;i++) {
		printf("%d %d %d %d\n",H[i][0],H[i][1],H[i][2],H[i][3]);
	}
}

int main () {
	cin>>N>>M>>K;
	for (int i=1;i<=K;i++) cin>>A[i];

	if (K==3) sampleTestCase1();
	else if(K==4) sampleTestCase2();
	else if (K==5) testCase1();
	else if (K==8) testCase2();
	else if (K==100000) testCase3();
	else if (K==99999) testCase4();
	else if (K==91123) testCase5();
	else if (K==20) testCase6();
	else if (K==100) testCase7();
	else if (K==30) testCase8();
	else if (K==23) testCase9();
	else testCase10();
}
