#include <execinfo.h>
#include <unistd.h>
#include <time.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void server_backtrace(void)
{
    // //打开文件
    time_t tSetTime;
    time(&tSetTime);
    struct tm* ptm = localtime(&tSetTime);
    // char fname[256] = {0};
    // sprintf(fname, "core.%d-%d-%d_%d_%d_%d",
    //         ptm->tm_year+1900, ptm->tm_mon+1, ptm->tm_mday,
    //         ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
    // FILE* f = fopen(fname, "a");
    // if (f == NULL){
    //     return;
    // }
    // int fd = fileno(f);
    //
    // //锁定文件
    // struct flock fl;
    // fl.l_type = F_WRLCK;
    // fl.l_start = 0;
    // fl.l_whence = SEEK_SET;
    // fl.l_len = 0;
    // fl.l_pid = getpid();
    // fcntl(fd, F_SETLKW, &fl);

    //输出程序的绝对路径
    char buffer[4096];
    memset(buffer, 0, sizeof(buffer));
    int count = readlink("/proc/self/exe", buffer, sizeof(buffer));
    if(count > 0){
        buffer[count] = '\n';
        buffer[count + 1] = 0;
        //fwrite(buffer, 1, count+1, f);
        printf("%s\n", buffer);
    }

    //输出信息的时间
    memset(buffer, 0, sizeof(buffer));
    sprintf(buffer, "Dump Time: %d-%d-%d %d:%d:%d\n",
            ptm->tm_year+1900, ptm->tm_mon+1, ptm->tm_mday,
            ptm->tm_hour, ptm->tm_min, ptm->tm_sec);
    printf("%s\n", buffer);
    //fwrite(buffer, 1, strlen(buffer), f);

    //fwrite(buffer, 1, strlen(buffer), f);

    //堆栈
    void* DumpArray[256];
    int    nSize =    backtrace(DumpArray, 256);
    sprintf(buffer, "backtrace rank = %d\n", nSize);
    printf("%s\n", buffer);
    //fwrite(buffer, 1, strlen(buffer), f);
    if (nSize > 0){
        char** symbols = backtrace_symbols(DumpArray, nSize);
        if (symbols != NULL){
            for (int i=0; i<nSize; i++){
                // fwrite(symbols[i], 1, strlen(symbols[i]), f);
                // fwrite("\n", 1, 1, f);
                printf("%s\n", symbols[i]);
            }
            free(symbols);
        }
    }

    // //文件解锁后关闭
    // fl.l_type = F_UNLCK;
    // fcntl(fd, F_SETLK, &fl);
    // fclose(f);
}

void test() {
	exit(1);
}

void test2() {
	test();
}

void test3() {
    printf("test3\n");
}

int main(int argc, char **argv) {
	atexit(server_backtrace);
	test3();
    test2();
    printf("the end3 of main\n");
    printf("the end2 of main\n");
    printf("the end1 of main\n");
    return 0;
}
