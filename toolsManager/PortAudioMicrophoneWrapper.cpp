/*
 * PortAudioMicrophoneWrapper.cpp
 *
 * Copyright (c) 2017 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *     http://aws.amazon.com/apache2.0/
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#include "SampleApp/PortAudioMicrophoneWrapper.h"
#include "SampleApp/ConsolePrinter.h"
#include <AVSCommon/Utils/File/FileUtils.h>

namespace alexaClientSDK {
namespace sampleApp {

using avsCommon::avs::AudioInputStream;

static const int NUM_OUTPUT_CHANNELS = 0;

PortAudioMicrophoneWrapper::PortAudioMicrophoneWrapper()
    : AudioIn(), m_paStream{nullptr} {
}

PortAudioMicrophoneWrapper::~PortAudioMicrophoneWrapper() {
#ifndef MICKWDOUTSIDE
    Pa_StopStream(m_paStream);
    Pa_CloseStream(m_paStream);
    Pa_Terminate(); //git://anongit.freedesktop.org/gstreamer/gst-docs
#endif
}

bool PortAudioMicrophoneWrapper::initialize(int sampleRate, int channels) {
#ifndef MICKWDOUTSIDE
    PaError err;
    err = Pa_Initialize();
    if (err != paNoError) {
        ConsolePrinter::simplePrint("Failed to initialize PortAudio");
        return false;
    }
    err = Pa_OpenDefaultStream(
        &m_paStream,
        channels,
        NUM_OUTPUT_CHANNELS,
        paInt16,
        sampleRate,
        (unsigned long)(sampleRate * 0.01),
        PortAudioCallback,
        this);
    if (err != paNoError) {
        ConsolePrinter::simplePrint("Failed to open PortAudio default stream");
        return false;
    }
#endif
    return true;
}

bool PortAudioMicrophoneWrapper::startStreamingMicrophoneData() {
#ifndef MICKWDOUTSIDE
    PaError err = Pa_StartStream(m_paStream);
    if (err != paNoError) {
        ConsolePrinter::simplePrint("Failed to start PortAudio stream");
        return false;
    }
#endif
    return true;
}

bool PortAudioMicrophoneWrapper::stopStreamingMicrophoneData() {
#ifndef MICKWDOUTSIDE
    PaError err = Pa_StopStream(m_paStream);
    if (err != paNoError) {
        ConsolePrinter::simplePrint("Failed to stop PortAudio stream");
        return false;
    }
#endif
    return true;
}

int PortAudioMicrophoneWrapper::PortAudioCallback(
    const void* inputBuffer,
    void* outputBuffer,
    unsigned long numSamples,
    const PaStreamCallbackTimeInfo* timeInfo,
    PaStreamCallbackFlags statusFlags,
    void* userData) {
    PortAudioMicrophoneWrapper* wrapper = static_cast<PortAudioMicrophoneWrapper*>(userData);
    ssize_t returnCode = wrapper->write(inputBuffer, numSamples);
    if (returnCode <= 0) {
        ConsolePrinter::simplePrint("Failed to write to stream.");
        return paAbort;
    }
    return paContinue;
}

}  // namespace sampleApp
}  // namespace alexaClientSDK
