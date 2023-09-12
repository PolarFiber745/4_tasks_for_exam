#include <iostream>
#include <vector>

using namespace std;


// creating our matrix of values for every possible weight depending on choice whether to pick item or not
void sol_matrix(long long N, long long W, std :: vector < vector <long long>> &sol, std :: vector <long long> &v, std :: vector <long long> &w){
    long long i, j;
    for (i = 0; i < N; i++)
    {
		for (j = 0; j <= W; j++)
		{
			if (w[i] > j)
            {
                if (i > 0)
                sol[i][j] = sol[i - 1][j];
			}
			else
			{
                if (i > 0)
					sol[i][j] = max(sol[i - 1][j], sol[i - 1][j - w[i]] + v[i]);
				else
					sol[i][j] = v[i];
			}
		}
	}
}

//creating an array containing our final choice of picked items
void Arraysol(long long N,long long W, std:: vector <int> &res, std :: vector <long long> &v, std :: vector <long long> &w )
{
    long long i, j;
    vector < vector <long long>> sol(N, vector <long long> (W + 1, 0));
    sol_matrix(N, W, sol, v, w);
    i = N - 1; j = W;
	while (sol[i][j])
	{
		if (i != 0)
        {
			if (sol[i][j] == sol[i - 1][j])
				i--;
			else if (sol[i][j] == v[i] + sol[i - 1][j - w[i]])
			{
				res[i] = 1;
				j = j - w[i];
				i--;
			}
		}
		else break;
	}
    long long vsum = 0, wsum = 0;
    for (i = 0; i < N; i++)
	{
	    if (res[i] != 0)
        {
		    vsum += v[i];
		    wsum += w[i];//res
	    }
	}
	// having issues with creating output in main
	cout << vsum<<' ';
	cout  << W - wsum << endl;
	for (i = 0; i < N; i++)
	    cout << res[i] << ' ';
}

int main(){
    long long N, W, vi, wi, i, j;
    vector <long long> v(N);
	vector <long long> w(N);
	cin >> N >> W;
	for (i = 0; i < N; i++)
    {
		cin >> vi >> wi;
		v[i] = vi;
		w[i] = wi;
	}
	vector <int> res(N, 0);
    Arraysol(N, W, res, v, w);
    return 0;
}
