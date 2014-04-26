#ifndef _3OSC_H
#define _3OSC_H


#define FRAMES_PER_BUFFER 1024
#define SAMPLE_RATE 44100
#define NUM_SYNTHS 3


#define OSC_SINE 100
#define OSC_TRIANGLE 101
#define OSC_SAWTOOTH 102

typedef struct t_synth{
    float* wave_tab;
    float gain;
} t_synth;

typedef int synth_t;



void oscInit();
void oscStartLoop();
void oscWait();


// public
void setFrequency();

void setSynth( int, synth_t );

void setGain( int, float );





#endif
