#include <stdio.h>
#include <math.h>
#include <portaudio.h>


#include "3osc.h"




PaStreamParameters output_params;
PaStream * stream;
PaError err;
double	phase;
double incr;
float buffer[FRAMES_PER_BUFFER][2]; // stereo


int buffer_count;



float* current_synth;

double frequency = 440; // A4


float chromatic_scale[] = {440, 466.16, 493.88, 523.25, 554.37, 587.33, 622.25};
int c_count = 7;


void setFrequency( double freq){
    frequency = freq;
    incr = (double)(TABLE_SIZE * frequency ) / (double)SAMPLE_RATE;
}


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
}



void setSynth( int synth_num, float* synth_tab ){
    current_synth = synth_tab;
}


void setGain( int synth_num, float gain ){


}



int main(){

    int i, j, k;

    // necessary to build waveforms
    build_tables();

    setFrequency( 500  );
    setSynth( 0, saw_tab );




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
    for( k = 0; k < c_count; k++ ){
        setFrequency( chromatic_scale[ k ] );

        if( err ){
            printf("error\n");
        }


        buffer_count = ((2 * SAMPLE_RATE) / FRAMES_PER_BUFFER );
        for( i = 0; i < buffer_count; i++ ){
            for( j = 0; j < FRAMES_PER_BUFFER; j++ ){
                buffer[j][0] = current_synth[ (int)phase ];
                buffer[j][1] = current_synth[ (int)phase ];
                phase += incr;
                if( phase > TABLE_SIZE ){ phase -= TABLE_SIZE; }
                printf( "%f, %f\n", current_synth[ (int)phase ], current_synth[ (int)phase ] );
            }
            Pa_WriteStream( stream, buffer, FRAMES_PER_BUFFER );
        }



    }


    err = Pa_StopStream( stream );
    if( err ){
        printf("error\n");
    }

}
