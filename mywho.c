// This program mimics the behavior of the standard who command
/*
    open UTMP
    repeat
        read utmp file
        display utmp file: NAME, LINE NUMBERS, TIME, HOST
    close UTMP
*/

#include <utmp.h>
#include <unistd.h>   // aka UNIX Standard; POSIX (Portable OS Interface) API incl read/write
#include <fcntl.h>    // aka File Control; POSIX API for open/close
#include <stdio.h>
#include <time.h>

#define BUF_LEN 256

int main() {
    struct utmp currentRecord;              // a single UTMP record will be stored here

    int intUTMPfile;                        // a file descriptor to work with the UTMP file
    int intUTMPlength=sizeof(currentRecord);// how many bytes are there in a UTMP record


    char buffer[BUF_LEN] = {0};     // used to hold date and time
    time_t rawtime = time(NULL);    
    struct tm *ptm = localtime(&rawtime);

    strftime(buffer, BUF_LEN, "%b %d %I:%M", ptm); // puts string containing date & time into buffer

    // UTMP_FILE is a #define that contains the current path of the UTMP file
    printf("UTMP file is %s\n", UTMP_FILE);
    intUTMPfile = open(UTMP_FILE, O_RDONLY);  // open the UTMP file

    // read and print all UTMP records, one at a time
    while(read(intUTMPfile, &currentRecord, intUTMPlength)==intUTMPlength) {
        printf("%s %s %s\n", currentRecord.ut_user, currentRecord.ut_line,
        buffer);
    }
    close(intUTMPfile);
    return 0;
}
