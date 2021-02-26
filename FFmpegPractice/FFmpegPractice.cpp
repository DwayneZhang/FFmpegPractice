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
    av_log_set_callback(my_logoutput);  // 设置自定义的日志输出方法
    av_log(NULL, AV_LOG_INFO, "Hello World\n");
    return 0;
}

// FFmpeg 删除文件操作
void ffmpegDelFile() {
    int ret;
    ret = avpriv_io_delete("1.txt");  // 在项目目录下创建的文件（测试时需要创建好）
    printf("Del File Code : %d \n", ret);
    if (ret < 0) {
        av_log(NULL, AV_LOG_ERROR, "Failed to delete file \n");
    }
    else {
        av_log(NULL, AV_LOG_INFO, "Delete File Success！\n ");
    }
}

// FFmpeg 重命名或移动文件
void ffmpegMoveFile(char* src, char* dst) {
    int ret;
    ret = avpriv_io_move(src, dst);
    printf("Move File Code : %d \n", ret);
    // 重命名时，如果文件不存在，ret也会0
    if (ret < 0) {
        av_log(NULL, AV_LOG_ERROR, "Failed to Move File %s!\n ", src);
    }
    else {
        av_log(NULL, AV_LOG_INFO, "Success Move File %s!\n", src);
    }
}

// FFmpeg 目录操作
void ffmpegDir() {

    int ret;

    // 上下文
    AVIODirContext* dirCtx = NULL;
    AVIODirEntry* dirEntry = NULL;

    // 注意Windows下会返回-40，也就是Function not implement，方法未实现，也就是说windows下不支持此方法
    ret = avio_open_dir(&dirCtx, "include", NULL);

    if (ret < 0) {
        // 输出错误日志
        printf("cant open dir，msg = %s", av_err2str(ret));
        return;
    }

    av_log(NULL, AV_LOG_INFO, "Open Dir Success!");

    while (1) {
        ret = avio_read_dir(dirCtx, &dirEntry);
        if (ret < 0) {
            printf("cant read dir : %s", av_err2str(ret));
            // 防止内存泄漏
            goto __failed;
        }
        av_log(NULL, AV_LOG_INFO, "read dir success");
        if (!dirEntry) {
            break;
        }
        printf("Entry Name = %s", dirEntry->name);
        // 释放资源
        avio_free_directory_entry(&dirEntry);
    }
    // 释放资源
__failed:
    avio_close_dir(&dirCtx);
}