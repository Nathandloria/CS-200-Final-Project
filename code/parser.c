#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#include "converter.c"
#include "bitwise.c"

void welcomeMessage()
{
	printf("\n\n\n\n\n\n\nWelcome to an arithmetic operator free Calculator/Converter! (No +, -, *, or / !)\n\nThis program can add, subtract, multiply, or divide two numbers of any combination of base 2, 10, and 16.\n");
}

void basicIns()
{
	printf("\nPlease start by choosing Convert (con), Calculate with logical operators (calc), or Calculate with BitWise operators (bit):\n\n\t(q) or (quit) to exit :(\n\n> ");
	
	
}

void conWelc()
{
	printf("\n\nWelcome to the converter!");
	
}

void conIns()
{
	printf("\n\nTo use this converter use the following syntax:\n-----------------------------------------------\n'bin/dec/hex' 'Number in given number system' 'What you want to convert to'\nEx. 'bin 1010 hex' will convert 1010 to hex\n\n> ");
	
}

void calcWelc()
{
	printf("\n\nWelcome to the Calculator!");
	
}

void calcIns()
{
	printf("\n\nTo use the logical calculator use the following syntax:\n---------------------------------------------------------------------------------------------------\nbin/dec/hex 'Number in given number system' 'operator' 'bin/dec/hex' 'Number in given number sytem'\nEx. 'hex 1ef - bin 101' will subtract the hex number 1ef from the bin number 101 \n\n> ");
	
}

void bitIns()
{
	printf("\n\nTo use the bitwise calculator use the following syntax:\n---------------------------------------------------------------------------------------------------\nbin/dec/hex 'Number in given number system' 'operator' 'bin/dec/hex' 'Number in given number sytem'\nEx. 'dec 136 * bin 11100' will multiply the dec number 136 with the bin number 11100 \n\n> ");
	
}

int matchDigitToBase(char digit, char *base)
{
	if ( !strcmp( base, "bin") && ( digit == 48 || digit == 49)) {
		// printf("\n\nbin success");
		return 1;
	}
	if ( !strcmp( base, "dec") && digit >= 48 && digit <= 57) {
		// printf("\n\ndec success");
		return 1;
	}
	if ( !strcmp( base, "hex") && ((digit >= 97 && digit <= 102) || (digit >= 48 && digit <= 57))) {
		// printf("\n\nhex success");
		return 1;
	}
	return 0;
}

int matchBase( char *str, char *base)
{
	int i = 0;
	
	// printf("\\n%i", !strcmp( base, "dec"));
	if ( !strcmp( base, "dec") || !strcmp( base, "bin") || !strcmp( base, "hex"))
	{
		// printf("\n\n----------------");
		// printf("\n\ni= %d", i);
		// printf("\n\nchar = %c", *(str+i));
		// printf("\n\nmatch: %i", matchDigitToBase( *(str+i), base));
		while( matchDigitToBase( *(str+i), base) == 1)
		{
			// printf("%i\n", *(str+i));
			if (*(str+i+1) == '\0' || *(str+i+1) == '\n') {
				// printf("\n\nboooooooom");
				return 0;
			}
			i++;
			// printf("\n\n----------------");
			// printf("\n\ni= %d", i);
			// printf("\n\nchar = %c", *(str+i));
			// printf("\n\nmatch: %i", matchDigitToBase( *(str+i), base));
		}
		return 1;
	}
	return 2;
}

int convertToDec(char *strNum, char *base)
{
	if ( !strcmp( base, "bin"))
		return binToDec( atoi( strNum));
	
	if ( !strcmp( base, "dec"))
		return atoi( strNum);
	
	if ( !strcmp( base, "hex"))
		return hexToDec( strNum);
	return 0;
}

int gotoMenu(char *or)
{
	if (!strcmp( or, "redo")) {
		printf("\n\nEnter (q) or (quit) to go back to the main menu otherwise the operation will repeat!\n\n> ");
	}
	fflush(stdin);
	
	char answer[10];
	scanf("%s", answer);
	fflush(stdin);
	if (!strcmp(answer, "q") || !strcmp(answer, "quit"))
		return 0;
	return 1;
}

int main(int argc, char *argv[])
{
	char choice[10];
	char *numStr1 = NULL;
	char *numStr2;
	char *operation;
	char *base1;
	char *base2;
	
	welcomeMessage();
	
	do
	{
		basicIns();
		scanf("%s", choice);
		// printf("%s", choice);
	
		while (!strcmp(choice, "con"))
		{
			if (numStr1 == NULL)
			{
				conWelc();
			}
			conIns();
			
			char str[60];
			
			fflush(stdin);
			fgets(str, 60, stdin);
			
			base1 =  strtok(str, " ");
			// printf("%s", base1);
			numStr1 =  strtok(NULL, " ");
			// printf("%s", num1);
			base2 =  strtok(NULL, "\n");
			// printf("%s", base2);
			
			if (base1 == NULL || numStr1 == NULL || base2 == NULL)
			{
				printf("\n\nNot enough inputs");
				
				if( gotoMenu("redo"))
					continue;
				else {
					break;
				}
			}

//			printf("-%s-", base2);

			if ( strlen(base2) > 3) {

                printf("\n\nSecond base input does not exist!");

                if( gotoMenu("redo"))
                    continue;
                else {
                    break;
                }
			}
			
			int num1;
			if (strcmp(numStr1, "0"))
			{
				int matchedBase = matchBase(numStr1, base1);
				if (matchedBase == 1)
				{
					printf("\n\nDigits do not exist in input number system");
					continue;
				}
				if (matchedBase == 2)
				{
					printf("\n\nInvalid number system entered (bin/dec/hex)");
					continue;
				}
			}
			
			num1 = atoi( numStr1);
			// printf("%s %d to %s", base1, num1, base2);
			
			printf("\n\n\tConverting %s in %s to %s", numStr1, base1, base2);
			
			switch (base1[0])
			{
				case 'b':

					switch (base2[0])
					{
						case 'b':
							printf("\n\nWhy would you convert binary to binary?");
							break;

						case 'd':
							printf("\n\nDec number: %d", convertToDec(numStr1, base1));
							break;

						case 'h':
							printf("\n\nHex number: %s", binToHex(atoi(numStr1)));
							break;


						default:
							;
					}

				break;

				case 'd':

					switch (base2[0])
					{
						case 'b':
							printf("\n\nBin number: %d", decToBin(convertToDec(numStr1, base1)));
							break;

						case 'd':
							printf("\n\nWhy would you convert decimal to decimal?");
							break;

						case 'h':
							printf("\n\nHex number: ");
							decToHex( convertToDec(numStr1, base1));
							break;

						default:
							;
					}

				break;

				case 'h':

					switch (base2[0])
					{
						case 'b':
							printf("\n\nBin number: ");
							hexToBin( numStr1);
							break;

						case 'd':
							printf("\n\nDec number: %d", hexToDec( numStr1));
							break;

						case 'h':
							printf("\n\nWhy would you convert hexadecimal to hexadecimal?");
							break;

						default:
							;

					}
				break;
				default:
					;
			}
			if ( gotoMenu("redo")) { continue;}
			strcpy( choice, "nop");
		}
		
		while (!strcmp(choice, "bit") || (!strcmp(choice, "calc")))
		{
			if (numStr1 == NULL)
			{
				calcWelc();
			}
			if ( !strcmp( choice, "calc")) {
				calcIns();
			} else {
				bitIns();
			}
			
			char str[60];
			
			fflush(stdin);
			fgets(str, 60, stdin);
			
			base1 =  strtok(str, " ");
			numStr1 =  strtok(NULL, " ");
			operation = strtok(NULL, " ");
			base2 =  strtok(NULL, " ");
			numStr2 =  strtok(NULL, "\n");
			
			if (base1 == NULL || numStr1 == NULL || base2 == NULL || numStr2 == NULL)
			{
				printf("\n\nNot enough inputs");
				
				if( gotoMenu("redo"))
					continue;
				else
					break;
			}
			
			if (strcmp(numStr1, "0") || strcmp(numStr2, "0"))
			{
				int num1Bad = matchBase(numStr1, base1);
				int num2Bad = matchBase(numStr2, base2);
				
				if (num1Bad == 1 && num2Bad == 1)
				{
					printf("\n\nInvalid characters detected in both numbers");
					continue;
				}
				if (num1Bad == 1 && num2Bad == 0)
				{
					printf("\n\nInvalid characters detected in your first number");
					continue;
				}
				if (num1Bad == 0 && num2Bad == 1)
				{
					printf("\n\nInvalid characters detected in your second number");
					continue;
				}
				if (num1Bad == 2 && num2Bad == 2)
				{
					printf("\n\nInvalid number system for your 1st and 2nd number (bin/dec/hex)");
					continue;
				}
				
				if (num1Bad == 2 && num2Bad == 0)
				{
					printf("\n\nInvalid number system for your 1st number (bin/dec/hex)");
					continue;
				}
				if (num1Bad == 0 && num2Bad == 2)
				{
					printf("\n\nInvalid number system for your 2nd number (bin/dec/hex)");
					continue;
				}
				if (num1Bad == 1 && num2Bad == 2)
				{
					printf("\n\nInvalid characters detected in your first number");
					printf("\n\nInvalid number system for your 2nd number (bin/dec/hex)");
					continue;
				}
				if (num1Bad == 2 && num2Bad == 1)
				{
					printf("\n\nInvalid number system for your 1st number (bin/dec/hex)");
					printf("\n\nInvalid characters detected in your second number");
					
					continue;
				}
			}

			int* num1Input;
            int* num2Input;

			
			// printf("\n\n\t\t%s %s %s %s %s", base1, numStr1, operation, base2, numStr2);
//			printf("\n\n\t\t%s %d %s %s %d", base1, num1, operation, base2, num2);
			switch (operation[0])
			{
				case '+':
					// printf("yo");
					if ( !strcmp( choice, "calc")) {
					printf("\n-%d-\n", convertToDec(numStr1, base1));
					printf("\n-%d-\n", convertToDec(numStr2, base2));
					printf("\n-%d-\n", *decimalToBinary(convertToDec(numStr1, base1)));
					printf("\n-%d-\n", *decimalToBinary(convertToDec(numStr2, base2)));
					printf("\n\nSum: %d", add( decimalToBinary(convertToDec(numStr1, base1)), decimalToBinary(convertToDec(numStr2, base2))));
					} else {
						printf("\n\nSum: %d", addWise(convertToDec(numStr1, base1), convertToDec(numStr2, base2)));
					}
					break;
					
				case '-':
					if ( !strcmp( choice, "calc")) {
					printf("\n-%d-\n", convertToDec(numStr1, base1));
					printf("\n-%d-\n", convertToDec(numStr2, base2));
					printf("\n-%d-\n", *decimalToBinary(convertToDec(numStr1, base1)));
					printf("\n-%d-\n", *decimalToBinary(convertToDec(numStr2, base2)));
					printf("\n\nDifference: %d", subtract( decimalToBinary(convertToDec(numStr1, base1)), decimalToBinary(convertToDec(numStr2, base2))));
					} else {
						printf("\n\nDifference: %d", subWise(convertToDec(numStr1, base1), convertToDec(numStr2, base2)));
					}
					break;

				case '*':
					if ( !strcmp( choice, "calc")) {
					printf("\n-%d-\n", convertToDec(numStr1, base1));
					printf("\n-%d-\n", convertToDec(numStr2, base2));
					printf("\n-%d-\n", *decimalToBinary(convertToDec(numStr1, base1)));
					printf("\n-%d-\n", *decimalToBinary(convertToDec(numStr2, base2)));
					printf("\n\nProduct: %d", multiply( decimalToBinary(convertToDec(numStr1, base1)), decimalToBinary(convertToDec(numStr2, base2))));
					} else {
						printf("\n\nProduct: %d", multWise(convertToDec(numStr1, base1), convertToDec(numStr2, base2)));
					}
					break;
					
				case '/':
					
					if ( !strcmp( choice, "calc")) {
					printf("\n-%d-\n", convertToDec(numStr1, base1));
					printf("\n-%d-\n", convertToDec(numStr2, base2));
					printf("\n-%d-\n", *decimalToBinary(convertToDec(numStr1, base1)));
					printf("\n-%d-\n", *decimalToBinary(convertToDec(numStr2, base2)));
					printf("\n\nQuotient: %d", divide( decimalToBinary(convertToDec(numStr1, base1)), decimalToBinary(convertToDec(numStr2, base2))));
					} else {
						printf("\n\nQuotient: %d", divWise(convertToDec(numStr1, base1), convertToDec(numStr2, base2)));
					}
					break;
					
				default:
					printf("\n\nInvalid operation entered (valid: (+),(-),(*), or (/)");
			}
			if ( gotoMenu("redo")) { continue;}
			strcpy( choice, "nop");
		
		}
		

		
		if ( !strcmp( choice, "quit") || !strcmp( choice, "q"))
			exit(0);
		
		// if ((strcmp(choice, "con") || strcmp(choice, "calc")) && strcmp(choice, "0")) {
			// printf("\nIncorrect input. Please try again");
		// }
		// printf("%s", choice);
	} while (1);
	//printf("%s", input);
	
	
	
}