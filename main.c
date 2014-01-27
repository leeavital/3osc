#include <stdio.h>
#include <math.h>
#include <portaudio.h>



int num_seconds;


#define FRAMES_PER_BUFFER 1024
#define SAMPLE_RATE 44100
#define N_PI 3.14159
#define TABLE_SIZE 1000


PaStreamParameters output_params;
PaStream * stream;
PaError err;
float sin_tab[ TABLE_SIZE ];
double phase;
double incr;
float buffer[FRAMES_PER_BUFFER][2]; // stereo


int buffer_count;


double frequency = 523.23;



int main(){

    int i, j, k;

    incr = (double)(TABLE_SIZE * frequency ) / (double)SAMPLE_RATE;
    printf("incr: %f\n", incr);
    // return 0;
    // fill up the sineseudal tab
    for( i = 0; i < TABLE_SIZE; i++ ){
        sin_tab[ i ] = (float) sin( ((double)i / (double)TABLE_SIZE) * 2 * N_PI );
    }



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


    buffer_count = ((8 * SAMPLE_RATE) / FRAMES_PER_BUFFER );
    for( i = 0; i < buffer_count; i++ ){
        for( j = 0; j < FRAMES_PER_BUFFER; j++ ){
            buffer[j][0] = sin_tab[ (int)phase ];
            buffer[j][1] = sin_tab[ (int)phase ];
            phase += incr;
            if( phase > TABLE_SIZE ){ phase -= TABLE_SIZE; }
            printf( "%f, %f\n", sin_tab[ (int)phase ], sin_tab[ (int)phase ] );
        }
        Pa_WriteStream( stream, buffer, FRAMES_PER_BUFFER );
    }

    // for( i =0; i < buffer_count; i++ ){
    //     for( j = 0; j < FRAMES_PER_BUFFER; j++ ){
    //         buffer[j][0] = sin_tab[ (int)phase ];
    //         buffer[j][1] = sin_tab[ (int)phase ];

    //         phase = (phase + incr);
    //         if( phase >= TABLE_SIZE ){ phase -= TABLE_SIZE; }
    //         printf( "%f %f\n", buffer[j][0], buffer[j][1] );
    //     }

    //     err = Pa_WriteStream( stream, buffer, FRAMES_PER_BUFFER );
    // }

    err = Pa_StopStream( stream );
    if( err ){
        printf("error\n");
    }

}
