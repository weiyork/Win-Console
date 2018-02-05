#ifndef _BASCI_ALGORITHM_
#define _BASCI_ALGORITHM_


class CBasicAlgorithm
{
protected:

public:
	static size_t zw_strlen(const char *str)
	{
		const char *s;
		for(s=str; *s; ++s){}
		return (s-str);
	}

	static char *zw_strcpy(char *to, const char *from)
	{
		if(to == NULL && from ==NULL )
			return NULL;

		char *p = to;

		while((*p++=*from++)!='\0')
			;
		return to;
	}

	//
	static void compute_prefix(const char *pattern, int next[])
	{
		int i;
		int j=-1;
		const int m = strlen(pattern);

		next[0] = j;

		for(i=1; i<m; i++)
		{
			while(j>1 && pattern[j+1]!=pattern[i])
				j=next[j];

			if(pattern[i]==pattern[j+1])
				j++;

			next[i]=j;
		}
	}

	static int kmp(const char*text, const char *pattern)
	{
		int i;
		int j=-1;
		int n = strlen(text);
		int m =strlen(pattern);

		if(m==0)
			return 0;

		int *next = (int *)malloc(sizeof(int)*m);

		compute_prefix(pattern, next);

		for(i=0; i<n; i++)
		{
			while (j > -1 && pattern[j + 1] != text[i])
				j = next[j];
			if (text[i] == pattern[j + 1])
				j++;
			if (j == m - 1)
			{
				free(next);
				return i-j;
			}
		}

		free(next);
		return -1;
	}

	static int *GetArrayPoint(int **ar, int &size)
	{
		*ar = new int[10];
		size = 10;

		int i=10;
		while(--i>=0)
			(*ar)[i] = i;

		return *ar;
	}

};
#endif