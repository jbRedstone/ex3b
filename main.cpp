#include <iostream>
#include <string>
#include <cmath>
#include "NTGate.hpp"
#include "Gate.hpp"
#include "NotGate.hpp"
#include "AndGate.hpp"
#include "OrGate.hpp"
#include "XorGate.hpp"
#include "MuxGate.hpp"
#include "CompositeGate.hpp"
#include "Exception.hpp"
#include "InvalidCommand.hpp"
#include "InvalidInputType.hpp"
#include "InvalidParameter.hpp"
#include "InvalidGate.hpp"
#include "InvalidGateSize.hpp"

using std::endl;
using std::cin;
using std::cout;
using std::istream;

void presentGates(vector<NTGate*> &gates, const size_t numOfGates);
void eval(vector<NTGate*> &gates);
void comp(vector<NTGate*> &gates, vector<CompositeGate> &cGates, const size_t numOfGates);
void table(vector<NTGate*> &gates);
void del(vector<NTGate*> &gates);
void help();
void checkGateValidity(const size_t input, const vector<NTGate*> & gates);
void runException(const Exception & exception);
void setGatesSize(size_t & size, const size_t minSize);

template <class T>
void getInput(T & in)
{
    if(!(cin >> in))
        throw InvalidInputType();
    
}

int main()
{
    size_t numOfGates = 5;

    //This vector holds all gates used by main
    vector<NTGate*> gates;
    
    //This vector holds all composite gates used by main
    vector<CompositeGate> cGates;
    
    //Create the first few gates to begin the program
	NotGate nGate;
    AndGate aGate;
    OrGate oGate;
    XorGate xGate;
    MuxGate mGate;
    
    //Put gates in vector
	gates.push_back(&nGate);
    gates.push_back(&aGate);
    gates.push_back(&oGate);
    gates.push_back(&xGate);
    gates.push_back(&mGate);
    
    //Holds user's command
    string command;
    
    while (true)
    {
        
        try
        {
            setGatesSize(numOfGates, gates.size());
            
            cout << endl;
            
            presentGates(gates, numOfGates);
            
            //Receive command
            getInput(command);
            
            if (command.compare("eval")==0)
                eval(gates);
            else if (command.compare("comp")==0)
                comp(gates, cGates, numOfGates);
            else if (command.compare("table")==0)
                table(gates);
            else if (command.compare("resize")==0)
                setGatesSize(numOfGates, gates.size());
            else if (command.compare("del")==0)
                del(gates);
            else if (command.compare("exit")==0)
                return EXIT_SUCCESS;
            else if (command.compare("help")==0)
                help();
            else
                throw InvalidCommand();
        }
        catch(InvalidCommand exception)
        {
            runException(exception);
            continue;
        }
        catch(InvalidInputType exception)
        {
            runException(exception);
            continue;
        }
        catch(InvalidParameter exception)
        {
            runException(exception);
            continue;
        }
        catch (InvalidGate exception)
        {
            runException(exception);
            continue;
        }
        catch (InvalidGateSize exception)
        {
            runException(exception);
            continue;
        }
    }
    
    return EXIT_SUCCESS;
}

//---------------------------- Present Gates ----------------------------

void presentGates(vector<NTGate*> &gates, const size_t numOfGates)
{
    cout << "List of Gates: (" << gates.size() << "/" << numOfGates << ") " << endl;
    
    //Present gates to user
    for (unsigned int i = 0; i < gates.size(); i++)
    {
        cout << i << ": " << gates[i]->getName() << " (" << gates[i]->getPars() << " Inputs)" << endl;
    }
    
    cout << "=============================" << endl <<
    "Please enter a command from the list, then press enter (type 'help' for the command list)..." << endl <<
    "(note: commands are case sensitive, so please type in lower case)" << endl;
}


//---------------------------- COMMAND = eval ----------------------------

void eval(vector<NTGate*> &gates)
{
    
    //Holds the input that comes after the command (which gate number, T/F inputs...)
    size_t input;
    
    //If eval, recieve gate number
    getInput(input);
    
    checkGateValidity(input, gates);
    
    int inBool;
    
    vector<bool> params;
    
    //Recieve gate's boolean inputs, and check for validity
    for(int i = 0; i < gates[input] -> getPars(); i++)
    {
        cin >> inBool;
        
        if (inBool != 0 && inBool != 1)
        {
            throw InvalidParameter();
        }
        
        //Populate vector of parametres to be fed into gate
        params.push_back((int)inBool);
    }
    
    //Output gate's boolean output
    cout << endl << gates[input] -> getName() << " (" << gates[input] -> getPars() << " Inputs) Result: " << gates[input] -> getLogic(params) << endl << endl;
}

//---------------------------- COMMAND = comp ----------------------------

void comp(vector<NTGate*> &gates, vector<CompositeGate> &cGates, const size_t numOfGates)
{
    if (gates.size() >= numOfGates)
        throw InvalidGateSize();
    
    //These to hold the gates to be merged
    size_t g1 = 0;
    getInput(g1);
    
    checkGateValidity(g1, gates);
    
    //Receive second gate
    size_t g2 = 0;
    getInput(g2);
    
    checkGateValidity(g2, gates);
    
    //Vector to hold gates that will be merged together to form new gate
    vector <NTGate*> newGates;
    
    
    //Check if g1 is already composite
    CompositeGate * cgPtr = dynamic_cast<CompositeGate*>(gates[g1]);
    
    //If it's composite, push all the elements of g1 into the vector
    if (cgPtr)
        for (size_t i = 0; i < cgPtr -> getGates().size(); i++)
            newGates.push_back(cgPtr -> getGates()[i]);
    //If g1 isn't composite, it's a simple Class, so push in to the new gate vector
    else
        newGates.push_back(gates[g1]);
    
    
    //Same for g2 as for g1
    cgPtr = dynamic_cast<CompositeGate*>(gates[g2]);
    
    if (cgPtr)
        for (size_t i = 0; i < cgPtr -> getGates().size(); i++)
            newGates.push_back(cgPtr -> getGates()[i]);
    else
        newGates.push_back(gates[g2]);
    
    
    //Make a new composite gate out of the vector of gates
    //            CompositeGate cGate(newGates);
    
    //this stops the new gate being destroyed out of scope
    cGates.emplace_back(CompositeGate(newGates));
    //            cout << endl << cGates.front().getName() << endl;
    
    //Add the new composite gate to the list of gates in main
    gates.push_back(&(cGates.back()));
    
    cout << endl;
    
}

//---------------------------- COMMAND = table ----------------------------

void table(vector<NTGate*> &gates)
{
    //Holds the input that comes after the command (which gate number, T/F inputs...)
    size_t input;
    
    //If table requested, input holds the gate number requested
    getInput(input);
    
    checkGateValidity(input, gates);

    //get number of parametres required for this particular gate
    int pars = gates[input]->getPars();
    
    //Title before truth table
    cout << endl << gates[input]->getName() << " (" << gates[input]->getPars() <<
    " Inputs) Truth Table: " << endl;
    
    //create truth table for all possible perumtations
    for (int i = 0; i < pars; i++)
    {
        cout << "input" << i << " |";
    }
    
    cout << "result |" << endl;
    
    for (int i = 0; i <= pars; i++)
    {
        cout << "========";
    }
    
    cout << endl;
    
    //holds all the possible permutations
    vector<bool> truthPermutations;
    
    for (int i = 0; i < pars; i++)
    {
        truthPermutations.push_back(false);
    }
    
    bool endOfArr;
    
    for (int i = 0; i < (pow(2,pars)); i++)
    {
        
        //print permutations in this row of truth table
        for (int j = 0; j < pars; j++)
        {
            cout << truthPermutations[j] << "      |";
        }
        
        //print gate's logic for this permutation
        cout << gates[input] -> getLogic(truthPermutations) << "      |";
        
        cout << endl;
        
        //switch to next permutation
        endOfArr = truthPermutations[pars-1];
        truthPermutations[pars-1] = !truthPermutations[pars-1];
        for (int j = pars - 2; j >= 0; j--)
        {
            if (endOfArr)
            {
                truthPermutations[j] = !truthPermutations[j];
                endOfArr = !truthPermutations[j] && endOfArr;
            }
            else
                endOfArr = truthPermutations[j] && endOfArr;
        }
        
    }
    
    cout << endl;
}

//---------------------------- COMMAND = delete ----------------------------

void del(vector<NTGate*> &gates)
{
    
    //Holds the input that comes after the command (which gate number, T/F inputs...)
    size_t input;
    
    //input which gate to be deleted
    getInput(input);
    
    checkGateValidity(input, gates);
    
    //otherwise just erase the gate
    gates.erase(gates.begin() + input);
    
    cout << endl;
}

//---------------------------- COMMAND = help ----------------------------

void help()
{
    cout << endl
    << "Following is the list of the available commands:" << endl
    << "* eval <gate index> <param1 param2 ...> - evaluates gate no. x with param1 param2 etc." << endl
    << "* comp <gate1 index> <gate2 index> - composites gate no. 1 with gate no. 2 and adds it to the list of the gates" << endl
    << "* table <gate index> - displays the truth table of the selected gate" << endl
    << "* resize - allows for the resizing of the gate array" << endl
    << "* del <gate index> - deletes the selected gate from the list" << endl
    << "* exit - greetings the user and closes the program" << endl
    << "* help - shows this menu again with the list of the gates" << endl << endl;
}

//------------------------- Check Gate Validity --------------------------
void checkGateValidity(const size_t input, const vector<NTGate*> & gates)
{
    if (!(input < (gates.size() - 1)))
    {
        throw InvalidGate();
    }
}
//---------------------------- Run Exception -----------------------------
void runException(const Exception & exception)
{
    cout << endl << exception << endl << endl;
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}
//---------------------------- Set Gate Size -----------------------------
void setGatesSize(size_t & size, const size_t minSize)
{
    cout << "Please enter the maximum number of gates you would like to set for this program:" << endl
    << "(number must be greater than or equal to 5)" << endl;
    getInput(size);
    
    if (size < minSize)
        throw InvalidGateSize();
    
}


