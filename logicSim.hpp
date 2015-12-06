#ifndef LOGICSIM_HPP
#define LOGICSIM_HPP
#include <string>
#include <map>
#include <utility>
using namespace std;
map<string, string> Tstats;
map<string, string> keepsignal;
// facility for each Unit 
#define MAX_UNIT 200 //MAX number of units in one circuit
Facility Units[MAX_UNIT];   // each unit has its own facility for set up pin values 
vector<string> unit_names; //names of units 
vector<string>INsig; //Input signals
vector<string>Outsig; //Output signals
string CLK=""; //CLK 
string TstatCLK=""; // CLK Statistic
bool clocksyn=false; //CLK enabled 
int CLK_freq=0; // frequency in ns
int CLK_S=0; //start value 

//Functions Statistic,Error
void Tstatprint();
void ErrorFun();

// class implements  unit AND with two outputs and one input 
class AND{
     public:
        string name; //name of the unit
        string Tstat ="";
        int clk=-1;
        int input1=-1;
        int input2=-1;
        int output=-1;
        int lastout=0;
        int delay=4;
        string s_input1;
        string s_input2;
        string s_output;
        void setvalues(string pad, int value){if(pad==s_input1)input1=value;if(pad==s_input2)input2=value;if(pad==CLK)clk=value;}
        string soutvalue(){return s_output;}
        int outvalue(){if(input1!=-1 && input2!=-1 ) return output=(input1 & input2); return -1;}
        void init(){ input1=-1;input2=-1;output=-1;clk=-1;}
        bool in(string pad){if(pad!=s_input1 && pad!=s_input2) return false; return true;}
};

// class implements  unit NOT with two outputs and one input 
class NOT:public AND {
     public:
        int delay=1;
        void setvalues(string pad, int value){if(pad==s_input1 || pad==s_input2 ){input1=value;input2=value;}if(pad==CLK)clk=value;}
        int outvalue(){if(input1!=-1 && input2!=-1 ) return output=!(input1 & input2); return -1;}
};
// class implements  unit OR with two outputs and one input 
class OR : public AND{
     public:
        int delay=2;
        int outvalue(){if(input1!=-1 && input2!=-1 ) return output=(input1 | input2); return -1;}
};

// class implements  unit NOR with two outputs and one input 
class NOR: public AND {
     public:
        int delay=3;
        int outvalue(){if(input1!=-1 && input2!=-1 ) return output=!(input1 | input2); return -1;}
};

// class implements  unit NAND with two outputs and one input 
class NAND: public AND {
     public:
        int delay=5;
        int outvalue(){if(input1!=-1 && input2!=-1 ) return output=!(input1 & input2); return -1;}
};

//Unit can be AND OR NOR NAND NOT 
class Unit
{
public:
    string type; // type of the Unit (ex. AND)
    AND *And; // reference on AND if 
    OR *Or; // reference on OR if
    NAND *Nand; // reference on NAND if 
    NOR *Nor; // reference on NOR if
    NOT *Not; //reference on  NOT
   // Unit(string type,AND *And,OR *Or,NAND *Nand,NOR *Nor,NOT *Not){this->type=type;this->And=And;this->Or=Or;this->Nor=Nor;this->Nand=Nand;this->Not=Not;}; // object create
    void SetUp(string type,AND *And,OR *Or,NAND *Nand,NOR *Nor,NOT *Not){this->type=type;this->And=And;this->Or=Or;this->Nor=Nor;this->Nand=Nand;this->Not=Not;};
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


#endif