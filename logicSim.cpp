////////////////////////////////////////////////////////////////////////////
// Simulating Logic circuits             SIMLIB/C++
//
#include "simlib.h"
#include <vector>
#include <string>
#include <functional>

using namespace std;
//main classes declaration 
//Class Circuit --> defines whole logic circuit with all units
//Class Unit --> defines one unit 
//Class AND --> inherit Unit's att + 'AND' behavior
//Class OR --> inherit Unit's att + 'OR' behavior

int Randomsig() {
    return int(2*Random()); //  0 .. 1
}

Facility Unit[200]; 





class AND {
     public:
        int input1=-1;
        int input2=-1;
        int output=-1;
        string s_input1;
        string s_input2;
        string s_output;
        void setvalues(string pad, int value){if(pad==s_input1)input1=value;if(pad==s_input2)input2=value;}
        string soutvalue(){return s_output;}
        int outvalue(){if(input1!=-1 && input2!=-1 ) return input1 & input2; return -1;}
        void init(){ input1=-1;input2=-1;output=-1;}
};

vector <reference_wrapper<AND>> units;


class zapisAND : public Process{
void Behavior();
public:
    AND *hradlo;
    int value;
    string input; 
    zapisAND(AND *hradlo,int value,string input){this->hradlo=hradlo;this->value=value;this->input=input;};
};



class INSignal : public Process {
    public:
        string input; //name of the signal
        vector <reference_wrapper<AND>> units;
        int value;
        INSignal(string name,vector <reference_wrapper<AND>> units,int value){this->input=name;this->units=units;this->value=value;};

    private:
        void Behavior() {
         AND &l=units.at(0);
        (new zapisAND(&l,value,input))->Activate();
        }

};



 void zapisAND::Behavior() { 

        Seize(Unit[1]);
        hradlo->setvalues(input,value);
        printf("signal %i %i %i  %i %s \n",value,hradlo->input2,hradlo->input1,hradlo->outvalue(),input.c_str() );
        if(hradlo->outvalue()!=-1)
            {hradlo->init();Wait(10);printf("we have output call next signal %f\n",Time);(new INSignal(hradlo->soutvalue().c_str(),units,Randomsig()))->Activate();}
        Release(Unit[1]);
    }







class Generator : public Event {       
public:
    vector <reference_wrapper<AND>> units;
    Generator(vector <reference_wrapper<AND>> units){this->units=units;};
private:
    void Behavior() {

      (new INSignal("IN1",units,Randomsig()))->Activate();
      (new INSignal("IN2",units,Randomsig()))->Activate();
    Activate(Time+Exponential(20));

   }
};


int main(){ // links for each unit 
    AND u;
    u.s_input1="IN1";
    u.s_input2="IN2";
     u.s_output="OUT";
    AND &obj_ref1=std::ref(u);
    units.push_back(obj_ref1);

  SetOutput("test.out");
   Init(0,1000); 
   (new Generator(units))->Activate();
    Run();    




//Unit &l=units.at(0);


    return true;
}
