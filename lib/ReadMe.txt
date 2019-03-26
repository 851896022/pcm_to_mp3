# 修改了编码函数中声道处理问题
# 修改在编解码中动态分配内存，不需要用户提供输出缓冲区的大小，但是用户得做释放缓冲区的操作。

使用前准备
1,将lame.h, lameHelper.cpp, lameHelper.h, libmp3lame.lib, libmpg123.lib, mp3Topcm.cpp
  mp3TOpcm.h, mpg123.h 这几个文件添加到工程中，并在工程中包含头文件 lameHelper.h，mp3TOpcm.h (不用导入静态库)
2，将 mpg123lame.dll libmpg123.dll以及放置到工程的输出文件夹（exe文件生成的文件夹），一般为工程目录下的debug和release文件夹内。

使用方法
注意：
	该编码方法只支持16位整型的pcm数据
编码：
	声明一个lameHelper类型的变量，调用encode方法即可。encode方法的参数说明请查看lameHelper。h文件中的是说明。
如：
	// pcm_buffer 要编码的pcm数据
	// pcm_buffer_size 要编码的pcm数据大小
	// mp3_buffer 一个指向数组的指针，用来接收输出的mp3数据。
	// settings   编码器的设置，详细请看头文件
	// done				接收实际编码成功的mp3数组大小
	lameHelper my；
	char *mp3_buffer = NULL;			// 请注意一定要进行初始化。
	my.int encode(short int *pcm_buffer, size_t pcm_buffer_size, unsigned char (&mp3_buffer), 
					settings_t settings, size_t *done);
	delete [] mp3_buffer; 	// mp3数据的数组是encode函数中动态分配的，因此在编码接收后一定要释放，否则可能造成内存泄露。
	
	附：调用完encode函数后，内置的编码缓冲还会残留一些数据，一般残留数据比较少可以忽略，如果一定要，请再一次调用encode函数，
			但是将输入缓冲大小即pcm_buffer_size设置为0，此时，mp3_buffer返回的将是残留的数据，done返回的是残留的数据的大小。

解码：
	声明一个CMP3ToPCM类型的变量，调用feedANDdecode方法即可；feedANDdecode的参数说明请
	查看mp3TOpcm.h文件中的说明
	
如：
	CMP3ToPCM my;
	char *output = NULL;				// 请注意一定要进行初始化。

	// input  输入的mp3数据数组
	// length 输入的mp3数据数组的大小
	// ouput	解码后的pcm数据数组
	// done 	解码后的pcm数据数组的大小
	my.feedANDdecode(input,length,&ouput,&done);
	.......
	delete [] output; // 请手动释放内存。
	
	
	注意：使用时将工程字符集设置为多字节字符集，否则程序中的错误提示相关的代码可能会出现错误。



	----------------------------------------------------------- LHC

	1. 2018-05-08 ServerDlg.cpp中有 'LHC' 注释的.