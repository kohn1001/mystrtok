#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define DICT_LEN 256

int *create_delim_dict(char *delim)
{
	int *d = (int*)malloc(sizeof(int)*DICT_LEN);
	memset((void*)d, 0, sizeof(int)*DICT_LEN);

	int i;
	for(i=0; i< strlen(delim); i++) {
		d[delim[i]] = 1;
	}
	return d;
}



char *my_strtok(char *str, char *delim)
{
	
	static char *last, *to_free;
	int *deli_dict = create_delim_dict(delim);

	if(!deli_dict) {
	/*this check if we allocate and fail the second time with entering this function */
		if(to_free) {
		    free(to_free);
		}
		return NULL;
	}

	if(!deli_dict) {
		
		return NULL;
	}

	if(str) {
		last = (char*)malloc(strlen(str)+1);
		if(!last) {
			free(deli_dict);
			return NULL;
		}
		to_free = last;
		strcpy(last, str);
	}

	while(deli_dict[*last] && *last != '\0') {
		last++;
	}
	str = last;
	if(*last == '\0') {
		free(deli_dict);
		free(to_free);
		return NULL;
	}
	while (*last != '\0' && !deli_dict[*last]) {
		last++;
	}
	
	*last = '\0';
	last++;

	free(deli_dict);
	return str;
}

int main()
{
	char * str = "- This is, a sample string.";
	char *del = " ,.-";
	char *s = my_strtok(str, del);
	while(s) {
		printf("%s\n", s);
		s = my_strtok(NULL, del);
	}
	return 0;
}
