#include <iostream>

extern "C" {
#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavutil/log.h"
}

void my_logoutput(void* ptr, int level, const char* fmt, va_list vl) {
    printf("Hello Log Output! Content = %s", fmt);
}

int main(int argc, char* argv[]) {
    //printf("%s\n", avcodec_configuration());
    av_log_set_callback(my_logoutput);  // �����Զ������־�������
    av_log(NULL, AV_LOG_INFO, "Hello World\n");
    return 0;
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