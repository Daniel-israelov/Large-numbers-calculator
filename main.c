#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#include<assert.h>

typedef char* verylong;
verylong input_long(void);
verylong add_verylong(verylong vl1, verylong vl2);
verylong multiply_verylong(verylong vl1, verylong vl2);

void main(void) {
	verylong a, b, c;

	do {
		printf("enter the first long integer: ");
		a = input_long();
	} while (!a);

	do {
		printf("enter the second long integer: ");
		b = input_long();
	} while (!b);

	c = add_verylong(a, b);
	printf("%s + %s = %s\n", a, b, c);
	free(c);

	c = multiply_verylong(a, b);
	printf("%s * %s = %s\n", a, b, c);
	free(c); 
	free(a); 
	free(b);
}

verylong input_long(void) //gets the string from user and checks if its valid
{
	int i = 0, j = 0;
	verylong longnum;
	char a[100];   // 100 is assumption for the max length of the string

	gets_s(a,sizeof(a));

	while (a[j] == '0')
		j++;

	if (j == strlen(a))
	{
		longnum = (verylong)malloc(2 * sizeof(char));
		if (!longnum)
			return NULL;
		else {
			longnum[0] = '0';
			i++;
		}
	}
	else
		longnum = (verylong)malloc((strlen(a + j) + 1) * sizeof(char));

	assert(longnum);
	
	for (; a[j]; i++, j++)
	{
		if (a[i] < '0' || a[i]>'9')
		{
			printf("Invalid character entered.\nTRY AGAIN\n");
			return NULL;
		}
		*(longnum + i) = a[j];
	}
	*(longnum + i) = '\0';
	
	return longnum;
}

verylong add_verylong(verylong vl1, verylong vl2)
{
	int i, lvl1, lvl2, lc, temp;
	verylong c, d;   // auxiliary strings

	lvl1 = strlen(vl1); // length of string 1
	lvl2 = strlen(vl2);	// length of string 2
	lc = lvl1 > lvl2 ? (lvl1 + 1) : (lvl2 + 1); // longest string
	
	c = (verylong)calloc(lc + 1, sizeof(char));
	assert(c);
	
	c[lc] = '\0';
	temp = 0;
	
	for (i = lc - 1; i > abs(lvl1 - lvl2); i--)
	{
		temp += vl1[--lvl1] - '0' + vl2[--lvl2] - '0';
		c[i] = temp % 10 + '0';
		temp /= 10;
	}
	if (lvl1 > 0) {
		for (i = lvl1; i > 0; i--)
		{
			temp += vl1[i - 1] - '0';
			c[i] = temp % 10 + '0';
			temp /= 10;
		}
	}
	else if (lvl2 > 0) {
		for (i = lvl2; i > 0; i--)
		{
			temp += vl2[i - 1] - '0';
			c[i] = temp % 10 + '0';
			temp /= 10;
		}
	}
	if (temp > 0){
		c[0] = temp + '0';
		return c;
	}
	else {
		d = (verylong)malloc(lc);
		if (!d)
			return NULL;
		else {
			strcpy(d, c + 1);
			free(c);
			return d;
		}
	}
}

verylong multiply_verylong(verylong vl1, verylong vl2)
{
	int i, j;
	int len1 = strlen(vl1);
	int len2 = strlen(vl2);
	verylong result = (verylong)calloc(sizeof(char), 100);
	verylong answer = (verylong)calloc(sizeof(char), 100);

	if (!result || !answer)
		return NULL;
	else {
		*(answer + 0) = '0';
		_strrev(vl1);
		_strrev(vl2);

		for (i = 0; i < len1; i++) {
			int k = i;
			int carry = 0;
			int curent = (vl1[i] - '0');

			for (j = 0; j < i; j++)
				result[j] = '0';
			
			for (j = 0; j < len2; j++) {
				int currentMulti = (curent * (vl2[j] - '0')) + carry;
				
				carry = (currentMulti / 10);
				result[k++] = (currentMulti % 10) + '0';
			}
			if (carry != 0)
				result[k++] = carry + '0';

			*(result + k) = '\0';
			_strrev(result);
			answer = add_verylong(answer, result);
		}
		_strrev(vl1);
		_strrev(vl2);

		return answer;
	}
}