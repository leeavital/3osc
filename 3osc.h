#ifndef _3OSC_H
#define _3OSCH


#define FRAMES_PER_BUFFER 1024
#define SAMPLE_RATE 44100
#define N_PI 3.14159
#define TABLE_SIZE 1000




typedef struct t_synth{
    float* wave_tab;
    float gain;
} t_synth;


float sin_tab[ TABLE_SIZE ];
float triangle_tab[ TABLE_SIZE ];
float saw_tab[ TABLE_SIZE ];

void build_tables();

void setFrequency();



void setSynth( int, float* );

void setGain( int, float );





#endif
