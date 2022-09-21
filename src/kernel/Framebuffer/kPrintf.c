#include "kPrintf.h"

#include "framebuffer.h"

#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>

/*
  %s	string
  %f	floating-point number
  %i	integer (base 10)
  %u	unsigned decimal (integer) number
  %x	number in hexadecimal (base 16)
*/

void kPrintf(const char* message, ...)
{
	va_list argp;
	va_start(argp, message);

	
	// This will be filled from the back to the front
	char numbers[20]; // This is the max characters in uint64_max
	int numberIndex = 19;

	while(*message != '\0')
	{
		if(*message == '%')
		{

			message++;
			switch(*message)
			{
			case 's': // String
				kPrintf(va_arg(argp, const char*));
			break;
			case 'i': // Integer
			{
				int64_t val = va_arg(argp, int64_t);
				bool neg = false;

				if(val < 0)
				{
					neg = true;
					val *= -1;
				}
				if(val == 0)
				{
					numbers[numberIndex] = '0';
					numberIndex--;
					break;
				}

				while(val > 0)
				{
					numbers[numberIndex] = (char)(48 + (val % 10));
					numberIndex--;
					// 48 is ascii 0
					val /= 10;
				}

				if(neg)
				{
					numbers[numberIndex] = '-';
					numberIndex--;
				}
			}
			break;
			// case 'f': // float
			// 	{
			// 		double val = va_arg(argp, double);

			// 		// Hardcoded to a max of 5
			// 		for(int i = 0; i < 6; i++)
			// 		{
			// 			framebuffer_put_char((char)(48 + ((uint64_t)val % 10)));
			// 			val /= 10;
			// 			if(val == 0)
			// 			{
			// 				break;
			// 			}
			// 		}
			// 	}
			// break;
			case 'u': // Unisgned int as decimal
				{
				uint64_t val = va_arg(argp, uint64_t);

				if(val == 0)
				{
					numbers[numberIndex] = '0';
					numberIndex--;
					break;
				}

				while(val > 0)
				{
					numbers[numberIndex] = (char)(48 + (val % 10));
					numberIndex--;
					// 48 is ascii 0
					val /= 10;
				}
			}
			break;
			case 'x': // Hex number
				{
				uint64_t val = va_arg(argp, uint64_t);

				if(val == 0)
				{
					numbers[numberIndex] = '0';
					numberIndex--;
				}

				while(val > 0)
				{
					int character = val % 16 + 48;
					
					// 57 is ascii 9 
					if(character > 57)
					{
						// 7 is the ascii offset from 9 to A
						character += 7;
					}

					numbers[numberIndex] = (char)character;
					numberIndex--;
					val /= 16;
				}

				numbers[numberIndex] = 'X';
				numberIndex--;
				numbers[numberIndex] = '0';
				numberIndex--;
			}
			break;
			default:
				numbers[numberIndex] = '%';
				numberIndex--;
			}

			for(int i = numberIndex + 1; i < 20; i++)
			{
				if(numbers[i] != 0)
				{
					framebuffer_put_char(numbers[i]);
					numbers[i] = 0;
				}
			}
		}
		else
		{
			framebuffer_put_char(*message);
		}
		message++;
	}

	va_end(argp);
}