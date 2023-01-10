#include <stdio.h>
#include <unistd.h>
#include <string.h>


int connections[26] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};

const char overrides[6] = "abcdef";

const char rotors[3][26] =
{
	"EKMFLGDQVZNTOWYHXUSPAIBRCJ",
	"AJDKSIRUXBLHWTMCQGZNPYFVOE",
	"BDFHJLCPRTXVZNYEIWGAKMUSQO",
};

const char reflector[26] = "EJMZALYXVBWFCRQUONTSPIKHGD";

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

int text_to_value(char d)
{
	return (d - 'A')+'a';
}


int encrypt(int v)
{
	int i = 0;
	int prev = v;
	while (i < 3) {
		prev = text_to_value(rotors[i][prev - 'a']);
		i++;
	}
	prev = reflector[prev - 'a'];
	i--;
	while (i > -1) {
		prev = text_to_value(rotors[i][prev - 'a']);
		i--;
	}
	return prev;
}

void connect_tables(int override)
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
	printf("Connections: ");
	i = 0;
	while (i < 26) {
		printf("%d", (char)connections[i]);
		i++;
	}
	printf("\n");
}

int main()
{
	connect_tables(1);
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
