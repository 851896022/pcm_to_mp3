/**********************************************************************************************
	* Filename:	lameHelper.cpp

	Use lame to encode pcm stream
***********************************************************************************************/


#include "lame.h"
#include "lameHelper.h"
#include <QMessageBox>
//#pragma comment(lib,"libmp3lame.lib")

settings_t::settings_t()
{
	//Setting the default values

    channels = EC_MONO;
	abr_bitrate = BR_128kbps;			
	cbr_bitrate = BR_128kbps;
	quality = 5;
	enc_mode = EM_CBR;
    resample_frequency = SR_48khz;
    in_samplerate = SR_48khz;
}

lameHelper::lameHelper()
{
	settings_t settings;
	gfp = NULL;
    gfp = lame_init();
    //设置采样率
	lame_set_in_samplerate(gfp, settings.in_samplerate);

	//Setting Channels
	switch(settings.channels)
	{
	case EC_MONO:
		lame_set_mode(gfp, MONO);
		lame_set_num_channels(gfp, 1);
		break;
	case EC_STEREO:
		lame_set_mode(gfp, JOINT_STEREO);
		lame_set_num_channels(gfp, 2);
		break;
	}

	//VbrTag
	//lame_set_bWriteVbrTag(gfp, 1);	
	switch(settings.enc_mode)
	{
	case EM_ABR:
		{
			int i = settings.abr_bitrate;
			if(i >= 8000)
			{
				i = (i + 500) / 1000;
			}
			if(i > 320)
			{
				i = 320;
			}
			if(i < 8)
			{
				i = 8;
			}
			lame_set_VBR(gfp, vbr_abr);
			lame_set_VBR_mean_bitrate_kbps(gfp, i);
		}
		break;
	case EM_CBR:
		lame_set_VBR(gfp, vbr_off);
		lame_set_quality(gfp, settings.quality);
		lame_set_brate(gfp, settings.cbr_bitrate);
		break;
	case EM_VBR:
		lame_set_VBR(gfp, vbr_mtrh);
		lame_set_VBR_q(gfp, settings.quality);
		break;
	}

	lame_set_out_samplerate(gfp, settings.resample_frequency);
}

lameHelper::lameHelper(settings_t settings)
{
	gfp = NULL;
	gfp = lame_init();
	lame_set_in_samplerate(gfp, settings.in_samplerate);

	//Setting Channels
	switch(settings.channels)
	{
	case EC_MONO:
		lame_set_mode(gfp, MONO);
		lame_set_num_channels(gfp, 1);
		break;
	case EC_STEREO:
		lame_set_mode(gfp, JOINT_STEREO);
		lame_set_num_channels(gfp, 2);
		break;
	}

	//VbrTag
	//lame_set_bWriteVbrTag(gfp, 1);	
	switch(settings.enc_mode)
	{
	case EM_ABR:
		{
			int i = settings.abr_bitrate;
			if(i >= 8000)
			{
				i = (i + 500) / 1000;
			}
			if(i > 320)
			{
				i = 320;
			}
			if(i < 8)
			{
				i = 8;
			}
			lame_set_VBR(gfp, vbr_abr);
			lame_set_VBR_mean_bitrate_kbps(gfp, i);
		}
		break;
	case EM_CBR:
        lame_set_VBR(gfp, vbr_off);
        lame_set_quality(gfp, settings.quality);
        lame_set_brate(gfp, settings.cbr_bitrate);
		break;
	case EM_VBR:
		lame_set_VBR(gfp, vbr_mtrh);
		lame_set_VBR_q(gfp, settings.quality);
		break;
	}

	lame_set_out_samplerate(gfp, settings.resample_frequency);

    if(lame_init_params(gfp) < 0)
    {
        //lame initialization failed
        QString errMsg = "FATAL ERROR: parameters failed to initialize properly in lame. Aborting!\n";
        errorHandler(errMsg);
    }
}

lameHelper::~lameHelper()
{
	lame_close(gfp);
}

int lameHelper::encode(short int *pcm_buffer, size_t pcm_buffer_size, unsigned char *mp3_buffer, size_t mp3_buffer_size, size_t *done)
{
	int lResult = 0;


	{
		int read = pcm_buffer_size;

		if(pcm_buffer_size == 0)
		{	
			*done = lame_encode_flush(gfp, mp3_buffer, mp3_buffer_size);
		}
		else
		{
            *done = lame_encode_buffer(gfp, pcm_buffer, NULL,pcm_buffer_size, mp3_buffer, mp3_buffer_size);
		}
	}
	return lResult;
}

void lameHelper::errorHandler(QString str)
{
    QString wcCaption = "Error Tips";
    QMessageBox::critical(NULL,wcCaption,str);
}
