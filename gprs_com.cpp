#include "mbed.h"
#include <string>
 
   
Serial gprs(PTC17,PTC16);
Serial pc(USBTX,USBRX);
Timer timeCnt;
char IPAdd[100];
    
// this is here to put so you dont have to keep typing the same AT commands
// repeatedly when trouble shooting.
// send the at command  gprs.puts("AT\r\n"); and set a litten timer get_response(1);
void get_response(int time_amount){
    char buffer[100];
    int count = 0;
    timeCnt.start();
    while(timeCnt.read() < time_amount)
    {  
        while(gprs.readable()) {
        char c = gprs.getc();
        buffer[count++] = c;            }
        }
       timeCnt.stop();
       timeCnt.reset();
       buffer[count] = '\0'; // this indicats when the string is done
       printf("%s \n",buffer);
        for(int i = 0; i < count+2; i++) {
            buffer[i] = NULL;
        }
        count = 0;
}

int main()
{
    char buffer[100];
    int count;
    pc.baud(19200);
    gprs.baud(19200);
    //all at commands must end with \r\n to indicate end to the sim900 
    // when communicating on a serial monitor \r\n is NOT needed
    gprs.puts("AT\r\n"); // send AT command
    get_response(1);    // get a response within 1 sec.

    printf("loopoing\n");
     while(1) {
        if(gprs.readable()) {
             
            while(gprs.readable()) {
                char c = gprs.getc();
                buffer[count++] = c;
                //pc.puts(&c);
                if(count == 64) break;
            }
            
            pc.puts(buffer); // this helps eliminate junk display
            for(int i = 0; i < count+2; i++) {
                buffer[i] = NULL;
            }
            count = 0;
        }
        if(pc.readable()) {
            gprs.putc(pc.getc());
        }
    }
}