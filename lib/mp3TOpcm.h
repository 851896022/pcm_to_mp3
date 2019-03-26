#include "mpg123.h"

class CMP3ToPCM
{
private:
	// 
	long samplerate; // ���������pcm���ݵĲ�����
	int channels,	 // ���������pcm���ݵ�������
		enc;		 // ���������pcm���ݵı����ʽ������μ�mpg123.h�е� mpg123_enc_enum ö�ٱ���

	// ��ʼ��libmp3��
	void initialMP3ToPCM();

	// �����libmp3���ռ��
	void cleanup(mpg123_handle *mh);
	

public:
	mpg123_handle *m_mh;

	CMP3ToPCM();
	~CMP3ToPCM();

	// ʹ��ʱ��� outmemory ��������һ����ڴ棬һ��Ϊ inmemory ��С��15������,
	// ��Ϊmp3ѹ���㷨��ѹ������󲻳���15
	// inmemory:	mp3����ָ��
	// inmemsize:	MP3�����С
	// outmemory:	pcm����ָ��
	// outmemsize:	pcm�����С
	// done��		ʵ�ʽ���õ���pcm�����С
	int feedANDdecode(const unsigned char *inmemory, size_t inmemsize, unsigned char *outmemory, size_t outmemsize, size_t *done);
};