
#include <algorithm>    // std::shuffle
#include <array>        // std::array
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

#include <iostream>
#include "SevenEval.h"


const int NSAMPLEHANDS=10;
const int NMAXPLAYERS= 10;


float getProbability(int nPlayers, std::array<int,10> handcards,int nCommonCards, std::array<int,5> commoncards)
{
    int nFixedCards= nPlayers*2+nCommonCards;


    std::array<std::array<int,47>,NMAXPLAYERS> spare_cards_player;
    std::array<int,49> spare_cards_samples;
    spare_cards_samples.fill(0);

    for (int i= 0; i<NMAXPLAYERS; i++)
        spare_cards_player[i].fill(0);



    int cardindex1=0;
    int cardindexplayers[NMAXPLAYERS]={0,0,0,0,0,0,0,0,0,0};

    for (int i= 0; i<52; i++)
    {
        for (int k=0;k<nCommonCards;k++)
        {
            if (i!=commoncards[k])
            {

                spare_cards_samples[cardindex1]=i;
                cardindex1++;
            }
            else
            {
              for(int j=0;j<nPlayers;j++)
                {
                    if (i!=handcards[2*j] && i!=handcards[2*j+1])
                        spare_cards_player[j][cardindexplayers[j]]=i;
                        cardindexplayers[j]++;
                }
            }
        }
    }

    unsigned long handsum=0;
    unsigned long samplesum[NSAMPLEHANDS];

    switch(nCommonCards)
    {
    case 3:
        for (int i=0;i < NSAMPLEHANDS;i++)
        {
            handsum
        }

    }



    for (int i=0;i < NSAMPLEHANDS;i++)
    {
        if (nCommonCards==3)
        {

        }
        else if(nCommonCards==4)
        {

        }
        else if(nCommonCards ==5)
        {

        }
    }










    return 0;

    }














int main() {



  SevenEval const* eval = new SevenEval();

  /*Indizes für Karten

  0: Pick Ass, 1: Herz Ass, 2: Karo Ass ,3: Kreuz Ass
  4: Pick König.... */
/*
  std::array<int,5> foo {1,2,3,4,5};


  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

  shuffle (foo.begin(), foo.end(), std::default_random_engine(seed));

  std::cout << "shuffled elements:";
  for (int& x: foo) std::cout << ' ' << x;
  std::cout << '\n';

  for (int i=0;i<100;i++)
  {

    std::cout << eval->GetRank(rand()%7, rand()%7+7, rand()%7+14, rand()%7+21, rand()%7+28, rand()%7+35, rand()%7+42) << std::endl;
  }

  delete eval;
  return 0;*/
  std::array<int,10> foo {1,2,3,4,5,14,0,0,0,0};
  std::array<int,5> foo2 {33,34,35,0,0};
  getProbability(3,foo,3,foo2);
  return 0;
}
