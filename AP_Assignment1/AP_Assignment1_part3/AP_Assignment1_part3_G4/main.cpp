//
//  main.cpp
//  Assignment1_part3
//
//  Created by Nuolin Lai on 2021/2/1.
//
//This project create a intreresting Progressive pitch and rynthm speed only using two kinds of Oscillator and 6 Oscillator in total for phase modualtion:
//Sine  Square
//Enjor it!


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
        return 0.5*sin(phase*2.0*3.1415926536);
    }
    
    //calculate the output of the Triangle Oscillator
    float getNextsample_TRIANGLE()
        {
            phase += phaseDelta;
            if(phase > 1.0)
            {
                phase -= 1.0;
            }
            return 0.5*(fabs(phase - 0.5f) - 0.5f);
        }
    
    //calculate the output of the Linear Oscillator
    float getNextsample_LINEAR()
        {
            phase += phaseDelta;
            if(phase > 1.0)
            {
                phase -= 1.0;
            }
            return 0.5*(phase - 0.5f);
        }
    
    //calculate the output of the Squate Oscillator
    float getNextsample_SQUARE()
        {
            phase += phaseDelta;
            if(phase > 1.0)
            {
                phase -= 1.0;
            }
            float sq = 0.5f;
            
            if (phase > 0.5)
            {
                sq = -0.5f;
            }
            
            return 0.5*sq;
        }

//private varibles
private:
    int sampleRate = 44100;             //Sampling Rate
    float frequency;                   //frequency of the Oscillator
    float phase=0;                    //phase
    float phaseDelta;                //phase delta
};

int main(int argc, const char * argv[]) {
    // insert code here...
    
    int duration = 15;                      //duration in seconds
    int sampleRate = 44100;                  //sampling rate
    int durationInSamples = duration*sampleRate;   // total number of samples
    float* Osc1samples = new float[durationInSamples];  //Empty array to store Osc1
    float* Osc2samples = new float[durationInSamples]; //Empty array to store Osc2
    float* Osc3samples = new float[durationInSamples]; //Empty array to store Osc3
    float* Osc4samples = new float[durationInSamples]; //Empty array to store Osc4
    float* Osc5samples = new float[durationInSamples]; //Empty array to store Osc5
    float* Osc6samples = new float[durationInSamples]; //Empty array to store Osc6
    float modulationphase;  //Modulation phase for Osc2
    float modulationphase2; //Modulation phase for Osc3
    float modulationphase3; //Modulation phase for Osc5
    Oscillator Osc1; //create Osc1
    Oscillator Osc2;//create Osc2
    Oscillator Osc3;//create Osc3
    Oscillator Osc4;//create Osc4
    Oscillator Osc5;//create Osc5
    Oscillator Osc6;//create Osc6
    
    Osc1.setfrequency(1);
    Osc2.setfrequency(0.6);
    Osc3.setfrequency(0.5);
    Osc4.setfrequency(1);
    Osc5.setfrequency(5000);
    Osc6.setfrequency(1000);
    
    //Using loop to create output
    for(int i=0; i<durationInSamples; i++)
    {
        //phase modulation3
        Osc6samples[i] = Osc6.getNextsample();
        //calculate modualtion phase
        modulationphase3 = ppa((Osc6.getNextsample()+Osc5.getphase()*2*3.1415926536)/(2*3.1415926536));
        Osc5.setphase(modulationphase3);
        //Read sine Oscillator output
        Osc5samples[i] = Osc5.getNextsample();
        
        //phase modulation2, Use the output of phase modulation 3 multiplise to next modulation signal
        //Read Sine Oscillator output
        Osc4samples[i] = Osc4.getNextsample();
        //calculate modualtion phase
        modulationphase2 = ppa((Osc4samples[i]*Osc5.getNextsample()+Osc3.getphase()*2*3.1415926536)/(2*3.1415926536));
        //Set modualtion phase
        Osc3.setphase(modulationphase2);
        //Read sine Oscillator output
        Osc3samples[i] = Osc3.getNextsample();
        
        //phase modulation1, Use the output of phase modulation 2 multiplise to next modulation signal
        //Read Sine Oscillator output
        Osc1samples[i] = Osc1.getNextsample();
        //calculate modualtion phase
        modulationphase = ppa((Osc3samples[i]* Osc1samples[i]+Osc2.getphase()*2*3.1415926536)/(2*3.1415926536));
        //Set modualtion phase
        Osc2.setphase(modulationphase);
        //Read sine Oscillator output
        Osc2samples[i] = Osc2.getNextsample_SQUARE();
    }
    
    //Audio Play
    AudioPlayerOpenAL Player;
    Player.playAudioData(Osc2samples,durationInSamples,1,sampleRate,16);
}
