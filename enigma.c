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

const char reflector[26] = "EJMZALYXVBWFCRQUONTSPIKHGD";


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
int pass_through_connections(int v)
{
	return connections[v];
}

/**
 * @brief Get value for a rotor at a given pos.
 * @param rotorID, rotor's index.
 * @param Index of the letter.
 * @return Output value for the letter.
 */
int pass_through_rotor(int rotorID, int v)
{
	return rotors[rotorID][v]-'A';
}

/**
 * @brief
 * @param v
 * @return Output value.
 */
int pass_through_reflector(int v)
{
	return reflector[v]-'A';
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


char encrypt(int v)
{
	v = pass_through_connections(v - 'a');

	int i = 0;
	while (i < 3) {
		v = pass_through_rotor(i, v);
		i++;
	}

	v = pass_through_reflector(v);

	while (i > 0) {
		v = pass_through_rotor(i, v);
		i--;
	}

	return v + 'a';
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

	connect_cables(1);

	char set[4] = "abc";
	printf("Input data: %s\n", set);
	int i = 0;
	while (i < 3) {
		set[i] = encrypt(set[i]);
		i++;
	}
	printf("Crypted output: %s\n", set);
	i = 0;
	while (i < 3) {
		set[i] = encrypt(set[i]);
		i++;
	}
	printf("Uncryted data: %s\n", set);

	return 0;
}
