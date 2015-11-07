////////////////////////////////////////////////////////////////////////////
// Simulating Logic circuits             SIMLIB/C++
//
#include "simlib.h"
#include <vector>
#include <string>
#include <functional>

using namespace std;
#define MAX_UNIT 200 //MAX number of units in one circuit
//=========================
//main classes declaration 
//=========================

// random number 0...1
int Randomsig() {
    return int(2*Random()); //  0 .. 1
}

// facility for each Unit 
Facility Units[MAX_UNIT]; 

// class implements  unit AND with two outputs and one input 
class AND {
     public:
        int input1=-1;
        int input2=-1;
        int output=-1;
        int lastout=0;
        string s_input1;
        string s_input2;
        string s_output;
        void setvalues(string pad, int value){if(pad==s_input1)input1=value;if(pad==s_input2)input2=value;}
        string soutvalue(){return s_output;}
        int outvalue(){if(input1!=-1 && input2!=-1 ) return output=(input1 & input2); return -1;}
        void init(){ input1=-1;input2=-1;output=-1;}
        bool in(string pad){if(pad!=s_input1 && pad!=s_input2) return false; return true;}
};


// class implements  unit OR with two outputs and one input 
class OR {
     public:
        int input1=-1;
        int input2=-1;
        int output=-1;
        int lastout=0;
        string s_input1;
        string s_input2;
        string s_output;
        void setvalues(string pad, int value){if(pad==s_input1)input1=value;if(pad==s_input2)input2=value;}
        string soutvalue(){return s_output;}
        int outvalue(){if(input1!=-1 && input2!=-1 ) return output=(input1 | input2); return -1;}
        void init(){ input1=-1;input2=-1;output=-1;}
        bool in(string pad){if(pad!=s_input1 && pad!=s_input2) return false; return true;}
};

class Unit
{
public:
    string type;
    AND *And;
    OR *Or;
    Unit(string type,AND *And,OR *Or){this->type=type;this->And=And;this->Or=Or;};
};

// vector with references on our circuit from file 
vector <reference_wrapper<Unit>> units;

class zapisOR : public Process{
void Behavior();
public:
    OR *hradlo;
    int value;
    string input; 
    int val;
    zapisOR(OR *hradlo,int value,string input,int val){this->hradlo=hradlo;this->value=value;this->input=input;this->val=val;};
};





class zapisAND : public Process{
void Behavior();
public:
    AND *hradlo;
    int value;
    string input; 
    int val;
    zapisAND(AND *hradlo,int value,string input,int val){this->hradlo=hradlo;this->value=value;this->input=input;this->val=val;};
};








class INSignal : public Process {
    public:
        string input; //name of the signal
        
        int value;
        INSignal(string name,int value){this->input=name;this->value=value;};

    private:
        void Behavior() {
            unsigned int val=0;  //for each  unit 
            for (;val<units.size();val++){
                Unit &l=units.at(val);
                if((&l)->type=="AND")
                (new zapisAND((&l)->And,value,input,val))->Activate();

                else if((&l)->type=="OR")
                (new zapisOR((&l)->Or,value,input,val))->Activate();
            }
    }

};



 void zapisAND::Behavior() { 
        if(!hradlo->in(input)) return;
        Seize(Units[val]);
        hradlo->setvalues(input,value);

        if(hradlo->outvalue()!=-1)    
        {       
                Wait(2);
                Print("%i %i  %f\n",val,hradlo->output,Time);
                hradlo->lastout=hradlo->output;
                int  val1=hradlo->outvalue();
                hradlo->init();  

            (new INSignal(hradlo->soutvalue().c_str(),val1))->Activate();
        }
        else
        {   
            Print("%i %i   %s guessed %f\n",val,hradlo->lastout,Time,input.c_str());
        }
        Release(Units[val]);
    }

 void zapisOR::Behavior() { 
        if(!hradlo->in(input)) return;
        Seize(Units[val]);
        hradlo->setvalues(input,value);

        if(hradlo->outvalue()!=-1)    
        {       
                Wait(5);
                Print("%i %i  %f\n",val,hradlo->output,Time);
                hradlo->lastout=hradlo->output;
                int  val1=hradlo->outvalue();
                hradlo->init();  

            (new INSignal(hradlo->soutvalue().c_str(),val1))->Activate();
        }
        else
        {   
            Print("%i %i   %s guessed OR %f\n",val,hradlo->lastout,Time,input.c_str());
        }
        Release(Units[val]);
    }






class Generator : public Event {       
private:
    void Behavior() {

      (new INSignal("IN1",Randomsig()))->Activate();
      (new INSignal("IN2",Randomsig()))->Activate();
    Activate(Time+Exponential(25));

   }
};





int main(){ // links for each unit 
    AND u;
    u.s_input1="IN1";
    u.s_input2="IN2";
     u.s_output="OUT";
     Unit x("AND",&u,NULL);
    Unit &obj_ref1=std::ref(x);
    units.push_back(obj_ref1);
   
   AND z;
    z.s_input1="IN1";
    z.s_input2="OUT";
     z.s_output="xx";
     Unit v("AND",&z,NULL);
    Unit &objj_ref1=std::ref(v);
    units.push_back(objj_ref1);

   OR n;
    n.s_input1="xx";
    n.s_input2="xx";
     n.s_output="ZZ";
     Unit m("OR",NULL,&n);
    Unit &objjj_ref1=std::ref(m);
    units.push_back(objjj_ref1);




   

  SetOutput("test.out");
  Print("id    value   time \n");
   Init(0,200); 
   (new Generator())->Activate();
    Run();    
SIMLIB_statistics.Output();



//Unit &l=units.at(0);


    return true;
}
