#include <iostream>
#include <fstream>
#include <vector>
#include <set>
#include <algorithm>

using namespace std;

float a = 0.5;
float b = 1-a;

double totalScore = 0;

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
   double score;
   double scorePercentage;
   double finalScore;

   Lib(int _id, int n, int t, int m, set<int>& bks): 
      id(_id), N(n), T(t), M(m), booksId(bks)
   {
      int sum = 0;
      for (int id : booksId)
      {
         sum += books[id].score;
      }
      score = sum;
   }
};

vector<Lib> libs;

struct Naive
{
   bool operator()(Lib& a, Lib& b) const
   {
      if (a.T != b.T)
      {
         return a.T < b.T;
      }
      else
      {
         return a.score > b.score;
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
      Lib lib(i, n, t, m, books);
      libs.push_back(lib);
      totalScore += lib.score;
   }

   for (auto& lib : libs)
   {
      lib.scorePercentage = lib.score/totalScore;
   }
   
   Naive comp;
   std::sort(libs.begin(), libs.end(), comp);
   
   ofstream file;
   string outputName = argv[1];
   outputName.append("output.txt");
   file.open(outputName);
   file << L << endl;
   for (int i = 0; i < L; i++)
   {
      Lib& lib = libs[i];
      cout << lib.scoreRatio << ":" << lib.T << " ";
      file << lib.id << " " << lib.N << endl;
      auto& bks = lib.booksId;
      for (int bookId : bks)
      {
         file << bookId << " ";
      }
      file << endl;
   }
   file.close();
   
   cout << endl;
   cout << "End" << endl;
   return 0;
}
