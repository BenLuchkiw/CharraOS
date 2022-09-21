#include "framebuffer.h"

#include "fonts.h"

#include "kPrintf.h"

typedef struct FramebufferData
{
	uint32_t* fb;
	uint16_t width;
	uint16_t height;
	uint16_t pixelsPerRow;

	uint32_t backgroundColour;
	uint32_t foregroundColour;
	
	uint8_t characterWidth;
	uint8_t characterHeight;
	uint8_t xSpacing;
	uint8_t ySpacing;
	uint16_t cursorX;
	uint16_t cursorY;
} FramebufferData;

static FramebufferData fb;

static uint32_t framebuffer_set_colour(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

void framebuffer_init(uint32_t* frameBuffer, uint16_t width, uint16_t height, uint16_t pixelsPerRow, uint32_t backgroundColour, uint32_t foregroundColour)
{
	fb.fb = frameBuffer;
	fb.width = width;
	fb.height = height;
	fb.pixelsPerRow = pixelsPerRow;
	fb.foregroundColour = foregroundColour;
	fb.backgroundColour = backgroundColour;

	fb.characterWidth = 8;
	fb.characterHeight = 15;
	fb.xSpacing = 11;
	fb.ySpacing = 17;
	fb.cursorX = 0;
	fb.cursorY = 0;
}

void framebuffer_set_background_colour(uint32_t colour)
{
	fb.backgroundColour = colour;
}

void framebuffer_set_foreground_colour(uint32_t colour)
{
	fb.foregroundColour = colour;
}

uint16_t framebuffer_get_width()
{
	return fb.width;
}

uint16_t framebuffer_get_height()
{
	return fb.height;
}

void framebuffer_clear()
{
	uint32_t rowStart;
	for(int y = 0; y < fb.height; y++)
	{
		rowStart = y * fb.pixelsPerRow;
		for(int x = 0; x < fb.width; x++)
		{
			fb.fb[rowStart + x] = fb.backgroundColour;
		}
	}
}

void framebuffer_scroll(uint16_t pixels)
{
	for(int y = 0; y < fb.height - pixels; y++)
	{
		for(int x = 0; x < fb.width; y++)
		{
			fb.fb[y*fb.pixelsPerRow + x] = fb.fb[(y+pixels)*fb.pixelsPerRow + x];
		}
	}

	for(int y = fb.height - pixels; y < fb.height; y++)
	{
		for(int x = 0; x < fb.width; x++)
		{
			fb.fb[y*fb.pixelsPerRow + x] = fb.backgroundColour;
		}
	}
}

void framebuffer_print_char_bmp(uint8_t bitmap[120], uint16_t screenX, uint16_t screenY)
{
	uint16_t endX = screenX + 8;
	uint16_t endY = screenY + 15;

	int index = 0;

	for(int y = screenY; y < endY; y++)
	{
		for(int x = screenX; x < endX; x++)
		{
			if(bitmap[index] == 255)
			{
				fb.fb[y*fb.pixelsPerRow + x] = fb.foregroundColour;
				index++;
				continue;
			}
			else if(bitmap[index] == 0)
			{
				fb.fb[y*fb.pixelsPerRow + x] = fb.backgroundColour;
				index++; 
				continue;
			}
			else
			{
				uint8_t r = (uint8_t)(((255 - bitmap[index]) * ((uint8_t)(fb.backgroundColour >> 16))) + (bitmap[index] * ((uint8_t)(fb.foregroundColour >> 16))) / 255);
				uint8_t g = (uint8_t)(((255 - bitmap[index]) * ((uint8_t)(fb.backgroundColour >>  8))) + (bitmap[index] * ((uint8_t)(fb.foregroundColour >>  8))) / 255);
				uint8_t b = (uint8_t)(((255 - bitmap[index]) * ((uint8_t)(fb.backgroundColour      ))) + (bitmap[index] * ((uint8_t)(fb.foregroundColour      ))) / 255);

				fb.fb[y*fb.pixelsPerRow + x] = framebuffer_set_colour(r, g, b, 0xff);
			}
			index++;
		}
	}
}


// Returns the format in aarrggbb
inline static uint32_t framebuffer_set_colour(uint8_t r, uint8_t g, uint8_t b, uint8_t a)
{
	return (uint32_t)(a << 24) + (uint32_t)(r << 16) + (uint32_t)(g << 8) + b;
}

void framebuffer_put_char(char c)
{
	switch(c)
	{
	case 'a':
		framebuffer_print_char_bmp(a_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'b':
		framebuffer_print_char_bmp(b_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'c':
		framebuffer_print_char_bmp(c_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'd':
		framebuffer_print_char_bmp(d_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'e':
		framebuffer_print_char_bmp(e_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'f':
		framebuffer_print_char_bmp(f_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'g':
		framebuffer_print_char_bmp(g_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'h':
		framebuffer_print_char_bmp(h_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'i':
		framebuffer_print_char_bmp(i_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'j':
		framebuffer_print_char_bmp(j_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'k':
		framebuffer_print_char_bmp(k_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'l':
		framebuffer_print_char_bmp(l_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'm':
		framebuffer_print_char_bmp(m_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'n':
		framebuffer_print_char_bmp(n_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'o':
		framebuffer_print_char_bmp(o_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'p':
		framebuffer_print_char_bmp(p_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'q':
		framebuffer_print_char_bmp(q_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'r':
		framebuffer_print_char_bmp(r_BMP, fb.cursorX, fb.cursorY);
	break;
	case 's':
		framebuffer_print_char_bmp(s_BMP, fb.cursorX, fb.cursorY);
	break;
	case 't':
		framebuffer_print_char_bmp(t_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'u':
		framebuffer_print_char_bmp(u_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'v':
		framebuffer_print_char_bmp(v_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'w':
		framebuffer_print_char_bmp(w_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'x':
		framebuffer_print_char_bmp(x_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'y':
		framebuffer_print_char_bmp(y_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'z':
		framebuffer_print_char_bmp(z_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'A':
		framebuffer_print_char_bmp(A_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'B':
		framebuffer_print_char_bmp(B_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'C':
		framebuffer_print_char_bmp(C_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'D':
		framebuffer_print_char_bmp(D_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'E':
		framebuffer_print_char_bmp(E_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'F':
		framebuffer_print_char_bmp(F_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'G':
		framebuffer_print_char_bmp(G_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'H':
		framebuffer_print_char_bmp(H_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'I':
		framebuffer_print_char_bmp(I_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'J':
		framebuffer_print_char_bmp(J_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'K':
		framebuffer_print_char_bmp(K_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'L':
		framebuffer_print_char_bmp(L_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'M':
		framebuffer_print_char_bmp(M_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'N':
		framebuffer_print_char_bmp(N_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'O':
		framebuffer_print_char_bmp(O_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'P':
		framebuffer_print_char_bmp(P_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'Q':
		framebuffer_print_char_bmp(Q_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'R':
		framebuffer_print_char_bmp(R_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'S':
		framebuffer_print_char_bmp(S_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'T':
		framebuffer_print_char_bmp(T_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'U':
		framebuffer_print_char_bmp(U_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'V':
		framebuffer_print_char_bmp(V_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'W':
		framebuffer_print_char_bmp(W_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'X':
		framebuffer_print_char_bmp(X_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'Y':
		framebuffer_print_char_bmp(Y_BMP, fb.cursorX, fb.cursorY);
	break;
	case 'Z':
		framebuffer_print_char_bmp(Z_BMP, fb.cursorX, fb.cursorY);
	break;
	case '0':
		framebuffer_print_char_bmp(zero_BMP, fb.cursorX, fb.cursorY);
	break;
	case '1':
		framebuffer_print_char_bmp(one_BMP, fb.cursorX, fb.cursorY);
	break;
	case '2':
		framebuffer_print_char_bmp(two_BMP, fb.cursorX, fb.cursorY);
	break;
	case '3':
		framebuffer_print_char_bmp(three_BMP, fb.cursorX, fb.cursorY);
	break;
	case '4':
		framebuffer_print_char_bmp(four_BMP, fb.cursorX, fb.cursorY);
	break;
	case '5':
		framebuffer_print_char_bmp(five_BMP, fb.cursorX, fb.cursorY);
	break;
	case '6':
		framebuffer_print_char_bmp(six_BMP, fb.cursorX, fb.cursorY);
	break;
	case '7':
		framebuffer_print_char_bmp(seven_BMP, fb.cursorX, fb.cursorY);
	break;
	case '8':
		framebuffer_print_char_bmp(eight_BMP, fb.cursorX, fb.cursorY);
	break;
	case '9':
		framebuffer_print_char_bmp(nine_BMP, fb.cursorX, fb.cursorY);
	break;
	case '!':
		framebuffer_print_char_bmp(exclamation_BMP, fb.cursorX, fb.cursorY);
	break;
	case '\"':
		framebuffer_print_char_bmp(doubleQuote_BMP, fb.cursorX, fb.cursorY);
	break;
	case '#':
		framebuffer_print_char_bmp(hash_BMP, fb.cursorX, fb.cursorY);
	break;
	case '$':
		framebuffer_print_char_bmp(dollar_BMP, fb.cursorX, fb.cursorY);
	break;
	case '%':
		framebuffer_print_char_bmp(percent_BMP, fb.cursorX, fb.cursorY);
	break;
	case '&':
		framebuffer_print_char_bmp(ampersand_BMP, fb.cursorX, fb.cursorY);
	break;
	case '\'':
		framebuffer_print_char_bmp(singleQuote_BMP, fb.cursorX, fb.cursorY);
	break;
	case '(':
		framebuffer_print_char_bmp(openBracket_BMP, fb.cursorX, fb.cursorY);
	break;
	case ')':
		framebuffer_print_char_bmp(closedBracket_BMP, fb.cursorX, fb.cursorY);
	break;
	case '*':
		framebuffer_print_char_bmp(star_BMP, fb.cursorX, fb.cursorY);
	break;
	case '+':
		framebuffer_print_char_bmp(plus_BMP, fb.cursorX, fb.cursorY);
	break;
	case ',':
		framebuffer_print_char_bmp(comma_BMP, fb.cursorX, fb.cursorY);
	break;
	case '-':
		framebuffer_print_char_bmp(dash_BMP, fb.cursorX, fb.cursorY);
	break;
	case '.':
		framebuffer_print_char_bmp(period_BMP, fb.cursorX, fb.cursorY);
	break;
	case '/':
		framebuffer_print_char_bmp(forwardSlash_BMP, fb.cursorX, fb.cursorY);
	break;
	case ':':
		framebuffer_print_char_bmp(colon_BMP, fb.cursorX, fb.cursorY);
	break;
	case ';':
		framebuffer_print_char_bmp(semiColon_BMP, fb.cursorX, fb.cursorY);
	break;
	case '=':
		framebuffer_print_char_bmp(equals_BMP, fb.cursorX, fb.cursorY);
	break;
	case '<':
		framebuffer_print_char_bmp(lessThan_BMP, fb.cursorX, fb.cursorY);
	break;
	case '>':
		framebuffer_print_char_bmp(greaterThan_BMP, fb.cursorX, fb.cursorY);
	break;
	case '?':
		framebuffer_print_char_bmp(questionMark_BMP, fb.cursorX, fb.cursorY);
	break;
	case '@':
		framebuffer_print_char_bmp(at_BMP, fb.cursorX, fb.cursorY);
	break;
	case '\\':
		framebuffer_print_char_bmp(backslash_BMP, fb.cursorX, fb.cursorY);
	break;
	case '[':
		framebuffer_print_char_bmp(squareOpen_BMP, fb.cursorX, fb.cursorY);
	break;
	case ']':
		framebuffer_print_char_bmp(squareClose_BMP, fb.cursorX, fb.cursorY);
	break;
	case '^':
		framebuffer_print_char_bmp(caret_BMP, fb.cursorX, fb.cursorY);
	break;
	case '_':
		framebuffer_print_char_bmp(underscore_BMP, fb.cursorX, fb.cursorY);
	break;
	case '`':
		framebuffer_print_char_bmp(accent_BMP, fb.cursorX, fb.cursorY);
	break;
	case '|':
		framebuffer_print_char_bmp(verticalBar_BMP, fb.cursorX, fb.cursorY);
	break;
	case '{':
		framebuffer_print_char_bmp(curlyBraceOpen_BMP, fb.cursorX, fb.cursorY);
	break;
	case '}':
		framebuffer_print_char_bmp(curlyBraceClose_BMP, fb.cursorX, fb.cursorY);
	break;
	case '~':
		framebuffer_print_char_bmp(tilde_BMP, fb.cursorX, fb.cursorY);
	break;
	case ' ':
		framebuffer_print_char_bmp(empty_BMP, fb.cursorX, fb.cursorY);
	break;
	case '\n':
		framebuffer_print_char_bmp(empty_BMP, fb.cursorX, fb.cursorY);

		if(fb.cursorY + fb.ySpacing >= fb.height)
		{
			framebuffer_scroll(fb.ySpacing);
			fb.cursorX = 0;
		}
		else
		{
			fb.cursorX = 0;
			fb.cursorY += fb.ySpacing;
		}
		framebuffer_print_char_bmp(full_BMP, fb.cursorX, fb.cursorY);
		return;
	break;
	case '\b':
		if(fb.cursorX == 0)
		{
			return;
		}
		framebuffer_print_char_bmp(empty_BMP, fb.cursorX, fb.cursorY);
		fb.cursorX -= fb.xSpacing;
		framebuffer_print_char_bmp(full_BMP, fb.cursorX, fb.cursorY);
		return;
	break;
	}

	fb.cursorX += fb.xSpacing;

	if(fb.cursorX >= fb.width)
	{
		if(fb.cursorY + fb.ySpacing >= fb.height)
		{
			framebuffer_scroll(fb.ySpacing);
			fb.cursorX = 0;

		}
		else
		{
			fb.cursorX = 0;
			fb.cursorY += fb.ySpacing;
		}
	}

	framebuffer_print_char_bmp(full_BMP, fb.cursorX, fb.cursorY);
}