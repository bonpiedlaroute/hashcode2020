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

int B, L, D;
struct Book
{
   int id;
   int score;
   bool done;
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

   Lib(int _id, int n, int t, int m, set<int>& bks) :
      id(_id), N(n), T(t), M(m), booksId(bks)
   {
      int sum = 0;
      for (int id : booksId)
      {
         sum += books[id].score;
      }
      naiveRatio = ((double)sum) / M;
   }

   void updateratio()
   {
      int sum = 0;
      for (int id : booksId)
      {
         if(!books[id].done)
         sum += books[id].score;
      }
      naiveRatio = ((double)sum) / M;
   }
};

vector<Lib> libs;

struct Naive
{
   bool operator()(Lib& a, Lib& b) const
   {
      /*if (a.T != b.T)
      {
         return a.T < b.T;
      }
      else
      {
         return a.naiveRatio > b.naiveRatio;
      }*/
      if (a.naiveRatio != b.naiveRatio)
      {
         return a.naiveRatio > b.naiveRatio;
      }
      else
      {
         return a.T < b.T;
      }
      /*if (a.M != b.M)
      {
         return a.M < b.M;
      }
      else
      if (a.naiveRatio != b.naiveRatio)
      {
         return a.naiveRatio > b.naiveRatio;
      }
      else
      {
         return a.T < b.T;
      }*/
      /*if (a.T != b.T)
      {
         return a.T < b.T;
      }
      else
         if (a.M != b.M)
         {
            return a.M < b.M;
         }
         else 
         {
            return a.naiveRatio > b.naiveRatio;
         }*/
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
      books.push_back({ i,s,false });
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
      libs.push_back({ i, n, t, m, books });
   }

   Naive comp;
   std::sort(libs.begin(), libs.end(), comp);

   ofstream file;
   file.open("output.txt");
   file << L << endl;

   auto iter = libs.begin();
   std::vector<Lib> solutions;
   while (iter != libs.end())
   {
      Lib& lib = *iter;
      solutions.push_back(lib);
      auto& bks = (*iter).booksId;

      for (int bookId : bks)
      {
         books[bookId].done = true;
      }
      iter = libs.erase(iter);
      //update ratio
      for (auto l : libs)
      {
         l.updateratio();
      }
      std::sort(libs.begin(), libs.end(), comp);
   }

   for (int i = 0; i < solutions.size(); i++)
   {   
      Lib& lib = solutions[i];
      file << lib.id << " " << lib.N << endl;
      auto& bks = lib.booksId;
      for (int bookId : bks)
      {
            file << bookId << " ";         
      }
      file << endl;

      //delete books already done
      //for (int bookId : bks)
      //{
      //   for (auto l : libs)
      //   {
      //      l.booksId.erase(bookId);
      //   }
      //}

   }

   
   file.close();

   cout << "End" << endl;
   return 0;
}
