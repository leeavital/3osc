#ifndef _3OSC_H
#define _3OSCH


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



void build_tables();


// public
void setFrequency();

void setSynth( int, int );

void setGain( int, float );





#endif
