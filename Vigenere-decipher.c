#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <stdlib.h> 

#define MAX_KEY_LENGTH 20 // Can be anything from 1 to 13

unsigned char  hex_to_int(char c){
        unsigned char  first = c / 16 - 3;
        unsigned char  second = c % 16;
        unsigned char  result = first*10 + second;
        if(result > 9) result--;
        return result;
}

unsigned char hex_to_ascii(char c, char d){
        unsigned char  high = hex_to_int(c) * 16;
        unsigned char  low = hex_to_int(d);
        return high+low;
}

int main(){
	const char* PLAINTEXT = "dtext.txt";
	const char* CIPHERTEXT = "ctext.txt";
	unsigned char ch;
	unsigned char *ptr;
        FILE *fpIn, *fpOut;
        int i,length,fd;
        unsigned char buf = 0;
	 
	fd = open(CIPHERTEXT, O_RDONLY );
	length = lseek(fd, 0, SEEK_END)+1;
	close(fd);
	ptr=(unsigned char*)malloc(length*sizeof(unsigned char));
	 
	fpIn = fopen(CIPHERTEXT, "r");
	fpOut = fopen(PLAINTEXT, "w");
	i = 0;

  while (fscanf(fpIn, "%c", &ch) != EOF) {
    /* avoid encrypting newline characters */  
    /* In a "real-world" implementation of the Vigenere cipher, 
       every ASCII character in the plaintext would be encrypted.
       However, I want to avoid encrypting newlines here because 
       it makes recovering the plaintext slightly more difficult... */
    /* ...and my goal is not to create "production-quality" code =) */
    if (ch=='\n') {
	    *(ptr + i) = ch;
	    i++;
    }
    else {
	    buf = ch;
	    fscanf(fpIn, "%c", &ch) ;
	    *(ptr + i) = hex_to_ascii(buf, ch);
	    i++;
      }
    }
    
    double q[MAX_KEY_LENGTH ][256];
    
    for (int index= 0; index< i ; index++ ) {
	     for (int key_length= 0; key_length< MAX_KEY_LENGTH; key_length++ ) {
		if(index % key_length == 0){
			q[key_length][*(ptr + i) ]++;
		}
	     }
    }
    
     return(0);
}