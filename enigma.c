#include <stdio.h>
#include <string.h>


int connections[26] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};

/**
 * @brief overrides
 */
const char overrides[6] = "abcdef";

const char rotors[3][26] =
{
	"EKMFLGDQVZNTOWYHXUSPAIBRCJ",
	"AJDKSIRUXBLHWTMCQGZNPYFVOE",
	"BDFHJLCPRTXVZNYEIWGAKMUSQO",
};

const char reflector[26] = "EJMZALYXVBWFCRQUONTSPIKHGD";

/**
 * @brief Print array of ints.
 * @param t int ptr.
 * @param n size of the array.
 */
void print_d(int *t, int n)
{
	int i = 0;
	while (i < n) {
		printf("%d ", t[i]);
		i++;
	}
	printf("\n");
}

int pass_through_connections(int v)
{
	return connections[v];
}

int pass_through_rotor(int rotorID, int v)
{
	return rotors[rotorID][v]-'A';
}

int pass_through_reflector(int v)
{
	return reflector[v]-'A';
}

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

int encrypt(int v)
{
	v = pass_through_connections(v);

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

void connect_cables(int override)
{
	print_d(connections, 26);
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
	printf("Connections: ");
	i = 0;
	while (i < 26) {
		printf("%d", (char)connections[i]);
		i++;
	}
	printf("\n");
	print_d(connections, 26);
}

int main()
{
	connect_cables(1);
	//char _d[] = "a";

	/*char set[4] = "abc";
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
	printf("Uncryted data: %s\n", set);*/

	return 0;
}
