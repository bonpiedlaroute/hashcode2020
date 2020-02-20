#include <iostream>
#include <fstream>
#include <vector>
#include "MyFile.h"

using namespace std;

int M, number;

int best = 0;
vector<int> solution;
vector<int> p;
vector<int> s;

bool finished = false;

void search(vector<int>& current, int& sum, int k, int length)
{
   // if (finished)
   // {
   //    return;
   // }
   if (k == length )
   {
      if (sum > best)
      {
         best = sum;
         solution.clear();
         solution = current;
         cout << "best " << best << endl;
         // for (int d : current)
         // {
         //    cout << d << " ";
         // }
         // cout << endl;
         // if (best == 505000000)
         // {
         //    finished = true;
         // }
         return;
      }
   }
   else
   {
      if (sum + s[k] <= best) return;
      if (sum + p[k] <= M)
      {
         current.push_back(length-1-k);
         sum+= p[k];
         search(current, sum, k+1, length);
         current.pop_back();
         sum-= p[k];
      }

      search(current, sum, k+1, length);
   }
}


int main(int argc, const char* argv[])
{
   print_file();
   string inputFile(argv[1]);
   ifstream input(inputFile);
   vector<int> pizzas;
   vector<int> s2;
   input >> M >> number;
   int somme = 0;
   for (int i = 0; i < number ; i++)
   {
      int d;
      input >> d;
      pizzas.push_back(d);
      somme += d;
      s2.push_back(somme);
   }

   for (int i = number-1; i>= 0; i--)
   {
      p.push_back(pizzas[i]);
      s.push_back(s2[i]);
   }

   int sum = 0;
   vector<int> current;
   search(current, sum, 0, number);

   ofstream file;
   file.open("output.txt");
   file << solution.size() << endl;
   for (int i = solution.size()-1; i>= 0; i--)
   {
      file << solution[i] << " ";
   }
   file.close();
   return 0;
}
