#include "SampleApp/WavFile.h"
#include <string.h>

// header of wav file
struct WAV_HDR {
    char chunkID[4];            // 'RIFF'
    int32_t  dwChunkSize;		// chunk size
    char format[4];             // format 'WAVE'
    char subchunk1ID[4];        // subchunk ID 'fmt '
    int32_t  dwSubchunk1Size;	// for PCM it's 16    	
    short int wAudioFormat;		// PCM=1
    short int wChannels;        // 1:mono, 2:stereo
    int32_t dwSampleRate;		// such as 16000
    int32_t dwByteRate;
    short int wBlockAlign;
    short int wBitsPerSample;	// such as 16 bits
};

// header of chunk
struct CHUNK_HDR{
    char subchunk2ID[4];            // 'data' or 'fact'
    int32_t dwSubchunk2Size;
};


WavFileWriter::WavFileWriter(): _file(NULL), _sampleCount(0) {
}

WavFileWriter::~WavFileWriter() {
	close();
}

bool WavFileWriter::open(const char* filename, short sampleRate, short channels) {
	close();

    _file = fopen(filename, "wb");
	if (NULL == _file) {
		return false;
	}

	writeHeader(sampleRate, channels);
	_sampleCount = 0;
	return true;
}

int WavFileWriter::write(const short *data, size_t count) {
    if (!isOpened() || NULL == data) {
        return -1;
    }

    int writen = fwrite(data, sizeof(short), count, _file);
	if (writen > 0) _sampleCount += writen;
    return writen;
}

void WavFileWriter::close() {
    if (isOpened()) {
        writeHeaderLen(_sampleCount * sizeof(short));
        fclose(_file);
        _file = NULL;
    }
}

void WavFileWriter::writeHeader(short sampleRate, short channels) {
    WAV_HDR hdr;
    memcpy(hdr.chunkID, "RIFF", 4);
    hdr.dwChunkSize = sizeof(WAV_HDR) + sizeof(CHUNK_HDR);
    memcpy(hdr.format, "WAVE", 4);
    memcpy(hdr.subchunk1ID, "fmt ", 4);
    hdr.dwSubchunk1Size = 16;
    hdr.wAudioFormat = 1;
    hdr.wChannels = channels;
    hdr.dwSampleRate = sampleRate;
    hdr.wBitsPerSample = 16;
    hdr.dwByteRate = channels*sampleRate*(hdr.wBitsPerSample>>3);
    hdr.wBlockAlign = channels*(hdr.wBitsPerSample>>3);
    fwrite(&hdr, 1, sizeof(hdr), _file);

    CHUNK_HDR chdr;
    memcpy(chdr.subchunk2ID, "data", 4);
    chdr.dwSubchunk2Size = 0;
    fwrite(&chdr, sizeof(chdr), 1, _file);
	return;
}

void WavFileWriter::writeHeaderLen(size_t len) {
    if (!isOpened()) {
        return;
    }

	// size_t is 8byte on 64bit arch, so convert type to int
	int dataLen = (int)len;
    int total = dataLen + sizeof(WAV_HDR);
    fseek(_file, 4, SEEK_SET);
    fwrite(&total, 1, 4, _file);

    fseek(_file, 40, SEEK_SET);
    fwrite(&dataLen, 1, 4, _file);
}

bool is_wav_header(const WAV_HDR& header) {
    return ((0 == memcmp(header.chunkID, "RIFF", 4))
        && (0 == memcmp(header.format, "WAVE", 4))
        && (0 == memcmp(header.subchunk1ID, "fmt ", 4)));
}

bool is_chunk_header(const CHUNK_HDR& header) {
    return ((0 == memcmp(header.subchunk2ID, "data", 4)) || (0 == memcmp(header.subchunk2ID, "fact", 4)));
}

WavFileReader::WavFileReader(): _file(NULL), _sampleRate(0), _channels(0),_realCount(-1) {
}

WavFileReader::~WavFileReader() {
	close();
}

bool WavFileReader::open(const char* filename) {
    close();

    FILE* file = fopen(filename, "rb");
    if (NULL == file) {
        return false;
    }

    WAV_HDR hdr;
    CHUNK_HDR chdr;
    size_t count = fread(&hdr, sizeof(hdr), 1, file);
    if (count < 1 || !is_wav_header(hdr)) {
        close();
        return false;
    }
    _sampleRate = hdr.dwSampleRate;
    _channels = hdr.wChannels;

    count = fread(&chdr, sizeof(chdr), 1, file);
    if (count < 1 || !is_chunk_header(chdr)) {
        close();
        return false;
    }
    // sampleCount = chdr.dwSubchunk2Size/(hdr.wBitsPerSample >> 3);
    _file = file;
    return true;
}

int WavFileReader::read(short *buffer, size_t count) {
    if (!isOpened()) {
        return -1;
    }

    return fread(buffer, sizeof(short), count, _file);
}

int WavFileReader::sampleCount() {
    if (-1 == _realCount) {
        if (!isOpened()) {
            return -1;
        }

        size_t lastPos = ftell(_file);
        fseek(_file, 0, SEEK_END);
        size_t pos = ftell(_file);
        fseek(_file, lastPos, SEEK_SET);
        _realCount = (pos - lastPos)/sizeof(short);
    }

    return _realCount;
}

void WavFileReader::close() {
    if (isOpened()) {
        fclose(_file);
        _file = NULL;
    }
}
