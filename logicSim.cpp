////////////////////////////////////////////////////////////////////////////
// Simulating Logic circuits             SIMLIB/C++
//
// contributors : xdurca01, xjusko00
// FIT VUTBR  2015 IMS (Projekt simulace)
#include "simlib.h"
#include <vector>
#include <string>
#include <functional>
#include <iostream>

using namespace std;
#define MAX_UNIT 200 //MAX number of units in one circuit
//=========================
//main classes declaration 
//=========================
void Tstatprint();

// random number 0...1
int Randomsig() {
    return int(2*Random()); //  0 .. 1
}

// facility for each Unit 
Facility Units[MAX_UNIT]; 


// class implements  unit NOT with two outputs and one input 
class NOT {
     public:
        string name; //name of the unit
        string Tstat ="";
        int input1=-1;
        int input2=input1;
        int output=-1;
        int lastout=0;
        int delay=0;
        string s_input1;
        string s_input2;
        string s_output;
        void setvalues(string pad, int value){if(pad==s_input1 || pad==s_input2 ){input1=value;input2=value;}}
        string soutvalue(){return s_output;}
        int outvalue(){if(input1!=-1 && input2!=-1 ) return output=!(input1 & input2); return -1;}
        void init(){ input1=-1;input2=-1;output=-1;}
        bool in(string pad){if(pad!=s_input1 && pad!=s_input2) return false; return true;}
};


// class implements  unit AND with two outputs and one input 
class AND {
     public:
        string name; //name of the unit
        string Tstat ="";
        int input1=-1;
        int input2=-1;
        int output=-1;
        int lastout=0;
        int delay=0;
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
        string name; //name of the unit
        string Tstat ="";
        int input1=-1;
        int input2=-1;
        int output=-1;
        int lastout=0;
        int delay=0;
        string s_input1;
        string s_input2;
        string s_output;
        void setvalues(string pad, int value){if(pad==s_input1)input1=value;if(pad==s_input2)input2=value;}
        string soutvalue(){return s_output;}
        int outvalue(){if(input1!=-1 && input2!=-1 ) return output=(input1 | input2); return -1;}
        void init(){ input1=-1;input2=-1;output=-1;}
        bool in(string pad){if(pad!=s_input1 && pad!=s_input2) return false; return true;}
};

// class implements  unit NOR with two outputs and one input 
class NOR {
     public:
        string name; //name of the unit
        string Tstat ="";
        int input1=-1;
        int input2=-1;
        int output=-1;
        int lastout=0;
        int delay=0;
        string s_input1;
        string s_input2;
        string s_output;
        void setvalues(string pad, int value){if(pad==s_input1)input1=value;if(pad==s_input2)input2=value;}
        string soutvalue(){return s_output;}
        int outvalue(){if(input1!=-1 && input2!=-1 ) return output=!(input1 | input2); return -1;}
        void init(){ input1=-1;input2=-1;output=-1;}
        bool in(string pad){if(pad!=s_input1 && pad!=s_input2) return false; return true;}
};

// class implements  unit NAND with two outputs and one input 
class NAND {
     public:
        string name; //name of the unit
        string Tstat ="";
        int input1=-1;
        int input2=-1;
        int output=-1;
        int lastout=0;
        int delay=0;
        string s_input1;
        string s_input2;
        string s_output;
        void setvalues(string pad, int value){if(pad==s_input1)input1=value;if(pad==s_input2)input2=value;}
        string soutvalue(){return s_output;}
        int outvalue(){if(input1!=-1 && input2!=-1 ) return output=!(input1 & input2); return -1;}
        void init(){ input1=-1;input2=-1;output=-1;}
        bool in(string pad){if(pad!=s_input1 && pad!=s_input2) return false; return true;}
};

//Unit can be AND OR NOR NAND NOT 
class Unit
{
public:
    string type; // type of the Unit (ex. AND)
    AND *And; // reference on AND if 
    OR *Or; // reference on OR if
    NAND *Nand; // reference on AND if 
    NOR *Nor; // reference on OR if
    NOT *Not;
    Unit(string type,AND *And,OR *Or,NAND *Nand,NOR *Nor,NOT *Not){this->type=type;this->And=And;this->Or=Or;this->Nor=Nor;this->Nand=Nand;this->Not=Not;}; // object create
};

// vector with references on our circuit from file 
vector <reference_wrapper<Unit>> units;

/** 
signal initialize this function  to check input signals of the unit, solve output for our unit
Unit type OR  
*/
class zapisOR : public Process{
void Behavior();
public:
    OR *hradlo;  // pointer on Unit 
    int value; //value of the signal
    string input;  // signal name 
    int val; // index of the unit (protected)
    zapisOR(OR *hradlo,int value,string input,int val){this->hradlo=hradlo;this->value=value;this->input=input;this->val=val;};
};

/** 
signal initialize this function  to check input signals of the unit, solve output for our unit
Unit type NOT  
*/
class zapisNOT : public Process{
void Behavior();
public:
    NOT *hradlo;  // pointer on Unit 
    int value; //value of the signal
    string input;  // signal name 
    int val; // index of the unit (protected)
    zapisNOT(NOT *hradlo,int value,string input,int val){this->hradlo=hradlo;this->value=value;this->input=input;this->val=val;};
};

/** 
signal initialize this function  to check input signals of the unit, solve output for our unit
Unit type AND  
*/
class zapisAND : public Process{
void Behavior();
public:
    AND *hradlo;
    int value;
    string input; 
    int val;
    zapisAND(AND *hradlo,int value,string input,int val){this->hradlo=hradlo;this->value=value;this->input=input;this->val=val;};
};
/** 
signal initialize this function  to check input signals of the unit, solve output for our unit
Unit type NAND  
*/
class zapisNAND : public Process{
void Behavior();
public:
    NAND *hradlo;
    int value;
    string input; 
    int val;
    zapisNAND(NAND *hradlo,int value,string input,int val){this->hradlo=hradlo;this->value=value;this->input=input;this->val=val;};
};
/** 
signal initialize this function  to check input signals of the unit, solve output for our unit
Unit type NOR  
*/
class zapisNOR : public Process{
void Behavior();
public:
    NOR *hradlo;
    int value;
    string input; 
    int val;
    zapisNOR(NOR *hradlo,int value,string input,int val){this->hradlo=hradlo;this->value=value;this->input=input;this->val=val;};
};
//==========================
// Create signal check Units, which one was affected 
//=================================
class INSignal : public Process {
    public:
        string input; //name of the signal
        int value; //value of the signal 0...1
        INSignal(string name,int value){this->input=name;this->value=value;};  //create signal 
    private:
        void Behavior() {
            unsigned int val=0;  //for each  unit  check and set 
            for (;val<units.size();val++){
                Unit &l=units.at(val);
                if((&l)->type=="AND")
                    (new zapisAND((&l)->And,value,input,val))->Activate();

                else if((&l)->type=="OR")
                    (new zapisOR((&l)->Or,value,input,val))->Activate();
                else if((&l)->type=="NOR")
                    (new zapisNOR((&l)->Nor,value,input,val))->Activate();
                else if((&l)->type=="NAND")
                    (new zapisNAND((&l)->Nand,value,input,val))->Activate();
                else if((&l)->type=="NOT")
                    (new zapisNOT((&l)->Not,value,input,val))->Activate();
            }
    }
};
//===============
//check and set NOT Unit 
//===============
 void zapisNOT::Behavior() { 
        if(!hradlo->in(input)) return; //if signal name  is not the input of the Unit return
        Seize(Units[val]);  // one process at time 
        hradlo->setvalues(input,value); // set values of the input 

        if(hradlo->outvalue()!=-1)    // if output can be solved 
        {       
                Wait(hradlo->delay); // delay of the Unit
                hradlo->Tstat+=to_string(val)+" "+to_string(hradlo->output)+" "+to_string(Time)+"\n"; //write to stat
                hradlo->lastout=hradlo->output; // lastvalue set
                int  val1=hradlo->outvalue(); // sup val
                hradlo->init();   // init values 

            (new INSignal(hradlo->soutvalue().c_str(),val1))->Activate(); // create new signal with the name of the output 
        }
        else
        {   
            hradlo->Tstat+=to_string(val)+" "+to_string(hradlo->lastout)+" "+to_string(Time)+"\n"; //write to stat
        }
        Release(Units[val]); // leave 
    }
//===============
//check and set AND Unit 
//===============
 void zapisAND::Behavior() { 
        if(!hradlo->in(input)) return; //if signal name  is not the input of the Unit return
        Seize(Units[val]);  // one process at time 
        hradlo->setvalues(input,value); // set values of the input 

        if(hradlo->outvalue()!=-1)    // if output can be solved 
        {       
                Wait(hradlo->delay); // delay of the Unit
                hradlo->Tstat+=to_string(val)+" "+to_string(hradlo->output)+" "+to_string(Time)+"\n"; //write to stat
                hradlo->lastout=hradlo->output; // lastvalue set
                int  val1=hradlo->outvalue(); // sup val
                hradlo->init();   // init values 

            (new INSignal(hradlo->soutvalue().c_str(),val1))->Activate(); // create new signal with the name of the output 
        }
        else
        {   
            hradlo->Tstat+=to_string(val)+" "+to_string(hradlo->lastout)+" "+to_string(Time)+"\n"; //write to stat
        }
        Release(Units[val]); // leave 
    }
//===============
//check and set OR Unit 
//===============
 void zapisOR::Behavior() { 
        if(!hradlo->in(input)) return;
        Seize(Units[val]);
        hradlo->setvalues(input,value);

        if(hradlo->outvalue()!=-1)    
        {       
                Wait(hradlo->delay);
                hradlo->Tstat+=to_string(val)+" "+to_string(hradlo->output)+" "+to_string(Time)+"\n"; //write to stat
                hradlo->lastout=hradlo->output;
                int  val1=hradlo->outvalue();
                hradlo->init();  

            (new INSignal(hradlo->soutvalue().c_str(),val1))->Activate();
        }
        else
        {   
           hradlo->Tstat+=to_string(val)+" "+to_string(hradlo->lastout)+" "+to_string(Time)+"\n"; //write to stat
        }
        Release(Units[val]);
    }
//===============
//check and set OR Unit 
//===============
 void zapisNOR::Behavior() { 
        if(!hradlo->in(input)) return;
        Seize(Units[val]);
        hradlo->setvalues(input,value);

        if(hradlo->outvalue()!=-1)    
        {       
                Wait(hradlo->delay);
                hradlo->Tstat+=to_string(val)+" "+to_string(hradlo->output)+" "+to_string(Time)+"\n"; //write to stat
                hradlo->lastout=hradlo->output;
                int  val1=hradlo->outvalue();
                hradlo->init();  

            (new INSignal(hradlo->soutvalue().c_str(),val1))->Activate();
        }
        else
        {   
            hradlo->Tstat+=to_string(val)+" "+to_string(hradlo->lastout)+" "+to_string(Time)+"\n"; //write to stat
        }
        Release(Units[val]);
    }

//===============
//check and set OR Unit 
//===============
 void zapisNAND::Behavior() { 
        if(!hradlo->in(input)) return;
        Seize(Units[val]);
        hradlo->setvalues(input,value);

        if(hradlo->outvalue()!=-1)    
        {       
                Wait(hradlo->delay);
                hradlo->Tstat+=to_string(val)+" "+to_string(hradlo->output)+" "+to_string(Time)+"\n"; //write to stat
                hradlo->lastout=hradlo->output;
                int  val1=hradlo->outvalue();
                hradlo->init();  

            (new INSignal(hradlo->soutvalue().c_str(),val1))->Activate();
        }
        else
        {   
            hradlo->Tstat+=to_string(val)+" "+to_string(hradlo->lastout)+" "+to_string(Time)+"\n"; //write to stat
        }
        Release(Units[val]);
    }

//======================
//INPUT signal generator
//======================
class Generator : public Event {       
private:
    void Behavior() {
      int rand=Randomsig();
      (new INSignal("IN1",rand))->Activate();
      Print("%i %f / ",rand,Time);
      rand=Randomsig();
      (new INSignal("IN2",rand))->Activate();
      Print("%i %f\n",rand,Time);
    Activate(Time+Exponential(25));

   }
};
int StructureUnitsNum(char *file, int *AND_count,int *OR_count,int *NOT_count,int *NAND_count,int *NOR_count)
{
   
    return true;
}

void Tstatprint(){

unsigned int val=0;  //for each  unit  check and set 
    for (;val<units.size();val++){
        Unit &l=units.at(val);
        Print("NAME     ID      INPUT       OUTPUT    \n");
        if((&l)->type=="AND")
            Print("%s\n",((&l)->And->Tstat).c_str() );
        else if((&l)->type=="NAND")
            Print("%s\n",((&l)->Nand->Tstat).c_str() );
        else if((&l)->type=="NOR")
            Print("%s\n",((&l)->Nor->Tstat).c_str() );
        else if((&l)->type=="OR")
            Print("%s\n",((&l)->Or->Tstat).c_str() );
        else if((&l)->type=="NOT")
            Print("%s\n",((&l)->Not->Tstat).c_str() );
    }
    return;
}


//=========================
//MAIN FUNCTION 
//=========================
int main(int argc, char **argv){ // links for each unit 
    int AND_count=0;
    int OR_count=0;
    int NOT_count=0;
    int NAND_count=0;
    int NOR_count=0;
    if(argc==2)
        StructureUnitsNum(argv[1],&AND_count,&OR_count,&NOT_count,&NAND_count,&NOR_count);
    else
    {   
        fprintf(stderr, "Wrong input: ./logicSim <file name>\n" );
        return false;
    }

    AND *u=new AND;
    u->s_input1="IN1";
    u->s_input2="IN2";
     u->s_output="OUT";
     Unit x("AND",u,NULL,NULL,NULL,NULL);
    Unit &obj_ref1=std::ref(x);
    units.push_back(obj_ref1);
   
   NOT z;
    z.s_input1="OUT";
     z.s_output="xx";
     Unit v("NOT",NULL,NULL,NULL,NULL,&z);
    Unit &objj_ref1=std::ref(v);
    units.push_back(objj_ref1);
    
  SetOutput("test.out");
   Init(0,1000); 
   (new Generator())->Activate();
    Run();   
    Tstatprint();
    SIMLIB_statistics.Output();
    return true;
}
