/*Inlcudes*/
#include <string.h>
#include <sh.h>
#include <stdio.h>

/*This function modifies a passed array of characters*/
/*which stores user input */
void getline_sh(char buf[])
{
	int i = 0;
	char input;

	while (1) {
		input = getchar();
		/*If the input is not a backspace, print the*/
		/*character and store character in array*/
		if (input != '\b') {

			/*When the enter key is pressed, there is no more user input*/
			if ((input == '\r') || (input == '\n'))
				break;
			else {
				/*Print the character and store int in array*/
				printf("%c",input);
				buf[i] = input;

				/*If the user input is too large,*/
				/*overwrite the last character with*/
				/*whatever the next user character is*/
				if (i == 510)
					i--;
				i++;
			}
		}

		/*When the backspace is pressed and the array has items in it,*/
		/*remove the character from the screen and in the array*/
		if ((input == '\b') && (i != 0)) {
			printf("%c",input);
			i--;
			buf[i] = '\0'; //remove the value the was backspaced from the array
			printf(" \b"); //this makes the display show the delete
		}
		if ((input == '\b') && (i == 0));
	}
	printf("\n\r");

	/*Make sure that after the array is stored, the last character is Null for string management*/
	if (i != 510)
		buf[i] = '\0';
	else
		buf[511] = '\0';
}

/*This function runs the shell which receives a line of input.*/
/*Checks the input for a leading echo command. If true, print */
/*the following user input. Otherwise, return out of the shell.*/
int sh(void)
{
	char buf[512]; //this array is used for user input
	char print_buf[512]; //this array is used for storing characters after 'echo' command
	printf("$ "); //shell always leads with $
	getline_sh(buf); //receive user input into buf array

	if (strncmp(buf,"echo ",5) == 0)
	{
		/*Cycle through buf after 'echo ', and store it into print_buf array*/
		/*making sure that the last character is /0*/
		for (int i = 0; i < 512; i++){
			if (buf[i+5] == '\0') {
				print_buf[i] = '\0';
				break;
			}
			print_buf[i] = buf[i+5];
		}
		printf("%s\n\r", print_buf);
	}

	return 0;
}

