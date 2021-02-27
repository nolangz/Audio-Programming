//
//  main.cpp
//  Assignment1_part2
//
//  Created by Nuolin Lai on 2021/2/1.
// Code for Part2

#include <iostream>
#include <cmath>

//Function Definition
float midiToFrequency(float midinote)
{
    //Calcualte freuqency based on input midinote
    float frequency = 440*pow(2.0,((midinote-69)/12));
    return frequency;
}

int main(int argc, const char * argv[]) {
    // insert code here...
    float midinote;          //Define midenote
    
    //Ask user input midinote
    std::cout << "Input your midi note\n";
    std::cin >> midinote;
    
    //judge if midinote right or not
    if(midinote <= 0 || midinote >= 127)
    {
        // if not right,print and end
        std::cout << "please enter a number in range(0,127)\n";
        std::cin >> midinote;
    }
    else
    {
        // if right, run miditoFrequency
        float freq = midiToFrequency(midinote);
        //print out
        std::cout << "Note " << midinote << " corresponds to a frequency of4 " << freq << " Hz\n";
    }
    
    return 0;
}

