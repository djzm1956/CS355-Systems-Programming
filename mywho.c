#include <utmp.h>
#include <unistd.h>   // aka UNIX Standard; POSIX (Portable OS Interface) API incl read/write
#include <fcntl.h>    // aka File Control; POSIX API for open/close
#include <stdio.h>
#include <time.h>
/*
    open UTMP
    repeat
        read utmp file
        display utmp file: NAME, LINE NUMBERS, TIME, HOST
    close UTMP
*/



int main() {
    struct utmp currentRecord;              // a single UTMP record will be stored here
    //struct tm *tm_info;
    time_t timer;
    char buffer[26];
  
    int intUTMPfile;                        // a file descriptor to work with the UTMP file
    int intUTMPlength=sizeof(currentRecord);// how many bytes are there in a UTMP record

    timer = time(NULL);
    tm_info = localtime(&timer);

    // UTMP_FILE is a #define that contains the current path of the UTMP file
    printf("UTMP file is %s\n", UTMP_FILE);
    intUTMPfile=open(UTMP_FILE, O_RDONLY);  // open the UTMP file

    // read and print all UTMP records, one at a time
    while(read(intUTMPfile, &currentRecord, intUTMPlength)==intUTMPlength) {
        strftime(buffer, 26, "%b %d %H:%M", tm_info);
        //printf("%s  %s "%b %d %H:%M " %s\n", currentRecord.ut_user, currentRecord.ut_line,
        //tm_info, currentRecord.ut_host);
    }
    close(intUTMPfile);
    return 0;
}

/*
void displayTime(long timeval) {
    char *ch;
    ch = ctime(&timeval);
    printf("%s", ch);

}
*/