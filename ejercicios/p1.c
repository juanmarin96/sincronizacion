#include <stdio.h>
#include <sys/time.h>

int main(void)
{
    struct timeval start, end;
    double time;
    gettimeofday(&start, NULL);   // Instante inicial
    sleep(5);
    gettimeofday(&end, NULL);   // Instante final
    time = (end.tv_sec - start.tv_sec)*1000 + (end.tv_usec - start.tv_usec)/1000.0;
    printf("Has tardado: %g milisegundos\n", time);
}