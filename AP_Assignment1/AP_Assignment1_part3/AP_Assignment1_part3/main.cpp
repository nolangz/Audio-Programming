//
//  main.cpp
//  Assignment1_part3
//
//  Created by Nuolin Lai on 2021/2/1.
//  Code for part 3

#include <iostream>
#include "src/MattsAudioTools.h"
#include <cmath>

//fucntion to warp number into (0,1);
float ppa(float modulationphase)
{
    float radian = (modulationphase-floor(modulationphase));
    return radian;
}

//define class Oscillator to make logic clear
class Oscillator{
   
    //Public
public:
    //constructor
    Oscillator(){
        std::cout << "Oscillator created!\n";
    }
    
    //create public function to set frequency
    void setfrequency(float newfrequency)
    {
        frequency = newfrequency;
        //calculate phase delta
        phaseDelta = frequency / sampleRate;
    }
    
    //create public function to set phase
    void setphase(float newphase)
    {
        phase = newphase;
    }
    
    //read phase from class private variabes
    float getphase()
    {
        return phase;
    }
    
    //calculate the output of the Sine Oscillator
    float getNextsample()
    {
        phase += phaseDelta;
        if(phase > 1.0)
        {
            phase -= 1.0;
        }
        return 0.35*sin(phase*2.0*3.1415926536);
    }
    
    //private varibles
private:
    int sampleRate = 44100;             //Sampling Rate
    float frequency;                   //frequency of the Oscillator
    float phase=0;                    //phase
    float phaseDelta;                //phase delta
    float modulationindex;          //modulationinedex
};

int main(int argc, const char * argv[]) {
    // insert code here...
    
    int duration = 15;                 //duration in seconds
    int sampleRate = 44100;            //sampling rate
    int durationInSamples = duration*sampleRate;   // total number of samples
    float* Osc1samples = new float[durationInSamples]; //Empty array to store Osc1
    float* Osc2samples = new float[durationInSamples]; //Empty array to store Osc2
    float modulationphase;             //modualtionpase for Osc2
    float* Osc3samples = new float[durationInSamples]; //Empty array to store Osc3
    
    
    Oscillator Osc1;//create Osc1
    Oscillator Osc2;//create Osc2
    Oscillator Osc3;//create Osc3
    
    //set frequency
    Osc1.setfrequency(3);
    Osc2.setfrequency(2);
    Osc3.setfrequency(0.0001);
    
    //Using loop to create output
    for(int i=0; i<durationInSamples; i++)
    {
        //read sine Osc1,3
        Osc1samples[i] = Osc1.getNextsample();
        Osc3samples[i] = Osc3.getNextsample();
        
        //Calculate modualtion phase
        modulationphase = ppa((Osc1samples[i]+Osc2.getphase()*2*3.1415926536)/(2*3.1415926536));
        //Read sine Oscillator output
        Osc2.setphase(modulationphase);
        //calculate modulation phase
        Osc2samples[i] = Osc2.getNextsample();
    }
    
    //Audio play
    AudioPlayerOpenAL Player;
    Player.playAudioData(Osc2samples,durationInSamples,1,sampleRate,16);
}
