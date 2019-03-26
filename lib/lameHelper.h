/**********************************************************************************************
	* Filename:	lameHelper.h

	Use lame to encode 16bit pcm stream
***********************************************************************************************/
#include <windows.h>
#include "lame.h"
#include <wchar.h>
#include <QApplication>
// 编码模式
enum encode_mode_e
{
	EM_ABR,					// 平均比特率
	EM_CBR,					// 固定比特率
	EM_VBR					// 可变比特率
};

// 声道数
enum encode_channel_e
{
	EC_MONO,				// 单声道
	EC_STEREO				// 立体声
};

// 比特率，单位为kbps
enum bitrate_e
{
	BR_8kbps = 8,
	BR_16kbps = 16,
	BR_24kbps = 24,
	BR_32kbps = 32,
	BR_40kbps = 40,
	BR_48kbps = 48,
	BR_56kbps = 56,
	BR_64kbps = 64,
	BR_80kbps = 80,
	BR_96kbps = 96,
	BR_112kbps = 112,
	BR_128kbps = 128,
	BR_144kbps = 144,
	BR_160kbps = 160,
	BR_192kbps = 192,
	BR_224kbps = 224,
	BR_256kbps = 256,
	BR_320kbps = 320
};

// 采样率，单位为Hz
enum samplerate_e
{
	SR_8khz = 8000,
	SR_11khz = 11025,
	SR_12khz = 12000,
	SR_16khz = 16000,
	SR_22khz = 22050,
	SR_24khz = 24000,
	SR_32khz = 32000,
	SR_44khz = 44100,
	SR_48khz = 48000
};

struct settings_t
{
	encode_channel_e channels;		// 输入的pcm流为单声道还是立体声
	bitrate_e abr_bitrate;			// 设置可变比特率
	bitrate_e cbr_bitrate;			// 设置固定比特率

	/*
	内部算法选择.  音频压缩质量由码率决定，而这个参数则决定选择的算法好坏。
	quality=0--9.  0=best (very slow).  9=worst.
	recommended:	2     near-best quality, not too slow
					5     good quality, fast
					7     ok quality, really fast
	*/
	int quality;

	encode_mode_e enc_mode;			// EM_ABR 平均比特率，如果设置为这一模式，则 abr_bitrate 设置的比特率有效
									// EM_CBR,固定比特率，如果设置为这一模式，则 cbr_bitrate 设置的比特率有效
									// EM_VBR,可变比特率，如果设置为这一模式，则 abr_bitrate 设置的比特率有效

	
	samplerate_e resample_frequency;// 重采样的采样率（即输出mp3的采样率）
	samplerate_e in_samplerate;		// 输入pcm流的采样率

	//构造函数，用于设置默认的参数
	settings_t();
};

class lameHelper
{
private:
	lame_global_flags*	gfp;

    void errorHandler(QString);
	char *errMsg;
public:
	// 使用默认的设置进行mp3的编码
	lameHelper();
	// 使用自定义的设置进行mp3的编码
	lameHelper(settings_t settings);

	~lameHelper();

	// 输入pcm数组，输出为mp3数组
	// 输入的pcm数组编码方式为 16位整型
	// 输出的mp3流都是无格式的
	// 即，mp3值为一帧一帧的流,不包含ID3V2和ID3V1标签头

	// 返回值,小于0则有错误，等于0则正确执行
	// pcm_buffer: pcm数组
	// pcm_buffer_size: pcm数组大小
	// mp3_buffer: mp3数组
	// mp3_buffer_size: mp3数组大小
	// settings: 编码关于pcm流以及mp3流的各种设置，设置参数见 settings_t 结构体
	// done：保存实际编码的mp3数组的大小

	// 当结束pcm流的输入以后，将mp3_buffer_size 设置为0，再调用encode一次，用于返回还在缓冲区内的mp3数组，
	// 来确保解码的完整性，此时的done参数依旧返回的编码完成的mp3的数组大小。
	int encode(short int *pcm_buffer, size_t pcm_buffer_size, unsigned char *mp3_buffer, size_t mp3_buffer_size, size_t *done);
};
