#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

int M, number;

int best = 0;
vector<int> solution;
vector<int> p;
vector<int> s;

int B,L,D;
struct Book
{
   int id;
   int score;
};

vector<Book> books;

struct Lib
{
   int id;
   int N;
   int T;
   int M;
   set<int> booksId;
   double naiveRatio;

   Lib(int _id, int n, int t, int m, set<int>& bks): 
      id(_id), N(n), T(t), M(m), booksId(bks)
   {
      int sum = 0;
      for (int id : booksId)
      {
         sum += books[id].score;
      }
      naiveRatio = ((double)sum)/M;
   }
};

vector<Lib> libs;

struct Naive
{
   bool operator()(Lib& a, Lib& b) const
   {
      if (a.naiveRatio != b.naiveRatio)
      {
         return a.naiveRatio > b.naiveRatio;
      }
      else
      {
         return a.T < b.T;
      }
   }
};

int main(int argc, const char* argv[])
{
   string inputFile(argv[1]);
   ifstream input(inputFile);
   input >> B >> L >> D;

   for (int i = 0; i < B; ++i)
   {
      int s;
      input >> s;
      books.push_back({i,s});      
   }

   for (int i = 0; i < L; i++)
   {
      int n, t, m;
      input >> n >> t >> m;
      set<int> books;
      for (int j = 0; j < n; ++j)
      {
         int d;
         input >> d;
         books.insert(d);
      }
      libs.push_back({i, n, t, m, books});
   }
   
   Naive comp;
   std::sort(libs.begin(), libs.end(), comp);
   
   ofstream file;
   file.open("output.txt");
   file << L << endl;
   for (int i = 0; i < L; i++)
   {
      Lib& lib = libs[i];
      file << lib.id << " " << lib.N << endl;
      auto& bks = lib.booksId;
      for (int bookId : bks)
      {
         file << bookId << " ";
      }
      file << endl;
   }
   file.close();

   cout << "End" << endl;
   return 0;
}
