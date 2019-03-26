#include "mpg123.h"

class CMP3ToPCM
{
private:
	// 
	long samplerate; // 解码输出的pcm数据的采样率
	int channels,	 // 解码输出的pcm数据的声道数
		enc;		 // 解码输出的pcm数据的编码格式，具体参见mpg123.h中的 mpg123_enc_enum 枚举变量

	// 初始化libmp3库
	void initialMP3ToPCM();

	// 解除对libmp3库的占用
	void cleanup(mpg123_handle *mh);
	

public:
	mpg123_handle *m_mh;

	CMP3ToPCM();
	~CMP3ToPCM();

	// 使用时请给 outmemory 数组分配大一点的内存，一般为 inmemory 大小的15倍即可,
	// 因为mp3压缩算法的压缩率最大不超过15
	// inmemory:	mp3数组指针
	// inmemsize:	MP3数组大小
	// outmemory:	pcm数组指针
	// outmemsize:	pcm数组大小
	// done：		实际解码得到的pcm数组大小
	int feedANDdecode(const unsigned char *inmemory, size_t inmemsize, unsigned char *outmemory, size_t outmemsize, size_t *done);
};