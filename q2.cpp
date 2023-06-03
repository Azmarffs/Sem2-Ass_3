/*
Name: Azmar Kashif
Section: B
Roll no: 22i-2716
*/
#include <iostream>
using namespace std;
/*Making a main class called as parent class*/
class Creature{
    public:
    //its data memebers
    string name;
    int level;
    int healthStatus;
    int force;
    int position;
    public:
    //parametrized constructor
    Creature(const string name, int level, int force, int healthStatus, int position = 0){
        this->name=name;
        this->level=level;
        this->force = force;
        this->healthStatus=healthStatus;
        this->position=position;
    }
    bool alive(){ //first checking if the creature is alive 
        if(healthStatus>0){
            return true;
        }else{
            return false;
        }
    }
    int AttackPoints(){ //calculating its attack points
        if(!(alive())){
            return 0;
        }
        return level*force;
    }
    void Move(int val){ //giving it a new postion when it moves
        position = position + val;
    }
    void GoodBye(){ //if the dragon dies 
        cout << name <<" > is no more!: " << endl;
    }
    void Weak(int points){
        if(alive()){
            if(alive()){
                healthStatus = healthStatus-points;
            }else{
                healthStatus = 0;
                GoodBye();
            }
        }
        if(!alive()){
            healthStatus = 0;
            GoodBye();
        }
    }
    void display(){
        cout << name << ", level: " << level << ", health_status: " << healthStatus
        << ", force: " << force << ", Attacking Points: " << AttackPoints() 
        << ", position: " << position << endl;  
    }
};
/*Making a dragon class which is a child class of parent class*/
class Dragon : public Creature{
    protected:
    //data member
    int RangeOfFlame;
    public:
    //constructor
    Dragon(string name, int level, int force, int healthStatus, int RangeOfFlame, int position= 0)
       : Creature(name, level, force, healthStatus, position)
    {
        this->RangeOfFlame = RangeOfFlame;
    }
    void Fly(int pos){
        position = pos;
    }
    void BlowFlame(Creature& c){ 
        int path = position - c.position; //here we are first calculating the distance between 2 creatures
        if(!c.alive()){ //checking if not alive we inc the lvl
            level+=1;
        }else if(alive() && c.alive()){ //otherwise we check if both the creatures are alive
            if(path >= RangeOfFlame && path >=0){ //and we check if the path of flame is in range and postive
                int FightDmg = AttackPoints(); //we make a FightDmg var in which we store attackpoints 
                int pointsGained = path; //then we make a pointsGained var in which we give its path
                c.Weak(FightDmg);//then we call the Weak() function where we sub heathstatus with point and get the remaining health
            }
        }
    }
};
/*Making a Ichneumon class which is a child class of Creature*/
class Ichneumon : public Creature{
    //data members
    int lenOfNeck;
    int doseOfPoison;
    public:
    //constructor
    Ichneumon(string name, int level, int healthStatus, int force, int lenOfNeck, int dosrOfPoison, int position= 0)
    : Creature(name, level, force, healthStatus, position)
    {
        this->lenOfNeck = lenOfNeck;
        this->doseOfPoison = doseOfPoison;
    }
    void InjectPoison(Creature& c1){
        int path = position - c1.position; //here we do the same first we calc the distance between 2 creatures
        if(!c1.alive()){
            level+=1; //here we inc 1 in the lvl if creature is dead
        }else if(alive() && c1.alive()){ //if both are alive then 
            if(path <= lenOfNeck){ //we check if neck of dragon is in range of Ichneumon to inject poison
                int FightDmg = AttackPoints() + doseOfPoison; //then we make a var and add its attack points acc to the amount of poison injected
                c1.Weak(FightDmg); //thn we call weak() func to calc the reamining health
            }
        }
    }     
    void Fight(Dragon& d, Ichneumon& i){ //here we pass both child classes as parameters
    /*
    We make both fight here vice versa
    */
        i.InjectPoison(d); 
        d.BlowFlame(i);
    }
};
int main()
{
  Dragon dragon("Dragon red"   , 2, 3, 10, 20         );
  Ichneumon  ichneumon ("ichneumon evil", 2, 10, 1, 10, 1,  42 );

  dragon.display();
  cout << "is preparing for fight with :" << endl;
  ichneumon.display();

  cout << endl;
  cout << "1st Fight :" << endl;
  cout << "    the creature-s are not within range, so can not Attacke."
       << endl;
  ichneumon.Fight(dragon, ichneumon);

  cout << "After the Fight :" << endl;
  dragon.display();
  ichneumon.display();

  cout << endl;
  cout << "Dragon has flown close to ichneumon :" << endl;
  dragon.Fly(ichneumon.position - 1);
  dragon.display();

  cout << endl;
  cout << "ichneumon moves :" << endl;
  ichneumon.Move(1);
  ichneumon.display();

  cout << endl;
  cout << "2nd Fight :" << endl;
  cout << ""
  <<"+ ichneumon inflicts a 3-point attack on dragon\n"
     " [ level (2) * force (1) + poison (1) = 3 ] ;\n"
  "+ Dragon inflicts a 6-point attack on ichneumon\n"
      "[ level (2) * force (3) = 6 ] ;\n"
  "+ during his attack, dragon loses two additional points\n"
"      [ corresponding to the distance between dragon and ichneumon : 43 - 41 = 2 ]." << endl;
  ichneumon.Fight(dragon, ichneumon);

  cout << "After the Fight :" << endl;
  dragon.display();
  ichneumon.display();

  cout << endl;
  cout << "Dragon moves by one step " << endl;
  dragon.Move(1);
  dragon.display();

  cout << endl;
  cout << "3rd Fight :" << endl;
  cout << "  + ichneumon inflicts a 3-point attack on dragon \n "
  "    [ level (2) * force (1) + poison (1) = 3 ] ; \n "
  "+ Dragon inflicts a 6-point attack on ichneumon \n "
"      [ level (2) * force (3) = 6 ] ; \n"
  "+ during his attack, dragon lost 1 additional life point.\n"
       "[ corresponding to the distance between dragon and ichneumon : 43 - 42 = 1 ] ;\n"
  "+ ichneumon is defeated and the dragon rises to level 3" << endl;
  ichneumon.Fight(dragon, ichneumon);

  cout << "After the Fight :" << endl;
  dragon.display();
  ichneumon.display();

  cout << endl;
  cout << "4th Fight :" << endl;
  cout << "    when one creatures is defeated, nothing happpens" << endl;
  ichneumon.Fight(dragon, ichneumon);

  cout << "After the Fight :" << endl;
  dragon.display();
  ichneumon.display();

  return 0;
}    


