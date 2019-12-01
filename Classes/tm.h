#pragma once

#include <ctime>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

#define TM_YEAR_BASE 1900

/*
 * We do not implement alternate representations. However, we always
 * check whether a given modifier is allowed for a certain conversion.
 */
#define ALT_E     0x01
#define ALT_O     0x02
#define LEGAL_ALT(x)    { if (alt_format & ~(x)) return (0); }


static  int conv_num(const char **, int *, int, int);

static const char *day[7] = {
    "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday",
    "Friday", "Saturday"
};
static const char *abday[7] = {
    "Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"
};
static const char *mon[12] = {
    "January", "February", "March", "April", "May", "June", "July",
    "August", "September", "October", "November", "December"
};
static const char *abmon[12] = {
    "Jan", "Feb", "Mar", "Apr", "May", "Jun",
    "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"
};
static const char *am_pm[2] = {
    "AM", "PM"
};


//window上自己实现strptime函数，linux已经提供strptime
//strptime函数windows平台上实现
char *
strptime(const char *buf, const char *fmt, struct tm *tm);


static int conv_num(const char **buf, int *dest, int llim, int ulim)
{
    int result = 0;

    /* The limit also determines the number of valid digits. */
    int rulim = ulim;

    if (**buf < '0' || **buf > '9')
        return (0);

    do {
        result *= 10;
        result += *(*buf)++ - '0';
        rulim /= 10;
    } while ((result * 10 <= ulim) && rulim && **buf >= '0' && **buf <= '9');

    if (result < llim || result > ulim)
        return (0);

    *dest = result;
    return (1);
}


#define ARDRONE_DATE_MAXSIZE    32
#define ARDRONE_FILE_DATE_FORMAT  "%Y%m%d_%H%M%S"
#define ARDRONE_DEFAULT_DATE        "19700101_000000"


void yunshouhu_time2date(time_t time, const char *format, char *date);

void yunshouhu_date2time(char *date, const char *format, time_t *time);
//https://github.com/phdesign/pebble-phd/blob/f72313800357fd509def6abdde379067438fb3c1/src/utils.c
char *format_date_time(time_t datetime, char *format);

// int main(int argc, char const *argv[])
// {
//     time_t nowTime = time(NULL);
//     char line[1024] = {0};
//     char *format = "%Y-%m-%d %H:%M:%S";
//     yunshouhu_time2date(nowTime, format, line);
//     printf("%s\n", line);

//     time_t secondTime;
//     strcpy(line, "2018-06-29 23:20:30");
//     yunshouhu_date2time(line, format, &secondTime);

//     printf("ctime is %s\n", ctime(&secondTime)); //得到日历时间

//     yunshouhu_time2date(nowTime, NULL, line);
//     printf("%s\n", line);

//     char *data = format_date_time(time(NULL), "%Y-%m-%d %H:%M:%S");
//     printf("%s\n", data);

//     char *format2 = "%Y year %m month %d date %H hour %M minute %S seconds "; //还不支持中文 要使用unicode编码的中文
//     data = format_date_time(time(NULL), format2);
//     printf("%s\n", data);

//     format2 = "%Y\u5e74%m\u6708%d\u65e5 %H\u65f6%M\u5206%S\u79d2"; //还不支持中文 要使用unicode编码的中文
//     data = format_date_time(time(NULL), format2);
//     printf("%s\n", data);


//     return 0;
// }
