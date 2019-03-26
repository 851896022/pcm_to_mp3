/**********************************************************************************************
	* Filename:	lameHelper.h

	Use lame to encode 16bit pcm stream
***********************************************************************************************/
#include <windows.h>
#include "lame.h"
#include <wchar.h>
#include <QApplication>
// ����ģʽ
enum encode_mode_e
{
	EM_ABR,					// ƽ��������
	EM_CBR,					// �̶�������
	EM_VBR					// �ɱ������
};

// ������
enum encode_channel_e
{
	EC_MONO,				// ������
	EC_STEREO				// ������
};

// �����ʣ���λΪkbps
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

// �����ʣ���λΪHz
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
	encode_channel_e channels;		// �����pcm��Ϊ����������������
	bitrate_e abr_bitrate;			// ���ÿɱ������
	bitrate_e cbr_bitrate;			// ���ù̶�������

	/*
	�ڲ��㷨ѡ��.  ��Ƶѹ�����������ʾ�������������������ѡ����㷨�û���
	quality=0--9.  0=best (very slow).  9=worst.
	recommended:	2     near-best quality, not too slow
					5     good quality, fast
					7     ok quality, really fast
	*/
	int quality;

	encode_mode_e enc_mode;			// EM_ABR ƽ�������ʣ��������Ϊ��һģʽ���� abr_bitrate ���õı�������Ч
									// EM_CBR,�̶������ʣ��������Ϊ��һģʽ���� cbr_bitrate ���õı�������Ч
									// EM_VBR,�ɱ�����ʣ��������Ϊ��һģʽ���� abr_bitrate ���õı�������Ч

	
	samplerate_e resample_frequency;// �ز����Ĳ����ʣ������mp3�Ĳ����ʣ�
	samplerate_e in_samplerate;		// ����pcm���Ĳ�����

	//���캯������������Ĭ�ϵĲ���
	settings_t();
};

class lameHelper
{
private:
	lame_global_flags*	gfp;

    void errorHandler(QString);
	char *errMsg;
public:
	// ʹ��Ĭ�ϵ����ý���mp3�ı���
	lameHelper();
	// ʹ���Զ�������ý���mp3�ı���
	lameHelper(settings_t settings);

	~lameHelper();

	// ����pcm���飬���Ϊmp3����
	// �����pcm������뷽ʽΪ 16λ����
	// �����mp3�������޸�ʽ��
	// ����mp3ֵΪһ֡һ֡����,������ID3V2��ID3V1��ǩͷ

	// ����ֵ,С��0���д��󣬵���0����ȷִ��
	// pcm_buffer: pcm����
	// pcm_buffer_size: pcm�����С
	// mp3_buffer: mp3����
	// mp3_buffer_size: mp3�����С
	// settings: �������pcm���Լ�mp3���ĸ������ã����ò����� settings_t �ṹ��
	// done������ʵ�ʱ����mp3����Ĵ�С

	// ������pcm���������Ժ󣬽�mp3_buffer_size ����Ϊ0���ٵ���encodeһ�Σ����ڷ��ػ��ڻ������ڵ�mp3���飬
	// ��ȷ������������ԣ���ʱ��done�������ɷ��صı�����ɵ�mp3�������С��
	int encode(short int *pcm_buffer, size_t pcm_buffer_size, unsigned char *mp3_buffer, size_t mp3_buffer_size, size_t *done);
};
