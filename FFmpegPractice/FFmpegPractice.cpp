#include <iostream>

extern "C" {
#include <stdio.h>
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavutil/log.h"
#include "libavutil/timestamp.h"
}


void my_logoutput(void* ptr, int level, const char* fmt, va_list vl) {
    printf("Hello Log Output! Content = %s", fmt);
}

// FFmpeg ɾ���ļ�����
void ffmpegDelFile() {
    int ret;
    ret = avpriv_io_delete("1.txt");  // ����ĿĿ¼�´������ļ�������ʱ��Ҫ�����ã�
    printf("Del File Code : %d \n", ret);
    if (ret < 0) {
        av_log(NULL, AV_LOG_ERROR, "Failed to delete file \n");
    }
    else {
        av_log(NULL, AV_LOG_INFO, "Delete File Success��\n ");
    }
}

// FFmpeg ���������ƶ��ļ�
void ffmpegMoveFile(char* src, char* dst) {
    int ret;
    ret = avpriv_io_move(src, dst);
    printf("Move File Code : %d \n", ret);
    // ������ʱ������ļ������ڣ�retҲ��0
    if (ret < 0) {
        av_log(NULL, AV_LOG_ERROR, "Failed to Move File %s!\n ", src);
    }
    else {
        av_log(NULL, AV_LOG_INFO, "Success Move File %s!\n", src);
    }
}

// FFmpeg Ŀ¼����
void ffmpegDir() {

    int ret;

    // ������
    AVIODirContext* dirCtx = NULL;
    AVIODirEntry* dirEntry = NULL;

    // ע��Windows�»᷵��-40��Ҳ����Function not implement������δʵ�֣�Ҳ����˵windows�²�֧�ִ˷���
    ret = avio_open_dir(&dirCtx, "include", NULL);

    if (ret < 0) {
        // ���������־
        printf("cant open dir��msg = %s", av_err2str(ret));
        return;
    }

    av_log(NULL, AV_LOG_INFO, "Open Dir Success!");

    while (1) {
        ret = avio_read_dir(dirCtx, &dirEntry);
        if (ret < 0) {
            printf("cant read dir : %s", av_err2str(ret));
            // ��ֹ�ڴ�й©
            goto __failed;
        }
        av_log(NULL, AV_LOG_INFO, "read dir success");
        if (!dirEntry) {
            break;
        }
        printf("Entry Name = %s", dirEntry->name);
        // �ͷ���Դ
        avio_free_directory_entry(&dirEntry);
    }
    // �ͷ���Դ
__failed:
    avio_close_dir(&dirCtx);
}


int main(int argc, char* argv[]) {

    /** 0.FFmpeg Hello World **/
    //av_register_all();
    //printf("%s\n", avcodec_configuration());

    /** 1.FFmpeg Log System **/
    //av_log_set_level(AV_LOG_INFO);

    /** 2.�����Զ������־������� **/
    av_log_set_callback(my_logoutput);  
    av_log(NULL, AV_LOG_INFO, "Hello World\n");

    /** 3.ʹ��FFmpegɾ���ļ� **/
    //ffmpegDelFile();  // ɾ���ļ�

    /** 4.ʹ��FFmpeg�������ļ� **/
    //char src[] = "111.txt";
    //char dst[] = "222.txt";
    //ffmpegMoveFile(src, dst);  //  �������ļ�

    /** 5.ʹ��FFmpeg�����ļ�Ŀ¼��ע:�˲���������Windows���治֧�֣� **/
    //ffmpegDir();  // �ļ�Ŀ¼����

    
    return 0;
}