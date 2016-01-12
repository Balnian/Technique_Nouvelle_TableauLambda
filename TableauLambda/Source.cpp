#include <iostream>
#include <vector>
#include <functional>
#include <conio.h>
#include <locale>
using namespace std;

class Clavier
{

   vector<function<bool(char)>> abonnes;

public:
   template <class F>
   void abonner(F f)
   {
      abonner.push_back(f);
   }

   char lire_touche()
   {
      return _getche();
   }
   bool reagir(char c)
   {
      bool quitter = false;
      for (auto & f : abonnes)
         if (f(c))
            quitter = true;

      return quitter;
   }

   void executer()
   {
      for (char c = lire_touche(); !reagir(c); c = lire_touche())
         ;
   }
};

char ROT13_encoder(char c)
{
   const auto & loc = locale{ "" };
   if (!isalpha(c, loc))return c;
   if (isupper(c)) return ((c - 'A') + 13) % 26 + 'A';
   return ((c - 'a') + 13) % 26 + 'a';

}

char ROT13_decoder(char c)
{
   return ROT13_encoder(c);
}

int main()
{
   Clavier clav;
   clav.abonner([](char c) { return c == 'q' || c == 'Q'; });
   clav.abonner([](char c)->bool {
      if (c == '.') cout << '\a' << flush;
      return false;
   });
   clav.abonner([](char c) {
      cout << c << ' ';
      return false;
   });
   clav.abonner([](char c){
      cout << toupper(c) << ' ';
      return false;
   });

   clav.executer();
   cout << endl;
}