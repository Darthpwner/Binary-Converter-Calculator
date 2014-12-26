/*NOTE: Binary ns have a maximum character limit of 100*/

#define _CRT_SECURE_NO_WARNINGS
#define TRUE 1
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

void to_binary  ( int  n, int w, int *x, int *o ) ;
void from_binary( int *x, int w, int *n );
void adder( int *x, int *y, int *z, int *o, int w ) ;
void mult ( int *x, int *y, int *z, int *o, int w ) ;
void storeBinaryInArray(int binary, int length);

void main()
   {
	   while(TRUE)
	   {
		   int get;
		   int length;

		   int storeNumber[100];
		   int decimal;
		
		   int binary;

		   int binary1[100];
		   int binary2[100];

		   int additionLength;
		   int multiplicationLength;

		   int binaryResult[100];
	
		   int i;
		   int* overflow = storeNumber;

		   printf("What would you like to do?\n");
		   printf("1) Convert decimal to binary\n");
		   printf("2) Convert from binary to decimal\n");
		   printf("3) Add two binary ns together\n");
		   printf("4) Multiply two binary ns together\n");
		   printf("Choose 1, 2, 3, or 4\n");
		   scanf("%i", &get);
		   printf("\n");
		   
		   *overflow = 1;
		  
		   if(get == 1)
		   {
			   printf("Enter a decimal n\n");
			   scanf("%i", &decimal);
			   printf("Enter the length you want for the binary n\n");
			   scanf("%i", &length);
			   to_binary(decimal, length, storeNumber, overflow);

			   printf("\nYour decimal to binary n is ");
			   for (i = length - 1; i >= 0; i--)
				   printf("%i", storeNumber[i]);
	
			   printf("\n\n");
		   }

		   else if(get == 2)
		   {
			   decimal = 0;

			   //BUG: Doesn't work for binary integers with more than 10 digits?
			   printf("Enter a binary n\n");
			   scanf("%d", &binary);
			   //

			   printf("Enter length of your binary n\n");
			   scanf("%i", &length);
			   storeBinaryInArray(binary, length, binary1);

			   from_binary(binary1, length, &decimal);

			   printf("\nYour binary to decimal n is ");
			   printf("%i", decimal);

			   printf("\n\n");
		   }

		   else if (get == 3)
		   {
			   //BUGGY FIX WHEN THERE IS OVERFLOW!!!!
			   printf("Enter first binary n\n");
			   scanf("%d", &binary);
			   
			   printf("Enter a length of your first binary n\n");
			   scanf("%i", &length);
			   additionLength = length;
			   
			   storeBinaryInArray(binary, length, binary1);

			   printf("Enter second binary n\n");
			   scanf("%d", &binary);

			   printf("Enter a length of your second binary n\n");
			   scanf("%i", &length);
			   if (additionLength > length)
				   additionLength = length;

			   storeBinaryInArray(binary, length, binary2);

			   adder(binary1, binary2, binaryResult, overflow, additionLength);

			   printf("\nYour binary sum is ");
			   for (i = 0; i < additionLength; i++)
				   printf("%i", binaryResult[i]);
	
			   printf("\n\n");
		   }

		   else if (get == 4)
		   {
			   multiplicationLength = 0;

			   printf("Enter first binary n\n");
			   scanf("%d", &binary);
			   
			   printf("Enter a length of your first binary n\n");
			   scanf("%i", &length);
			   multiplicationLength += length;

			   storeBinaryInArray(binary, length, binary1);

			   printf("Enter second binary n\n");
			   scanf("%i", &binary);
			  
			   printf("Enter a length of your second binary n\n");
			   scanf("%i", &length);
			   multiplicationLength += length;
			  
			   storeBinaryInArray(binary, length, binary2);

			   mult(binary1, binary2, binaryResult, overflow, multiplicationLength);

			   printf("\nYour binary calculator is ");
			   for (i = 0; i < multiplicationLength; i++)
				   printf("%i", binaryResult[i]);
	
			   printf("\n\n");
		   
		   }

		   else
		   {
			   printf("Input must be 1, 2, 3, or 4\n\n");
			   continue;
		   }
	   }
   }

void adder( int *x, int *y, int *z, int *o, int w )
   {
   /* x is an input array of w ints, either 0 or 1 representing the first addend */
   /* y is an input array of w ints, either 0 or 1 representing the second addend */
   /* z is an output array of w ints, either 0 or 1 representing the sum of x and y */
   /* o is an output = 1 if an overflow occurred */
   /* w is an input = to the width in bits of x, y, z */

	   int overflowArray[100];
	   int iter = w - 1;
	   int carry = 0;

	   while (iter >= 0)
	   {
			if(x[iter] == y[iter])	/*1 + 1 or 0 + 0*/
			{
				if (carry)
				{
					if (x[iter] == 0)
					{
						z[iter] = 1;
						carry = 0;	/*Carrying stops at this digit*/
					}

					else if (x[iter] == 1)
					{
						z[iter] = 1;
						carry = 1;	/*Carrying continues to next digit*/
					}
				}

				else	/*No carrying*/
				{
					if(x[iter] == 0)
						z[iter] = 0;

					else if(x[iter] == 1)	/*carry over a 1*/
					{
						carry = 1;
						z[iter] = 0;
					}
				}
			}

			else if(x[iter] ^ y[iter])	/*1 + 0 or 0 + 1*/
			{
				if(!carry)
					z[iter] = 1;

				else if(carry)	/*carrying continues*/
					z[iter] = 0;
			}

			iter--;
	   }

	   /*Check to see if the most significant bit addends add and get an opposite sign. The two examples of overflow happen when you add two positives
	   and get a negative signed int, or if you add two negatives and get a positive signed int. It is impossible to overflow if you add a positive 
	   and a negative together.*/

	   if(x[iter-1] == y[iter-1] && x[iter-1] != z[iter-1])		
	   {
		   *o = 1;
			//Factor in the overflow bit and move into a new array
		   
	   }
   }

void mult ( int *x, int *y, int *z, int *o, int w )
   {
   /* x is an input array of w ints, either 0 or 1 representing the first multiplicand */
   /* y is an input array of w ints, either 0 or 1 representing the second multicand */
   /* z is an output array of w ints, either 0 or 1 representing the product of x and y */
   /* o is an output = 1 if an overflow occurred */
   /* w is an input = to the width in bits of x, y, z */

	   //BUGGY!

	   int xIsZero, yIsZero;
		int checkZeroX, checkZeroY;
		
	   int xIter = 0, yIter = 0;
		int startPos = 0, reset = startPos;
		int zArray[32][32] = {0};

		int storeEachAddition[32] = {0};
		int firstAddition = 1;
		int storeCounter = 0;


		/*Obtain all the elements*/
		while (yIter != w)
		{
			while (xIter != w)
			{
				if(y[yIter] == 0)
					break;
				else if(y[yIter] == 1 && x[xIter] == 1)	
					zArray[yIter][startPos] = 1;
				xIter++;
				startPos++;
			}

			xIter = 0;
			reset++;
			startPos = reset;
			yIter++;
		}
	
		xIter = 0;	/*Reset to zero because we are going to add the entire row.*/

		
		while (xIter != w)
		{
			if (firstAddition)
				adder(zArray[xIter], zArray[xIter+1], z, o, w);

			else
				adder(storeEachAddition, zArray[xIter], z, o, w);
			
			while (storeCounter != w)
			{
				storeEachAddition[storeCounter] = z[storeCounter];
				storeCounter++;
			}

			storeCounter = 0;	/*Reset variable that counts storeEachAddition*/
			
			if(firstAddition)
				xIter += 2;
			else
				xIter++;
			firstAddition = 0;	/*Change firstAddition after first run*/
		}

		/*Overflow*/
		xIsZero = 0, yIsZero = 0;
		checkZeroX = 0, checkZeroY = 0;
		
		/*Check if either x or y arrays are 0.*/
		while(checkZeroX != w)
		{
			if(x[checkZeroX] == 1)
			{
				xIsZero = 1;
				break;
			}
			checkZeroX++;
		}

		while(checkZeroY != w)
		{
			if(y[checkZeroY] == 1)
			{
				yIsZero = 1;
				break;
			}
			checkZeroY++;
		}

		if(xIsZero == 0 || yIsZero == 0)
			return;

		/*positive * positive == negative*/
		else if (x[w-1] == 0 && y[w-1] == 0 && z[w-1] == 1)
			*o = 1;
		/*negative * negative == negative*/
		else if (x[w-1] == 1 && y[w-1] == 1 && z[w-1] == 1)
			*o = 1;
		/*positive * negative == positive*/
		else if (x[w-1] == 0 && y[w-1] == 1 && z[w-1] == 0)
			*o = 1;
		/*negative * positive == positive*/
		else if (x[w-1] == 1 && y[w-1] == 0 && z[w-1] == 0)
			*o = 1;
   }

void to_binary( int n, int w, int *x, int *o )
   {
   /* n is an input and is the n to be converted to binary */
   /* w is an input = to the width in bits of x */
   /* x is an output array of w ints, either 0 or 1: the binary representation of n */
   /*           x[0] is the least significant bit   */
   /*           x[w-1] is the most signifcant bit, for a signed n, it is the sign */
   /* o is an output = 1 if an overflow occurred ( n is too large for w bits ) */

	   /*My code has to be in big endian encoding*/
	   int numOfDigits;
	   int temp;
	   int iter;
	   int complement;

	   float twos_base = 2;

	   numOfDigits = 0, temp = 0;

	   /*Initialize the overflow flag, or else you get a ton of weird flag errors.*/
	   *o = 0;

	   /*Scenario when n is positive*/
	   if (n > 0)
	   {
			while (n > 0)		/*Get binary representation of decimal value*/
			{
				x[temp] = n % 2;
				numOfDigits++;
				n /= 2;		
				temp++;
			}
	   }

	   /*Scenario when n is negative, we need to use two's complement*/
	   else if (n < 0)
	   {
			complement = pow(twos_base, w) - abs(n);
			
				while (complement != 0)		/*Get binary representation of decimal value*/
				{
					x[temp] = complement % 2;
					numOfDigits++;
					complement = complement/2;		
					temp++;
				}
	   }

		   iter = temp;		/*Fill in remaining slots with 0*/
		   while (iter < w)
		   {
			   x[iter] = 0;
			   iter++;
		   }

		   if(numOfDigits > w)
				*o = 1;
   }

void from_binary( int *x, int w, int *n )
{
   /* x is an input array of w ints, either 0 or 1: the binary representation of n */
   /*           x[0] is the least significant bit   */
   /*           x[w-1] is the most signifcant bit, for a signed number, it is the sign */
   /* w is an input = to the width in bits of x */
   /* n is an output and will be equal to the value stored in binary in x */
	   
	   float twos_base = 2;
	   int i = 1;
	   int getW = w - 2;

	   *n = -1 * pow(twos_base, w-1) * x[0];

	   while (i < w)
	   {
		   *n += pow(twos_base, getW) * x[i];
		   i++;
		   getW--;
	   }
}

void storeBinaryInArray(int binary, int length, int* array)
{
	int i = 0;
	int remainder;
	int lengthIterator = length - 1;

	while (i < length)
	{
		//Repeatedly divide by 10 and keep track of the remainder
		remainder = binary % 10;
		array[lengthIterator] = remainder;
		binary /= 10;
		i++;
		lengthIterator--;
	}
}