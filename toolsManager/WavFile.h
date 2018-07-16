#pragma once

#include <string>

class WavFileWriter {
public:
    WavFileWriter();
    ~WavFileWriter();
    bool open(const char* filename, short sampleRate, short channels=1);
    int  write(const short *data, size_t count);
    void close();
	bool isOpened() const { return (NULL != _file); }
private:
    void writeHeader(short sampleRate, short channels);
    void writeHeaderLen(size_t count);
private:
    FILE* _file;
    size_t _sampleCount;
};

class WavFileReader {
public:
    WavFileReader();
	~WavFileReader();
    bool open(const char* filename);
    int  read(short *buffer, size_t count);
    void close();
	
    // it should be called after open() if want to read all PCM data
    int sampleCount();

    int sampleRate() const { return _sampleRate; }
    short channels() const { return _channels; }
    bool isOpened() const { return (NULL != _file); }
private:
    FILE* _file;
    int _sampleRate;
    short _channels;
    int _realCount; // sample count
};
