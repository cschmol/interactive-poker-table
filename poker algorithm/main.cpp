
#include <cstdlib>
#include <ctime>

#include <iostream>
#include "SevenEval.h"




int main() {


  srand((unsigned)time(0));

  SevenEval const* eval = new SevenEval();

  /*Indizes f�r Karten

  0: Pick Ass, 1: Herz Ass, 2: Karo Ass ,3: Kreuz Ass
  4: Pick K�nig.... */

  for (int i=0;i<100;i++)
  {

    std::cout << eval->GetRank(rand()%7, rand()%7+7, rand()%7+14, rand()%7+21, rand()%7+28, rand()%7+35, rand()%7+42) << std::endl;
  }

  delete eval;
  return 0;
}
