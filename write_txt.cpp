#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <fcntl.h>

#define STRING 10

uint64_t c1,
    c2;
struct timespec ts1, ts2, ts3, ts4;
double t;
double tsum;

char *filename;
char *logfilename;

int fdo;

int main()
{
    fdo = open("ex-write.txt", (O_CREAT | O_RDWR), 0644);
    if (fdo == -1)
    {
        printf("file open error\n");
        exit(1);
    }
    printf("fdo: %d\n", fdo);

    char input[STRING];
    char a[5];
    fgets(a, 5, stdin);

    for (int i = 0; i < STRING; i++)
    {
        input[i] = a[0];
    }

    for (int i = 0; i < 10; i++)
    {

        clock_gettime(CLOCK_MONOTONIC, &ts1);

        write(fdo, &input, sizeof(char) * STRING);
        fsync(fdo);

        clock_gettime(CLOCK_MONOTONIC, &ts2);

        t = ts2.tv_sec - ts1.tv_sec + (ts2.tv_nsec - ts1.tv_nsec) / 1e9;
        printf("%.4f\n", t);
    }
    close(fdo);

    exit(0);
}

// fio -filename=/fiotest -direct=1 -rw=write -bs=18b -size=1G -numjobs=1 -runtime=10 -group_reporting -name=file1
