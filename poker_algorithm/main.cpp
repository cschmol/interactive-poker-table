
#include <algorithm>    // std::shuffle
#include <array>        // std::array
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock

#include <iostream>
#include "SevenEval.h"





const int NSAMPLEHANDS=7;
const int NMAXPLAYERS= 10;


void getProbability(int nPlayers, std::array<int,10> handcards,int nCommonCards, std::array<int,5> commoncards,double *arr)
{

    SevenEval const* eval = new SevenEval();

    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::time_t now_c = std::chrono::system_clock::to_time_t(now - std::chrono::hours(24));

    auto engine = std::default_random_engine{};
    engine.seed(now_c);

    std::array<std::array<int,47>,NMAXPLAYERS> player_decks;
    std::array<std::array<int,47>,NMAXPLAYERS> spare_cards_player;
    //std::array<std::array<int,47>,NMAXPLAYERS> spare_cards_samples;


    for (int i= 0; i<NMAXPLAYERS; i++)
    {
        spare_cards_player[i].fill(0);
        //spare_cards_samples[i].fill(0);
        player_decks[i].fill(0);
    }




    int cardindexplayers[NMAXPLAYERS]={0,0,0,0,0,0,0,0,0,0};

    for (int i= 0; i<52; i++)
    {
        for (int k=0;k<nCommonCards;k++)
        {
              for(int j=0;j<nPlayers;j++)
                {
                    if (i!=handcards[2*j] && i!=handcards[2*j+1])
                    {
                        player_decks[j][cardindexplayers[j]]=i;
                        spare_cards_player[j][cardindexplayers[j]]=i;
                        cardindexplayers[j]++;
                    }
                }
            }
    }


    for(int j=0;j<nPlayers;j++)
    {
                std::shuffle(std::begin(spare_cards_player[j]), std::end(spare_cards_player[j]), engine);
                //std::shuffle(std::begin(spare_cards_samples[j]), std::end(spare_cards_samples[j]), engine);
    }


    std::array<int,NMAXPLAYERS> nPlayerWins;

    nPlayerWins.fill(0);
    int playerrank,samplerank;

    switch (nCommonCards)
    {
    case 3:
        for (int j=0;j<nPlayers;j++)
        {
                for (int k=0;k<NSAMPLEHANDS  ;k++)
                {
                    playerrank=eval->GetRank(handcards[j*2], handcards[j*2+1], commoncards[0], commoncards[1], commoncards[2], spare_cards_player[j][2*k], spare_cards_player[j][2*k+1]);
                    samplerank=eval->GetRank(commoncards[0], commoncards[1], commoncards[2], spare_cards_player[j][4*k], spare_cards_player[j][4*k+1],spare_cards_player[j][4*k+2],spare_cards_player[j][4*k+3]);
                    if (playerrank>samplerank)
                        nPlayerWins[j]++;
                }


        }
        break;
    case 4:
        for (int j=0;j<nPlayers;j++)
        {
                for (int k=0;k<NSAMPLEHANDS  ;k++)
                {
                    playerrank=eval->GetRank(handcards[j*2], handcards[j*2+1], commoncards[0], commoncards[1], commoncards[2], commoncards[3], spare_cards_player[j][k]);
                    samplerank=eval->GetRank(commoncards[0], commoncards[1], commoncards[2], commoncards[3], spare_cards_player[j][3*k],spare_cards_player[j][3*k+1],spare_cards_player[j][3*k+2]);
                    if (playerrank>samplerank)
                        nPlayerWins[j]++;


                }


        }
        break;
    case 5:
        for (int j=0;j<nPlayers;j++)
        {
                for (int k=0;k<NSAMPLEHANDS  ;k++)
                {
                    playerrank=eval->GetRank(handcards[j*2], handcards[j*2+1], commoncards[0], commoncards[1], commoncards[2], commoncards[3], commoncards[4]);
                    samplerank=eval->GetRank(commoncards[0], commoncards[1], commoncards[2], commoncards[3], commoncards[4],spare_cards_player[j][2*k],spare_cards_player[j][2*k+1]);
                    if (playerrank>samplerank)
                        nPlayerWins[j]++;
                }


        }
        break;
    }



    for (int j=0;j<nPlayers;j++)
    {
        *arr=static_cast<double>(nPlayerWins[j])/static_cast<double>(NSAMPLEHANDS);
        //std::cout<<*arr<<std::endl;
        arr++;
    }



    }












int main() {


  std::array<int,10> handcards {1,44,3,4,5,14,0,0,0,0};
  std::array<int,5> commoncards {33,34,35,7,0};


  double winprops[NMAXPLAYERS];
  getProbability(3,handcards,4,commoncards,&winprops[0]);


    //for (int i=0;i<3;i++)
    std::cout << winprops[0]<<std::endl;
    std::cout << winprops[1]<<std::endl;
    std::cout << winprops[2]<<std::endl;

  //std::cout << *winprops<<std::endl;

  return 0;
}
