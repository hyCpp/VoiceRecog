#include <string>
#include <stdio.h>
#include "portaudio.h"
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#define SAMPLE_RATE       (16000)
#define FRAMES_PER_BUFFER (1024)
#define NUM_CHANNELS      (1)
#define NUM_SECONDS       (5)

#if 0
#define PA_SAMPLE_TYPE  paFloat32
typedef float SAMPLE;
#define SAMPLE_SILENCE  (0.0f)
#define PRINTF_S_FORMAT "%.8f"
#elif 1
#define PA_SAMPLE_TYPE  paInt16
typedef short SAMPLE;
#define SAMPLE_SILENCE  (0)
#define PRINTF_S_FORMAT "%d"
#elif 0
#define PA_SAMPLE_TYPE  paInt8
typedef char SAMPLE;
#define SAMPLE_SILENCE  (0)
#define PRINTF_S_FORMAT "%d"
#else
#define PA_SAMPLE_TYPE  paUInt8
typedef unsigned char SAMPLE;
#define SAMPLE_SILENCE  (128)
#define PRINTF_S_FORMAT "%d"
#endif

int exiting = 0;
FILE  *fid;


void sigroutine(int dunno) {
    switch (dunno) {
    case SIGINT:
        exiting = 1;
        break;
    }
}
int recordCallback(const void *input,
       void *output,
       unsigned long frameCount,
       const PaStreamCallbackTimeInfo* timeInfo,
       PaStreamCallbackFlags statusFlags,
       void *userData)
{
    printf("recv %lu frames\n", frameCount);
    fwrite(input, NUM_CHANNELS * sizeof(SAMPLE), frameCount, fid);

    if (exiting) {
        printf("exiting loop\n");
        return paComplete;
    }
    else
        return paContinue;
}


void read()
{
    PaStreamParameters inputParameters, output;
    PaStream *stream;
    PaError err;
    fid  = fopen("/home/huyang/MyDemo/C++Test/VR/Demo/weather.wav", "wb");

    if (fid == NULL) {
        return;
    }

    signal(SIGINT, sigroutine);

    err = Pa_Initialize();
    if (err != paNoError) {
        printf("Error Initialize \n");
        return;
    }

    inputParameters.device = Pa_GetDefaultInputDevice();
    if (inputParameters.device == paNoDevice) {
        printf("Error: no default input device \n");
    }
    inputParameters.channelCount = NUM_CHANNELS;
    inputParameters.sampleFormat = paInt16;
    inputParameters.suggestedLatency = Pa_GetDeviceInfo(inputParameters.device)->defaultLowInputLatency;
    inputParameters.hostApiSpecificStreamInfo = NULL;

    err = Pa_OpenStream(&stream, &inputParameters, NULL, SAMPLE_RATE, FRAMES_PER_BUFFER, paClipOff, recordCallback, NULL);
    if (err != paNoError) {
        printf("Error openstream\n");
        return;
    }

    err = Pa_StartStream(stream);
    printf("Now recording !\n");
    fflush(stdout);

    while (Pa_IsStreamActive(stream)) {
        usleep(50000);
    }

    err = Pa_CloseStream(stream);
    if (err != paNoError) {
        printf("Error close\n");
        return;
    }

    fclose(fid);
    Pa_Terminate();
}

int main(void)
{
    read();
}
