

#include "mp3TOpcm.h"
#include <stdio.h>

//#pragma comment(lib,"libmpg123.lib")

CMP3ToPCM::CMP3ToPCM()
{
	initialMP3ToPCM();
}

CMP3ToPCM::~CMP3ToPCM()
{
	cleanup(m_mh);
}


void CMP3ToPCM::cleanup(mpg123_handle *mh)
{	
	mpg123_close(mh);
	mpg123_delete(mh);
	mpg123_exit();
}

void CMP3ToPCM::initialMP3ToPCM()
{
	int err = mpg123_init();
	if(err != MPG123_OK || (m_mh = mpg123_new(NULL, &err)) == NULL)
	{
		printf("Basic setup error: %s",mpg123_plain_strerror(err));
		cleanup(m_mh);
	}

	// 设置一些具体的解码过程中libmpg123库的一些选项，一般使用默认的即可,详细的资料可以查看mpg123.h中的mpg123_param的说明
// 	err = mpg123_param(m_mh, MPG123_VERBOSE, 4, 0);
// 	if(err != MPG123_OK || (m_mh = mpg123_new(NULL, &err)) == NULL)
// 	{
// 		printf("Unable to set library options: %s\n", mpg123_plain_strerror(err));
// 		cleanup(m_mh);
// 	}
// 
// 	err = mpg123_param(m_mh, MPG123_FLAGS, MPG123_FUZZY | MPG123_SEEKBUFFER | MPG123_GAPLESS, 0);
// 	if(err != MPG123_OK)
// 	{
// 		printf("Unable to set library options: %s\n", mpg123_plain_strerror(err));
// 		cleanup(m_mh);
// 	}
// 
// 	// Let the seek index auto-grow and contain an entry for every frame
// 	err = mpg123_param(m_mh, MPG123_INDEX_SIZE, -1, 0);
// 	if(err != MPG123_OK)
// 	{
// 		printf("Unable to set index size: %s\n", mpg123_plain_strerror(err));
// 		cleanup(m_mh);
// 	}

	// Use float output formats only
	err = mpg123_format_none(m_mh);
	if(err != MPG123_OK)
	{
		printf("Unable to disable all output formats: %s\n", mpg123_plain_strerror(err));
		cleanup(m_mh);
	}

	size_t nrates;
	const long *rates;
	mpg123_rates(&rates, &nrates);
    for(int i=0; i<(int)nrates; i++)
	{
		err = mpg123_format(m_mh, rates[i], MPG123_MONO | MPG123_STEREO,  MPG123_ENC_SIGNED_16);
		if(err != MPG123_OK)
		{
			fprintf(stderr,"Unable to set float output formats: %s\n", mpg123_plain_strerror(err));
			cleanup(m_mh);
		}
	}

	err = mpg123_open_feed(m_mh);
	if(err != MPG123_OK)
	{
		printf("Unable open feed: %s\n", mpg123_plain_strerror(err));
		cleanup(m_mh);
	}
}

int CMP3ToPCM::feedANDdecode(const unsigned char *inmemory, size_t inmemsize, unsigned char *outmemory, size_t outmemsize, size_t *done)
{
	/* Feed input chunk and get first chunk of decoded audio. */

	size_t defaultSize = mpg123_outblock(m_mh);
	outmemsize = outmemsize > defaultSize ? outmemsize : defaultSize;
	int ret = mpg123_decode(m_mh,inmemory,inmemsize,outmemory,outmemsize,done);
    //printf("mpg123_decode return %d\n",ret);
	if(ret == MPG123_NEW_FORMAT)
	{
		mpg123_getformat(m_mh, &samplerate, &channels, &enc);
		fprintf(stderr, "New format: %li Hz, %i channels, encoding value %i\n", samplerate, channels, enc);
	}

	while(ret != MPG123_ERR && ret != MPG123_NEED_MORE)
	{ /* Get all decoded audio that is available now before feeding more input. */
		ret = mpg123_decode(m_mh,NULL,0,outmemory,outmemsize,done);
		if(ret == MPG123_ERR)
			printf("some error: %s", mpg123_strerror(m_mh)); 
	}
	if(ret == MPG123_ERR)
		printf("some error: %s", mpg123_strerror(m_mh)); 

	return 1;
}
