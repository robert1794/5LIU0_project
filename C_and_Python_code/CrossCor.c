#define _GNU_SOURCE
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "string.h"
#include "stdlib.h"
#define BUFFSIZE 10000 //101
#define XCORRSIZE (BUFFSIZE *2) -1

//uint8_t buffer1[BUFFSIZE]  = {127,135,143,151,159,166,174,181,
//188,195,202,208,214,220,225,230,
//234,238,242,245,248,250,252,253,
//254,254,254,253,252,250,248,245,
//242,238,234,230,225,220,214,208,
//202,195,188,181,174,166,159,151,
//143,135,127,119,111,103,95,88,
//80,73,66,59,52,46,40,34,
//29,24,20,16,12,9,6,4,
//2,1,0,0,0,1,2,4,
//6,9,12,16,20,24,29,34,
//40,46,52,59,66,73,80,88,
//95,103,111,119,127};
//
//uint8_t buffer2[BUFFSIZE]  = {127,135,143,151,159,166,174,181,
//188,195,202,208,214,220,225,230,
//234,238,242,245,248,250,252,253,
//254,254,254,253,252,250,248,245,
//242,238,234,230,225,220,214,208,
//202,195,188,181,174,166,159,151,
//143,135,127,119,111,103,95,88,
//80,73,66,59,52,46,40,34,
//29,24,20,16,12,9,6,4,
//2,1,0,0,0,1,2,4,
//6,9,12,16,20,24,29,34,
//40,46,52,59,66,73,80,88,
//95,103,111,119,127};


int16_t buffer2[BUFFSIZE] = {0 , 1, 5, 2};//{1 , 2, 0}
int16_t buffer1[BUFFSIZE] = {0 , 1, 5, 2};//{0 , 1, 5, 2};


uint8_t interPolationBuff[BUFFSIZE * 2];



int32_t corrBuffer[(BUFFSIZE * 2) -1] ;



uint32_t cross_correlate(uint8_t stepSize);


uint32_t cross_correlate(uint8_t stepSize)
{
	uint32_t largestCorrelation = 0;
	uint32_t sampleNumber = 0;
	int64_t sum = 0;
	uint16_t xcorrCounter = 0;
	int i = 0;
	int j = 0;
	int k = 0;//0
	for(i = 2 ; i >0 ; i--){
		if(i == 2){
		for(j = 0; j < BUFFSIZE; j++){
			for(k = 0; k <= j; k++)
			{	
				printf(" i = %d j = %d k = %d, %d * %d =  %d , j -k = %d , i -k = %d\n", i, j, k, buffer1[j + k], buffer2[i - k], buffer1[j - k] * buffer2[(BUFFSIZE -1) - k], j -k, i - k);
				sum += buffer1[j - k] * buffer2[(BUFFSIZE -1) - k];	
			}
		printf(" sum is %d \n", sum);
		corrBuffer[xcorrCounter] = sum;
		xcorrCounter ++;
		sum  = 0;
		}
	}
	else
	{
		for(j = BUFFSIZE -2; j >= 0 ; j --){
			for(k = 0 ; k <= j; k++)
			{	
				printf(" i = %d j = %d k = %d, %d * %d =  %d , j -k = %d , i -k = %d\n", i, j, k, buffer1[0 + k], buffer2[0 + k], buffer1[0 + k] * buffer2[(BUFFSIZE -1) - k], 0 + k, 0 + k);
				sum += buffer1[j - k] * buffer2[(BUFFSIZE -1) - k];	
			}
		printf(" sum is %d \n", sum);
		corrBuffer[xcorrCounter] = sum;
		xcorrCounter++;
		sum  = 0;
		}
	
		}
	}
			
	return sampleNumber;
}




uint32_t cross_correlate_step(uint8_t stepSize, uint8_t from, uint8_t to)
{
	uint32_t largestCorrelation = 0;
	uint32_t sampleNumber = 0;
	int64_t sum = 0;
	uint16_t xcorrCounter = 0;
	int i = 0;
	int j = 0;
	int k = 0;//0
	for(i = 2 ; i >0 ; i--){
		if(i == 2){
		for(j = 0; j < BUFFSIZE; j+= stepSize){
			for(k = 0; k <= j; k++)
			{	
				//printf(" i = %d j = %d k = %d, %d * %d =  %d , j -k = %d , i -k = %d\n", i, j, k, buffer1[j + k], buffer2[i - k], buffer1[j - k] * buffer2[(BUFFSIZE -1) - k], j -k, i - k);
				sum += buffer1[j - k] * buffer2[(BUFFSIZE -1) - k];	
			}
		printf(" sum is %d \n", sum);
		corrBuffer[xcorrCounter] = sum;
		xcorrCounter += stepSize;
		sum  = 0;
		}
	}
	else
	{
		printf("should be = %d \n", BUFFSIZE - (stepSize % BUFFSIZE));
		for(j = BUFFSIZE - (stepSize % BUFFSIZE); j >= 0 ; j -= stepSize){//(stepSize % BUFFSIZE)
			if(j == BUFFSIZE - 1 || xcorrCounter > XCORRSIZE){
				continue;
				
			}
			printf("j = %d \n", j);	
			for(k = 0 ; k <= j; k++)
			{	
				//printf(" i = %d j = %d k = %d, %d * %d =  %d , j -k = %d , i -k = %d\n", i, j, k, buffer1[j - k], buffer2[0 + k], buffer1[0 + k] * buffer2[(BUFFSIZE -1) - k], 0 + k, 0 + k);
				sum += buffer1[j - k] * buffer2[(BUFFSIZE -1) - k];	
			}
		printf(" sum is %d \n", sum);
		corrBuffer[xcorrCounter] = sum;
		xcorrCounter += stepSize;
		sum  = 0;
		}
	
		}
	}
			
	return sampleNumber;
}

//uint8_t *inputBuffer, uint8_t targetBuffer, 
void interpolate(uint16_t length)
{	
	int i = 0;
	for(i = 0; i < length; i ++)
	{
		interPolationBuff[i] = buffer1[i];
		interPolationBuff[i + 1] = buffer1[i] + ((buffer1[i + 1] - buffer1[i])/ 2);
		printf("%d", interPolationBuff[i]);
		printf("%d", interPolationBuff[i + 1]);
		
	}
	
}


void corrBuffToFile()
{
	FILE *f = fopen("C:/Users/Benno/Dropbox/Jaar 4/Q2/5LIU0/crosscorrrrr.txt", "wt");
	int i;
	fprintf(f, "%s\n", "CrossCorrelation");
	for(i = 0; i < XCORRSIZE; i++){
		fprintf(f, "%d,", corrBuffer[i]);
		fprintf(f, "%c", '\n');
		//fprintf(f, "%c", '\r');
	}
	
	fclose(f);
}

size_t getline(char **lineptr, size_t *n, FILE *stream) {
    char *bufptr = NULL;
    char *p = bufptr;
    size_t size;
    int c;

    if (lineptr == NULL) {
        return -1;
    }
    if (stream == NULL) {
        return -1;
    }
    if (n == NULL) {
        return -1;
    }
    bufptr = *lineptr;
    size = *n;

    c = fgetc(stream);
    if (c == EOF) {
        return -1;
    }
    if (bufptr == NULL) {
        bufptr = malloc(128);
        if (bufptr == NULL) {
            return -1;
        }
        size = 128;
    }
    p = bufptr;
    while(c != EOF) {
        if ((p - bufptr) > (size - 1)) {
            size = size + 128;
            bufptr = realloc(bufptr, size);
            if (bufptr == NULL) {
                return -1;
            }
        }
        *p++ = c;
        if (c == '\n') {
            break;
        }
        c = fgetc(stream);
    }

    *p++ = '\0';
    *lineptr = bufptr;
    *n = size;

    return p - bufptr - 1;
}

void readBuffFromFile()
{
	
	char *tok;
	char tempString[100];
	char line[100000];
	char *buf = NULL;
	size_t len = sizeof(line);
	size_t read;
	
	//tok = strtok(, ",\n");
	int ret;
//int c;
	FILE *fp = fopen("C:/Users/Benno/Dropbox/Jaar 4/Q2/5LIU0/30cm_center.csv", "rb");
	
	read = getline(&buf, &len, fp);
    int counter = 0;
    int tokCounter = 0;
	while ((read = getline(&buf, &len, fp)) != -1) {
        //printf("Retrieved line of length %zu:\n", read);
        //printf("%s", buf);
        tok = strtok(buf, ",");
        tokCounter = 0;
        while(tok != NULL)
		{
			
			switch(tokCounter)
			{
				case 0:
					tok = strtok(NULL, ",");
					tokCounter++;
					continue;
					break;
				case 1:
					buffer1[counter] = atoi(tok);
				//	printf("buffer1 = %d\r\n", buffer1[counter]);
					break;
				case 2:
					buffer2[counter] = atoi(tok);
				//	printf("buffer2 = %d\r\n", buffer2[counter]);
					break;	
			}
			tokCounter++;
			tok = strtok(NULL, ",");
			//printf("tok = %s, tokcount = %d\r\n", tok, tokCounter);
			
		}
		counter++;
		if(counter == BUFFSIZE)
			break;
    }

 fclose(fp);
}

void removeDC()
{
	int i;
	uint64_t samplesb1 = 0;
	uint64_t samplesb2 = 0;
	int j;
	
	for(j = 0; j < BUFFSIZE; j++)
	{
		printf("values = %d\n", buffer1[j]);
		samplesb1 += buffer1[j];
		samplesb2 += buffer2[j];
	}
	printf("b1b4 = %d\n", samplesb1);
	printf("b2b4 = %d\n", samplesb2);
	samplesb1 /= BUFFSIZE;
	samplesb2 /= BUFFSIZE;
	printf("b1 = %d\n", samplesb1);
	printf("b2 = %d\n", samplesb2);
	
	for(i = 0; i < BUFFSIZE; i++)
	{
		buffer1[i] -= samplesb1;
		buffer2[i] -= samplesb2;
	}
}



//*buff
//uint8_t searchLargest(int16_t length, uint8_t stepSize)
//{ 
//	uint16_t largest = -1;
//	uint8_t sample;
//	int i;
//	for( i = 0; i < length; i += stepSize)
//	{
//		if(xcorrBuff[i] > largest)
//			largest = ;
//	}
//}

int main()
{
	//interpolate(BUFFSIZE *2);
	//int maxSample = cross_correlate(1);
	//does not work when bigger than buff size
	readBuffFromFile();
	removeDC();
	int maxSample = cross_correlate_step(1, 0, 3);
	corrBuffToFile();
	
//	printf("%d \n",maxSample );
}

