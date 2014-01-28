#include <stdio.h>
#include <math.h>
#include <portaudio.h>
#include <pthread.h>
#include <unistd.h>

#include "3osc.h"




PaStreamParameters output_params;
PaStream * stream;
PaError err;
double	phase;
double incr;
float buffer[FRAMES_PER_BUFFER][2]; // stereo


int buffer_count;



float* current_synth;

double frequency = 440.0; // A4




void *loop( void* arg ){

    int i, j, k;
    i = 0;
    j = 0;
    k = 0;

    // necessary to build waveforms
    build_tables();

    setSynth( 0, triangle_tab );
    setSynth( 1, triangle_tab );
    setSynth( 2, sin_tab );

    setFrequency( 400.0  );






    err = Pa_Initialize();
    if( err != paNoError ){
        printf( "error\n");
    }

    output_params.device = Pa_GetDefaultOutputDevice();
    // do error checking here

    output_params.channelCount = 2;
    output_params.sampleFormat= paFloat32;
    output_params.suggestedLatency = 0.050;
    output_params.hostApiSpecificStreamInfo = NULL; // wat?

    err = Pa_OpenStream( &stream,
        NULL, // no input
        &output_params,
        SAMPLE_RATE,
        FRAMES_PER_BUFFER,
        paClipOff,
        NULL,
        NULL );

    if( err != paNoError ){
        printf( "error\n");
    }



    err = Pa_StartStream( stream );

    if( err ){
        printf("error\n");
    }


    // buffer_count = ((2 * SAMPLE_RATE) / FRAMES_PER_BUFFER );
    while(  1 ){
        for( i = 0; i < FRAMES_PER_BUFFER; i++ ){
            buffer[i][0] = 0; //current_synth[ (int)phase ];
            buffer[i][1] = 0; //current_synth[ (int)phase ];

            for ( j = 0; j < NUM_SYNTHS; j++ ){
                buffer[i][0] += synthesizers[ j ].wave_tab[ (int)phase ] * synthesizers[ j ].gain;
                buffer[i][1] = buffer[i][0];
            }

            phase += incr;
            if( phase > TABLE_SIZE ){ phase -= TABLE_SIZE; }
            // printf( "%f, %f\n", current_synth[ (int)phase ], current_synth[ (int)phase ] );
        }
        Pa_WriteStream( stream, buffer, FRAMES_PER_BUFFER );
    }





    err = Pa_StopStream( stream );
    if( err ){
        printf("error\n");
    }

}



void setFrequency( double freq){
    frequency = freq;
    incr = (double)(TABLE_SIZE * frequency ) / (double)SAMPLE_RATE;
}



// build tables and also synths
void build_tables(){
    // fill up the sineseudal tab
    int i = 0;
    for( i = 0; i < TABLE_SIZE; i++ ){
        sin_tab[ i ] = (float) sin( ((double)i / (double)TABLE_SIZE) * 2 * N_PI );
    }


    // build a triangle wave
    for( i = 0; i < TABLE_SIZE / 2; i++ ){
        triangle_tab[ i  ] = 2 * (i) / (TABLE_SIZE / 2.0) - 1.0;
        triangle_tab[ TABLE_SIZE - i - 1] = sin_tab[ i ];
    }

    // build a saw tab
    for( i = 0; i < TABLE_SIZE; i++ ){
        saw_tab[ i ] = (double)i / TABLE_SIZE - 1;
    }


    // fill the synth table full of synths
    for( i = 0; i < NUM_SYNTHS; i++ ){
        synthesizers[i] = (t_synth){.wave_tab = sin_tab, .gain = .5 + i * .1};
    }
}



void setSynth( int synth_num, float* synth_tab ){
    synthesizers[ synth_num ].wave_tab = synth_tab;
}


void setGain( int synth_num, float gain ){


}




int main(){

    pthread_t loop_thread;
    pthread_attr_t *attrs = NULL;

    void *arg = NULL;

    pthread_create( &loop_thread, attrs, loop, arg );

    char ch;
    while( (ch = getchar()) != '.'  ){
        printf( "got %c\n", ch);
        fflush( stdout );
    }
    pthread_join( loop_thread, NULL );


}

