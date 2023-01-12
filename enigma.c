#include <stdio.h>
#include <string.h>


	/*
	 * [SECTION] Global defs.
	 */


#define UNUSED(d) (void)d

//Letters' equivalent, swapped later.
int connections[26] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};

// Used if we won't use user's input.
const char overrides[6] = "abcdef";

//Different rotors' defs.
const char rotors[3][26] =
{
	"EKMFLGDQVZNTOWYHXUSPAIBRCJ",
	"AJDKSIRUXBLHWTMCQGZNPYFVOE",
	"BDFHJLCPRTXVZNYEIWGAKMUSQO",
};

//Reflector, we have t[v0], t[v1] = v1, v0.
const char reflector[26] = "EJMZALYXVBWFCRQUONTSPIKHGD";

//Shiftings to the right of the rotors.
int shifts[3] = {0, 0, 0};


	/*
	 * [SECTION] Helper functions.
	 */


/**
 * @brief Print array of ints.
 * @param t int ptr.
 * @param n size of the array.
 */
void print_array(int *t, int n)
{
	int i = 0;
	while (i < n) {
		printf("%d ", t[i]);
		i++;
	}
	printf("\n");
}

/**
 * @brief Access value of the connections array.
 * @param index of the value.
 * @return value at the index.
 */
char pass_through_connections(char v)
{
	return connections[(int)v];
}

/**
 * @brief Get value for a rotor at a given pos.
 * @param rotorID, rotor's index.
 * @param v, Index of the letter.
 * @return Output value for the letter.
 */
char pass_through_rotor(int rotorID, char v)
{
	return rotors[rotorID][(int)v]-'A';
}

/**
 * @brief Returns the opposite of what pass_through_rotor does.
 * @param rotorID, rotor's index.
 * @param v, Index of the letter, from 0 up to 25.
 * @return Output value for the letter.
 */
char pass_through_rotor_opposite(int rotorID, char v)
{
	//We have to make a lookup to know the pos of the letter, and so its value.
	int i = 0;
	while (i < 26) {
		if ((rotors[rotorID][i] - 'A') == v) {
			return i;
		}
		i++;
	}
	return -1;
}

/**
 * @brief
 * @param v
 * @return Output value.
 */
char pass_through_reflector(char v)
{
	return reflector[(int)v]-'A';
}

/**
 * @brief Accessor for a value of shifts.
 * @param shiftID, the shift to retrieve the value from.
 * @return Output, the value for the shift.
 */
int access_shift(int shiftID)
{
	return shifts[shiftID]%26;
}

/**
 * @brief Increments the shift for a rotor.
 * @param shiftID, the shift to change.
 * @param offset, the value to add.
 */
void sum_shift(int shiftID, int offset)
{
	//If the value is less than 0, we have to make it go to a higher value.
	while ((offset + shifts[shiftID]) < 0) {
		offset += 26;
	}

	int upper = 0, tmp = shifts[shiftID] + offset;
	while ((tmp - 26) > 0) {
		upper++;
		tmp -= 26;
	}

	shifts[shiftID] += offset;
	//Then ensure that it is in our range.
	shifts[shiftID] %= 26;

	//Increment the upper one if we've reached 26.
	if (shiftID < 2) {
		sum_shift(shiftID+1, upper);
	}
}

/**
 * @brief Lookup for a value in an array.
 * @param v Value to search.
 * @param t Array.
 * @param s Array's size.
 * @return
 */
int is_in_table(int v, int *t, int s)
{
	int i = 0;
	while (i < s) {
		if (t[i] == v) {
			return 1;
		}
		i++;
	}
	return 0;
}


	/*
	 * [SECTION] Logical functions, main parts.
	 */


/**
 * @brief Encrypt a character!
 * @param v the character.
 * @return the crypted character.
 */
char encrypt(char v)
{
	printf("-----------------\n");
	printf("Numerical value: %d\n", v - 'a');
	v = pass_through_connections(v - 'a');
	printf("Passed through conns: %d\n", v);

	int i = 0;
	while (i < 3) {
		v = pass_through_rotor(i, v);
		printf("Passed through %d, value: %d\n", i+1, v);
		i++;
	}

	v = pass_through_reflector(v);
	printf("Passed through reflector, value: %d\n", v);

	while (i > 0) {
		v = pass_through_rotor_opposite(i-1, v);
		printf("Passed back through %d, value: %d\n", i, v);
		i--;
	}

	v = pass_through_connections(v);
	printf("Passed through conns: %d\n", v);

	printf("Output numerical value: %d\n", v);
	printf("-----------------\n");

	return v + 'a';
}

void f(int d)
{
	int arr[d];
	int i = 0;
	while (i < 100) {
		arr[i] = 4;
		i++;
	}
}

/**
 * @brief Swap values in the connections array.
 * @param override if you want to ask the user for input or use default one.
 */
void connect_cables(int override)
{
	char inputs[6];
	int i = 0;
	if (!override) {
		while (i < 6) {
			char c = 0;
			printf("Lettre %d: ", i);
			scanf("%s", &c);
			while ('a' > c || c > 'z' || is_in_table(c, (int *)&inputs[0], 6)) {
				printf("Valeur incorrect, réentrez-la: :");
				scanf("%s", &inputs[i]);
			}
			inputs[i] = c;
			i++;
		}
	} else {
		while (i < 6) {
			inputs[i] = overrides[i];
			i++;
		}
	}

	i = 0;
	while (i < 6) {
		int v = connections[(int)inputs[i] - 'a'];
		connections[(int)inputs[i] - 'a'] = connections[(int)inputs[i+1] - 'a'];
		connections[(int)inputs[i+1] - 'a'] = v;
		i += 2;
	}
}

int main(int argc, char **argv)
{
	UNUSED(argc);
	UNUSED(argv);

	print_array(shifts, 3);
	int i = 0;
	while (i < 28) {
		sum_shift(0, 1);
		i++;
	}
	print_array(shifts, 3);

	/*
	connect_cables(1);

	char set[4] = "abc";
	printf("*** Input data: %s\n", set);
	unsigned long i = 0;
	while (i < strlen(set)) {
		set[i] = encrypt(set[i]);
		i++;
	}

	printf("*** Crypted output: %s\n", set);

	i = 0;
	while (i < strlen(set)) {
		set[i] = encrypt(set[i]);
		i++;
	}
	printf("*** Uncryted data: %s\n", set);
	*/

	return 0;
}
