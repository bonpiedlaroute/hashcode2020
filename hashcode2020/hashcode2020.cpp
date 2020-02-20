// hashcode2020.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <fstream>
#include <vector>

void split(const std::string& str, const std::string& delimiter, std::vector<std::string>& results)
{
   std::string::size_type pos = 0, cur = 0;

   while ((pos = str.find(delimiter.c_str(), cur)) != std::string::npos)
   {
      std::string word = str.substr(cur, pos - cur);
      results.emplace_back(word);
      cur = pos + 1;
   }

   std::string word = str.substr(cur, str.length() - cur);
   results.emplace_back(word);
}

void read_input(const std::string& filename)
{
   std::fstream f;
   f.open(filename.c_str(), std::ios_base::in);
   if (f.is_open())
   {
      std::string line;
      while (std::getline(f, line))
      {
         std::vector <std::string> tokens;
         split(line, " ", tokens);

         // insert tokens in the correct data structure test
      }
   }
   else
   {
      std::cout << "Cannot open file " << filename << "\n";
   }
   f.close();
}

void write_output(const std::string& filename)
{
   std::fstream f;
   f.open(filename.c_str(), std::ios_base::out);

   if (f.is_open())
   {
      //f << some_value;
      //f << " ";
      //f << "\n";

   }
   else
   {
      std::cout << "Cannot open file " << filename << "\n";
   }
   
   f.close();
}

int main(int argc, char* argv[])
{
   if (argc != 3)
   {
      std::cout << "hashcode2020.exe [input_file] [output_file]\n";
      return 1;
   }

   std::string input = argv[1];
   std::string output = argv[2];

   read_input(input);



   write_output(output);


    return 0;
}
