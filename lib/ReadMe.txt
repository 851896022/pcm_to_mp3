# �޸��˱��뺯����������������
# �޸��ڱ�����ж�̬�����ڴ棬����Ҫ�û��ṩ����������Ĵ�С�������û������ͷŻ������Ĳ�����

ʹ��ǰ׼��
1,��lame.h, lameHelper.cpp, lameHelper.h, libmp3lame.lib, libmpg123.lib, mp3Topcm.cpp
  mp3TOpcm.h, mpg123.h �⼸���ļ���ӵ������У����ڹ����а���ͷ�ļ� lameHelper.h��mp3TOpcm.h (���õ��뾲̬��)
2���� mpg123lame.dll libmpg123.dll�Լ����õ����̵�����ļ��У�exe�ļ����ɵ��ļ��У���һ��Ϊ����Ŀ¼�µ�debug��release�ļ����ڡ�

ʹ�÷���
ע�⣺
	�ñ��뷽��ֻ֧��16λ���͵�pcm����
���룺
	����һ��lameHelper���͵ı���������encode�������ɡ�encode�����Ĳ���˵����鿴lameHelper��h�ļ��е���˵����
�磺
	// pcm_buffer Ҫ�����pcm����
	// pcm_buffer_size Ҫ�����pcm���ݴ�С
	// mp3_buffer һ��ָ�������ָ�룬�������������mp3���ݡ�
	// settings   �����������ã���ϸ�뿴ͷ�ļ�
	// done				����ʵ�ʱ���ɹ���mp3�����С
	lameHelper my��
	char *mp3_buffer = NULL;			// ��ע��һ��Ҫ���г�ʼ����
	my.int encode(short int *pcm_buffer, size_t pcm_buffer_size, unsigned char (&mp3_buffer), 
					settings_t settings, size_t *done);
	delete [] mp3_buffer; 	// mp3���ݵ�������encode�����ж�̬����ģ�����ڱ�����պ�һ��Ҫ�ͷţ������������ڴ�й¶��
	
	����������encode���������õı��뻺�廹�����һЩ���ݣ�һ��������ݱȽ��ٿ��Ժ��ԣ����һ��Ҫ������һ�ε���encode������
			���ǽ����뻺���С��pcm_buffer_size����Ϊ0����ʱ��mp3_buffer���صĽ��ǲ��������ݣ�done���ص��ǲ��������ݵĴ�С��

���룺
	����һ��CMP3ToPCM���͵ı���������feedANDdecode�������ɣ�feedANDdecode�Ĳ���˵����
	�鿴mp3TOpcm.h�ļ��е�˵��
	
�磺
	CMP3ToPCM my;
	char *output = NULL;				// ��ע��һ��Ҫ���г�ʼ����

	// input  �����mp3��������
	// length �����mp3��������Ĵ�С
	// ouput	������pcm��������
	// done 	������pcm��������Ĵ�С
	my.feedANDdecode(input,length,&ouput,&done);
	.......
	delete [] output; // ���ֶ��ͷ��ڴ档
	
	
	ע�⣺ʹ��ʱ�������ַ�������Ϊ���ֽ��ַ�������������еĴ�����ʾ��صĴ�����ܻ���ִ���



	----------------------------------------------------------- LHC

	1. 2018-05-08 ServerDlg.cpp���� 'LHC' ע�͵�.