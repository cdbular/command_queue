#include <stdio.h>
#include <string.h>
/*Definiciones y funciones para cola de comandos*/
#define QUEUE_LENGHT 20
#define QUEUE_CMDLINE_LEN 20
#define QUEUE_ADDR_LEN 20


typedef struct
{
	char cmdline[QUEUE_CMDLINE_LEN];
	char address[QUEUE_ADDR_LEN];
}cmd_queue_t;

void cmd_queue_push(char* sl_address, char* cmdline);
unsigned char cmd_queue_pop(char* sl_address, char* cmdline);

/*Variables para cola de comandos*/
cmd_queue_t cmd_queue[QUEUE_LENGHT];
unsigned char tail=0;
unsigned char head=0;
char empty_queue = 1;


int main(void) {
	// your code goes here
	int i = 0;
	char lines[20];
	char address[5];

	
	for (i = 0; i < 100; i++)
	{
		sprintf(lines, "prueba linea %i", i);
		sprintf(address, "AB%0.2X", i);
		printf("%s ", address);
		printf("%s\n", lines);
		cmd_queue_push(address, lines);
	}
	printf("Cola...\n");
	
	for (i = 0; i < 20; i++)
	{
		printf("%s ", cmd_queue[i].address);
		printf("%s\n", cmd_queue[i].cmdline);
	}

	printf("lectura...\n");
	while(cmd_queue_pop(address, lines)==1)
	{
		printf("%s ", address);
		printf("%s\n",  lines);

	}
	


	return 0;
}







void cmd_queue_push(char* sl_address, char* cmdline)
{
	char i;
	
	if (tail >= QUEUE_LENGHT)
	{
		tail = 0;
	}
	if (tail == head && empty_queue == 0)
	{
		head++;
		if (head >= QUEUE_LENGHT)
			head = 0;
	}

	for (i = 0; i<4; i++)
		cmd_queue[tail].address[i] = sl_address[i];
	strcpy(cmd_queue[tail].cmdline, cmdline);
	tail++;
	
	
	empty_queue = 0;
}

unsigned char cmd_queue_pop(char* sl_address, char* cmdline)
{

	unsigned char i;
	if (empty_queue==1) //no hay datos en cola
		return 0;
	

	for (i = 0; i < 4; i++)
	{
		sl_address[i] = cmd_queue[head].address[i];
	}
		strcpy(cmdline, cmd_queue[head].cmdline);
		head++;
	
	if (head >= QUEUE_LENGHT)
		head = 0; 
	if (tail >= QUEUE_LENGHT)
	{
		tail = 0;
	}
	if (head == tail) //no hay datos en cola
		empty_queue = 1;
	return 1;
}
