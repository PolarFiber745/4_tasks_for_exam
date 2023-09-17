#include<iostream>
#include<fstream>
#include<iomanip>
#include<list>
#include<vector>
#include<cmath>
#include<algorithm>
using namespace std;

struct CSet
{
  int c;
  int index; // unit cost
  vector<int> elements;
};

int input(vector<CSet> &Sets, string filename)
{
  int N, M, c, s;
  string line;
  CSet S_tmp;
  ifstream input_file(filename);
  if (input_file.is_open())
  {
    input_file >> N;
    input_file >> M;
    for(size_t i=0; i<M; i++)
    {
      input_file >> S_tmp.c;
      getline(input_file, line);
      istringstream iss(line);
      while (iss >> s) S_tmp.elements.push_back(s);
      S_tmp.index = i;
      Sets.push_back(S_tmp);
      S_tmp.elements.clear();
    }
  }

  input_file.close();
  return N;
}

int Coef_Need(CSet a, vector<int> used)
{
  int cnt=0;
  for(auto x: a.elements)
  {
    if(used[x] == 0) cnt++;
  }
  return cnt;
}

bool UsedElements(vector<int> used)
{
  int cnt = 0;
  int size = used.size();
  for(size_t i = 0; i < size; i++)
  {
    if(used[i] == 1)
        cnt++;
  }
  return cnt == size;
}

double Sol(vector<CSet> &Sets, int N, vector<int> &used_sets)
{
  vector<int> used_elem;
  double sum = 0;

  for(int i = 0; i < N; i++) used_elem.push_back(0);
  for(int i = 0; i < Sets.size(); i++) used_sets.push_back(0);
  int needSet_index = -1;
  int needSet_coef = -1, Coef;

  while(!UsedElements(used_elem))
  {
    for(auto s: Sets)
    {
      if(used_sets[s.index] == 0)
      {
        Coef = Coef_Need(s, used_elem);
        if(Coef > needSet_coef)
        {
            needSet_coef = Coef;
            needSet_index = s.index;
        }
      }
    }
    if(needSet_index > -1)
    {
      for(auto x: Sets[needSet_index].elements) used_elem[x] = 1;
      sum += Sets[needSet_index].c;
      used_sets[needSet_index] = 1;
    }
    needSet_coef = -1;
    needSet_index = -1;
  }
  return sum;
}

int main()
{
    vector<CSet> Sets;
    vector<int> used;
    string filename;
    cout << "Enter the filename from the list of tests (for example, sc_6_1):";//from the list of tests
    cin >> filename;
    int N = input(Sets, filename);
    cout << Sol(Sets, N, used) << endl;
    for(auto u: used) cout << u << " ";
    cout << endl;
    return 0;
}
