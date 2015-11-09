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
#include <fstream>
#include <algorithm>

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
string TstatOut=""; 
vector<string> unit_names;
vector<string>INsig;
vector<string>Outsig;
string CLK="";
string TstatCLK="";
bool clocksyn=false;
int CLK_freq=0;
int CLK_S=0;
int IN_EXP=0; //Exponencial generate signal

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

            if(std::find(Outsig.begin(), Outsig.end(), input) != Outsig.end())
                    TstatOut+=input+"\t"+to_string(value)+"\t"+to_string(Time)+"\n";

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
        if(!hradlo->in(input) && !clocksyn) return;//if signal name  is not the input of the Unit return
        Seize(Units[val]);  // one process at time 
        hradlo->setvalues(input,value); // set values of the input 

        if(hradlo->outvalue()!=-1)    // if output can be solved 
        {       
               if(!clocksyn)
                {   
                    Wait(hradlo->delay); // delay of the Unit
                    hradlo->Tstat+=to_string(val)+"\t"+to_string(hradlo->input1)+"|"+"-"+"\t"+to_string(hradlo->output)+"\t"+to_string(Time)+"\n"; //write to stat
                    hradlo->lastout=hradlo->output; // lastvalue set
                    int  val1=hradlo->outvalue(); // sup val
                    hradlo->init();   // init values 

                    (new INSignal(hradlo->soutvalue().c_str(),val1))->Activate();
                }
                else if(input==CLK && CLK_S==1)
                {
                    Wait(hradlo->delay); // delay of the Unit
                    hradlo->Tstat+=to_string(val)+"\t"+to_string(hradlo->input1)+"|"+"-"+"\t"+to_string(hradlo->output)+"\t"+to_string(Time)+"\n"; //write to stat
                    hradlo->lastout=hradlo->output; // lastvalue set
                    int  val1=hradlo->outvalue(); // sup val
                    hradlo->init();   // init values 
                    (new INSignal(hradlo->soutvalue().c_str(),val1))->Activate();

                }
        }

        Release(Units[val]); // leave 
    }
//===============
//check and set AND Unit 
//===============
 void zapisAND::Behavior() { 
        if(!hradlo->in(input) && !clocksyn) return; //if signal name  is not the input of the Unit return
        Seize(Units[val]);  // one process at time 
        hradlo->setvalues(input,value); // set values of the input 

        if(hradlo->outvalue()!=-1)    // if output can be solved 
        {       if(!clocksyn)
                {   
                    Wait(hradlo->delay); // delay of the Unit
                    hradlo->Tstat+=to_string(val)+"\t"+to_string(hradlo->input1)+"|"+to_string(hradlo->input2)+"\t"+to_string(hradlo->output)+"\t"+to_string(Time)+"\n"; //write to stat
                    hradlo->lastout=hradlo->output; // lastvalue set
                    int  val1=hradlo->outvalue(); // sup val
                    hradlo->init();   // init values 

                    (new INSignal(hradlo->soutvalue().c_str(),val1))->Activate();
                }
                else if(input==CLK && CLK_S==1)
                {
                    Wait(hradlo->delay); // delay of the Unit
                    hradlo->Tstat+=to_string(val)+"\t"+to_string(hradlo->input1)+"|"+to_string(hradlo->input2)+"\t"+to_string(hradlo->output)+"\t"+to_string(Time)+"\n"; //write to stat
                    hradlo->lastout=hradlo->output; // lastvalue set
                    int  val1=hradlo->outvalue(); // sup val
                    hradlo->init();   // init values 
                    (new INSignal(hradlo->soutvalue().c_str(),val1))->Activate();

                }
        }

        Release(Units[val]); // leave 
    }
//===============
//check and set OR Unit 
//===============
 void zapisOR::Behavior() { 
        if(!hradlo->in(input) && !clocksyn) return;
        Seize(Units[val]);
        hradlo->setvalues(input,value);

        if(hradlo->outvalue()!=-1)    
        {       
                if(!clocksyn)
                {   
                    Wait(hradlo->delay); // delay of the Unit
                    hradlo->Tstat+=to_string(val)+"\t"+to_string(hradlo->input1)+"|"+to_string(hradlo->input2)+"\t"+to_string(hradlo->output)+"\t"+to_string(Time)+"\n"; //write to stat
                    hradlo->lastout=hradlo->output; // lastvalue set
                    int  val1=hradlo->outvalue(); // sup val
                    hradlo->init();   // init values 

                    (new INSignal(hradlo->soutvalue().c_str(),val1))->Activate();
                }
                else if(input==CLK && CLK_S==1)
                {
                    Wait(hradlo->delay); // delay of the Unit
                    hradlo->Tstat+=to_string(val)+"\t"+to_string(hradlo->input1)+"|"+to_string(hradlo->input2)+"\t"+to_string(hradlo->output)+"\t"+to_string(Time)+"\n"; //write to stat
                    hradlo->lastout=hradlo->output; // lastvalue set
                    int  val1=hradlo->outvalue(); // sup val
                    hradlo->init();   // init values 
                    (new INSignal(hradlo->soutvalue().c_str(),val1))->Activate();

                }
        }

        Release(Units[val]);
    }
//===============
//check and set OR Unit 
//===============
 void zapisNOR::Behavior() { 
        if(!hradlo->in(input) && !clocksyn) return;
        Seize(Units[val]);
        hradlo->setvalues(input,value);

        if(hradlo->outvalue()!=-1)    
        {       
               if(!clocksyn)
                {   
                    Wait(hradlo->delay); // delay of the Unit
                    hradlo->Tstat+=to_string(val)+"\t"+to_string(hradlo->input1)+"|"+to_string(hradlo->input2)+"\t"+to_string(hradlo->output)+"\t"+to_string(Time)+"\n"; //write to stat
                    hradlo->lastout=hradlo->output; // lastvalue set
                    int  val1=hradlo->outvalue(); // sup val
                    hradlo->init();   // init values 

                    (new INSignal(hradlo->soutvalue().c_str(),val1))->Activate();
                }
                else if(input==CLK && CLK_S==1)
                {
                    Wait(hradlo->delay); // delay of the Unit
                    hradlo->Tstat+=to_string(val)+"\t"+to_string(hradlo->input1)+"|"+to_string(hradlo->input2)+"\t"+to_string(hradlo->output)+"\t"+to_string(Time)+"\n"; //write to stat
                    hradlo->lastout=hradlo->output; // lastvalue set
                    int  val1=hradlo->outvalue(); // sup val
                    hradlo->init();   // init values 
                    (new INSignal(hradlo->soutvalue().c_str(),val1))->Activate();

                }
        }

        Release(Units[val]);
    }

//===============
//check and set OR Unit 
//===============
 void zapisNAND::Behavior() { 
        if(!hradlo->in(input) && !clocksyn) return;
        Seize(Units[val]);
        hradlo->setvalues(input,value);

        if(hradlo->outvalue()!=-1)    
        {       
               if(!clocksyn)
                {   
                    Wait(hradlo->delay); // delay of the Unit
                    hradlo->Tstat+=to_string(val)+"\t"+to_string(hradlo->input1)+"|"+to_string(hradlo->input2)+"\t"+to_string(hradlo->output)+"\t"+to_string(Time)+"\n"; //write to stat
                    hradlo->lastout=hradlo->output; // lastvalue set
                    int  val1=hradlo->outvalue(); // sup val
                    hradlo->init();   // init values 

                    (new INSignal(hradlo->soutvalue().c_str(),val1))->Activate();
                }
                else if(input==CLK && CLK_S==1)
                {
                    Wait(hradlo->delay); // delay of the Unit
                    hradlo->Tstat+=to_string(val)+"\t"+to_string(hradlo->input1)+"|"+to_string(hradlo->input2)+"\t"+to_string(hradlo->output)+"\t"+to_string(Time)+"\n"; //write to stat
                    hradlo->lastout=hradlo->output; // lastvalue set
                    int  val1=hradlo->outvalue(); // sup val
                    hradlo->init();   // init values 
                    (new INSignal(hradlo->soutvalue().c_str(),val1))->Activate();

                }
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
        for (unsigned i=0; i < INsig.size(); i++)   
        {
            (new INSignal(INsig[i],rand))->Activate();
            Print("%i\t",rand);
            rand=Randomsig();
        }
        Print("%f\n",Time);
        Activate(Time+Exponential(50));
   }
};

class CLKGenerator :public Event{
void Behavior() {
            (new INSignal(CLK,CLK_S=!CLK_S))->Activate();
        TstatCLK+=to_string(CLK_S)+"\t"+to_string(Time)+"\n";
        Activate(Time+CLK_freq);
   }
};










int StructureUnitsNum(char *file, int *AND_count,int *OR_count,int *NOT_count,int *NAND_count,int *NOR_count,int *SYNCLOCK_count)
{
   
std::ifstream input(file);

for( std::string line; getline( input, line ); )
{
    if(line.find("type:AND")!=std::string::npos)
        (*AND_count)++;
    if(line.find("type:NOR")!=std::string::npos)
        (*NOR_count)++;
    if(line.find("type:OR")!=std::string::npos)
        (*OR_count)++;
    if(line.find("type:NAND")!=std::string::npos)
        (*NAND_count)++;
    if(line.find("type:NOT")!=std::string::npos)
        (*NOT_count)++;
    if(line.find("type:SYNCLOCK")!=std::string::npos)
        (*SYNCLOCK_count)++;
}
    return true;
}

void Tstatprint(){

unsigned int val=0;  //for each  unit  check and set 
    for (;val<units.size();val++){
        Unit &l=units.at(val);
        if((&l)->type=="AND")
            {Print("#=======================================================\n");
            Print("# %s Statistic - Unit(%s)(IN:%s,%s)(OUT:%s)\n\nID\tINPUT\tOUTPUT\tTIME \n%s",(&l)->And->name.c_str(),(&l)->type.c_str(),(&l)->And->s_input1.c_str(),(&l)->And->s_input2.c_str(),(&l)->And->s_output.c_str(),((&l)->And->Tstat).c_str() );
            Print("#=======================================================\n\n");}
        else if((&l)->type=="NAND")
             {Print("#=======================================================\n");
            Print("# %s Statistic - Unit(%s)(IN:%s,%s)(OUT:%s)\nID\tINPUT\tOUTPUT\tTIME \n%s",(&l)->Nand->name.c_str(),(&l)->type.c_str(),(&l)->Nand->s_input1.c_str(),(&l)->Nand->s_input2.c_str(),(&l)->Nand->s_output.c_str(),((&l)->Nand->Tstat).c_str() );
            Print("#=======================================================\n\n");}
        else if((&l)->type=="NOR")
             {Print("#=======================================================\n");
            Print("# %s Statistic - Unit(%s)(IN:%s,%s)(OUT:%s)\nID\tINPUT\tOUTPUT\tTIME \n%s",(&l)->Nor->name.c_str(),(&l)->type.c_str(),(&l)->Nor->s_input1.c_str(),(&l)->Nor->s_input2.c_str(),(&l)->Nor->s_output.c_str(),((&l)->Nor->Tstat).c_str() );
            Print("#=======================================================\n\n");}
        else if((&l)->type=="OR")
             {Print("#=======================================================\n");
            Print("# %s Statistic - Unit(%s)(IN:%s,%s)(OUT:%s)\nID\tINPUT\tOUTPUT\tTIME \n%s",(&l)->Or->name.c_str(),(&l)->type.c_str(),(&l)->Or->s_input1.c_str(),(&l)->Or->s_input2.c_str(),(&l)->Or->s_output.c_str(),((&l)->Or->Tstat).c_str() );
            Print("#=======================================================\n\n");}
        else if((&l)->type=="NOT")
             {Print("#=======================================================\n");
            Print("# %s Statistic - Unit(%s)(IN:%s)(OUT:%s)\nID\tINPUT\tOUTPUT\tTIME \n%s",(&l)->Not->name.c_str(),(&l)->type.c_str(),(&l)->Not->s_input1.c_str(),(&l)->Not->s_output.c_str(),((&l)->Not->Tstat).c_str() );
            Print("#=======================================================\n\n");}
    }
    return;
}

bool LoadUnit(char *file,AND *AND_unit,OR *OR_unit,NOR *NOR_unit,NOT *NOT_unit,NAND *NAND_unit,bool synclock)
{
std::ifstream input(file);
string name="";
int delay=-1;
string one="";
string two="";
string three="";
string type;

if(AND_unit!=NULL)
type="AND";
else if(OR_unit!=NULL)
type="OR";
else if(NOR_unit!=NULL)
type="NOR";
else if(NAND_unit!=NULL)
type="NAND";
else if(NOT_unit!=NULL)
type="NOT";
else
type="SYNCLOCK";

for( std::string line; getline( input, line ); )
{   

    if(line.find("#")!=std::string::npos && line.find("#")==0 )
        continue;
    if(line.find(":type:"+type)!=std::string::npos && !synclock)
    {   
     

         
        if(name=="")
            {  

                name=line.substr(0,line.find(":type:"+type));
                if(std::find(unit_names.begin(), unit_names.end(), name) != unit_names.end())
                {name="";continue;} 
               
            }
        else if(name==line.substr(0,line.find(":type:"+type)))
            return false;

        continue;
    }
    else if(line.find(":delay:")!=std::string::npos && !synclock)
    {
        if(name=="")
        {   
            name=line.substr(0,line.find(":delay:"));
            if(std::find(unit_names.begin(), unit_names.end(), name) != unit_names.end())
                {name="";continue;} 

            delay=stoi((line.substr(line.find(":delay:")+7)));
        }else if(name==line.substr(0,line.find(":delay:")))
            delay=stoi((line.substr(line.find(":delay:")+7)));
        else continue;

    }
    else if((line.find(".INPUT:")!=std::string::npos) && !synclock) 
    {
        if(line.find(":PINLIST:")==std::string::npos)
            return false;

        line.erase(line.begin(),line.begin()+line.find(".INPUT:")+7);

        if(name=="")
        {   
            name=line.substr(0,line.find(":PINLIST:"));
            if(std::find(unit_names.begin(), unit_names.end(), name) != unit_names.end())
                {name="";continue;} 
            line.erase(line.begin(),line.begin()+line.find(":PINLIST:")+9);

            if(one!="" or two!="" )
                return false;

            if(line.find(":")==std::string::npos && type!="NOT")
                    return false;
            one=line.substr(0,line.find(":"));
            two=one;
            if(type!="NOT")
                two=line.substr(line.find(":")+1);

        }else if(name==line.substr(0,line.find(":PINLIST:")))
            {     
                line.erase(line.begin(),line.begin()+line.find(":PINLIST:")+9);
                if(line.find(":")==std::string::npos && type!="NOT")
                    return false;
                if(one!="" or two!="" )
                    return false;
                one=line.substr(0,line.find(":"));
                two=one;
                if(type!="NOT")
                    two=line.substr(line.find(":")+1);

            }else continue;
    }

    else if((line.find(".OUTPUT:")!=std::string::npos)&& !synclock)
    {

        if(line.find(":PINLIST:")==std::string::npos)
            return false;

        
        line.erase(line.begin(),line.begin()+line.find(".OUTPUT:")+8);

        if(name=="")
        {   
            name=line.substr(0,line.find(":PINLIST:"));
            if(std::find(unit_names.begin(), unit_names.end(), name) != unit_names.end())
                {name="";continue;} 
            line.erase(line.begin(),line.begin()+line.find(":PINLIST:")+9);
            if(three!="")
                return false;
            three=line.substr(line.find(":")+1);

        }else if(name==line.substr(0,line.find(":PINLIST:")))
            {    
          
                if(line.find(":")==std::string::npos)
                    return false;

                line.erase(line.begin(),line.begin()+line.find(":PINLIST:")+9);
                 if(three!="")
                    return false;
                three=line.substr(line.find(":")+1);
                
            }else continue;
    }
    else if((line.find("IN:")!=std::string::npos) && !synclock)
    {
        string signal=line.substr(line.find("IN:")+3);
        if(std::find(INsig.begin(), INsig.end(), signal) != INsig.end())
                continue;
        INsig.push_back(signal);

    }
    else if((line.find("OUT:")!=std::string::npos) && !synclock)
    {
        string signal=line.substr(line.find("OUT:")+4);
        if(std::find(Outsig.begin(), Outsig.end(), signal) != Outsig.end())
                continue;
        Outsig.push_back(signal);
    }
    else if(synclock && line.find(":type:"+type)!=std::string::npos)
    {
           

        if(CLK!="" && CLK!=line.substr(0,line.find(":type:")))
            return false;
        CLK=line.substr(0,line.find(":type:"+type));
    }
    else if(synclock && line.find(":freq:")!=std::string::npos)
    {

        if(CLK!="" && CLK!=line.substr(0,line.find(":freq:")))
            return false;
        CLK=line.substr(0,line.find(":freq:"));
        CLK_freq=stoi((line.substr(line.find(":freq:")+6)));
    }
    else if(synclock && line.find(":start_logic:")!=std::string::npos)
    {
        if(CLK!="" && CLK!=line.substr(0,line.find(":start_logic:")))
            return false;
        CLK=line.substr(0,line.find(":start_logic:"));
        CLK_S=stoi((line.substr(line.find(":start_logic:")+13)));
    }
}
unit_names.push_back(name);

if((one=="" || two=="" || three=="" || name=="" || delay==-1 || INsig.empty() || Outsig.empty()) && (!synclock))
    return false;

if(type=="AND")
{
    AND_unit->s_input1=one;
    AND_unit->s_input2=two;
    AND_unit->s_output=three;
    AND_unit->delay=delay;
    AND_unit->name=name;
}else if(type=="OR")
{
    OR_unit->s_input1=one;
    OR_unit->s_input2=two;
    OR_unit->s_output=three;
    OR_unit->delay=delay;
    OR_unit->name=name;
}
else if(type=="NOR")
{
    NOR_unit->s_input1=one;
    NOR_unit->s_input2=two;
    NOR_unit->s_output=three;
    NOR_unit->delay=delay;
    NOR_unit->name=name;
}
else if(type=="NAND")
{
    NAND_unit->s_input1=one;
    NAND_unit->s_input2=two;
    NAND_unit->s_output=three;
    NAND_unit->delay=delay;
    NAND_unit->name=name;
}
else if(type=="NOT")
{
    NOT_unit->s_input1=one;
    NOT_unit->s_input2=one;
    NOT_unit->s_output=three;
    NOT_unit->delay=delay;
    NOT_unit->name=name;
}
    return true;
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
    int SYNCLOCK_count=0;
    if(argc==2)
        StructureUnitsNum(argv[1],&AND_count,&OR_count,&NOT_count,&NAND_count,&NOR_count,&SYNCLOCK_count);
    else
    {   
        fprintf(stderr, "Wrong input: ./logicSim <file name>\n" );
        return false;
    }

// create arrays for our units
    AND *andvector;
    OR *orvector;
    NOR *norvector;
    NAND *nandvector;
    NOT *notvector;
    Unit *unitvector;
    if(AND_count>0)
    {
        andvector=new AND[AND_count];
        unitvector=new Unit[AND_count];
        for(int c_unit=0;c_unit<AND_count;c_unit++)
        {       
            if(!LoadUnit(argv[1],&(andvector[c_unit]),NULL,NULL,NULL,NULL,false))
                return 10;
            unitvector[c_unit].SetUp("AND",&(andvector[c_unit]),NULL,NULL,NULL,NULL);
            Unit &obj_ref1=std::ref(unitvector[c_unit]);
            units.push_back(obj_ref1);
        }
    }
    if(OR_count>0)
    {
        orvector=new OR[OR_count];
        unitvector=new Unit[OR_count];
        for(int c_unit=0;c_unit<OR_count;c_unit++)
        {       
            if(!LoadUnit(argv[1],NULL,&(orvector[c_unit]),NULL,NULL,NULL,false))
                return 10;
            unitvector[c_unit].SetUp("OR",NULL,&(orvector[c_unit]),NULL,NULL,NULL);
            Unit &obj_ref1=std::ref(unitvector[c_unit]);
            units.push_back(obj_ref1);
        }
    }
    if(NOR_count>0)
    {
        norvector=new NOR[NOR_count];
        unitvector=new Unit[NOR_count];
        for(int c_unit=0;c_unit<NOR_count;c_unit++)
        {       
            if(!LoadUnit(argv[1],NULL,NULL,&(norvector[c_unit]),NULL,NULL,false))
                return 10;
            unitvector[c_unit].SetUp("NOR",NULL,NULL,NULL,&(norvector[c_unit]),NULL);
            Unit &obj_ref1=std::ref(unitvector[c_unit]);
            units.push_back(obj_ref1);
        }
    }
    if(NAND_count>0)
    {
        nandvector=new NAND[NAND_count];
        unitvector=new Unit[NAND_count];
        for(int c_unit=0;c_unit<NAND_count;c_unit++)
        {       
            if(!LoadUnit(argv[1],NULL,NULL,NULL,NULL,&(nandvector[c_unit]),false))
                return 10;
            unitvector[c_unit].SetUp("NAND",NULL,NULL,&(nandvector[c_unit]),NULL,NULL);
            Unit &obj_ref1=std::ref(unitvector[c_unit]);
            units.push_back(obj_ref1);
        }
    }
    if(NOT_count>0)
    {
        notvector=new NOT[NOT_count];
        unitvector=new Unit[NOT_count];
        for(int c_unit=0;c_unit<NOT_count;c_unit++)
        {       
            if(!LoadUnit(argv[1],NULL,NULL,NULL,&(notvector[c_unit]),NULL,false))
                return 10;
            unitvector[c_unit].SetUp("NOT",NULL,NULL,NULL,NULL,&(notvector[c_unit]));
            Unit &obj_ref1=std::ref(unitvector[c_unit]);
            units.push_back(obj_ref1);
        }
    }
    if(SYNCLOCK_count>0)
    {   if(SYNCLOCK_count!=1)
            return 10;
        else
            if(!LoadUnit(argv[1],NULL,NULL,NULL,NULL,NULL,true))
                return 10;
        if(std::find(unit_names.begin(), unit_names.end(), CLK) != unit_names.end())
                return 10;
        if(std::find(INsig.begin(), INsig.end(), CLK) != INsig.end())
                return 10;
        if(std::find(Outsig.begin(), Outsig.end(), CLK) != Outsig.end())
                return 10; 
        clocksyn=true;  
        CLK_S=!CLK_S;
    }
        unit_names.clear();
    

    SetOutput("test.out");
    
    Print("#=======================================================\n#Global input signals\n#=======================================================\n");
    unsigned int val=0;
    Print("#");
    for(;val<INsig.size();val++)
        Print("%s\t",INsig[val].c_str());
    Print("Time\n");

    Init(0,500); 
    (new Generator())->Activate();
    if(clocksyn)
        (new CLKGenerator())->Activate();
    Run();

    Print("#=======================================================\n#Global output signals\n#=======================================================\n");
    Print("#Signal\tValue\tTime\n");
    Print("%s\n",TstatOut.c_str());  
    Print("#=======================================================\n#CLK signal\n#=======================================================\n");
    Print("#Value\tTime\n"); 
    Print("%s\n",TstatCLK.c_str());
    Tstatprint();
    SIMLIB_statistics.Output();
    return true;
}
