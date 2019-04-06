//Kunal Baran Maiti

#include <unistd.h>

/* You may want to use this */
char hex2asc[17]="0123456789ABCDEF";

// The function that prints out the position, the hex representation of the 8
// characters passed to it, followed by printing out the string
// of those 8 characters
static int putout(char asci[8], int position, int n) {

	//A 16 bit address, displayed as a 4 digit hexadecimal number
	//followed by two spaces. If the address reaches FFF8
	//the next address should be 0000.

	unsigned char pos[6];

	unsigned char p1 = (position & 0xf000) >> 12;
	unsigned char p2 = (position & 0x0f00) >> 8;
	unsigned char p3 = (position & 0x00f0) >> 4;
	unsigned char p4 = (position & 0x000f);

	unsigned char pos1 = hex2asc[p1];
	unsigned char pos2 = hex2asc[p2];
	unsigned char pos3 = hex2asc[p3];
	unsigned char pos4 = hex2asc[p4];

	pos[0] = pos1;
	pos[1] = pos2;
	pos[2] = pos3;
	pos[3] = pos4;
	pos[4] = (' ');
	pos[5] = (' ');


	if (write(1, pos, 6) != 6) {
		return -1;
	}

	//Eight bytes of data, displayed as 2 digit hexadecimal numbers
	//separated by single spaces and followed by two spaces.

	char asci2[3];

	for (int h = 0; h < (n + 1); h++) {

		char c, c1, c2 = 0;
		c = asci[h];

		c1 = c  & 0x0f;
		c2 = (c  & 0xf0) >> 4;

		char hex1 = hex2asc[c1];
		char hex2 = hex2asc[c2];

		asci2[0] = hex2;
		asci2[1] = hex1;
		asci2[2] = (' ');

		if (write(1, asci2, 3) != 3) {
        	return -1;
        }

	}

	//printing out the right number of spaces
	int z = 0;

	if (n < 7) {

		z = (2*(8 - n)) + (6 - n);

		for (int g = 0; g < z; g++) {

			if (write(1, " ", 1) != 1) {
				return -1;
			}

		}

	}

	if (n == 7) {

		if (write(1, " ", 1) != 1) {
			return -1;
		}

	}

	//priting out the right characters

	unsigned char asci3[8];

	for (int k = 0; k < 8; k++) {

		if ((asci[k] >= 32) && (asci[k] <= 126)) {
			asci3[k] = asci[k];
		}

		else if ((asci[k] < 32) || (asci[k] > 126)) {
			asci3[k] = '.';
		}

	}

	for (int r = 0; r < (n+1); r++) {

		if (write(1, &asci3[r], 1) > 1) {
			return -1;
		}

	}

	for (int w = 0; w < 8; w++) {

		asci3[w] = 0;

	}

	if (write(1, "\n", 1) != 1) {
		return -1;
	}

	return 1;

}

//---------------------------------------------------------------------------

// The Main method is where the input is taken and fed into a character array
// and then another, smaller character array - exactly 8 characters long,
// is created from the initial array, multiple times, and fed into the putout
// method written above.
int main(void) {

	//to check for EOF, you'll see
	char x = 0;
	//to get the number of bytes read gets
	ssize_t n = 0;
	//position is to keep track of memory location
	int position = 0;

	//initial character array
	unsigned char inputted[8];

	for (int a = 0; a < 8; a++) {

		inputted[a] = 0;

	}

	unsigned char seven[7];

	for (int h1 = 0; h1 < 7; h1++) {

		seven[h1] = 0;

	}

	//check for EOF
	while (read(0, &x, 1) != 0) {

		inputted[0] = x;

	//populate the initial character array
		if (n = read(0, seven, 7)) {

			if (n == 0) {

				for (int t = 1; t < 8; t++) {

					inputted[t] = 0;

				}

			}

			else {

				for (int r = 0; r < n; r++) {

					inputted[r+1] = seven[r];

				}

			}

		}

		//sending to the outout function which will print out a line of output
		if (!(putout(inputted, position, n))) {
			return 0;
		}

		for (int s = 0; s < 8; s++) {

			inputted[s] = 0;

		}

		for (int h = 0; h < 7; h++) {

			seven[h] = 0;

		}

		position += 8;

	}


	return 0;

}
