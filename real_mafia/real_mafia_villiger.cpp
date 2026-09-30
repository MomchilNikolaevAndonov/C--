#include <algorithm>
#include <iostream>
#include <cstdlib> // Needed for rand() and srand()
#include <ctime>   // Needed for time()
#include <vector>
#include <typeinfo>
using namespace std;


int vill_wins = 0;
int killers_wins = 0;


class villiger
{
  public:
    using Self = villiger;
    static int br;
    bool healed = false;

            static vector<villiger*> Add(vector<villiger*>& V_players){
            for (int i = 0; i < Self::br; i++)
                V_players.push_back(new Self);
            
            cout<<V_players.size();
            return V_players;
        }

    static int Left(const vector<villiger*>& V_players) {
    return count_if(V_players.begin(), V_players.end(), [](villiger* p) {
        return dynamic_cast<Self*>(p) != nullptr;
    });
}
    virtual ~villiger() = default;

};int villiger::br = 0;


class killer : public villiger
{
    public:
        using  Self = killer;
        static int br;
        killer() = default;

         static vector<villiger*> Add(vector<villiger*>& V_players) {
            for (int i = 0; i < Self::br; i++)
                V_players.push_back(new Self);
            return V_players;
        }


        static vector<villiger*> kill(vector<villiger*>& V_players){
            int index = 0;

            do {
                 index = rand() % V_players.size();
            }while(( dynamic_cast<killer*>(V_players[index]) != nullptr || dynamic_cast<super_killer*>(V_players[index]) != nullptr  )|| V_players[index]->healed
);
            
            if( V_players[index]->healed != true)
             V_players.erase(V_players.begin() + index);

        return V_players;
        }

        ~killer(){}
};int killer::br = 0;


class super_killer : public killer
{
    public:
        using Self = super_killer;
        static int br;
        super_killer() = default;

    static vector<villiger*> Add(vector<villiger*>& V_players){
        for (int i = 0; i < Self::br; i++)
            V_players.push_back(new Self);
        return V_players;
    }

    static vector<villiger*> kill(vector<villiger*>& V_players){
            int index = 0;

            do {
                 index = rand() % V_players.size();
            }while(!(dynamic_cast<Self*>(V_players.at(index)) == nullptr && V_players.at(index)->healed != true));

            if( V_players[index]->healed != true)
             V_players.erase(V_players.begin() + index);
             //return "a player was killed";

        //"no one was killed";
        return V_players;

        }

        ~super_killer(){}
};int super_killer::br = 0;



class healer : public villiger
{
    public:
        using Self = healer;
        static int br;
        healer() = default;

    static vector<villiger*> Add(vector<villiger*>& V_players)
    {
        for (int i = 0; i < Self::br; i++)
            V_players.push_back(new Self);
        return V_players;
    }


        static vector<villiger*> kill(vector<villiger*>& V_players){

            int index = rand() % V_players.size();
            V_players.erase(V_players.begin() + index);

        return V_players;
        }
        ~healer(){}
};int healer::br = 0;


class kurtizanka : public villiger
{
   public:
        using Self = kurtizanka;
        static int br;
        kurtizanka() = default;

   static vector<villiger*> Add(vector<villiger*>& V_players)
   {
        for (int i = 0; i < Self::br; i++)
            V_players.push_back(new Self);
        return V_players;
   }

        ~kurtizanka(){}
};int kurtizanka::br = 0;


class detectiv : public villiger
{
    public:
        using Self = detectiv;
        static int br;
        detectiv() = default;

    static vector<villiger*> Add(vector<villiger*>& V_players)
    {
        for (int i = 0; i < Self::br; i++)
            V_players.push_back(new Self);
        return V_players;
    }

        ~detectiv(){}
};int detectiv::br = 0;


class  game{
    public:
     static bool win(vector<villiger*>& V_plears) {

         if(killer::Left(V_plears) == 0 && super_killer::Left(V_plears) == 0) {
             vill_wins++;
             return true;
         }
         else if(villiger::Left(V_plears) <= (killer::Left(V_plears)+super_killer::Left(V_plears))) {
             killers_wins++;
             return true;
         }
         else
         {
             return false;
         }

     }


    static vector<villiger*> vote(vector<villiger*>& V_players)
    {
            
            int index = rand() % V_players.size();
            V_players.erase(V_players.begin() + index);
            return V_players;
    }   
};
/*
bool chose_skip();
int rounds_left(int left);
bool check_win(int killers, int left);
int heal_cheker(int healers,int left);
int kurtizanka_cheker(int healers,int left);
bool vote(int left);
int vote_kill(int left);
int  kill(int left);
*/
/////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////

int main()
 {
        srand(time(0)); //random number generator
        int current_game = 0; // number of current game
        int games = 100; // number of games played

        //imput the players
        villiger::br = 10;
        killer::br = 0;
        super_killer::br = 5;
        healer::br = 6;
        kurtizanka::br = 0;
        detectiv::br = 0;
 
    do
    {
        vector <villiger*> V_players;
        current_game++; // increment the number of attempts

        V_players = killer::Add(V_players);
        V_players = super_killer::Add(V_players);
        V_players = healer::Add(V_players);
        V_players = kurtizanka::Add(V_players);
        V_players = detectiv::Add(V_players);

       
    

        do
        {
            V_players = killer::kill(V_players);
            V_players = super_killer::kill(V_players); 
            
            if (game::win(V_players) == true)
                    break;

                V_players = killer::kill(V_players);
                V_players = game::vote(V_players);

               
         /*  //int rounds = rounds_left(left);
            left = kill(left);//make a random kill
            if(kurtizanka > 0)
            {
                left = kurtizanka_cheker(kurtizanka, left);//healers are heal
            }
            if(healers > 0)
            {
                left = heal_cheker(healers, left);//kurtizanka are heal        
            }
                       
            win = check_win(Killers.br, left);//cheks for winn
            if(win == true)
            {
                break;
            }

           skip = chose_skip();
           if(skip != true)
           {
            win = vote(left); //vote function
            left = vote_kill(left);
           }
            if(win == true)
            {
                break;
            }
           
            win = check_win(Killers.br, left);
 */
        }while(game::win(V_players) != true);//check for win


    }while (current_game != games);
   
    cout << "killers win: " << killers_wins << endl;
    cout <<"villigers win: " << vill_wins << endl;
    cout << "total rounds: " << games << endl;
    cout << "villigers win rate: " << double(vill_wins)/games*100 << "%" << endl;
    cout << "killers win rate: " << double(killers_wins)/games*100 << "%" << endl;

    return 0;
 }

