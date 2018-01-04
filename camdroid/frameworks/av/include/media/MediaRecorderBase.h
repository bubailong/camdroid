/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MEDIA_RECORDER_BASE_H_

#define MEDIA_RECORDER_BASE_H_

#include <media/mediarecorder.h>

#include <system/audio.h>

namespace android {

class ICameraRecordingProxy;
class Surface;
class ISurfaceTexture;

struct MediaRecorderBase {
    MediaRecorderBase() {}
    virtual ~MediaRecorderBase() {}

    virtual status_t init() = 0;
    virtual status_t setAudioSource(audio_source_t as) = 0;
    virtual status_t setVideoSource(video_source vs) = 0;
    virtual status_t setOutputFormat(output_format of) = 0;
    virtual status_t setAudioEncoder(audio_encoder ae) = 0;
    virtual status_t setVideoEncoder(video_encoder ve) = 0;
    virtual status_t setVideoSize(int width, int height) = 0;
    virtual status_t setVideoFrameRate(int frames_per_second) = 0;
    virtual status_t setMuteMode(bool mute) = 0;
    virtual status_t setCamera(const sp<ICamera>& camera,
                               const sp<ICameraRecordingProxy>& proxy) = 0;
    virtual status_t setPreviewSurface(const unsigned int hlay) = 0;
    virtual status_t setOutputFile(const char *path) = 0;
    virtual status_t setOutputFile(const char *path, int64_t offset, int64_t length) = 0;
    virtual status_t setOutputFile(int fd, int64_t offset, int64_t length) = 0;
    virtual status_t setOutputFileAuxiliary(int fd) {return INVALID_OPERATION;}
    virtual status_t setParameters(const String8& params) = 0;
    virtual status_t setListener(const sp<IMediaRecorderClient>& listener) = 0;
    virtual status_t prepare() = 0;
    virtual status_t start() = 0;
    virtual status_t stop() = 0;
    virtual status_t close() = 0;
    virtual status_t reset() = 0;
    virtual status_t getMaxAmplitude(int *max) = 0;
    virtual status_t dump(int fd, const Vector<String16>& args) const = 0;
    virtual unsigned int querySurfaceMediaSource() const = 0;
    virtual status_t queueBuffer(int index, int addr_y, int addr_c, int64_t timestamp) = 0;
    virtual	sp<IMemory> getOneBsFrame(int mode) = 0;
	virtual	void freeOneBsFrame() = 0;
	virtual	sp<IMemory> getEncDataHeader() = 0;
	virtual status_t setVideoEncodingBitRateSync(int bitRate) = 0;
	virtual status_t setVideoFrameRateSync(int frames_per_second) = 0;
    virtual status_t setVideoEncodingIFramesNumberIntervalSync(int nMaxKeyItl) = 0;
    virtual status_t reencodeIFrame() = 0;
    virtual status_t setOutputFileSync(int fd, int64_t fallocateLength, int muxerId) = 0;
    virtual status_t setOutputFileSync(const char* path, int64_t fallocateLength, int muxerId) = 0;
    virtual status_t setSdcardState(bool bExist) = 0;

    virtual int addOutputFormatAndOutputSink(int of, int fd, int FallocateLen, bool callback_out_flag) = 0;
    virtual int addOutputFormatAndOutputSink(int of, const char* path, int FallocateLen, bool callback_out_flag) = 0;
    virtual status_t removeOutputFormatAndOutputSink(int muxerId) = 0;
	virtual status_t setMaxDuration(int max_duration_ms) = 0;
	virtual status_t setMaxFileSize(int64_t max_filesize_bytes) = 0;
	virtual status_t setImpactOutputFile(int fd, int64_t fallocateLength, int muxerId) = 0;
    virtual status_t setImpactOutputFile(const char* path, int64_t fallocateLength, int muxerId) = 0;

private:
    MediaRecorderBase(const MediaRecorderBase &);
    MediaRecorderBase &operator=(const MediaRecorderBase &);
};

}  // namespace android

#endif  // MEDIA_RECORDER_BASE_H_